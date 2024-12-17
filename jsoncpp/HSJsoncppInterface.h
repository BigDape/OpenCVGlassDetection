#ifndef HSJSONCPPINTERFACE_H
#define HSJSONCPPINTERFACE_H

#include <QString>
#include <QDateTime>
#include "HSTool.h"


namespace HSJsoncppNamespace {

    class HSJsoncppInterface
    {
    public:
        virtual ~HSJsoncppInterface(){}
        virtual void getFlawImageFromJson(QString jsonFileName,
                                  int GlassID,
                                  int defectid,
                                  QString& ImagePath1,
                                  QString& ImagePath2,
                                  QString& ImagePath3) = 0;

        virtual void readHoleFromJson(QString jsonFullPath, int glassid, QString& ImageHolesLinePath) = 0;

        virtual void readSizeSmallImage(QString jsonFileName, int GlassID, int row, QString& ImageHolesPath) = 0;

        //communication模块保存json
        virtual void writeComDataToJson(QString recipeFullpath, const SignalControl& data) = 0;

        //main创建空白json工单
        virtual void writeEmptyRecipeToJson(QString path) = 0;
        virtual void readRecipeFromJson(QString path, SignalControl& signalCtrl) = 0;
        virtual void writeRecipeToJson(QString fullpath, SignalControl signalCtrl) = 0;
        //更新json文件内容
        virtual void updateRecipeToJson(QString fullpath, SignalControl signalCtrl) = 0;
        //Cabrate创建空白json文件
        virtual void writeEmptyCalibrateToJson(QString path) = 0;
        virtual void readCalibrateFromJson(QString path, CropArgPackage& crop) = 0;
        virtual void writeCalibrateToJson(QString path, CropArgPackage crop) = 0;
    };
}

    // 用于创建对象的函数（DLL 导出函数）
    extern "C" __declspec(dllexport) HSJsoncppNamespace::HSJsoncppInterface* createJsoncppObject();


#endif // HSJSONCPPINTERFACE_H
