#include "database.h"
#include <QDateTime>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

DataBase::DataBase()
{
    qDebug()<<QSqlDatabase::drivers();          //查看QT支持的驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(HOSTNAME);                   // server name
    db.setDatabaseName(DATABASENAME);           // database name
    db.setUserName(USERNAME);                   // user name for login
    db.setPassword(PASSWORD);                   // passward
}

DataBase* DataBase::GetInstance()
{
    static DataBase instance;
    return &instance;
}

bool DataBase::openDataBase()
{
    if (db.open()) {
        qDebug()<<"已连接到数据库！";
        //创建数据统计
        QString createGlassTable = "CREATE TABLE IF NOT EXISTS glass_table"
                                 "(id INTEGER PRIMARY KEY AUTOINCREMENT, \
                                  time TEXT, OKorNG TEXT, sizeOKorNG TEXT, \
                                  length REAL, width REAL, duijiaoxian1 REAL, \
                                  duijiaoxian2 REAL, defectNumber INTEGER, defectOKorNG TEXT, \
                                  huashanNumber INTEGER, qipaoNumber INTEGER, jieshiNumber INTEGER, \
                                  benbianNumber INTEGER, zanwuNumber INTEGER, liewenNumber INTEGER, qitaNumber INTEGER)";

        //创建glass_defect
        QString createGlassDefectTable="CREATE TABLE IF NOT EXISTS glass_defect"
                                        "(id INTEGER PRIMARY KEY AUTOINCREMENT, \
                                         defectid INTEGER, time TEXT, defectype INTEGER, \
                                         defectlevel INTEGER, X REAL, Y REAL, \
                                         length REAL,width REAL, area REAL, glassid INTEGER, ImagePath TEXT)";

        //创建glass_sizeinfo，孔洞、丝印、门夹
        QString createGlassSizeInfo = "CREATE TABLE IF NOT EXISTS glass_sizeinfo"
                "(id INTEGER PRIMARY KEY AUTOINCREMENT, \
                 sizeno INTEGER, time TEXT, sizeType TEXT, sizeLevel TEXT, \
                 lengthX REAL, widthY REAL, marginsX REAL, marginsY REAL, glassid INTEGER, ImagePath TEXT)";
        //创建汇总信息
        QString createSummaryTable = "CREATE TABLE IF NOT EXISTS glass_summary"
                                     "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "time TEXT, glasstotalcount INTEGER, currentglassstatus TEXT, OKcount INTEGER,"
                                     "NGcount INTEGER, passrate REAL, exceptioncount INTEGER, messagepath TEXT,"
                                     "lastglassID INTEGER)";

        QSqlQuery query(db);
        if(!query.exec(createGlassTable)) {
            qDebug() << "Create table glass_table is fail.";
        } else {
            qDebug() << "成功创建glass_table或者已经存在.";
        }

        QSqlQuery query1(db);
        if(!query1.exec(createGlassDefectTable)) {
            qDebug() << "Create table glass_defect is fail.";
        } else{
            qDebug() << "成功创建glass_defect或者已经存在.";
        }

        QSqlQuery query2(db);
        if(!query2.exec(createGlassSizeInfo)) {
            qDebug() << "Create table glass_sizeinfo is fail.";
        } else {
            qDebug() << "成功创建glass_sizeinfo或者已经存在.";
        }

        QSqlQuery query3(db);
        if(!query3.exec(createSummaryTable)) {
            qDebug() << "Create table glass_summary is fail.";
        } else {
            qDebug() << "成功创建glass_summary或者已经存在.";
        }
    } else {
        //log_singleton::Write_Log(db.lastError().text(), Error);
        qDebug()<<db.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::insertOneData(const GlassDataBaseInfo2& data)
{
    QSqlQuery query(db);
    QString sql = QString("INSERT INTO glass_table"
                          "(id, time, OKorNG, sizeOKorNG, length, width, duijiaoxian1, duijiaoxian2, defectNumber, defectOKorNG, "
                          "huashanNumber, qipaoNumber, jieshiNumber, benbianNumber, zanwuNumber, liewenNumber, qitaNumber)"
                          "VALUES (%1, '%2', '%3', '%4', %5, %6, %7, %8, %9, '%10', %11, %12, %13, %14, %15, %16, %17)")
                          .arg(data.id)
                          .arg(data.time)
                          .arg(data.OKorNG)
                          .arg(data.sizeOKorNG)
                          .arg(data.length)
                          .arg(data.width)
                          .arg(data.duijiaoxian1)
                          .arg(data.duijiaoxian2)
                          .arg(data.defectNumber)
                          .arg(data.defectOKorNG)
                          .arg(data.huashanNumber)
                          .arg(data.qipaoNumber)
                          .arg(data.jieshiNumber)
                          .arg(data.benbianNumber)
                          .arg(data.zanwuNumber)
                          .arg(data.liewenNumber)
                          .arg(data.qitaNumber);
    qDebug()<<sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to insert data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::insertOneData(const GlassSizeInfo2& data)
{
    QSqlQuery query(db);
    QString sqlGlassSizeInfo = QString("INSERT INTO glass_sizeinfo (id, sizeno, time, sizeType, sizeLevel, lengthX, widthY, marginsX, marginsY, glassid, ImagePath)"
                                  "VALUES (%1, %2, '%3', '%4', '%5', %6, %7, %8, %9, %10, '%11')")
                                  .arg(data.id)
                                  .arg(data.sizeno)
                                  .arg(data.time)
                                  .arg(data.sizeType)
                                  .arg(data.sizeLevel)
                                  .arg(data.lengthX)
                                  .arg(data.widthY)
                                  .arg(data.marginsX)
                                  .arg(data.marginsY)
                                  .arg(data.glassid)
                                  .arg(data.imagePath);
    qDebug()<<sqlGlassSizeInfo;
    if (!query.exec(sqlGlassSizeInfo)) {
        qDebug() << "Failed to insert data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::insertOneData(const GlassDefect2& data)
{
    QSqlQuery query(db);
    QString sqlGlassDefect=QString("INSERT INTO glass_defect(id, defectid, time, defectype, defectlevel, X, Y, length, width,area, glassid, ImagePath)"
                                "VALUES (%1, %2, '%3', '%4', '%5', %6, %7, %8, %9, %10, %11, '%12')")
                .arg(data.id)
                .arg(data.defectId)
                .arg(data.time)
                .arg(data.defectType)
                .arg(data.defectLevel)
                .arg(data.x)
                .arg(data.y)
                .arg(data.length)
                .arg(data.width)
                .arg(data.area)
                .arg(data.glassid)
                .arg(data.imagePath);
   qDebug()<<sqlGlassDefect;
   if (!query.exec(sqlGlassDefect)) {
       qDebug() << "Failed to insert data: " << query.lastError().text();
       return false;
   }
   return true;
}

bool DataBase::insertOneData(const GlassSummary& data)
{
    QSqlQuery query(db);
    QString sqlGlassSummary=QString("INSERT INTO glass_summary(id,time,glasstotalcount,currentglassstatus,OKcount,NGcount,passrate,exceptioncount, messagepath,lastglassID)"
                                     " VALUES (%1, '%2', %3, '%4', %5, %6, %7, %8, '%9', %10)")
                                 .arg(data.id)
                                 .arg(data.time)
                                 .arg(data.glasstotalcount)
                                 .arg(data.currentglassstatus)
                                 .arg(data.OKcount)
                                 .arg(data.NGcount)
                                 .arg(data.passrate)
                                 .arg(data.exceptioncount)
                                 .arg(data.messagePath)
                                 .arg(data.lastglassID);
    qDebug()<<sqlGlassSummary;
    if (!query.exec(sqlGlassSummary)) {
        qDebug() << "Failed to insert data: " << query.lastError().text();
        return false;
    }
    return true;
}


bool DataBase::updateData(const GlassDataBaseInfo2& data)
{
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_table SET time='%1', OKorNG='%2', sizeOKorNG='%3', length=%4, width=%5, duijiaoxian1=%6, duijiaoxian2=%7, defectNumber=%8, defectOKorNG='%9',"
                          "huashanNumber=%10, qipaoNumber=%11, jieshiNumber=%12, benbianNumber=%13, zanwuNumber=%14, liewenNumber=%15, qitaNumber=%16 WHERE id=%17")
            .arg(data.time)
            .arg(data.OKorNG)
            .arg(data.sizeOKorNG)
            .arg(data.length)
            .arg(data.width)
            .arg(data.duijiaoxian1)
            .arg(data.duijiaoxian2)
            .arg(data.defectNumber)
            .arg(data.defectOKorNG)
            .arg(data.huashanNumber)
            .arg(data.qipaoNumber)
            .arg(data.jieshiNumber)
            .arg(data.benbianNumber)
            .arg(data.zanwuNumber)
            .arg(data.liewenNumber)
            .arg(data.qitaNumber)
            .arg(data.id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::updateData(const GlassSizeInfo2& data)
{
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_sizeinfo SET sizeno=%1, time='%2', sizeType='%3', sizeLevel='%4', lengthX=%5, widthY=%6, "
                          "marginsX=%7, marginsY=%8, glassid=%9, ImagePath='%10'  WHERE id=%11")
            .arg(data.sizeno)
            .arg(data.time)
            .arg(data.sizeType)
            .arg(data.sizeLevel)
            .arg(data.lengthX)
            .arg(data.widthY)
            .arg(data.marginsX)
            .arg(data.marginsY)
            .arg(data.glassid)
            .arg(data.imagePath)
            .arg(data.id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::updateData(const GlassDefect2& data)
{
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_defect SET defectid=%1, time='%2', defectype='%3', defectlevel='%4', X=%5, Y=%6, length=%7, width=%8, area=%9,"
                          "glassid=%10, ImagePath='%11' WHERE id=%12")
            .arg(data.defectId)
            .arg(data.time)
            .arg(data.defectType)
            .arg(data.defectLevel)
            .arg(data.x)
            .arg(data.y)
            .arg(data.length)
            .arg(data.width)
            .arg(data.area)
            .arg(data.glassid)
            .arg(data.imagePath)
            .arg(data.id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::updateData(const GlassSummary& data)
{
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_summary SET id=%1, time='%2', glasstotalcount=%3, currentglassstatus='%4', OKcount=%5, NGcount=%6, passrate=%7, "
                  "exceptioncount=%8, messagepath='%9', lastglassID=%10")
                      .arg(data.id)
                      .arg(data.time)
                      .arg(data.glasstotalcount)
                      .arg(data.currentglassstatus)
                      .arg(data.OKcount)
                      .arg(data.NGcount)
                      .arg(data.passrate)
                      .arg(data.exceptioncount)
                      .arg(data.messagePath)
                      .arg(data.lastglassID);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::deleteGlassTableData(int id)
{
    QSqlQuery query(db);
    QString sql = QString("DELETE FROM glass_table WHERE id=%1").arg(id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
       qDebug() << "Failed to delete data: " << query.lastError().text();
       return false;
    }
    return true;
}

bool DataBase::deleteGlassDefectData(int id)
{
    QSqlQuery query(db);
    QString sql = QString("DELETE FROM glass_defect WHERE id=%1").arg(id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
       qDebug() << "Failed to delete data: " << query.lastError().text();
       return false;
    }
    return true;
}

bool DataBase::deleteGlassSizeinfoData(int id)
{
    QSqlQuery query(db);
    QString sql = QString("DELETE FROM glass_sizeinfo WHERE id=%1").arg(id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
       qDebug() << "Failed to delete data: " << query.lastError().text();
       return false;
    }
    return true;
}

bool DataBase::deleteGlassSummary(int id)
{
    QSqlQuery query(db);
    QString sql = QString("DELETE FROM glass_summary WHERE id=%1").arg(id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to delete data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::queryTableData(std::vector<GlassDataBaseInfo2>& datas,QString querySql)
{
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    while (query.next()) {
        GlassDataBaseInfo2 data;
        data.id= query.value(0).toInt();
        data.time = query.value(1).toString();
        data.OKorNG = query.value(2).toString();
        data.sizeOKorNG = query.value(3).toString();
        data.length = query.value(4).toDouble();
        data.width = query.value(5).toDouble();
        data.duijiaoxian1 = query.value(6).toDouble();
        data.duijiaoxian2 = query.value(7).toDouble();
        data.defectNumber = query.value(8).toInt();
        data.defectOKorNG = query.value(9).toString();
        data.huashanNumber = query.value(10).toInt();
        data.qipaoNumber = query.value(11).toInt();
        data.jieshiNumber = query.value(12).toInt();
        data.benbianNumber = query.value(13).toInt();
        data.zanwuNumber = query.value(14).toInt();
        data.liewenNumber = query.value(15).toInt();
        data.qitaNumber = query.value(16).toInt();
        datas.push_back(data);
    }
    return true;
}

bool DataBase::queryTableData(std::vector<GlassSizeInfo2>& datas, QString querySql)
{
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    while (query.next()) {
        GlassSizeInfo2 data;
        data.id= query.value(0).toInt();
        data.sizeno = query.value(1).toInt();
        data.time = query.value(2).toString();
        data.sizeType = query.value(3).toString();
        data.sizeLevel = query.value(4).toString();
        data.lengthX = query.value(5).toDouble();
        data.widthY = query.value(6).toDouble();
        data.marginsX = query.value(7).toDouble();
        data.marginsY = query.value(8).toDouble();
        data.glassid = query.value(9).toInt();
        data.imagePath = query.value(10).toString();
        datas.push_back(data);
    }
    return true;
}

bool DataBase::queryTableData(std::vector<GlassDefect2>& datas, QString querySql)
{
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    while (query.next()) {
        GlassDefect2 data;
        data.id= query.value(0).toInt();
        data.defectId = query.value(1).toInt();
        data.time = query.value(2).toString();
        data.defectType = query.value(3).toString();
        data.defectLevel = query.value(4).toString();
        data.x = query.value(5).toDouble();
        data.y = query.value(6).toDouble();
        data.length = query.value(7).toDouble();
        data.width = query.value(8).toDouble();
        data.area = query.value(9).toDouble();
        data.glassid = query.value(10).toInt();
        data.imagePath = query.value(11).toString();
        datas.push_back(data);
    }
    return true;
}

bool DataBase::queryTableData(std::vector<GlassSummary>& datas, QString querySql)
{
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    while (query.next()) {
        GlassSummary data;
        data.id= query.value(0).toInt();
        data.time = query.value(1).toString();
        data.glasstotalcount = query.value(3).toInt();
        data.currentglassstatus = query.value(4).toString();
        data.OKcount = query.value(5).toInt();
        data.NGcount = query.value(6).toInt();
        data.passrate= query.value(7).toDouble();
        data.exceptioncount = query.value(8).toInt();
        data.messagePath = query.value(9).toString();
        data.lastglassID = query.value(10).toInt();
        datas.push_back(data);
    }
    return true;
}

bool DataBase::getCurrentDefectTableMaxID(int64_t& count)
{
    QString querySql = "SELECT MAX(id) FROM glass_defect;";
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    if (query.next()) {
        count = query.value(0).toInt();
        qDebug() << "glass_table max(id) =" << count;
        return true;
    } else {
        qDebug() << "查询失败";
    }
    return false;
}

bool DataBase::getCurrentGlassTableMaxID(int64_t& count)
{
    QString querySql = "SELECT MAX(id) FROM glass_table;";
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    if (query.next()) {
        count = query.value(0).toInt();
        qDebug() << "glass_table max(id) =" << count;
        return true;
    } else {
        qDebug() << "查询失败";
    }
    return false;
}


bool DataBase::closeDataBase()
{
    if(db.isOpen()) {
        db.close();
    }
    return true;
}
