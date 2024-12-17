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
    std::lock_guard<std::mutex> lock(mutex);
    if (db.open()) {
        qDebug()<<"已连接到数据库！";
        //
        // 创建数据统计表格
        //
        QString createGlassTable = "CREATE TABLE IF NOT EXISTS glass_table"
                                 "(id INTEGER PRIMARY KEY AUTOINCREMENT, \
                                  time TEXT, OKorNG TEXT, sizeOKorNG TEXT, length REAL, width REAL,\
                                  defectOKorNG TEXT, defectNumber INTEGER, huahenNumber INTEGER, yiwuNumber INTEGER, AyiwuNumber INTEGER, \
                                  ByiwuNumber INTEGER,qipaoNumber INTEGER, sqipaoNumber INTEGER, madianNumber INTEGER, A2madianNumber INTEGER, \
                                  A3madianNumber INTEGER, A10mmmadianNumber INTEGER, B2madianNumber INTEGER, B3madianNumber INTEGER, B10mmmadianNumber INTEGER,\
                                  siyin30mm2madianNumber INTEGER, siyin30mm3madianNumber INTEGER, shuiyinNumber INTEGER, AshuiyinNumber INTEGER, B5mmshuiyinNumber INTEGER,\
                                  youmobuliangNumber INTEGER, A3youmobuliangNumber INTEGER, A2youmobuliangNumber INTEGER, A10mm2youmobuliangNumber INTEGER, A10mm3youmobuliangNumber INTEGER,\
                                  B3youmobuliangNumber INTEGER, B2youmobuliangNumber INTEGER, B10mm2youmobuliangNumber INTEGER, B10mm3youmobuliangNumber INTEGER, siyin30mm3youmobuliangNumber INTEGER,\
                                  siyin30mm2youmobuliangNumber INTEGER, juchibianNumber INTEGER, juchibianAllLength INTEGER, siyinquexianNumber INTEGER, guahuaNumber INTEGER,\
                                  AguahuaNumber INTEGER, liewenNumber INTEGER, benbianjiaoNumber INTEGER, historyImage TEXT)";
        QSqlQuery query(db);
        if(!query.exec(createGlassTable)) {
            qDebug() << "Create table glass_table is fail.";
        } else {
            qDebug() << "成功创建glass_table或者已经存在.";
        }

        //
        // 创建glass_defect
        //
        QString createGlassDefectTable="CREATE TABLE IF NOT EXISTS glass_defect"
                                        "(id INTEGER PRIMARY KEY AUTOINCREMENT, \
                                         defectid INTEGER, time TEXT, defectype INTEGER, defectLevel INTEGER, pixX INTEGER,\
                                         pixY INTEGER, pixLength INTEGER, pixWidth INTEGER, pixArea INTEGER, X REAL,\
                                         Y REAL, length REAL, width REAL, area REAL, glassid INTEGER,\
                                         imagePath0 TEXT, imagePath1 TEXT, imagePath2 TEXT, typeID INTEGER)";
        QSqlQuery query1(db);
        if(!query1.exec(createGlassDefectTable)) {
            qDebug() << "Create table glass_defect is fail.";
        } else{
            qDebug() << "成功创建glass_defect或者已经存在.";
        }

        //
        // 创建glass_sizeinfo
        //
        QString createGlassSizeInfo = "CREATE TABLE IF NOT EXISTS glass_sizeinfo"
                "(id INTEGER PRIMARY KEY AUTOINCREMENT, \
                 sizeID INTEGER, time TEXT, sizeType TEXT, sizeLevel TEXT, lengthX REAL,\
                 widthY REAL, marginsX REAL, marginsY REAL, Pixlength INTEGER, PixWidth INTEGER,\
                 PixMarginsX INTEGER, PixMarginsY INTEGER, glassid INTEGER, ImagePath0 TEXT, ImagePath1 TEXT, ImagePath2 TEXT)";
        QSqlQuery query2(db);
        if(!query2.exec(createGlassSizeInfo)) {
            qDebug() << "Create table glass_sizeinfo is fail.";
        } else {
            qDebug() << "成功创建glass_sizeinfo或者已经存在.";
        }

        //
        // 创建汇总信息
        //
        QString createSummaryTable = "CREATE TABLE IF NOT EXISTS glass_summary"
                                     "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                     "time TEXT, glasstotalcount INTEGER, currentglassstatus TEXT, OKcount INTEGER,"
                                     "NGcount INTEGER, passrate REAL, exceptioncount INTEGER, messagepath TEXT,"
                                     "lastglassID INTEGER)";
        QSqlQuery query3(db);
        if(!query3.exec(createSummaryTable)) {
            qDebug() << "Create table glass_summary is fail.";
        } else {
            qDebug() << "成功创建glass_summary或者已经存在.";
        }
    } else {
        qDebug()<<db.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::insertOneData(const GlassDataBaseInfo2& data)
{
    std::lock_guard<std::mutex> lock(mutex);
    QSqlQuery query(db);
    QString sql = QString("INSERT INTO glass_table"
                          "("
                          "id, time, OKorNG, sizeOKorNG, length, width, "
                          "defectOKorNG, defectNumber, huahenNumber, yiwuNumber, AyiwuNumber, "
                          "ByiwuNumber, qipaoNumber, sqipaoNumber, madianNumber, A2madianNumber, "
                          "A3madianNumber, A10mmmadianNumber, B2madianNumber, B3madianNumber, B10mmmadianNumber,"
                          "siyin30mm2madianNumber, siyin30mm3madianNumber, shuiyinNumber, AshuiyinNumber, B5mmshuiyinNumber, "
                          "youmobuliangNumber, A3youmobuliangNumber, A2youmobuliangNumber, A10mm2youmobuliangNumber, A10mm3youmobuliangNumber,"
                          "B3youmobuliangNumber, B2youmobuliangNumber, B10mm2youmobuliangNumber, B10mm3youmobuliangNumber, siyin30mm3youmobuliangNumber,"
                          "siyin30mm2youmobuliangNumber, juchibianNumber, juchibianAllLength, siyinquexianNumber, guahuaNumber,"
                          "AguahuaNumber, liewenNumber, benbianjiaoNumber, historyImage"
                          ")"
                          "VALUES ("
                          "%1, '%2', '%3', '%4', %5, %6, "
                          "'%7', %8, %9, %10, %11, "
                          "%12, %13, %14, %15, %16"
                          "%17, %18, %19, %20, %21"
                          "%22, %23, %24, %25, %26"
                          "%27, %28, %29, %30, %31,"
                          "%32, %33, %34, %35, %36,"
                          "%37, %38, %39, %40, %41,"
                          "%42, %43, %44, '%45'"
                          ")")
                          .arg(data.id).arg(data.time).arg(data.OKorNG).arg(data.sizeOKorNG).arg(data.length).arg(data.width)
                          .arg(data.defectOKorNG).arg(data.defectNumber).arg(data.huahenNumber).arg(data.yiwuNumber).arg(data.AyiwuNumber)
                          .arg(data.ByiwuNumber).arg(data.qipaoNumber).arg(data.sqipaoNumber).arg(data.madianNumber).arg(data.A2madianNumber)
                          .arg(data.A3madianNumber).arg(data.A10mmmadianNumber).arg(data.B2madianNumber).arg(data.B3madianNumber).arg(data.B10mmmadianNumber)
                          .arg(data.siyin30mm2madianNumber).arg(data.siyin30mm3madianNumber).arg(data.shuiyinNumber).arg(data.AshuiyinNumber).arg(data.B5mmshuiyinNumber)
                          .arg(data.youmobuliangNumber).arg(data.A3youmobuliangNumber).arg(data.A2youmobuliangNumber).arg(data.A10mm2youmobuliangNumber).arg(data.A10mm3youmobuliangNumber)
                          .arg(data.B3youmobuliangNumber).arg(data.B2youmobuliangNumber).arg(data.B10mm2youmobuliangNumber).arg(data.B10mm3youmobuliangNumber).arg(data.siyin30mm3youmobuliangNumber)
                          .arg(data.siyin30mm2youmobuliangNumber).arg(data.juchibianNumber).arg(data.juchibianAllLength).arg(data.siyinquexianNumber).arg(data.guahuaNumber)
                          .arg(data.AguahuaNumber).arg(data.liewenNumber).arg(data.benbianjiaoNumber).arg(data.historyPath);
    qDebug()<<sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to insert data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::insertOneData(const GlassSizeInfo2& data)
{
    std::lock_guard<std::mutex> lock(mutex);
    QSqlQuery query(db);
    QString sqlGlassSizeInfo = QString("INSERT INTO glass_sizeinfo "
                                       "("
                                       "id, sizeID, time, sizeType, sizeLevel, lengthX,"
                                        "widthY, marginsX, marginsY, Pixlength, PixWidth,"
                                       "PixMarginsX, PixMarginsY, glassid, ImagePath0, ImagePath1, ImagePath2"
                                       ")"
                                        "VALUES ("
                                       "%1, %2, '%3', '%4', '%5', %6,"
                                       " %7, %8, %9, %10, %11, "
                                       "%12, %13, %14, '%15', '%16', '%17')")
                                  .arg(data.id).arg(data.sizeID).arg(data.time).arg(data.sizeType).arg(data.sizeLevel).arg(data.lengthX)
                                  .arg(data.widthY).arg(data.marginsX).arg(data.marginsY).arg(data.Pixlength).arg(data.PixWidth)
                                  .arg(data.PixMarginsX).arg(data.PixMarginsY).arg(data.glassid).arg(data.imagePath0).arg(data.imagePath1).arg(data.imagePath2);
    qDebug()<<sqlGlassSizeInfo;
    if (!query.exec(sqlGlassSizeInfo)) {
        qDebug() << "Failed to insert data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::insertOneData(const GlassDefect2& data)
{
    std::lock_guard<std::mutex> lock(mutex);
    QSqlQuery query(db);
    QString sqlGlassDefect=QString("INSERT INTO glass_defect"
                                     "(id, defectid, time, defectype, defectLevel, pixX,"
                                     "pixY, pixLength, pixWidth, pixArea, X,"
                                     "Y, length, width, area, glassid,"
                                     "imagePath0, imagePath1, imagePath2, typeID)"
                                    "VALUES (%1, %2, '%3', '%4', '%5', %6, "
                                     "%7, %8, %9, %10, %11, "
                                     "%12, %13, %14, %15, %16,"
                                     "'%17', '%18', '%19', %20)")
                .arg(data.id).arg(data.defectId).arg(data.time).arg(data.defectType).arg(data.defectLevel).arg(data.pixX)
                .arg(data.pixY).arg(data.pixLength).arg(data.pixWidth).arg(data.pixArea).arg(data.x)
                .arg(data.y).arg(data.length).arg(data.width).arg(data.area).arg(data.glassid)
                .arg(data.imagePath0).arg(data.imagePath1).arg(data.imagePath2).arg(data.typeID);
   //qDebug()<<sqlGlassDefect;
   if (!query.exec(sqlGlassDefect)) {
       qDebug() << "Failed to insert data: " << query.lastError().text();
       return false;
   }
   return true;
}

bool DataBase::insertOneData(const GlassSummary& data)
{
    std::lock_guard<std::mutex> lock(mutex);
    QSqlQuery query(db);
    QString sqlGlassSummary=QString("INSERT INTO glass_summary"
                                      "(id ,time, glasstotalcount, currentglassstatus, OKcount,"
                                      "NGcount, passrate, exceptioncount, messagepath,"
                                      "lastglassID)"
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

bool DataBase::batchInsertData(std::vector<GlassDefect2>& datas)
{
    std::lock_guard<std::mutex> lock(mutex);
    // 开启事务
    QSqlQuery query;
    if (!query.exec("BEGIN;")) {
        qDebug() << "开启事务失败：" << query.lastError().text();
        return false;
    }
    // 循环插入数据
    for (int i = 0; i < (int)datas.size(); i++) {
        QString sqlGlassDefect=QString("INSERT INTO glass_defect"
                                         "(id, defectid, time, defectype, defectLevel, pixX,"
                                         "pixY, pixLength, pixWidth, pixArea, X,"
                                         "Y, length, width, area, glassid,"
                                         "imagePath0, imagePath1, imagePath2, typeID)"
                                         "VALUES (%1, %2, '%3', '%4', '%5', %6, "
                                         "%7, %8, %9, %10, %11, "
                                         "%12, %13, %14, %15, %16,"
                                         "'%17', '%18', '%19', %20)")
                                     .arg(datas[i].id).arg(datas[i].defectId).arg(datas[i].time).arg(datas[i].defectType).arg(datas[i].defectLevel).arg(datas[i].pixX)
                                     .arg(datas[i].pixY).arg(datas[i].pixLength).arg(datas[i].pixWidth).arg(datas[i].pixArea).arg(datas[i].x)
                                     .arg(datas[i].y).arg(datas[i].length).arg(datas[i].width).arg(datas[i].area).arg(datas[i].glassid)
                                     .arg(datas[i].imagePath0).arg(datas[i].imagePath1).arg(datas[i].imagePath2).arg(datas[i].typeID);

        if (!query.exec(sqlGlassDefect)) {
            qDebug() << "插入数据失败（第 " << i + 1 << " 次）：" << query.lastError().text();
            continue;
        }
    }
    // 提交事务
    if (!query.exec("COMMIT;")) {
        qDebug() << "提交事务失败：" << query.lastError().text();
        return false;
    } else {
        qDebug()<<"提交事务成功。";
    }
    return true;
}

bool DataBase::batchInsertData(std::vector<GlassSizeInfo2>& datas)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (datas.size() == 0)
        return true;
    // 开启事务
    QSqlQuery query;
    if (!query.exec("BEGIN;")) {
        qDebug() << "开启事务失败：" << query.lastError().text();
        return false;
    }

    // 循环插入数据
    for (int i = 0; i < (int)datas.size(); i++) {
        QString sqlGlassSizeInfo = QString("INSERT INTO glass_sizeinfo "
                                           "("
                                           "id, sizeID, time, sizeType, sizeLevel, lengthX,"
                                           "widthY, marginsX, marginsY, Pixlength, PixWidth,"
                                           "PixMarginsX, PixMarginsY, glassid, ImagePath0, ImagePath1, ImagePath2"
                                           ")"
                                           "VALUES ("
                                           "%1, %2, '%3', '%4', '%5', %6,"
                                           " %7, %8, %9, %10, %11, "
                                           "%12, %13, %14, '%15', '%16', '%17')")
                                       .arg(datas[i].id).arg(datas[i].sizeID).arg(datas[i].time).arg(datas[i].sizeType).arg(datas[i].sizeLevel).arg(datas[i].lengthX)
                                       .arg(datas[i].widthY).arg(datas[i].marginsX).arg(datas[i].marginsY).arg(datas[i].Pixlength).arg(datas[i].PixWidth)
                                       .arg(datas[i].PixMarginsX).arg(datas[i].PixMarginsY).arg(datas[i].glassid).arg(datas[i].imagePath0).arg(datas[i].imagePath1).arg(datas[i].imagePath2);
        if (!query.exec(sqlGlassSizeInfo)) {
            qDebug() << "插入数据失败（第 " << i + 1 << " 次）：" << query.lastError().text();
            continue;
        }
    }

    // 提交事务
    if (!query.exec("COMMIT;")) {
        qDebug() << "提交事务失败：" << query.lastError().text();
        return false;
    } else {
        qDebug()<<"提交事务成功";
    }
    return true;
}

bool DataBase::updateData(const GlassDataBaseInfo2& data)
{
    std::lock_guard<std::mutex> lock(mutex);
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_table SET time='%1', OKorNG='%2', sizeOKorNG='%3', length=%4, width=%5,"
                          "defectOKorNG='%6', defectNumber=%7, huahenNumber=%8, yiwuNumber=%9, AyiwuNumber=%10, "
                          "ByiwuNumber=%11, qipaoNumber=%12, sqipaoNumber=%13, madianNumber=%14, A2madianNumber=%15,"
                          "A3madianNumber=%16, A10mmmadianNumber=%17, B2madianNumber=%18, B3madianNumber=%19, B10mmmadianNumber=%20,"
                          "siyin30mm2madianNumber=%21, siyin30mm3madianNumber=%22, shuiyinNumber=%23, AshuiyinNumber=%24, B5mmshuiyinNumber=%25, "
                          "youmobuliangNumber=%26, A3youmobuliangNumber=%27, A2youmobuliangNumber=%28, A10mm2youmobuliangNumber=%29, A10mm3youmobuliangNumber=%30,"
                          "B3youmobuliangNumber=%31, B2youmobuliangNumber=%32, B10mm2youmobuliangNumber=%33, B10mm3youmobuliangNumber=%34, siyin30mm3youmobuliangNumber=%35,"
                          "siyin30mm2youmobuliangNumber=%36, juchibianNumber=%37, juchibianAllLength=%38, siyinquexianNumber=%39, guahuaNumber=%40,"
                          "AguahuaNumber=%41, liewenNumber=%42, benbianjiaoNumber=%43, historyImage='%44' WHERE id=%45")
                      .arg(data.time).arg(data.OKorNG).arg(data.sizeOKorNG).arg(data.length).arg(data.width)
                      .arg(data.defectOKorNG).arg(data.defectNumber).arg(data.huahenNumber).arg(data.yiwuNumber).arg(data.AyiwuNumber)
                      .arg(data.ByiwuNumber).arg(data.qipaoNumber).arg(data.sqipaoNumber).arg(data.madianNumber).arg(data.A2madianNumber)
                      .arg(data.A3madianNumber).arg(data.A10mmmadianNumber).arg(data.B2madianNumber).arg(data.B3madianNumber).arg(data.B10mmmadianNumber)
                      .arg(data.siyin30mm2madianNumber).arg(data.siyin30mm3madianNumber).arg(data.shuiyinNumber).arg(data.AshuiyinNumber).arg(data.B5mmshuiyinNumber)
                      .arg(data.youmobuliangNumber).arg(data.A3youmobuliangNumber).arg(data.A2youmobuliangNumber).arg(data.A10mm2youmobuliangNumber).arg(data.A10mm3youmobuliangNumber)
                      .arg(data.B3youmobuliangNumber).arg(data.B2youmobuliangNumber).arg(data.B10mm2youmobuliangNumber).arg(data.B10mm3youmobuliangNumber).arg(data.siyin30mm3youmobuliangNumber)
                      .arg(data.siyin30mm2youmobuliangNumber).arg(data.juchibianNumber).arg(data.juchibianAllLength).arg(data.siyinquexianNumber).arg(data.guahuaNumber).arg(data.id)
                      .arg(data.AguahuaNumber).arg(data.liewenNumber).arg(data.benbianjiaoNumber).arg(data.historyPath);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::updateData(const GlassSizeInfo2& data)
{
    std::lock_guard<std::mutex> lock(mutex);
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_sizeinfo SET sizeID=%1, time='%2', sizeType='%3', sizeLevel='%4', lengthX=%5,"
                          "widthY=%6, marginsX=%7, marginsY=%8, Pixlength=%9, PixWidth=%10,"
                          "PixMarginsX=%11, PixMarginsY=%12, glassid=%13, ImagePath0='%14', ImagePath1='%15', ImagePath2='%16'  WHERE id=%17")
                      .arg(data.sizeID).arg(data.time).arg(data.sizeType).arg(data.sizeLevel).arg(data.lengthX)
                      .arg(data.widthY).arg(data.marginsX).arg(data.marginsY).arg(data.Pixlength).arg(data.PixWidth)
                      .arg(data.PixMarginsX).arg(data.PixMarginsY).arg(data.glassid).arg(data.imagePath0).arg(data.imagePath1).arg(data.imagePath2).arg(data.id);

    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::updateData(const GlassDefect2& data)
{
    std::lock_guard<std::mutex> lock(mutex);
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_defect SET defectid=%1, time='%2', defectype='%3', defectLevel='%4', pixX=%5,"
                          "pixY=%6, pixLength=%7, pixWidth=%8, pixArea=%9, X=%10,"
                          "Y=%11, length=%12, width=%13, area=%14, glassid=%15,"
                          "imagePath0='%16', imagePath1='%17', imagePath2='%18', typeID=%19 WHERE id=%20")
                      .arg(data.defectId).arg(data.time).arg(data.defectType).arg(data.defectLevel).arg(data.pixX)
                      .arg(data.pixY).arg(data.pixLength).arg(data.pixWidth).arg(data.pixArea).arg(data.x)
                      .arg(data.y).arg(data.length).arg(data.width).arg(data.area).arg(data.glassid)
                      .arg(data.imagePath0).arg(data.imagePath1).arg(data.imagePath2).arg(data.typeID).arg(data.id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::updateData(const GlassSummary& data)
{
    std::lock_guard<std::mutex> lock(mutex);
    QSqlQuery query(db);
    QString sql = QString("UPDATE glass_summary SET time='%1', glasstotalcount='%2', currentglassstatus='%3', OKcount=%4, NGcount=%5,"
                          "passrate=%6, exceptioncount=%7, messagepath='%8', lastglassID=%9 WHERE id=%10")
                      .arg(data.time)
                      .arg(data.glasstotalcount)
                      .arg(data.currentglassstatus)
                      .arg(data.OKcount)
                      .arg(data.NGcount)
                      .arg(data.passrate)
                      .arg(data.exceptioncount)
                      .arg(data.messagePath)
                      .arg(data.lastglassID)
                      .arg(data.id);
    qDebug()<< sql;
    if (!query.exec(sql)) {
        qDebug() << "Failed to update data: " << query.lastError().text();
        return false;
    }
    return true;
}

bool DataBase::deleteGlassTableData(int id)
{
    std::lock_guard<std::mutex> lock(mutex);
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
    std::lock_guard<std::mutex> lock(mutex);
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
    std::lock_guard<std::mutex> lock(mutex);
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
    std::lock_guard<std::mutex> lock(mutex);
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
    std::lock_guard<std::mutex> lock(mutex);
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
        data.defectOKorNG = query.value(6).toString();
        data.defectNumber = query.value(7).toInt();
        data.huahenNumber = query.value(8).toInt();
        data.yiwuNumber = query.value(9).toInt();
        data.AyiwuNumber = query.value(10).toInt();
        data.ByiwuNumber = query.value(11).toInt();
        data.qipaoNumber = query.value(12).toInt();
        data.sqipaoNumber = query.value(13).toInt();
        data.madianNumber = query.value(14).toInt();
        data.A2madianNumber = query.value(15).toInt();
        data.A3madianNumber = query.value(16).toInt();
        data.A10mmmadianNumber = query.value(17).toInt();
        data.B2madianNumber = query.value(18).toInt();
        data.B3madianNumber = query.value(19).toInt();
        data.B10mmmadianNumber = query.value(20).toInt();
        data.siyin30mm2madianNumber = query.value(21).toInt();
        data.siyin30mm3madianNumber = query.value(22).toInt();
        data.shuiyinNumber = query.value(23).toInt();
        data.AshuiyinNumber = query.value(24).toInt();
        data.B5mmshuiyinNumber = query.value(25).toInt();
        data.youmobuliangNumber = query.value(26).toInt();
        data.A3youmobuliangNumber = query.value(27).toInt();
        data.A2youmobuliangNumber = query.value(28).toInt();
        data.A10mm2youmobuliangNumber = query.value(29).toInt();
        data.A10mm3youmobuliangNumber = query.value(30).toInt();
        data.B3youmobuliangNumber = query.value(31).toInt();
        data.B2youmobuliangNumber = query.value(32).toInt();
        data.B10mm2youmobuliangNumber = query.value(33).toInt();
        data.B10mm3youmobuliangNumber = query.value(34).toInt();
        data.siyin30mm3youmobuliangNumber = query.value(35).toInt();
        data.siyin30mm2youmobuliangNumber = query.value(36).toInt();
        data.juchibianNumber = query.value(37).toInt();
        data.juchibianAllLength = query.value(38).toInt();
        data.siyinquexianNumber = query.value(39).toInt();
        data.guahuaNumber = query.value(40).toInt();
        data.AguahuaNumber = query.value(41).toInt();
        data.liewenNumber = query.value(42).toInt();
        data.benbianjiaoNumber = query.value(43).toInt();
        data.historyPath = query.value(43).toString();
        datas.push_back(data);
    }
    return true;
}

bool DataBase::queryTableData(std::vector<GlassSizeInfo2>& datas, QString querySql)
{
    std::lock_guard<std::mutex> lock(mutex);
    QSqlQuery query(db);
    qDebug()<<querySql;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
        return false;
    }
    while (query.next()) {
        GlassSizeInfo2 data;
        data.id = query.value(0).toInt();
        data.sizeID = query.value(1).toInt();
        data.time = query.value(2).toString();
        data.sizeType = query.value(3).toString();
        data.sizeLevel = query.value(4).toString();
        data.lengthX = query.value(5).toDouble();
        data.widthY = query.value(6).toDouble();
        data.marginsX = query.value(7).toDouble();
        data.marginsY = query.value(8).toDouble();
        data.Pixlength = query.value(8).toInt();
        data.PixWidth = query.value(9).toInt();
        data.PixMarginsX = query.value(10).toInt();
        data.PixMarginsY = query.value(11).toInt();
        data.glassid = query.value(12).toInt();
        data.imagePath0 = query.value(13).toString();
        data.imagePath1 = query.value(14).toString();
        data.imagePath2 = query.value(15).toString();
        datas.push_back(data);
    }
    return true;
}

bool DataBase::queryTableData(std::vector<GlassDefect2>& datas, QString querySql)
{
    std::lock_guard<std::mutex> lock(mutex);
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
        data.pixX = query.value(5).toInt();
        data.pixY = query.value(6).toInt();
        data.pixLength = query.value(7).toInt();
        data.pixWidth = query.value(8).toInt();
        data.pixArea = query.value(9).toInt();
        data.x = query.value(10).toDouble();
        data.y = query.value(11).toDouble();
        data.length = query.value(12).toDouble();
        data.width = query.value(13).toDouble();
        data.area = query.value(14).toDouble();
        data.glassid = query.value(15).toInt();
        data.imagePath0 = query.value(16).toString();
        data.imagePath1 = query.value(17).toString();
        data.imagePath2 = query.value(18).toString();
        data.typeID = query.value(19).toInt();
        datas.push_back(data);
    }
    return true;
}

bool DataBase::queryTableData(std::vector<GlassSummary>& datas, QString querySql)
{
    std::lock_guard<std::mutex> lock(mutex);
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

int64_t DataBase::getCurrentDefectTableMaxID()
{
    std::lock_guard<std::mutex> lock(mutex);
    QString querySql = "SELECT MAX(id) FROM glass_defect;";
    QSqlQuery query(db);
    qDebug()<<querySql;
    int64_t count = 0;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
    }
    if (query.next()) {
        count = query.value(0).toInt();
        qDebug() << "glass_table max(id) =" << count;
    } else {
        qDebug() << "查询失败";
    }
    return count;
}

int64_t DataBase::getCurrentGlassTableMaxID()
{
    std::lock_guard<std::mutex> lock(mutex);
    QString querySql = "SELECT MAX(id) FROM glass_table;";
    QSqlQuery query(db);
    qDebug()<<querySql;
    int64_t count = 0;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
    }
    if (query.next()) {
        count = query.value(0).toInt();
        qDebug() << "glass_table max(id) =" << count;
    } else {
        qDebug() << "查询失败";
    }
    return count;
}

int64_t DataBase::getCurrentSizeTableMaxID()
{
    std::lock_guard<std::mutex> lock(mutex);
    QString querySql = "SELECT MAX(id) FROM glass_sizeinfo;";
    QSqlQuery query(db);
    qDebug()<<querySql;
    int64_t count = 0;
    if(!query.exec(querySql)) {
        qDebug() << "Failed to query data: " << query.lastError().text();
    }
    if (query.next()) {
        count = query.value(0).toInt();
        qDebug() << "glass_sizeinfo max(id) =" << count;
    } else {
        qDebug() << "查询失败";
    }
    return count;
}


bool DataBase::closeDataBase()
{
    std::lock_guard<std::mutex> lock(mutex);
    if(db.isOpen()) {
        db.close();
    }
    return true;
}
