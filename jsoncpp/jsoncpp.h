#ifndef JSONCPP_H
#define JSONCPP_H

#include <json.h>
#include <QString>
#include <QDateTime>
#include "HSJsoncppInterface.h"

class Jsoncpp: public HSJsoncppNamespace::HSJsoncppInterface
{
public:
    virtual ~Jsoncpp(){}
    /**
     * @brief getFlawImageFromJson is get image path.
     * @param jsonFileName full path name, PS:D:/abc/2018-01-01.json
     * @param GlassID
     * @param defectid
     * @param ImagePath1
     * @param ImagePath2
     * @param ImagePath3
     */
    virtual void getFlawImageFromJson(QString jsonFileName,
                              int GlassID,
                              int defectid,
                              QString& ImagePath1,
                              QString& ImagePath2,
                              QString& ImagePath3) override;

    virtual void readHoleFromJson(QString jsonFullPath, int glassid, QString& ImageHolesLinePath) override;

    virtual void readSizeSmallImage(QString jsonFileName, int GlassID, int row, QString& ImageHolesPath) override;

    //communication模块保存json
    virtual void writeComDataToJson(QString recipeFullpath, const SignalControl& data) override;

    //main创建空白json工单
    virtual void writeEmptyRecipeToJson(QString path) override;
    virtual void readRecipeFromJson(QString path, SignalControl& signalCtrl) override;
    virtual void writeRecipeToJson(QString fullpath, SignalControl signalCtrl) override;
    //更新json文件内容
    virtual void updateRecipeToJson(QString fullpath, SignalControl signalCtrl) override;
    // Calibrate
    virtual void writeEmptyCalibrateToJson(QString path) override;
    virtual void readCalibrateFromJson(QString path, CropArgPackage& crop) override;
    virtual void writeCalibrateToJson(QString path, CropArgPackage crop) override;
};

#endif // JSONCPP_H
