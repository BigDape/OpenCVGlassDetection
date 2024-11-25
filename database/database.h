#ifndef DATABASE_H
#define DATABASE_H

#include <QDateTime>
#include <QHash>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlRecord>
#include "HSDatabaseInterface.h"

#define HOSTNAME "127.0.0.1"
#define DATABASENAME "DaTuo"
#define USERNAME "haoshi"
#define PASSWORD "123456"


class DataBase: public HSDatabaseNamespace::HSDatabaseInterface
{
private:
    DataBase();
    DataBase(DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;

public:
    virtual ~DataBase(){}
    static DataBase* GetInstance();

    virtual bool openDataBase() override;    // 打开数据库
    virtual bool insertOneData(const GlassDataBaseInfo2& data) override;   //插入数据库
    virtual bool insertOneData(const GlassSizeInfo2& data) override;       //插入数据库
    virtual bool insertOneData(const GlassDefect2& data) override;         //插入数据库
    virtual bool insertOneData(const GlassSummary& data) override;         //插入数据库

    virtual bool updateData(const GlassDataBaseInfo2& data) override;      //更新数据库
    virtual bool updateData(const GlassSizeInfo2& data) override;      //更新数据库
    virtual bool updateData(const GlassDefect2& data) override;      //更新数据库
    virtual bool updateData(const GlassSummary& data) override;

    virtual bool deleteGlassTableData(int id) override;      //删除数据库
    virtual bool deleteGlassDefectData(int id) override;      //删除数据库
    virtual bool deleteGlassSizeinfoData(int id) override;      //删除数据库
    virtual bool deleteGlassSummary(int id) override;

    virtual bool queryTableData(std::vector<GlassDataBaseInfo2>& datas, QString querySql) override;       //查询数据库
    virtual bool queryTableData(std::vector<GlassSizeInfo2>& datas, QString querySql) override;       //查询数据库
    virtual bool queryTableData(std::vector<GlassDefect2>& datas, QString querySql) override;       //查询数据库
    virtual bool queryTableData(std::vector<GlassSummary>& datas, QString querySql) override;       //查询数据库
    virtual bool closeDataBase() override;   //关闭数据库

    virtual bool getCurrentDefectTableMaxID(int64_t& count) override;
    virtual bool getCurrentGlassTableMaxID(int64_t& count)  override;
    virtual bool getCurrentSizeTableMaxID(int64_t& count) override;
public:
    QSqlDatabase db;
};

#endif // DATABASE_H
