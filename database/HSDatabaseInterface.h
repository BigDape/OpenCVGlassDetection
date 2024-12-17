#ifndef HSDATABASEINTERFACE_H
#define HSDATABASEINTERFACE_H

#include <QString>
#include "HSTool.h"

namespace HSDatabaseNamespace{
    class HSDatabaseInterface
    {
    public:
        virtual ~HSDatabaseInterface(){}

        virtual bool openDataBase() = 0 ;
        virtual bool insertOneData(const GlassDataBaseInfo2& data) = 0;
        virtual bool insertOneData(const GlassSizeInfo2& data) = 0;       //插入数据库
        virtual bool insertOneData(const GlassDefect2& data) = 0;         //插入数据库
        virtual bool insertOneData(const GlassSummary& data) = 0;         //插入数据库

        virtual bool batchInsertData(std::vector<GlassDefect2>& datas) = 0; //批量插入缺陷数据
        virtual bool batchInsertData(std::vector<GlassSizeInfo2>& datas) = 0; //批量插入数据

        virtual bool updateData(const GlassDataBaseInfo2& data) = 0;      //更新数据库
        virtual bool updateData(const GlassSizeInfo2& data) = 0;      //更新数据库
        virtual bool updateData(const GlassDefect2& data) = 0;      //更新数据库
        virtual bool updateData(const GlassSummary& data) = 0;

        virtual bool deleteGlassTableData(int id) = 0;      //删除数据库
        virtual bool deleteGlassDefectData(int id) = 0;      //删除数据库
        virtual bool deleteGlassSizeinfoData(int id) = 0;      //删除数据库
        virtual bool deleteGlassSummary(int id) = 0;

        virtual bool queryTableData(std::vector<GlassDataBaseInfo2>& datas, QString querySql) = 0;       //查询数据库
        virtual bool queryTableData(std::vector<GlassSizeInfo2>& datas, QString querySql) = 0;       //查询数据库
        virtual bool queryTableData(std::vector<GlassDefect2>& datas, QString querySql) = 0;       //查询数据库
        virtual bool queryTableData(std::vector<GlassSummary>& datas, QString querySql) = 0;       //查询数据库
        virtual bool closeDataBase() = 0;   //关闭数据库
        virtual int64_t getCurrentDefectTableMaxID() = 0;
        virtual int64_t getCurrentGlassTableMaxID() = 0;
        virtual int64_t getCurrentSizeTableMaxID() = 0;
    };
}

    // 用于创建对象的函数（DLL 导出函数）
extern "C" __declspec(dllexport) HSDatabaseNamespace::HSDatabaseInterface* createDatabaseObject();



#endif // HSDATABASEINTERFACE_H
