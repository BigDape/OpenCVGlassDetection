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
        //自定义参数
        root["CustomParams"]["SaveOriginImage"] = data.SaveOriginImage;
        root["CustomParams"]["SaveEntireImage"] = data.SaveEntireImage;
        root["CustomParams"]["SaveFlawImage"] = data.SaveFlawImage;
        root["CustomParams"]["SaveCropImage"] = data.SaveCropImage;
        root["CustomParams"]["XYLengthEnable"] = data.XYLengthEnable;
        root["CustomParams"]["FlawDefectEnable"] = data.FlawDefectEnable;
        //缺陷检测
        root["DefectDetectionParams"]["Camera12PixelDeviation"] = data.Camera12PixelDeviation;
        root["DefectDetectionParams"]["Camera23PixelDeviation"] = data.Camera23PixelDeviation;
        root["DefectDetectionParams"]["Camera24PixelDeviation"] = data.Camera24PixelDeviation;
        root["DefectDetectionParams"]["SilkToRollerDist"] = data.SilkToRollerDist;
        root["DefectDetectionParams"]["ScratchAreaThreshold"] = data.ScratchAreaThreshold;
        root["DefectDetectionParams"]["BubbleStoneAreaThreshold"] = data.BubbleStoneAreaThreshold;
        root["DefectDetectionParams"]["DirtyAreaThreshold"] = data.DirtyAreaThreshold;
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
        root["EncoderParams"]["EncodeUnitToDist"] = data.temp0;
        root["EncoderParams"]["EncodePulseFilterUs"] = data.temp1;
        root["EncoderParams"]["EncodeCountEndFlag"] = data.temp2;
        root["EncoderParams"]["EncodeCount"] = data.temp3;
        root["EncoderParams"]["EncodeTriggerRowCount"] = data.temp4;
        root["EncoderParams"]["Encode4FrequencyMultiplierCount"] = data.temp5;
        root["EncoderParams"]["EncodeUnitTimePulseCount"] = data.temp6;
        root["EncoderParams"]["EncodeCountTimeHalfSecond"] = data.temp7;
        root["EncoderParams"]["EncodeChannel"] = data.temp8;
        root["EncoderParams"]["EncodeRevolution"] = data.temp9;
        root["EncoderParams"]["RollerPerimeterUm"] = data.temp10;
        root["EncoderParams"]["ExpectSinglePixelAccuracy"] = data.temp11;
        root["EncoderParams"]["RollerMaxSpeedToRowCount"] = data.temp12;
        root["EncoderParams"]["EveryRowToEncodeCount"] = data.temp13;
        root["EncoderParams"]["PressureEncodecoefficient"] = data.tempRollerCofficient;
        //控制器参数
        root["ControllerParams"]["PixelAccuracyUm"] = data.temp14;
        root["ControllerParams"]["PhotoelectricSignalPulseFilter"] = data.temp15;
        root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"] = data.temp16;
        root["ControllerParams"]["PhotoelectricToCamareDist"] = data.temp17;
        root["ControllerParams"]["CamareFrameTrigerDelayRowCount"] = data.temp18;
        root["ControllerParams"]["FrameSignalContinueTime"] = data.temp19;
        root["ControllerParams"]["ModuleEnableSignal"] = data.temp20;
        root["ControllerParams"]["CamarePhotoRowCount"] = data.temp21;
        root["ControllerParams"]["InnerRowFrequency"] = data.temp22;
        root["ControllerParams"]["PhotoMode"] = data.tempAutoPhoto;
        root["ControllerParams"]["PhotoEndDelayRowCount"] = data.temp18;
        //光源控制器参数
        root["LighterParams"]["LightField1DelayTime"] = data.temp23;
        root["LighterParams"]["LightField1GlowTime"] = data.temp24;
        root["LighterParams"]["LightField2DelayTime"] = data.temp25;
        root["LighterParams"]["LightField2GlowTime"] = data.temp26;
        root["LighterParams"]["LightField3DelayTime"] = data.temp27;
        root["LighterParams"]["LightField3GlowTime"] = data.temp28;
        root["LighterParams"]["LightField4DelayTime"] = data.temp29;
        root["LighterParams"]["LightField4GlowTime"] = data.temp30;
        root["LighterParams"]["SelectedLightFieldNumber"] = data.temp55;
        root["LighterParams"]["HorizontalDarkfieldSelectRegister"] = data.temp56;
        root["LighterParams"]["CamareAndLightFieldControl"] = data.temp35;
        root["LighterParams"]["SignalSwitch"] = data.temp36;
        root["LighterParams"]["RowSignalSelected"] = data.temp37;


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
        //自定义参数
        root["CustomParams"]["SaveOriginImage"] = 0;
        root["CustomParams"]["SaveEntireImage"] = 0;
        root["CustomParams"]["SaveFlawImage"] = 0;
        root["CustomParams"]["SaveCropImage"] = 0;
        root["CustomParams"]["XYLengthEnable"] = 0;
        root["CustomParams"]["FlawDefectEnable"] = 0;
        //缺陷检测
        root["DefectDetectionParams"]["Camera12PixelDeviation"] = 0;
        root["DefectDetectionParams"]["Camera23PixelDeviation"] = 0;
        root["DefectDetectionParams"]["Camera24PixelDeviation"] = 0;
        root["DefectDetectionParams"]["SilkToRollerDist"] = 0;
        root["DefectDetectionParams"]["ScratchAreaThreshold"] = 0;
        root["DefectDetectionParams"]["BubbleStoneAreaThreshold"] = 0;
        root["DefectDetectionParams"]["DirtyAreaThreshold"] = 0;
        //尺寸测量
        root["DimensionalMeasurementParams"]["YAccuracyB"] = 0;
        root["DimensionalMeasurementParams"]["YAccuracyK"] = 0;
        root["DimensionalMeasurementParams"]["Width"] = 0;
        root["DimensionalMeasurementParams"]["WidthDeviation"] = 0;
        root["DimensionalMeasurementParams"]["Digonal1"] = 0;
        root["DimensionalMeasurementParams"]["Digonal1Deviation"] = 0;
        root["DimensionalMeasurementParams"]["Diagonal2"] = 0;
        root["DimensionalMeasurementParams"]["Digonal2Deviation"] = 0;
        root["DimensionalMeasurementParams"]["Camera1Pixel0Accuracy"] = 0;
        root["DimensionalMeasurementParams"]["Camera1PixelKValue"] = 0;
        root["DimensionalMeasurementParams"]["Camera21AccuracyRatio"] = 0;
        root["DimensionalMeasurementParams"]["Camera2PixelKValue"] = 0;
        root["DimensionalMeasurementParams"]["Length"] = 0;
        root["DimensionalMeasurementParams"]["LengthDeviation"] = 0;
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
        root["EncoderParams"]["EncodeUnitToDist"] = 0;
        root["EncoderParams"]["EncodePulseFilterUs"] = 0;
        root["EncoderParams"]["EncodeRevolution"] = 0;
        root["EncoderParams"]["RollerPerimeterUm"] = 0;
        root["EncoderParams"]["ExpectSinglePixelAccuracy"] = 0;
        root["EncoderParams"]["RollerMaxSpeedToRowCount"] = 0;
        root["EncoderParams"]["EveryRowToEncodeCount"] = 0;
        //控制器参数
        root["ControllerParams"]["PixelAccuracyUm"] = 0;
        root["ControllerParams"]["PhotoelectricSignalPulseFilter"] = 0;
        root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"] = 0;
        root["ControllerParams"]["PhotoelectricToCamareDist"] = 0;
        root["ControllerParams"]["CamareFrameTrigerDelayRowCount"] = 0;
        root["ControllerParams"]["FrameSignalContinueTime"] = 0;
        root["ControllerParams"]["ModuleEnableSignal"] = 0;
        root["ControllerParams"]["CamarePhotoRowCount"] = 0;
        root["ControllerParams"]["InnerRowFrequency"] = 0;
        root["ControllerParams"]["PhotoMode"] = 0;
        root["ControllerParams"]["PhotoEndDelayRowCount"] = 0;
        //光源控制器参数
        root["LighterParams"]["LightField1DelayTime"] = 0;
        root["LighterParams"]["LightField1GlowTime"] = 0;
        root["LighterParams"]["LightField2DelayTime"] = 0;
        root["LighterParams"]["LightField2GlowTime"] = 0;
        root["LighterParams"]["LightField3DelayTime"] = 0;
        root["LighterParams"]["LightField3GlowTime"] = 0;
        root["LighterParams"]["LightField4DelayTime"] = 0;
        root["LighterParams"]["LightField4GlowTime"] = 0;
        root["LighterParams"]["SelectedLightFieldNumber"] = 0;
        root["LighterParams"]["HorizontalDarkfieldSelectRegister"] = 0;
        root["LighterParams"]["CamareAndLightFieldControl"] = 0;
        root["LighterParams"]["SignalSwitch"] = 0;
        root["LighterParams"]["RowSignalSelected"] = 0;

        // std::string json_content = writer.write(root);
        // std::ofstream ofs;
        // ofs.open(path.toStdString().data());
        // if (ofs.is_open()) {
        //     ofs<<json_content;
        //     ofs.close();
        // }
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
        //自定义参数
        signalCtrl.SaveOriginImage = root["CustomParams"]["SaveOriginImage"].asInt();
        signalCtrl.SaveEntireImage = root["CustomParams"]["SaveEntireImage"].asInt();
        signalCtrl.SaveFlawImage = root["CustomParams"]["SaveFlawImage"].asInt();
        signalCtrl.SaveCropImage = root["CustomParams"]["SaveCropImage"].asInt();
        signalCtrl.XYLengthEnable = root["CustomParams"]["XYLengthEnable"].asInt();
        signalCtrl.FlawDefectEnable = root["CustomParams"]["FlawDefectEnable"].asInt();
        //缺陷检测
        signalCtrl.Camera12PixelDeviation = root["DefectDetectionParams"]["Camera12PixelDeviation"].asInt();
        signalCtrl.Camera23PixelDeviation = root["DefectDetectionParams"]["Camera23PixelDeviation"].asInt();
        signalCtrl.Camera24PixelDeviation = root["DefectDetectionParams"]["Camera24PixelDeviation"].asInt();
        signalCtrl.SilkToRollerDist = root["DefectDetectionParams"]["SilkToRollerDist"].asInt();
        signalCtrl.ScratchAreaThreshold = root["DefectDetectionParams"]["ScratchAreaThreshold"].asInt();
        signalCtrl.BubbleStoneAreaThreshold = root["DefectDetectionParams"]["BubbleStoneAreaThreshold"].asInt();
        signalCtrl.DirtyAreaThreshold = root["DefectDetectionParams"]["DirtyAreaThreshold"].asInt();
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
        signalCtrl.temp0 = root["EncoderParams"]["EncodeUnitToDist"].asInt();
        signalCtrl.temp1 = root["EncoderParams"]["EncodePulseFilterUs"].asInt();
        signalCtrl.temp9 = root["EncoderParams"]["EncodeRevolution"].asInt();
        signalCtrl.temp10 = root["EncoderParams"]["RollerPerimeterUm"].asInt();
        signalCtrl.temp11 = root["EncoderParams"]["ExpectSinglePixelAccuracy"].asInt();
        signalCtrl.temp12 = root["EncoderParams"]["RollerMaxSpeedToRowCount"].asInt();
        signalCtrl.temp13 = root["EncoderParams"]["EveryRowToEncodeCount"].asInt();
        // 控制器参数
        signalCtrl.temp14 = root["ControllerParams"]["PixelAccuracyUm"].asDouble();
        signalCtrl.temp15 = root["ControllerParams"]["PhotoelectricSignalPulseFilter"].asInt();
        signalCtrl.temp16 = root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"].asInt();
        signalCtrl.temp17 = root["ControllerParams"]["PhotoelectricToCamareDist"].asInt();
        signalCtrl.temp18 = root["ControllerParams"]["CamareFrameTrigerDelayRowCount"].asInt();
        signalCtrl.temp19 = root["ControllerParams"]["FrameSignalContinueTime"].asInt();
        signalCtrl.temp20 = root["ControllerParams"]["ModuleEnableSignal"].asInt();
        signalCtrl.temp21 = root["ControllerParams"]["CamarePhotoRowCount"].asInt();
        signalCtrl.temp22 = root["ControllerParams"]["InnerRowFrequency"].asInt();
        signalCtrl.tempAutoPhoto = root["ControllerParams"]["PhotoMode"].asInt();
        signalCtrl.tempPhotoEndDelayLine = root["ControllerParams"]["PhotoEndDelayRowCount"].asInt();
        // 光源控制器参数
        signalCtrl.temp23 = root["LighterParams"]["LightField1DelayTime"].asInt();
        signalCtrl.temp24 = root["LighterParams"]["LightField1GlowTime"].asInt();
        signalCtrl.temp25 = root["LighterParams"]["LightField2DelayTime"].asInt();
        signalCtrl.temp26 = root["LighterParams"]["LightField2GlowTime"].asInt();
        signalCtrl.temp27 = root["LighterParams"]["LightField3DelayTime"].asInt();
        signalCtrl.temp28 = root["LighterParams"]["LightField3GlowTime"].asInt();
        signalCtrl.temp29 = root["LighterParams"]["LightField4DelayTime"].asInt();
        signalCtrl.temp30 = root["LighterParams"]["LightField4GlowTime"].asInt();
        signalCtrl.temp55 = root["LighterParams"]["SelectedLightFieldNumber"].asInt();
        signalCtrl.temp56 = root["LighterParams"]["HorizontalDarkfieldSelectRegister"].asInt();
        signalCtrl.temp35 = root["LighterParams"]["CamareAndLightFieldControl"].asInt();
        signalCtrl.temp36 = root["LighterParams"]["SignalSwitch"].asInt();
        signalCtrl.temp37 = root["LighterParams"]["RowSignalSelected"].asInt();
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
        //自定义参数
        root["CustomParams"]["SaveOriginImage"] = signalCtrl.SaveOriginImage;
        root["CustomParams"]["SaveEntireImage"] = signalCtrl.SaveEntireImage;
        root["CustomParams"]["SaveFlawImage"] = signalCtrl.SaveFlawImage;
        root["CustomParams"]["SaveCropImage"] = signalCtrl.SaveCropImage;
        root["CustomParams"]["XYLengthEnable"] = signalCtrl.XYLengthEnable;
        root["CustomParams"]["FlawDefectEnable"] = signalCtrl.FlawDefectEnable;
        //缺陷检测
        root["DefectDetectionParams"]["Camera12PixelDeviation"] = signalCtrl.Camera12PixelDeviation;
        root["DefectDetectionParams"]["Camera23PixelDeviation"] = signalCtrl.Camera23PixelDeviation;
        root["DefectDetectionParams"]["Camera24PixelDeviation"] = signalCtrl.Camera24PixelDeviation;
        root["DefectDetectionParams"]["SilkToRollerDist"] = signalCtrl.SilkToRollerDist;
        root["DefectDetectionParams"]["ScratchAreaThreshold"] = signalCtrl.ScratchAreaThreshold;
        root["DefectDetectionParams"]["BubbleStoneAreaThreshold"] = signalCtrl.BubbleStoneAreaThreshold;
        root["DefectDetectionParams"]["DirtyAreaThreshold"] = signalCtrl.DirtyAreaThreshold;
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
        root["EncoderParams"]["EncodeUnitToDist"] = signalCtrl.temp0;
        root["EncoderParams"]["EncodePulseFilterUs"] = signalCtrl.temp1;
        root["EncoderParams"]["EncodeRevolution"] = signalCtrl.temp9;
        root["EncoderParams"]["RollerPerimeterUm"] = signalCtrl.temp10;
        root["EncoderParams"]["ExpectSinglePixelAccuracy"] = signalCtrl.temp11;
        root["EncoderParams"]["RollerMaxSpeedToRowCount"] = signalCtrl.temp12;
        root["EncoderParams"]["EveryRowToEncodeCount"] = signalCtrl.temp13;
        //控制器参数
        root["ControllerParams"]["PixelAccuracyUm"] = signalCtrl.temp14;
        root["ControllerParams"]["PhotoelectricSignalPulseFilter"] = signalCtrl.temp15;
        root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"] = signalCtrl.temp16;
        root["ControllerParams"]["PhotoelectricToCamareDist"] = signalCtrl.temp17;
        root["ControllerParams"]["CamareFrameTrigerDelayRowCount"] = signalCtrl.temp18;
        root["ControllerParams"]["FrameSignalContinueTime"] = signalCtrl.temp19;
        root["ControllerParams"]["ModuleEnableSignal"] = signalCtrl.temp20;
        root["ControllerParams"]["CamarePhotoRowCount"] = signalCtrl.temp21;
        root["ControllerParams"]["InnerRowFrequency"] = signalCtrl.temp22;
        root["ControllerParams"]["PhotoMode"] = signalCtrl.tempAutoPhoto;
        root["ControllerParams"]["PhotoEndDelayRowCount"] = signalCtrl.tempPhotoEndDelayLine;
        //光源控制器参数
        root["LighterParams"]["LightField1DelayTime"] = signalCtrl.temp23;
        root["LighterParams"]["LightField1GlowTime"] = signalCtrl.temp24;
        root["LighterParams"]["LightField2DelayTime"] = signalCtrl.temp25;
        root["LighterParams"]["LightField2GlowTime"] = signalCtrl.temp26;
        root["LighterParams"]["LightField3DelayTime"] = signalCtrl.temp27;
        root["LighterParams"]["LightField3GlowTime"] = signalCtrl.temp28;
        root["LighterParams"]["LightField4DelayTime"] = signalCtrl.temp29;
        root["LighterParams"]["LightField4GlowTime"] = signalCtrl.temp30;
        root["LighterParams"]["SelectedLightFieldNumber"] = signalCtrl.temp55;
        root["LighterParams"]["HorizontalDarkfieldSelectRegister"] = signalCtrl.temp56;
        root["LighterParams"]["CamareAndLightFieldControl"] = signalCtrl.temp35;
        root["LighterParams"]["SignalSwitch"] = signalCtrl.temp36;
        root["LighterParams"]["RowSignalSelected"] = signalCtrl.temp37;
        // std::string json_content = writer.write(root);
        // std::ofstream ofs;
        // ofs.open(fullpath.toStdString().data());
        // if (ofs.is_open()) {
        //     ofs<<json_content;
        //     ofs.close();
        // }
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
    //自定义参数
    root["CustomParams"]["SaveOriginImage"] = signalCtrl.SaveOriginImage;
    root["CustomParams"]["SaveEntireImage"] = signalCtrl.SaveEntireImage;
    root["CustomParams"]["SaveFlawImage"] = signalCtrl.SaveFlawImage;
    root["CustomParams"]["SaveCropImage"] = signalCtrl.SaveCropImage;
    root["CustomParams"]["XYLengthEnable"] = signalCtrl.XYLengthEnable;
    root["CustomParams"]["FlawDefectEnable"] = signalCtrl.FlawDefectEnable;
    //缺陷检测
    root["DefectDetectionParams"]["Camera12PixelDeviation"] = signalCtrl.Camera12PixelDeviation;
    root["DefectDetectionParams"]["Camera23PixelDeviation"] = signalCtrl.Camera23PixelDeviation;
    root["DefectDetectionParams"]["Camera24PixelDeviation"] = signalCtrl.Camera24PixelDeviation;
    root["DefectDetectionParams"]["SilkToRollerDist"] = signalCtrl.SilkToRollerDist;
    root["DefectDetectionParams"]["ScratchAreaThreshold"] = signalCtrl.ScratchAreaThreshold;
    root["DefectDetectionParams"]["BubbleStoneAreaThreshold"] = signalCtrl.BubbleStoneAreaThreshold;
    root["DefectDetectionParams"]["DirtyAreaThreshold"] = signalCtrl.DirtyAreaThreshold;
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
    root["EncoderParams"]["EncodeUnitToDist"] = signalCtrl.temp0;
    root["EncoderParams"]["EncodePulseFilterUs"] = signalCtrl.temp1;
    root["EncoderParams"]["EncodeRevolution"] = signalCtrl.temp9;
    root["EncoderParams"]["RollerPerimeterUm"] = signalCtrl.temp10;
    root["EncoderParams"]["ExpectSinglePixelAccuracy"] = signalCtrl.temp11;
    root["EncoderParams"]["RollerMaxSpeedToRowCount"] = signalCtrl.temp12;
    root["EncoderParams"]["EveryRowToEncodeCount"] = signalCtrl.temp13;
    //控制器参数
    root["ControllerParams"]["PixelAccuracyUm"] = signalCtrl.temp14;
    root["ControllerParams"]["PhotoelectricSignalPulseFilter"] = signalCtrl.temp15;
    root["ControllerParams"]["CamareTrigerPulseContinueTime10ns"] = signalCtrl.temp16;
    root["ControllerParams"]["PhotoelectricToCamareDist"] = signalCtrl.temp17;
    root["ControllerParams"]["CamareFrameTrigerDelayRowCount"] = signalCtrl.temp18;
    root["ControllerParams"]["FrameSignalContinueTime"] = signalCtrl.temp19;
    root["ControllerParams"]["ModuleEnableSignal"] = signalCtrl.temp20;
    root["ControllerParams"]["CamarePhotoRowCount"] = signalCtrl.temp21;
    root["ControllerParams"]["InnerRowFrequency"] = signalCtrl.temp22;
    root["ControllerParams"]["PhotoMode"] = signalCtrl.tempAutoPhoto;
    root["ControllerParams"]["PhotoEndDelayRowCount"] = signalCtrl.tempPhotoEndDelayLine;
    //光源控制器参数
    root["LighterParams"]["LightField1DelayTime"] = signalCtrl.temp23;
    root["LighterParams"]["LightField1GlowTime"] = signalCtrl.temp24;
    root["LighterParams"]["LightField2DelayTime"] = signalCtrl.temp25;
    root["LighterParams"]["LightField2GlowTime"] = signalCtrl.temp26;
    root["LighterParams"]["LightField3DelayTime"] = signalCtrl.temp27;
    root["LighterParams"]["LightField3GlowTime"] = signalCtrl.temp28;
    root["LighterParams"]["LightField4DelayTime"] = signalCtrl.temp29;
    root["LighterParams"]["LightField4GlowTime"] = signalCtrl.temp30;
    root["LighterParams"]["SelectedLightFieldNumber"] = signalCtrl.temp55;
    root["LighterParams"]["HorizontalDarkfieldSelectRegister"] = signalCtrl.temp56;
    root["LighterParams"]["CamareAndLightFieldControl"] = signalCtrl.temp35;
    root["LighterParams"]["SignalSwitch"] = signalCtrl.temp36;
    root["LighterParams"]["RowSignalSelected"] = signalCtrl.temp37;

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
