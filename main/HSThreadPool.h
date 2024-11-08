#ifndef HSTHREADPOOL_H
#define HSTHREADPOOL_H

#include <windows.h>
#include <mutex>
#include <queue>
#include <QString>
#include <QDateTime>
#include <mutex>
#include <thread>
#include <list>
#include <memory>
#include <vector>
#include <utility>
#include <queue>
#include <future>
#include <functional>
#include <condition_variable>
#include <unordered_map>
#include <QDebug>
#include <iostream>
#include <sstream>

//线程安全的队列
template <typename T>
class SafeQueue{
public:
    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _condition_variable;
    int _maxcount;
public:
    SafeQueue(int count = INT_MAX):_maxcount(count){
    }
    SafeQueue(SafeQueue& q) {
        if(this != &q) {
            _queue = q._queue;
        }
    }
    SafeQueue& operator=(const SafeQueue& q){
        if(this != &q) {
            _queue = q._queue;
        }
        return *this;
    }
    ~SafeQueue(){}
    bool empty(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return _queue.empty();
    }
    bool empty(std::chrono::milliseconds timeout){//如果为空，则延时等待timeout
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait_for(sbguard,timeout,[this]{
            if(_queue.empty())
                return false;
                    return true;
        });
        return _queue.empty();
    }
    int size(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return _queue.size();
    }
    T& front() {
        std::unique_lock<std::mutex> sbguard(_mutex);
        return (_queue.front());
    }
    T& back(){
        std::unique_lock<std::mutex> sbguard(_mutex);
        return (_queue.back());
    }
    void push(T& t) {//压入元素
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait(sbguard,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void push(T& t,std::chrono::milliseconds timeout) {//压入元素
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait_for(sbguard,timeout,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void push_back(T& t) {//压入元素
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait(sbguard,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void push_back(T& t,std::chrono::milliseconds timeout) {//压入元素
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait_for(sbguard,timeout,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void inqueue(T& t){
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait(sbguard,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    void inqueue(T& t,std::chrono::milliseconds timeout){
        std::unique_lock<std::mutex> sbguard(_mutex);
        _condition_variable.wait_for(sbguard,timeout,[this]{
            if(_queue.size() + 1 > _maxcount)
                return false;
            return true;
        });
        _queue.push(t);
    }
    bool dequeue(T& t){
        std::unique_lock<std::mutex> sbguard(_mutex);
        if(_queue.empty()){
            _condition_variable.notify_all();
            return false;
        }
        t = std::move(_queue.front());
        _queue.pop();
        _condition_variable.notify_one();
        return true;
    }
};

class HSThreadPool{
private:
    //内置线程工作类
    class ThreadWorker{
    private:
        HSThreadPool* _pool;
        int _id;
    public:
        ThreadWorker(HSThreadPool* pool,const int id)
        :_pool(pool),_id(id){
        }
        void operator()(){
            std::function<void()> func;
            bool dequeued;
            while(!_pool->_shutdown){
                {
                    std::unique_lock<std::mutex> lock(_pool->_conditional_mutex);
                    _pool->_conditional_lock.wait(lock,[this]{if(!_pool->_queue.empty() || _pool->_shutdown)
                                                                        return true;
                                                                   return false;});
                    dequeued = _pool->_queue.dequeue(func);
                }
                if(dequeued){
                    try {
                        func();
                    } catch (...) {
                        std::thread::id threadId = std::this_thread::get_id();
                        std::stringstream ss;
                        ss << threadId;
                        QString threadIdStr = QString::fromStdString(ss.str());
                        qDebug()<<threadIdStr<<" has throw a exception";
                    }

                }
            }
        }
    };

    bool _shutdown;                                     //线程池是否关闭
    SafeQueue<std::function<void()>> _queue;            //执行函数安全队列，即任务队列
    std::vector<std::thread> _threads;                  //工作线程队列
    std::mutex _conditional_mutex;                      //线程休眠锁互斥量
    std::condition_variable _conditional_lock;          //线程环境锁，让线程可以处于休眠或者唤醒状态

public:
    explicit HSThreadPool(const int n_threads = std::thread::hardware_concurrency(), const int n_taskmaxcount = INT_MAX)
    :_shutdown(false),
     _threads(std::vector<std::thread>(n_threads)){
        _queue = SafeQueue<std::function<void()>>(n_taskmaxcount);
        for(int i=0;i<(int)_threads.size();++i){//生成指定个数线程
            _threads[i]=std::thread(ThreadWorker(this,i));
        }
    }
    HSThreadPool(const HSThreadPool&)=delete;
    HSThreadPool(HSThreadPool&&)=delete;
    HSThreadPool& operator=(const HSThreadPool&)=delete;
    HSThreadPool& operator=(HSThreadPool&&)=delete;

    void wait(){//等待所有线程执行完成
        _shutdown = true;
        _conditional_lock.notify_all(); //通知 唤醒所有工作线程

        for (int i = 0; i < (int)_threads.size(); ++i) {
            if(_threads[i].joinable()) { //判断线程是否正在等待
                _threads[i].join();  //将线程加入等待队列
            }
        }
    }

    template <typename F, typename...Args>
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        //连接函数和参数定义，特殊函数类型,避免左、右值错误
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        //封装获取任务对象，方便另外一个线程查看结果
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        //利用正则表达式，返回一个函数对象
        std::function<void()> wrapper_func = [task_ptr]() {
            (*task_ptr)();
        };
        // 队列通用安全封包函数，并压入安全队列
        _queue.inqueue(wrapper_func);
        // 唤醒一个等待中的线程
        _conditional_lock.notify_one();
        // 返回先前注册的任务指针
        return task_ptr->get_future();
  }
};

#endif // HSTHREADPOOL_H
