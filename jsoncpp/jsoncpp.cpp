#include "jsoncpp.h"
#include <QFile>
#include <fstream>
#include <QString>
#include <fstream>
#include <QTextStream>
#include <fstream>
#include <QDebug>

void Jsoncpp::getFlawImageFromJson(QString jsonFileName,
                                   int GlassID,
                                   int defectid,
                                   QString& ImagePath1,
                                   QString& ImagePath2,
                                   QString& ImagePath3)
{
    Json::Value root;
    QFile file(jsonFileName);
    if (file.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFileName.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
            Json::Reader reader;
            // 解析到root，root将包含Json里所有子元素
            reader.parse(ifs, root, false);
            ifs.close();
        } else {
            qCritical()<<__FUNCTION__<<" ifs.is_open() =  false";
        }
    } else {
        qCritical()<<__FUNCTION__<<jsonFileName<<" is not exit.";
    }
    if(!root.empty()) {
        Json::Value glass = root[QString::number(GlassID).toStdString().c_str()];
        Json::Value defect = glass[QString::number(defectid).toStdString().c_str()];
        ImagePath1 = defect["ImageNGPath"].asString().data() + QString("/1.jpg");
        ImagePath2 = defect["ImageNGPath"].asString().data() + QString("/2.jpg");
        ImagePath3 = defect["ImageNGPath"].asString().data() + QString("/3.jpg");
    } else {
        qWarning()<<"root is empty!";
    }
}

void Jsoncpp::getDefectSFromJson(QString jsonFullPath,
                                 int glassid,
                                 std::vector<DefectData>& Defects)
{
    //
    // 将文件中已有的数据读出来
    //
    Json::Value root;
    QFile file(jsonFullPath);
    qDebug()<<"jsonFullPath="<<jsonFullPath;
    if (file.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFullPath.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
            Json::Reader reader;
            // 解析到root，root将包含Json里所有子元素
            reader.parse(ifs, root, false);
            ifs.close();
        } else {
            qDebug()<<"ifs.is_open() =  false";
        }
    } else {
        qDebug()<<jsonFullPath<<" is not exit.";
    }
    if(!root.empty()) {
        Json::Value glass = root[QString::number(glassid).toStdString().c_str()];
        int count = glass.size() - 3;
        for (int i = 0; i < count; i++) {
            Json::Value defect = glass[QString::number(i).toStdString().c_str()];
            DefectData temp;
            temp.DefectID = defect["DefectID"].asInt();//序号
            temp.Time = defect["Time"].asString().data();//时间
            temp.DefectType = defect["DefectType"].asString().data();//类型
            temp.DetectLeve = defect["DetectLeve"].asString().data();//等级
            temp.X = defect["X"].asDouble();//坐标X
            temp.Y = defect["Y"].asDouble();//坐标Y
            temp.Lenth = defect["Lenth"].asDouble();//长
            temp.Width = defect["Width"].asDouble();//宽
            temp.Area = defect["Area"].asDouble();//区域
            Defects.push_back(temp);
        }
    } else {
        qWarning()<<"root is empty!";
    }
}

void Jsoncpp::readHoleFromJson(QString jsonFullPath, int glassid, QString& ImageHolesLinePath)
{
    //
    // 将文件中已有的数据读出来
    //
    Json::Value root;
    QFile folderDir(jsonFullPath);
    qDebug()<<"jsonFullPath  = "<<jsonFullPath;
    if (folderDir.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFullPath.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<jsonFullPath<<" is not exit.";
    }

    if(!root.empty()) {
        Json::Value holes = root[QString::number(glassid).toStdString().c_str()];
        ImageHolesLinePath = holes["ImageHolesLinePath"].asString().data();
    } else {
        qDebug()<<"ifs.is_open() =  false";
    }
}

void Jsoncpp::readSizeSmallImage(QString jsonFileName, int GlassID, int row, QString& ImageHolesPath)
{
    Json::Value root;
    QFile fileer(jsonFileName);
    if (fileer.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFileName.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<__FUNCTION__<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<__FUNCTION__<<jsonFileName<<" is not exit.";
    }

    if(!root.empty()) {
          qDebug()<<__FUNCTION__<<"GlassID ="<<GlassID;
          Json::Value holes = root[QString::number(GlassID).toStdString().c_str()];
          Json::Value hole = holes[QString::number(row).toStdString().c_str()];
          ImageHolesPath = hole["ImageHolesPath"].asString().data() + QString("/") + QString::number(row) + ".jpg";
    }
}

void Jsoncpp::readSizeFromJson(QString jsonFilePath,int glassid,std::vector<SizeData>& result)
{
    //
    // 将文件中已有的数据读出来
    //
    Json::Value root;
    QFile filer(jsonFilePath);
    if (filer.exists()) {
        std::ifstream ifs;
        ifs.open(jsonFilePath.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<jsonFilePath<<" is not exit.";
    }
    if(!root.empty()) {
        Json::Value holes = root[QString::number(glassid).toStdString().c_str()];
        int count = holes.size() - 4; //减去角度、长度、宽度、轮廓图路径
        for (int i = 0; i < count; i++) {
            Json::Value hole = holes[QString::number(i).toStdString().c_str()];
            SizeData temp;
            temp.HolesID = hole["HolesID"].asInt();                             // 序号
            temp.Time = hole["Time"].asString().data();                         // 时间
            temp.Type = hole["Type"].asString().data();                         // 类型
            temp.HolesHeight = hole["HolesHeight"].asDouble();                  // 长X
            temp.HolesWidth = hole["HolesWidth"].asDouble();                    // 宽Y
            temp.DistanceHorizontal = hole["DistanceHorizontal"].asDouble();    // 边距X
            temp.DistanceVertical = hole["DistanceVertical"].asDouble();        // 边距Y
            temp.HolesLeve = hole["HolesLeve"].asString().data();               // 等级
            result.push_back(temp);
        }
    }
}

void Jsoncpp::writeSizeToJson(HoleResult inputdata)
{
    //
    // 每块玻璃单独一个文件
    //
    try{
        Json::Value root;
        Json::Value glassholedata;
        for(int i=0; i<(int)inputdata.holes.size(); ++i) {
            HoleData temp = inputdata.holes[i];
            Json::Value holeData;
            holeData["DistanceHorizontal"] = temp.DistanceHorizontal;
            holeData["DistanceVertical"] = temp.DistanceVertical;
            holeData["HolesHeight"] = temp.HolesHeight;
            holeData["HolesID"] = i;
            holeData["HolesLeve"] = temp.HolesLeve.toStdString().c_str();
            holeData["HolesWidth"] = temp.HolesWidth;
            holeData["ImageHolesPath"] = temp.ImageHolesPath.toStdString().c_str();
            holeData["Time"] = temp.Time.toStdString().c_str();
            holeData["Type"] = temp.Type.toStdString().c_str();
            glassholedata[QString::number(i).toStdString().c_str()] = holeData;
        }
        glassholedata["GlassLength"] = inputdata.GlassLength;
        glassholedata["GlassAngle"] = inputdata.GlassAngle;
        glassholedata["GlassWidth"] = inputdata.GlassWidth;
        glassholedata["ImageHolesLinePath"] = inputdata.ImageHolesLinePath.toStdString().c_str();
        root[QString::number(inputdata.GlassID).toStdString().c_str()] = glassholedata;

        Json::StreamWriterBuilder jswBuilder;
        jswBuilder["emitUTF8"] = true;//中文转换
        std::unique_ptr<Json::StreamWriter> jsWriter(jswBuilder.newStreamWriter());
        std::ofstream ofs;
        ofs.open(inputdata.jsonFullPath.toStdString().data());
        if (ofs.is_open()) {
            jsWriter->write(root, &ofs);
            ofs.close();
        }
    } catch(std::exception e) {
        qDebug()<<"Process_Detect::writeHoleDataToJsonfile Error"<<e.what();
    } catch(...) {
        qDebug()<<"Process_Detect::writeHoleDataToJsonfile Error";
    }
}

void Jsoncpp::writeDefectToJson(DefeteResult defect,int GlassID)
{
    //
    // 一块玻璃一个json文件
    //
    try{
        //
        // 将文件中已有的数据读出来
        //
        Json::Value root;
        QFile file(defect.jsonFullPath);
        int precount = 0;
        qDebug()<<"jsonFullPath="<<defect.jsonFullPath;
        if (file.exists()) {
            std::ifstream ifs;
            ifs.open(defect.jsonFullPath.toStdString().data()); // Windows自己注意路径吧
            if (ifs.is_open()) {
                Json::Reader reader;
                // 解析到root，root将包含Json里所有子元素
                reader.parse(ifs, root, false);
                ifs.close();
                precount = root[QString::number(GlassID).toStdString().c_str()].size() - 3;//减去宽度、长度、角度
                qDebug()<<"precount = " <<precount;
            } else {
                qDebug()<<__FUNCTION__<<" ifs.is_open() =  false";
            }
        }
        // 添加新数据
        Json::Value glassdata;
        if (precount != 0) {
            glassdata = root[QString::number(GlassID).toStdString().c_str()];
        }
        for(int i=0; i<(int)defect.defetes.size(); ++i) {
            DefeteData temp = defect.defetes[i];
            Json::Value defectdata;
            defectdata["Area"] = temp.Area;
            defectdata["DefectID"] = precount+i;//加上上一帧的数据个数
            defectdata["DefectType"] = temp.DefectType.toStdString().c_str();
            defectdata["DetectLeve"] = temp.DetectLeve.toStdString().c_str();
            defectdata["ImageNGPath"] = temp.ImageNGPath.toStdString().c_str();
            defectdata["Lenth"] = temp.Lenth;
            defectdata["Time"] = temp.Time.toStdString().c_str();
            defectdata["Width"] = temp.Width;
            defectdata["X"] = temp.X;
            defectdata["Y"] = temp.Y;
            glassdata[QString::number(precount+i).toStdString().c_str()] = defectdata;
        }
        glassdata["GlassLength"] = defect.GlassLength;
        glassdata["GlassAngle"] = defect.GlassAngle;
        glassdata["GlassWidth"] = defect.GlassWidth;
        root[QString::number(GlassID).toStdString().c_str()] = glassdata;

        Json::StreamWriterBuilder jswBuilder;
        jswBuilder["emitUTF8"] = true;//中文转换
        std::unique_ptr<Json::StreamWriter> jsWriter(jswBuilder.newStreamWriter());
        std::ofstream ofs;
        ofs.open(defect.jsonFullPath.toStdString().data());
        if (ofs.is_open()) {
            jsWriter->write(root, &ofs);
            ofs.close();
        }
    } catch(std::exception e) {
        qDebug()<<"[Process_Detect::DetectData2Json] Error"<<e.what();
    } catch(...) {
        qDebug()<<"[Process_Detect::DetectData2Json] Error";
    }
}

//communication模块保存json
void Jsoncpp::writeComDataToJson(QString recipeFullpath, const SignalControl& data)
{
    //
    // 直接将数据覆盖到文件中
    //
    try{
        Json::Value root;
        //系统参数
        root["SystemParams"]["SystemName"] = data.systemName.toStdString().c_str();
        root["SystemParams"]["CamareNumber"] = data.CamareNumber;
        root["SystemParams"]["Camare0Name"] = data.Camare0Name.toStdString().c_str();
        root["SystemParams"]["Camare1Name"] = data.Camare1Name.toStdString().c_str();
        root["SystemParams"]["Camare2Name"] = data.Camare2Name.toStdString().c_str();
        root["SystemParams"]["Camare3Name"] = data.Camare3Name.toStdString().c_str();
        root["SystemParams"]["ServerIP"] = data.ServerIP.toStdString().c_str();
        root["SystemParams"]["ServerPort"] = data.ServerPort;
        //尺寸测量
        root["DimensionalMeasurementParams"]["YAccuracy"] = data.YAccuracy;
        root["DimensionalMeasurementParams"]["XCamera0Accuracy"] = data.XCamera0Accuracy;
        root["DimensionalMeasurementParams"]["XCamera1Accuracy"] = data.XCamera1Accuracy;
        //相机参数
        root["CamareParams"]["Camera0Frame"] = data.Camera0Frame;
        root["CamareParams"]["Camera0PhotoRow"] = data.Camera0PhotoRow;
        root["CamareParams"]["Camera0ExposureTime"] = data.Camera0ExposureTime;
        root["CamareParams"]["Camera0Gain"] = data.Camera0Gain;
        root["CamareParams"]["Camera1Frame"] = data.Camera1Frame;
        root["CamareParams"]["Camera1PhotoRow"] = data.Camera1PhotoRow;
        root["CamareParams"]["Camera1ExposureTime"] = data.Camera1ExposureTime;
        root["CamareParams"]["Camera1Gain"] = data.Camera1Gain;
        root["CamareParams"]["Camera2Frame"] = data.Camera2Frame;
        root["CamareParams"]["Camera2PhotoRow"] = data.Camera2PhotoRow;
        root["CamareParams"]["Camera2ExposureTime"] = data.Camera2ExposureTime;
        root["CamareParams"]["Camera2Gain"] = data.Camera2Gain;
        root["CamareParams"]["Camera3Frame"] = data.Camera3Frame;
        root["CamareParams"]["Camera3PhotoRow"] = data.Camera3PhotoRow;
        root["CamareParams"]["Camera3ExposureTime"] = data.Camera3ExposureTime;
        root["CamareParams"]["Camera3Gain"] = data.Camera3Gain;
        //编码器参数
        root["EncoderParams"]["EncodePulseFilterUs"] = data.EncodePulseFilterUs;
        root["EncoderParams"]["PhotoelectricSensorFiltering"] = data.PhotoelectricSensorFiltering;
        root["EncoderParams"]["WheelEncoderPhotoPulse"] = data.WheelEncoderPhotoPulse;
        root["EncoderParams"]["EncoderMode"] = data.EncoderMode;
        root["EncoderParams"]["SolenoidValve1DownDelay"] = data.SolenoidValve1DownDelay;
        root["EncoderParams"]["SolenoidValve1UpDelay"] = data.SolenoidValve1UpDelay;
        root["EncoderParams"]["SolenoidValve2DownDelay"] = data.SolenoidValve2DownDelay;
        root["EncoderParams"]["SolenoidValve2UpDelay"] = data.SolenoidValve2UpDelay;
        root["EncoderParams"]["WheelAEncoder"] = data.WheelAEncoder;
        root["EncoderParams"]["WheelBEncoder"] = data.WheelBEncoder;
        root["EncoderParams"]["ErrorPhotoCount"] = data.ErrorPhotoCount;

        //光源控制器参数
        root["LighterParams"]["LightField1GlowTime"] = data.LightField1GlowTime;
        root["LighterParams"]["LightField2GlowTime"] = data.LightField2GlowTime;
        root["LighterParams"]["LightField3GlowTime"] = data.LightField3GlowTime;
        root["LighterParams"]["LightField4GlowTime"] = data.LightField4GlowTime;
        root["LighterParams"]["LightSignalSynchronizationDelayRegister"] = data.LightSignalSynchronizationDelayRegister;
        root["LighterParams"]["PhotoMode"] = data.PhotoMode;
        root["LighterParams"]["LightCameraEnable"] = data.LightCameraEnable;
        root["LighterParams"]["WorkMode"] = data.WorkMode;
        root["LighterParams"]["LightSourcePulseEndPointRegister"] = data.LightSourcePulseEndPointRegister;
        root["LighterParams"]["SyncPulsePeriodRegister"] = data.SyncPulsePeriodRegister;
        root["LighterParams"]["CameraFrameSignalTriggerDelay"] = data.CameraFrameSignalTriggerDelay;
        root["LighterParams"]["TimelapseAfterPhotoShootEnd"] = data.TimelapseAfterPhotoShootEnd;
        root["LighterParams"]["SelectedLightFieldNumber"] = data.SelectedLightFieldNumber;
        root["LighterParams"]["FrameSignalOutput"] = data.FrameSignalOutput;


        Json::StreamWriterBuilder jswBuilder;
        jswBuilder["emitUTF8"] = true;//中文转换
        std::unique_ptr<Json::StreamWriter> jsWriter(jswBuilder.newStreamWriter());
        std::ofstream ofs;
        ofs.open(recipeFullpath.toStdString().data());
        if (ofs.is_open()) {
            jsWriter->write(root, &ofs);
            ofs.close();
        }
    } catch(std::exception e) {
        qDebug()<<"[Process_Detect::DetectData2Json] Error"<<e.what();
    } catch(...) {
        qDebug()<<"[Process_Detect::DetectData2Json] Error";
    }
}

//main创建空白json工单
void Jsoncpp::writeEmptyRecipeToJson(QString path)
{
    try {
        Json::Value root;
        // Json::FastWriter writer;
        //系统参数
        root["SystemParams"]["SystemName"] = "Haoshi Intelligent visual inspection";
        root["SystemParams"]["CamareNumber"] = 4;
        root["SystemParams"]["Camare0Name"] = "DSXL810003076";
        root["SystemParams"]["Camare1Name"] = "DSXL810002378";
        root["SystemParams"]["Camare2Name"] = "DSXL810002135";
        root["SystemParams"]["Camare3Name"] = "DSXL810002382";
        root["SystemParams"]["ServerIP"] = "192.168.1.200";
        root["SystemParams"]["ServerPort"] = 7002;
        //尺寸测量
        root["DimensionalMeasurementParams"]["YAccuracy"] = 0;
        root["DimensionalMeasurementParams"]["XCamera0Accuracy"] = 0;
        root["DimensionalMeasurementParams"]["XCamera1Accuracy"] = 0;
        //相机参数
        root["CamareParams"]["Camera0Frame"] = 0;
        root["CamareParams"]["Camera0PhotoRow"] = 0;
        root["CamareParams"]["Camera0ExposureTime"] = 0;
        root["CamareParams"]["Camera0Gain"] = 0;
        root["CamareParams"]["Camera1Frame"] = 0;
        root["CamareParams"]["Camera1PhotoRow"] = 0;
        root["CamareParams"]["Camera1ExposureTime"] = 0;
        root["CamareParams"]["Camera1Gain"] = 0;
        root["CamareParams"]["Camera2Frame"] = 0;
        root["CamareParams"]["Camera2PhotoRow"] = 0;
        root["CamareParams"]["Camera2ExposureTime"] = 0;
        root["CamareParams"]["Camera2Gain"] = 0;
        root["CamareParams"]["Camera3Frame"] = 0;
        root["CamareParams"]["Camera3PhotoRow"] = 0;
        root["CamareParams"]["Camera3ExposureTime"] = 0;
        root["CamareParams"]["Camera3Gain"] = 0;
        //编码器参数
        root["EncoderParams"]["EncodePulseFilterUs"] = 0;
        root["EncoderParams"]["PhotoelectricSensorFiltering"] = 0;
        root["EncoderParams"]["WheelEncoderPhotoPulse"] = 0;
        root["EncoderParams"]["EncoderMode"] = 0;
        root["EncoderParams"]["SolenoidValve1DownDelay"] = 0;
        root["EncoderParams"]["SolenoidValve1UpDelay"] = 0;
        root["EncoderParams"]["SolenoidValve2DownDelay"] = 0;
        root["EncoderParams"]["SolenoidValve2UpDelay"] = 0;
        root["EncoderParams"]["WheelAEncoder"] = 0;
        root["EncoderParams"]["WheelBEncoder"] = 0;
        root["EncoderParams"]["ErrorPhotoCount"] = 0;

        //光源控制器参数
        root["LighterParams"]["LightField1GlowTime"] = 0;
        root["LighterParams"]["LightField2GlowTime"] = 0;
        root["LighterParams"]["LightField3GlowTime"] = 0;
        root["LighterParams"]["LightField4GlowTime"] = 0;
        root["LighterParams"]["LightSignalSynchronizationDelayRegister"] = 0;
        root["LighterParams"]["PhotoMode"] = 0;
        root["LighterParams"]["LightCameraEnable"] = 0;
        root["LighterParams"]["WorkMode"] = 0;
        root["LighterParams"]["LightSourcePulseEndPointRegister"] = 0;
        root["LighterParams"]["SyncPulsePeriodRegister"] = 0;
        root["LighterParams"]["CameraFrameSignalTriggerDelay"] = 0;
        root["LighterParams"]["TimelapseAfterPhotoShootEnd"] = 0;
        root["LighterParams"]["SelectedLightFieldNumber"] = 0;
        root["LighterParams"]["FrameSignalOutput"] = 0;

        Json::StyledWriter writer;
        std::string json_content = writer.write(root);
        std::ofstream ofs;
        ofs.open(path.toStdString().data());
        if (ofs.is_open()) {
            ofs << json_content;
            ofs.close();
        }
    } catch (...) {
        qDebug() << "An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
    }

}

void Jsoncpp::readRecipeFromJson(QString path, SignalControl& signalCtrl)
{
    Json::Value root;
    QFile filer(path);
    if (filer.exists()) {
        std::ifstream ifs;
        ifs.open(path.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
             Json::Reader reader;
             // 解析到root，root将包含Json里所有子元素
             reader.parse(ifs, root, false);
             ifs.close();
        } else {
            qDebug()<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<path<<" is not exit.";
    }
    if(!root.empty()) {
        //系统参数
        signalCtrl.systemName = root["SystemParams"]["SystemName"].asCString();
        signalCtrl.CamareNumber = root["SystemParams"]["CamareNumber"].asInt();
        signalCtrl.Camare0Name = root["SystemParams"]["Camare0Name"].asCString();
        signalCtrl.Camare1Name = root["SystemParams"]["Camare1Name"].asCString();
        signalCtrl.Camare2Name = root["SystemParams"]["Camare2Name"].asCString();
        signalCtrl.Camare3Name = root["SystemParams"]["Camare3Name"].asCString();
        signalCtrl.ServerIP = root["SystemParams"]["ServerIP"].asCString();
        signalCtrl.ServerPort = root["SystemParams"]["ServerPort"].asInt();
        //尺寸测量
        signalCtrl.YAccuracy = root["DimensionalMeasurementParams"]["YAccuracy"].asDouble();
        signalCtrl.XCamera0Accuracy = root["DimensionalMeasurementParams"]["XCamera0Accuracy"].asDouble();
        signalCtrl.XCamera1Accuracy = root["DimensionalMeasurementParams"]["XCamera1Accuracy"].asDouble();
        //相机参数
        signalCtrl.Camera0Frame = root["CamareParams"]["Camera0Frame"].asInt();
        signalCtrl.Camera0PhotoRow = root["CamareParams"]["Camera0Frame"].asInt();
        signalCtrl.Camera0ExposureTime = root["CamareParams"]["Camera0ExposureTime"].asInt();
        signalCtrl.Camera0Gain = root["CamareParams"]["Camera0Gain"].asInt();
        signalCtrl.Camera1Frame = root["CamareParams"]["Camera1Frame"].asInt();
        signalCtrl.Camera1PhotoRow = root["CamareParams"]["Camera1Frame"].asInt();
        signalCtrl.Camera1ExposureTime = root["CamareParams"]["Camera1ExposureTime"].asInt();
        signalCtrl.Camera1Gain = root["CamareParams"]["Camera1Gain"].asInt();
        signalCtrl.Camera2Frame = root["CamareParams"]["Camera2Frame"].asInt();
        signalCtrl.Camera2PhotoRow = root["CamareParams"]["Camera2Frame"].asInt();
        signalCtrl.Camera2ExposureTime = root["CamareParams"]["Camera2ExposureTime"].asInt();
        signalCtrl.Camera2Gain = root["CamareParams"]["Camera2Gain"].asInt();
        signalCtrl.Camera3Frame = root["CamareParams"]["Camera3Frame"].asInt();
        signalCtrl.Camera3PhotoRow = root["CamareParams"]["Camera3Frame"].asInt();
        signalCtrl.Camera3ExposureTime = root["CamareParams"]["Camera3ExposureTime"].asInt();
        signalCtrl.Camera3Gain = root["CamareParams"]["Camera3Gain"].asInt();
        //编码器参数
        signalCtrl.EncodePulseFilterUs = root["EncoderParams"]["EncodePulseFilterUs"].asInt();
        signalCtrl.PhotoelectricSensorFiltering = root["EncoderParams"]["PhotoelectricSensorFiltering"].asInt();
        signalCtrl.WheelEncoderPhotoPulse = root["EncoderParams"]["WheelEncoderPhotoPulse"].asInt();
        signalCtrl.EncoderMode = root["EncoderParams"]["EncoderMode"].asInt();
        signalCtrl.SolenoidValve1DownDelay = root["EncoderParams"]["SolenoidValve1DownDelay"].asInt();
        signalCtrl.SolenoidValve1UpDelay = root["EncoderParams"]["SolenoidValve1UpDelay"].asInt();
        signalCtrl.SolenoidValve2DownDelay = root["EncoderParams"]["SolenoidValve2DownDelay"].asInt();
        signalCtrl.SolenoidValve2UpDelay = root["EncoderParams"]["SolenoidValve2UpDelay"].asInt();
        signalCtrl.WheelAEncoder = root["EncoderParams"]["WheelAEncoder"].asInt();
        signalCtrl.WheelBEncoder = root["EncoderParams"]["WheelBEncoder"].asInt();
        signalCtrl.ErrorPhotoCount = root["EncoderParams"]["ErrorPhotoCount"].asInt();
        // 光源控制器参数
        signalCtrl.LightField1GlowTime = root["LighterParams"]["LightField1GlowTime"].asInt();
        signalCtrl.LightField2GlowTime = root["LighterParams"]["LightField2GlowTime"].asInt();
        signalCtrl.LightField3GlowTime = root["LighterParams"]["LightField3GlowTime"].asInt();
        signalCtrl.LightField4GlowTime = root["LighterParams"]["LightField4GlowTime"].asInt();
        signalCtrl.LightSignalSynchronizationDelayRegister = root["LighterParams"]["LightSignalSynchronizationDelayRegister"].asInt();
        signalCtrl.PhotoMode = root["LighterParams"]["PhotoMode"].asInt();
        signalCtrl.LightCameraEnable = root["LighterParams"]["LightCameraEnable"].asInt();
        signalCtrl.WorkMode = root["LighterParams"]["WorkMode"].asInt();
        signalCtrl.LightSourcePulseEndPointRegister = root["LighterParams"]["LightSourcePulseEndPointRegister"].asInt();
        signalCtrl.SyncPulsePeriodRegister = root["LighterParams"]["SyncPulsePeriodRegister"].asInt();
        signalCtrl.CameraFrameSignalTriggerDelay = root["LighterParams"]["CameraFrameSignalTriggerDelay"].asInt();
        signalCtrl.TimelapseAfterPhotoShootEnd = root["LighterParams"]["TimelapseAfterPhotoShootEnd"].asInt();
        signalCtrl.SelectedLightFieldNumber = root["LighterParams"]["SelectedLightFieldNumber"].asInt();
        signalCtrl.FrameSignalOutput = root["LighterParams"]["FrameSignalOutput"].asInt();
    }
}

void Jsoncpp::writeRecipeToJson(QString fullpath, SignalControl signalCtrl)
{
    try {
        Json::Value root;
        // Json::FastWriter writer;
        //系统参数
        root["SystemParams"]["SystemName"] = signalCtrl.systemName.toStdString().data();
        root["SystemParams"]["CamareNumber"] = signalCtrl.CamareNumber;
        root["SystemParams"]["Camare0Name"] = signalCtrl.Camare0Name.toStdString().data();
        root["SystemParams"]["Camare1Name"] = signalCtrl.Camare1Name.toStdString().data();
        root["SystemParams"]["Camare2Name"] = signalCtrl.Camare2Name.toStdString().data();
        root["SystemParams"]["Camare3Name"] = signalCtrl.Camare3Name.toStdString().data();
        root["SystemParams"]["ServerIP"] = signalCtrl.ServerIP.toStdString().data();
        root["SystemParams"]["ServerPort"] = signalCtrl.ServerPort;
        //尺寸测量
        root["DimensionalMeasurementParams"]["YAccuracy"] = signalCtrl.YAccuracy;
        root["DimensionalMeasurementParams"]["XCamera0Accuracy"] = signalCtrl.XCamera0Accuracy;
        root["DimensionalMeasurementParams"]["XCamera1Accuracy"] = signalCtrl.XCamera1Accuracy;
        //相机参数
        root["CamareParams"]["Camera0Frame"] = signalCtrl.Camera0Frame;
        root["CamareParams"]["Camera0PhotoRow"] = signalCtrl.Camera0PhotoRow;
        root["CamareParams"]["Camera0ExposureTime"] = signalCtrl.Camera0ExposureTime;
        root["CamareParams"]["Camera0Gain"] = signalCtrl.Camera0Gain;
        root["CamareParams"]["Camera1Frame"] = signalCtrl.Camera1Frame;
        root["CamareParams"]["Camera1PhotoRow"] = signalCtrl.Camera1PhotoRow;
        root["CamareParams"]["Camera1ExposureTime"] = signalCtrl.Camera1ExposureTime;
        root["CamareParams"]["Camera1Gain"] = signalCtrl.Camera1Gain;
        root["CamareParams"]["Camera2Frame"] = signalCtrl.Camera2Frame;
        root["CamareParams"]["Camera2PhotoRow"] = signalCtrl.Camera2PhotoRow;
        root["CamareParams"]["Camera2ExposureTime"] = signalCtrl.Camera2ExposureTime;
        root["CamareParams"]["Camera2Gain"] = signalCtrl.Camera2Gain;
        root["CamareParams"]["Camera3Frame"] = signalCtrl.Camera3Frame;
        root["CamareParams"]["Camera3PhotoRow"] = signalCtrl.Camera3PhotoRow;
        root["CamareParams"]["Camera3ExposureTime"] = signalCtrl.Camera3ExposureTime;
        root["CamareParams"]["Camera3Gain"] = signalCtrl.Camera3Gain;
        //编码器参数
        root["EncoderParams"]["EncodePulseFilterUs"] = signalCtrl.EncodePulseFilterUs;
        root["EncoderParams"]["PhotoelectricSensorFiltering"] = signalCtrl.PhotoelectricSensorFiltering;
        root["EncoderParams"]["WheelEncoderPhotoPulse"] = signalCtrl.WheelEncoderPhotoPulse;
        root["EncoderParams"]["EncoderMode"] = signalCtrl.EncoderMode;
        root["EncoderParams"]["SolenoidValve1DownDelay"] = signalCtrl.SolenoidValve1DownDelay;
        root["EncoderParams"]["SolenoidValve1UpDelay"] = signalCtrl.SolenoidValve1UpDelay;
        root["EncoderParams"]["SolenoidValve2DownDelay"] = signalCtrl.SolenoidValve2DownDelay;
        root["EncoderParams"]["SolenoidValve2UpDelay"] = signalCtrl.SolenoidValve2UpDelay;
        root["EncoderParams"]["WheelAEncoder"] = signalCtrl.WheelAEncoder;
        root["EncoderParams"]["WheelBEncoder"] = signalCtrl.WheelBEncoder;
        root["EncoderParams"]["ErrorPhotoCount"] = signalCtrl.ErrorPhotoCount;
        //光源控制器参数
        root["LighterParams"]["LightField1GlowTime"] = signalCtrl.LightField1GlowTime;
        root["LighterParams"]["LightField2GlowTime"] = signalCtrl.LightField2GlowTime;
        root["LighterParams"]["LightField3GlowTime"] = signalCtrl.LightField3GlowTime;
        root["LighterParams"]["LightField4GlowTime"] = signalCtrl.LightField4GlowTime;
        root["LighterParams"]["LightSignalSynchronizationDelayRegister"] = signalCtrl.LightSignalSynchronizationDelayRegister;
        root["LighterParams"]["PhotoMode"] = signalCtrl.PhotoMode;
        root["LighterParams"]["LightCameraEnable"] = signalCtrl.LightCameraEnable;
        root["LighterParams"]["WorkMode"] = signalCtrl.WorkMode;
        root["LighterParams"]["LightSourcePulseEndPointRegister"] = signalCtrl.LightSourcePulseEndPointRegister;
        root["LighterParams"]["SyncPulsePeriodRegister"] = signalCtrl.SyncPulsePeriodRegister;
        root["LighterParams"]["CameraFrameSignalTriggerDelay"] = signalCtrl.CameraFrameSignalTriggerDelay;
        root["LighterParams"]["TimelapseAfterPhotoShootEnd"] = signalCtrl.TimelapseAfterPhotoShootEnd;
        root["LighterParams"]["SelectedLightFieldNumber"] = signalCtrl.SelectedLightFieldNumber;
        root["LighterParams"]["FrameSignalOutput"] = signalCtrl.FrameSignalOutput;

        Json::StyledWriter writer;
        std::string json_content = writer.write(root);
        std::ofstream ofs;
        ofs.open(fullpath.toStdString().data());
        if (ofs.is_open()) {
            ofs << json_content;
            ofs.close();
        }
    } catch (...) {
        qDebug() << "An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
    }
}

//更新json文件内容
void Jsoncpp::updateRecipeToJson(QString fullpath, SignalControl signalCtrl)
{
    Json::Value root;
    std::ifstream ifs(fullpath.toStdString().c_str());
    if (ifs.is_open()) {
        Json::CharReaderBuilder builder;
        JSONCPP_STRING errs;
        if (!parseFromStream(builder, ifs, &root, &errs)) {
            qDebug() << "Error parsing JSON: " << errs;
            return;
        }
        ifs.close();
    } else {
        qDebug() << "Failed to open file.";
        return;
    }

    // 修改 JSON 内容
    //系统参数
    root["SystemParams"]["SystemName"] = signalCtrl.systemName.toStdString().data();
    root["SystemParams"]["CamareNumber"] = signalCtrl.CamareNumber;
    root["SystemParams"]["Camare0Name"] = signalCtrl.Camare0Name.toStdString().data();
    root["SystemParams"]["Camare1Name"] = signalCtrl.Camare1Name.toStdString().data();
    root["SystemParams"]["Camare2Name"] = signalCtrl.Camare2Name.toStdString().data();
    root["SystemParams"]["Camare3Name"] = signalCtrl.Camare3Name.toStdString().data();
    root["SystemParams"]["ServerIP"] = signalCtrl.ServerIP.toStdString().data();
    root["SystemParams"]["ServerPort"] = signalCtrl.ServerPort;
    //尺寸测量
    root["DimensionalMeasurementParams"]["YAccuracy"] = signalCtrl.YAccuracy;
    root["DimensionalMeasurementParams"]["XCamera0Accuracy"] = signalCtrl.XCamera0Accuracy;
    root["DimensionalMeasurementParams"]["XCamera1Accuracy"] = signalCtrl.XCamera1Accuracy;
    //相机参数
    root["CamareParams"]["Camera0Frame"] = signalCtrl.Camera0Frame;
    root["CamareParams"]["Camera0PhotoRow"] = signalCtrl.Camera0PhotoRow;
    root["CamareParams"]["Camera0ExposureTime"] = signalCtrl.Camera0ExposureTime;
    root["CamareParams"]["Camera0Gain"] = signalCtrl.Camera0Gain;
    root["CamareParams"]["Camera1Frame"] = signalCtrl.Camera1Frame;
    root["CamareParams"]["Camera1PhotoRow"] = signalCtrl.Camera1PhotoRow;
    root["CamareParams"]["Camera1ExposureTime"] = signalCtrl.Camera1ExposureTime;
    root["CamareParams"]["Camera1Gain"] = signalCtrl.Camera1Gain;
    root["CamareParams"]["Camera2Frame"] = signalCtrl.Camera2Frame;
    root["CamareParams"]["Camera2PhotoRow"] = signalCtrl.Camera2PhotoRow;
    root["CamareParams"]["Camera2ExposureTime"] = signalCtrl.Camera2ExposureTime;
    root["CamareParams"]["Camera2Gain"] = signalCtrl.Camera2Gain;
    root["CamareParams"]["Camera3Frame"] = signalCtrl.Camera3Frame;
    root["CamareParams"]["Camera3PhotoRow"] = signalCtrl.Camera3PhotoRow;
    root["CamareParams"]["Camera3ExposureTime"] = signalCtrl.Camera3ExposureTime;
    root["CamareParams"]["Camera3Gain"] = signalCtrl.Camera3Gain;
    //编码器参数
    root["EncoderParams"]["EncodePulseFilterUs"] = signalCtrl.EncodePulseFilterUs;
    root["EncoderParams"]["PhotoelectricSensorFiltering"] = signalCtrl.PhotoelectricSensorFiltering;
    root["EncoderParams"]["WheelEncoderPhotoPulse"] = signalCtrl.WheelEncoderPhotoPulse;
    root["EncoderParams"]["EncoderMode"] = signalCtrl.EncoderMode;
    root["EncoderParams"]["SolenoidValve1DownDelay"] = signalCtrl.SolenoidValve1DownDelay;
    root["EncoderParams"]["SolenoidValve1UpDelay"] = signalCtrl.SolenoidValve1UpDelay;
    root["EncoderParams"]["SolenoidValve2DownDelay"] = signalCtrl.SolenoidValve2DownDelay;
    root["EncoderParams"]["SolenoidValve2UpDelay"] = signalCtrl.SolenoidValve2UpDelay;
    root["EncoderParams"]["WheelAEncoder"] = signalCtrl.WheelAEncoder;
    root["EncoderParams"]["WheelBEncoder"] = signalCtrl.WheelBEncoder;
    root["EncoderParams"]["ErrorPhotoCount"] = signalCtrl.ErrorPhotoCount;
    //光源控制器参数
    root["LighterParams"]["LightField1GlowTime"] = signalCtrl.LightField1GlowTime;
    root["LighterParams"]["LightField2GlowTime"] = signalCtrl.LightField2GlowTime;
    root["LighterParams"]["LightField3GlowTime"] = signalCtrl.LightField3GlowTime;
    root["LighterParams"]["LightField4GlowTime"] = signalCtrl.LightField4GlowTime;
    root["LighterParams"]["LightSignalSynchronizationDelayRegister"] = signalCtrl.LightSignalSynchronizationDelayRegister;
    root["LighterParams"]["PhotoMode"] = signalCtrl.PhotoMode;
    root["LighterParams"]["LightCameraEnable"] = signalCtrl.LightCameraEnable;
    root["LighterParams"]["WorkMode"] = signalCtrl.WorkMode;
    root["LighterParams"]["LightSourcePulseEndPointRegister"] = signalCtrl.LightSourcePulseEndPointRegister;
    root["LighterParams"]["SyncPulsePeriodRegister"] = signalCtrl.SyncPulsePeriodRegister;
    root["LighterParams"]["CameraFrameSignalTriggerDelay"] = signalCtrl.CameraFrameSignalTriggerDelay;
    root["LighterParams"]["TimelapseAfterPhotoShootEnd"] = signalCtrl.TimelapseAfterPhotoShootEnd;
    root["LighterParams"]["SelectedLightFieldNumber"] = signalCtrl.SelectedLightFieldNumber;
    root["LighterParams"]["FrameSignalOutput"] = signalCtrl.FrameSignalOutput;

    std::ofstream ofs(fullpath.toStdString().c_str());
    if (ofs.is_open()) {
        Json::StreamWriterBuilder writerBuilder;
        std::unique_ptr<Json::StreamWriter> writer(writerBuilder.newStreamWriter());
        writer->write(root, &ofs);
        ofs.close();
        qDebug() << "JSON file modified successfully.";
    } else {
        qDebug() << "Failed to open file for writing.";
    }
}

void Jsoncpp::writeEmptyCalibrateToJson(QString path)
{
    try {
        Json::Value root;
        //相机0参数
        root["Camera0"]["topPixCrop"] = 0;//图像上边缘裁剪多少像元
        root["Camera0"]["bottomPixCrop"] = 0;//图像下边缘裁剪多少像元
        root["Camera0"]["leftPixCrop"] = 0;//图像左侧边缘裁剪多少像元
        root["Camera0"]["rightPixCrop"] = 0;//图像右侧边缘裁剪多少像元
        //相机1参数
        root["Camera1"]["topPixCrop"] = 0;//图像上边缘裁剪多少像元
        root["Camera1"]["bottomPixCrop"] = 0;//图像下边缘裁剪多少像元
        root["Camera1"]["leftPixCrop"] = 0;//图像左侧边缘裁剪多少像元
        root["Camera1"]["rightPixCrop"] = 0;//图像右侧边缘裁剪多少像元
        //相机2参数
        root["Camera2"]["topPixCrop"] = 0;//图像上边缘裁剪多少像元
        root["Camera2"]["bottomPixCrop"] = 0;//图像下边缘裁剪多少像元
        root["Camera2"]["leftPixCrop"] = 0;//图像左侧边缘裁剪多少像元
        root["Camera2"]["rightPixCrop"] = 0;//图像右侧边缘裁剪多少像元
        //相机3参数
        root["Camera3"]["topPixCrop"] = 0;//图像上边缘裁剪多少像元
        root["Camera3"]["bottomPixCrop"] = 0;//图像下边缘裁剪多少像元
        root["Camera3"]["leftPixCrop"] = 0;//图像左侧边缘裁剪多少像元
        root["Camera3"]["rightPixCrop"] = 0;//图像右侧边缘裁剪多少像元

        Json::StyledWriter writer;
        std::string json_content = writer.write(root);
        std::ofstream ofs;
        ofs.open(path.toStdString().data());
        if (ofs.is_open()) {
            ofs << json_content;
            ofs.close();
        }
    } catch (...) {
        qDebug() << "An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
    }
}

void Jsoncpp::readCalibrateFromJson(QString path, CropArgPackage& crop)
{
    Json::Value root;
    QFile filer(path);
    if (filer.exists()) {
        std::ifstream ifs;
        ifs.open(path.toStdString().c_str()); // Windows自己注意路径吧
        if (ifs.is_open()) {
            Json::Reader reader;
            // 解析到root，root将包含Json里所有子元素
            reader.parse(ifs, root, false);
            ifs.close();
        } else {
            qDebug()<<" ifs.is_open() =  false";
        }
    } else {
        qDebug()<<path<<" is not exit.";
    }
    if(!root.empty()) {
        crop.args.clear();
        //相机0参数
        CameraCropArg arg0;
        arg0.topPixCrop = root["Camera0"]["topPixCrop"].asInt();//图像上边缘裁剪多少像元
        arg0.bottomPixCrop = root["Camera0"]["bottomPixCrop"].asInt();//图像下边缘裁剪多少像元
        arg0.leftPixCrop = root["Camera0"]["leftPixCrop"].asInt();//图像左侧边缘裁剪多少像元
        arg0.rightPixCrop = root["Camera0"]["rightPixCrop"].asInt();//图像右侧边缘裁剪多少像元
        crop.args.push_back(arg0);
        //相机1参数
        CameraCropArg arg1;
        arg1.topPixCrop = root["Camera1"]["topPixCrop"].asInt();//图像上边缘裁剪多少像元
        arg1.bottomPixCrop = root["Camera1"]["bottomPixCrop"].asInt();//图像下边缘裁剪多少像元
        arg1.leftPixCrop = root["Camera1"]["leftPixCrop"].asInt();//图像左侧边缘裁剪多少像元
        arg1.rightPixCrop = root["Camera1"]["rightPixCrop"].asInt();//图像右侧边缘裁剪多少像元
        crop.args.push_back(arg1);
        //相机2参数
        CameraCropArg arg2;
        arg2.topPixCrop = root["Camera2"]["topPixCrop"].asInt();//图像上边缘裁剪多少像元
        arg2.bottomPixCrop = root["Camera2"]["bottomPixCrop"].asInt();//图像下边缘裁剪多少像元
        arg2.leftPixCrop = root["Camera2"]["leftPixCrop"].asInt();//图像左侧边缘裁剪多少像元
        arg2.rightPixCrop = root["Camera2"]["rightPixCrop"].asInt();//图像右侧边缘裁剪多少像元
        crop.args.push_back(arg2);
        //相机3参数
        CameraCropArg arg3;
        arg3.topPixCrop = root["Camera3"]["topPixCrop"].asInt();//图像上边缘裁剪多少像元
        arg3.bottomPixCrop = root["Camera3"]["bottomPixCrop"].asInt();//图像下边缘裁剪多少像元
        arg3.leftPixCrop = root["Camera3"]["leftPixCrop"].asInt();//图像左侧边缘裁剪多少像元
        arg3.rightPixCrop = root["Camera3"]["rightPixCrop"].asInt();//图像右侧边缘裁剪多少像元
        crop.args.push_back(arg3);
    }
}

void Jsoncpp::writeCalibrateToJson(QString path, CropArgPackage crop)
{
    try {
        Json::Value root;
        if (crop.args.size() == 4) {
            //相机0参数
            CameraCropArg arg0 = crop.args[0];
            root["Camera0"]["topPixCrop"] = arg0.topPixCrop;//图像上边缘裁剪多少像元
            root["Camera0"]["bottomPixCrop"] = arg0.bottomPixCrop;//图像下边缘裁剪多少像元
            root["Camera0"]["leftPixCrop"] = arg0.leftPixCrop;//图像左侧边缘裁剪多少像元
            root["Camera0"]["rightPixCrop"] = arg0.rightPixCrop;//图像右侧边缘裁剪多少像元
            //相机1参数
            CameraCropArg arg1 = crop.args[1];
            root["Camera0"]["topPixCrop"] = arg1.topPixCrop;//图像上边缘裁剪多少像元
            root["Camera0"]["bottomPixCrop"] = arg1.bottomPixCrop;//图像下边缘裁剪多少像元
            root["Camera0"]["leftPixCrop"] = arg1.leftPixCrop;//图像左侧边缘裁剪多少像元
            root["Camera0"]["rightPixCrop"] = arg1.rightPixCrop;//图像右侧边缘裁剪多少像元
            //相机2参数
            CameraCropArg arg2= crop.args[2];
            root["Camera0"]["topPixCrop"] = arg2.topPixCrop;//图像上边缘裁剪多少像元
            root["Camera0"]["bottomPixCrop"] = arg2.bottomPixCrop;//图像下边缘裁剪多少像元
            root["Camera0"]["leftPixCrop"] = arg2.leftPixCrop;//图像左侧边缘裁剪多少像元
            root["Camera0"]["rightPixCrop"] = arg2.rightPixCrop;//图像右侧边缘裁剪多少像元
            //相机3参数
            CameraCropArg arg3= crop.args[3];
            root["Camera0"]["topPixCrop"] = arg3.topPixCrop;//图像上边缘裁剪多少像元
            root["Camera0"]["bottomPixCrop"] = arg3.bottomPixCrop;//图像下边缘裁剪多少像元
            root["Camera0"]["leftPixCrop"] = arg3.leftPixCrop;//图像左侧边缘裁剪多少像元
            root["Camera0"]["rightPixCrop"] = arg3.rightPixCrop;//图像右侧边缘裁剪多少像元
        }

        Json::StyledWriter writer;
        std::string json_content = writer.write(root);
        std::ofstream ofs;
        ofs.open(path.toStdString().data());
        if (ofs.is_open()) {
            ofs << json_content;
            ofs.close();
        }
    } catch (...) {
        qDebug() << "An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
    }
}
