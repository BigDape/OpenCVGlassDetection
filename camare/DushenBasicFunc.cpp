#include "DushenBasicFunc.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <opencv2/opencv.hpp>

CAThreadSafeUnorderedMap<dvpHandle,callbackDataStruct> DushenBasicFunc::MapSS;
CAThreadSafeUnorderedMap<dvpHandle,deepCopyStruct> DushenBasicFunc::MapDC;
int DushenBasicFunc::ImageLineSize = 0;

CameraNameSpace::HSCameraError DushenBasicFunc::InitCamera(DushenCameraArgs args)
{
    m_expo = args.expo;//曝光时间
    m_gain = args.gain;//相机增益
    m_height = args.height;//拍照行数
    m_framecount = (int)args.framecount;//帧次
    FieldNumberSet = args.fieldnumberset;//一共有多少个光场
    m_currentFriendlyName = args.camName;
    ImageLineSize = WIDTH_BYTES(8, 8192);// 计算图像一行需要多少字节
    //
    // 初始化数组指针
    //
    Last_Buffer = new byte*[FieldNumberSet];
    for (int i = 0; i < FieldNumberSet; i++) {
        Last_Buffer[i] = new byte[ImageLineSize * ImageOffset];
    }
    offsetBuffer0 = cv::Mat(ImageOffset,8192,CV_8UC1);
    offsetBuffer1 = cv::Mat(ImageOffset,8192,CV_8UC1);
    offsetBuffer2 = cv::Mat(ImageOffset,8192,CV_8UC1);

    m_currentIniPath = QDir::currentPath()+ "/SystemParam/" + m_currentFriendlyName + ".ini";//配置文件路径
    qDebug()<<"m_currentIniPath = "<<m_currentIniPath;
    DushenBasicFunc::ScanFunc(m_currentFriendlyName); //扫描
    return CameraNameSpace::HSCameraError::SUCCESS;
}


bool DushenBasicFunc::IsValidHandle(dvpHandle handle)
{
    bool bValidHandle;
    dvpIsValid(handle, &bValidHandle);
    return bValidHandle;
}

void DushenBasicFunc::IsMonoCamera(dvpHandle handle)
{
    dvpSensorInfo sSensorInfo;
    dvpStatus status = dvpGetSensorInfo(handle, &sSensorInfo);
    if (status == DVP_STATUS_OK) {
        if (SENSOR_PIXEL_MONO == sSensorInfo.pixel)
            bMono = true;
        else
            bMono = false;
    } else if (status != DVP_STATUS_OK) {
        QMessageBox::about(NULL, "About", "Get sensor information fail!");
    }
}

void DushenBasicFunc::InitSpinExpoTime()
{
    dvpDoubleDescr ExpoTimeDescr;
    dvpStatus status;

    if (IsValidHandle(m_handle)) {
        status = dvpGetExposureDescr(m_handle, &ExpoTimeDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get exposure time description fail!");
        }
        qDebug()<<"m_handle ="<<m_handle<<",m_expo ="<<m_expo;
        status = dvpSetExposure(m_handle, m_expo);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Set exposure time fail!");
        }
    }
}

void DushenBasicFunc::InitSpinGain()
{
    dvpStatus status;
    dvpFloatDescr AnalogGainDescr;

    if (IsValidHandle(m_handle)) {
        status = dvpGetAnalogGainDescr(m_handle, &AnalogGainDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get analog gain description fail!");
        }
        qDebug()<<"m_handle = "<<m_handle<<", m_gain ="<<m_gain;
        status = dvpSetAnalogGain(m_handle, m_gain);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Set analog gain fail!");
        }
    }
}

void DushenBasicFunc::InitImageHeight()
{
    dvpStatus status;

    if (IsValidHandle(m_handle)) {
        dvpRegion roi;
        status = dvpGetRoi(m_handle,&roi);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get ROI fail!");
        } else {
            qDebug()<<"m_handle ="<<m_handle<<",m_height ="<<m_height;
            roi.H = m_height;
            status = dvpSetRoi(m_handle,roi);
            if (status != DVP_STATUS_OK) {
                QMessageBox::about(NULL, "About", "Set ImageHeight fail!");
            }
            status = dvpGetRoi(m_handle,&roi);
            qDebug()<<"Height"<<roi.H;
        }
    }
}
void DushenBasicFunc::InitFrameCount()
{
    dvpStatus status;
    if (IsValidHandle(m_handle)) {
        qDebug()<<"m_handle ="<<m_handle<<", m_framecount="<<m_framecount;
        status = dvpSetFramesPerTrigger(m_handle, m_framecount);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "set framecount fail!");
        }
    }
}

void DushenBasicFunc::InitAETarget()
{
    dvpStatus status;
    QString strValue;
    dvpInt32 iAETarget;
    dvpIntDescr sAETargetDescr;

    if (IsValidHandle(m_handle)) {
        status = dvpGetAeTargetDescr(m_handle, &sAETargetDescr);
        if (status != DVP_STATUS_OK)
            QMessageBox::about(NULL, "About", "Get AE target description fails!");
        status = dvpGetAeTarget(m_handle, &iAETarget);
        if (status != DVP_STATUS_OK)
            QMessageBox::about(NULL, "About", "Get AE target fail!");
    }
}

void DushenBasicFunc::InitTrigger()
{
    dvpStatus status;
    if (IsValidHandle(m_handle)) {
        status = dvpGetTriggerState(m_handle, &m_SoftTriggerFlag);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get Trigger description fail!");
        }
    }
}

void DushenBasicFunc::InitROIMode()
{
    dvpStatus status;
    dvpSelectionDescr QuickRoiDescr;

    if (IsValidHandle(m_handle)) {
        // 获取相机分辨率索引号
        status = dvpGetQuickRoiSelDescr(m_handle, &QuickRoiDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get quick roi sel description fail!");
        } else {
            for (unsigned int iNum = 0; iNum < QuickRoiDescr.uCount; iNum++) {
                status = dvpGetQuickRoiSelDetail(m_handle, iNum, &QuickRoiDetail);
                QuickRoiDetailInfo[iNum] = (QString)QuickRoiDetail.selection.string;
                //                QuickRoiDetail++; //指针后移
            }
        }
        // 获取分辨率模式索引
        status = dvpGetResolutionModeSel(m_handle, &QuickRoiSel);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get roi sel fail!");
        }
    }
}

void DushenBasicFunc::InitTargetFormat()
{
    dvpStatus status;
    if (IsValidHandle(m_handle)) {
        status = dvpSetTargetFormat(m_handle, S_BGR24);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Set target format fail!");
        }
    }
}

void DushenBasicFunc::InitColorSolution()
{
    dvpSelection ColorSolutionDetail;
    dvpStatus status;
    dvpSelectionDescr ColorSolutionDescr;

    if (IsValidHandle(m_handle)) {
        if (bMono)
            return;
        // 获取索引号
        status = dvpGetColorSolutionSelDescr(m_handle, &ColorSolutionDescr);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get ColorSolutionDescr fail!");
        } else {
            for (unsigned int iNum = 0; iNum < ColorSolutionDescr.uCount; iNum++) {
                status = dvpGetColorSolutionSelDetail(m_handle, iNum, &ColorSolutionDetail);
            }
        }
        // 获取分辨率模式索引
        status = dvpGetColorSolutionSel(m_handle, &ColorSolutionSel);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get ColorSolutionSel fail!");
        }
    }
}



int DushenBasicFunc::WIDTH_BYTES(int BitCount, int Width)
{
    int nwBytePerLine;
    nwBytePerLine = (Width * BitCount + 31) / 32 * 4;
    return nwBytePerLine;
}

unsigned int DushenBasicFunc::getCameraCounts()
{
    return (unsigned int)m_CameraCounts;
}

std::vector<QString> DushenBasicFunc::getCameraFriendlyNames()
{
    std::vector<QString> res ={};
    for (int i = 0; i < (int)m_CameraCounts; i++) {
        res.push_back( info[i].FriendlyName);
    }
    return res;
}

QString DushenBasicFunc::getCurrentCameraFriendlyName()
{
    return m_currentFriendlyName;
}

bool DushenBasicFunc::IsScanned(const QString FriendlyName)
{
    if(m_currentFriendlyName == FriendlyName) {
        return m_IsScanned;
    } else {
        return false;
    }
}

bool DushenBasicFunc::IsOpened(const QString FriendlyName)
{
    if(m_currentFriendlyName == FriendlyName) {
        return m_IsOpened;
    } else {
        return false;
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::StopFunc(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        if (m_handle != 0) {
            dvpStatus status = dvpStop(m_handle);
            if (status == DVP_STATUS_OK) {
                m_IsStarted = false;
                return CameraNameSpace::HSCameraError::SUCCESS;
            } else {
                return (CameraNameSpace::HSCameraError::INNER_ERROR);
            }
        } else {
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }
    } else {
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::Closefunc(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        if (!m_IsOpened || m_handle == 0) {
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }

        dvpGetStreamState(m_handle, &state);
        if (state == STATE_STARTED) {
            StopFunc(m_currentFriendlyName);
        }
        dvpSaveConfig(m_handle, 0);
        dvpClose(m_handle);
        m_handle = 0;
        m_IsOpened = false;
        return CameraNameSpace::HSCameraError::SUCCESS;
    } else {
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

bool DushenBasicFunc::SearchCamera(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        if (m_IsScanned ==  false) {
            return false;
        }

        for (dvpUint32 i = 0; i < m_CameraCounts; i++) {
            if (m_currentFriendlyName == QString(info[i].FriendlyName)) {
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::OpenFunc(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        dvpStatus status;

        if (m_IsScanned ==  false) {
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }

        if (!DushenBasicFunc::IsValidHandle(m_handle)) {
            //
            // 获取相机句柄
            //
            status = dvpOpenByName(FriendlyName.toLatin1().data(), OPEN_NORMAL, &m_handle);
            if (status != DVP_STATUS_OK) {
                return (CameraNameSpace::HSCameraError::INNER_ERROR);
            }
            //一系列初始化流程
            DushenBasicFunc::IsMonoCamera(m_handle);
            DushenBasicFunc::InitTrigger();
            DushenBasicFunc::InitAETarget();
            DushenBasicFunc::InitROIMode();
            DushenBasicFunc::InitTargetFormat();
            DushenBasicFunc::InitColorSolution();

            status = dvpGetStreamState(m_handle, &state);
            if (status != DVP_STATUS_OK) {
                return (CameraNameSpace::HSCameraError::INNER_ERROR);
            }
            if (state == STATE_STARTED) {
                status = dvpStop(m_handle);
            }

            m_IsOpened = true;

            // 初始化MapSS结构体
            std::queue<callbackDataStruct> initData;
            DushenBasicFunc::MapSS.insert(m_handle, initData);
            std::queue<deepCopyStruct> newinitData;
            DushenBasicFunc::MapDC.insert(m_handle, newinitData);

            return (CameraNameSpace::HSCameraError::SUCCESS);
        } else {
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }
    } else {
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::LoadIni(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        dvpStatus status = dvpLoadConfig(m_handle, m_currentIniPath.toStdString().c_str());
        if (status != DVP_STATUS_OK) {
            return CameraNameSpace::HSCameraError::INNER_ERROR;
        }
        return CameraNameSpace::HSCameraError::SUCCESS;

    } else {
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::ScanFunc(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        m_IsScanned = false;
        if (!m_IsScanned) {
            dvpStatus status = dvpRefresh(&m_CameraCounts);

            if (status == DVP_STATUS_OK) {
                //
                // 查询m_currentFriendlyName名称，以防构造参数错误
                //
                bool is_exist_m_currentFriendlyName = false;
                for (dvpUint32 i = 0; i < m_CameraCounts; i++) {
                    dvpEnum(i, &info[i]);
                    if ( info[i].FriendlyName == m_currentFriendlyName) {
                        is_exist_m_currentFriendlyName = true;
                    }
                }
                // 则将m_currentFriendlyName设置为NULL
                if(is_exist_m_currentFriendlyName == false) {
                    m_currentFriendlyName =  QString();
                }
                m_IsScanned = true;
                return (CameraNameSpace::HSCameraError::SUCCESS);
            } else {
                m_IsScanned = false;
                return (CameraNameSpace::HSCameraError::INNER_ERROR);
            }
        } else {
            m_IsScanned = false;
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }
    } else {
        m_IsScanned = false;
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::ShowProperty(const QString FriendlyName,HWND windowsID)
{
    if (m_currentFriendlyName == FriendlyName) {
        if (IsValidHandle(m_handle)) {
#ifdef Q_OS_WIN32
            dvpShowPropertyModalDialog(m_handle, windowsID);
#endif
            return (CameraNameSpace::HSCameraError::SUCCESS);
        } else {
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }
    } else {
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::TriggerFunc(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        bool triggerState = false;

        dvpStatus status = dvpGetTriggerState(m_handle, &triggerState);
        if (status != DVP_STATUS_FUNCTION_INVALID) {
            status = dvpTriggerFire(m_handle);
            if (status != DVP_STATUS_OK) {
                return (CameraNameSpace::HSCameraError::INNER_ERROR);
            }
            return (CameraNameSpace::HSCameraError::SUCCESS);
        } else {
           return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }
    } else {
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::SaveIni(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        dvpStatus status = dvpSaveConfig(m_handle, m_currentIniPath.toStdString().c_str());
        if (DVP_STATUS_OK != status) {
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }
        return (CameraNameSpace::HSCameraError::SUCCESS);
    } else {
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::setFieldSelectedView(int field)
{
    if(field >= 0) {
        m_FieldSelectedView = field;
        return (CameraNameSpace::HSCameraError::SUCCESS);
    } else {
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

CameraNameSpace::HSCameraError DushenBasicFunc::setSoftTriggerFlag(bool flag)
{
    m_SoftTriggerFlag = flag;
    return (CameraNameSpace::HSCameraError::SUCCESS);
}

CameraNameSpace::HSCameraError DushenBasicFunc::StartFunc(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        if (m_IsOpened == false) {
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }

        if (IsValidHandle(m_handle)) {
            // 注册回调函数OnGetFrame，需要在dvpstart函数调用之前
            dvpStatus status1 = dvpRegisterStreamCallback(m_handle, DushenBasicFunc::OnGetFrame, STREAM_EVENT_FRAME_THREAD, NULL);
            if (status1 != DVP_STATUS_OK)
            {
                qDebug()<<"dvpRegisterStreamCallback failed with err:"<< status1;
            }

            dvpStatus status = dvpGetStreamState(m_handle, &state);
            if (status != DVP_STATUS_OK) {
                return (CameraNameSpace::HSCameraError::INNER_ERROR);
            }
            if (state == STATE_STOPED) {
                status = dvpGetTriggerState(m_handle, &bTrigStatus);
                if (status != DVP_STATUS_FUNCTION_INVALID) {
                    // 在启动视频流之前先设置为触发模式
                    status = dvpSetTriggerState(m_handle, m_SoftTriggerFlag ? true : false);
                    if (status != DVP_STATUS_OK) {
                        return (CameraNameSpace::HSCameraError::INNER_ERROR);
                    }
                }
                status = dvpStart(m_handle);
                if (status != DVP_STATUS_OK) {
                    return (CameraNameSpace::HSCameraError::INNER_ERROR);
                } else {
                    DushenBasicFunc::InitSpinExpoTime();        //初始化曝光时间
                    DushenBasicFunc::InitSpinGain();            //初始化增益
                    DushenBasicFunc::InitImageHeight();         //初始化相机高度；
                    DushenBasicFunc::InitFrameCount();          //初始化帧次；
                    m_IsStarted = true;
                }
            }
            return (CameraNameSpace::HSCameraError::SUCCESS);
        } else {
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }
    } else {
        return (CameraNameSpace::HSCameraError::INVALID_PARAMETER);
    }
}

bool DushenBasicFunc::IsStarted(const QString FriendlyName)
{
    qDebug()<<"FriendlyName ="<<FriendlyName
             <<",m_currentFriendlyName="<<m_currentFriendlyName
             <<",m_IsStarted =" <<m_IsStarted;
    if (m_currentFriendlyName == FriendlyName) {
        return m_IsStarted;
    } else {
        return false;
    }
}

bool DushenBasicFunc::GetCameraState(const QString FriendlyName)
{
    if (m_currentFriendlyName == FriendlyName) {
        dvpStreamState state;
        dvpStatus status = dvpGetStreamState(m_handle, &state);
        if (status != DVP_STATUS_OK) {
            return false;
        }
        if (state == STATE_STOPED) {
            CameraState = false;
        }
        if (state == STATE_STARTED) {
            CameraState = true;
        }
        return true;
    } else {
        return false;
    }
}

QString DushenBasicFunc::DispRate()
{
    if (IsValidHandle(m_handle)) {
        //更新帧率信息
        dvpStatus status = dvpGetFrameCount(m_handle, &FrameCount);
        if (status != DVP_STATUS_OK) {
            QMessageBox::about(NULL, "About", "Get frame count fail!");
        }
        QString strFrameCount = QString::number(FrameCount.uFrameCount);    // 采集帧数
        QString strFrameRate = QString::number(FrameCount.fFrameRate);      // 图像帧率
        return strFrameRate; //更新窗口上的帧率
    } else {
        return QString();
    }
}

QImage DushenBasicFunc::DispImage()
{
   //todo:更新一次图片，显示一次
   return m_ShowImage; //图像数据到显示控件
}

CameraNameSpace::HSCameraError DushenBasicFunc::startGetFrameBuffer(FrameImage& imageunit)
{
    bool isEmpty = DushenBasicFunc::MapDC.empty(m_handle);
    if (isEmpty == false) {
        deepCopyStruct data = DushenBasicFunc::MapDC.pop(m_handle);
        if (data.uFrameID == 0) {
            return (CameraNameSpace::HSCameraError::INNER_ERROR);
        }
        try{
            imageunit.framecount = data.uFrameID;           // 相机的帧号 从1开始递增
            imageunit.fieldnumberset = FieldNumberSet;      // 光场的数量

            int FrameWidth = data.iWidth;                           //单通道图像宽度
            int FrameHeight= data.iHeight / FieldNumberSet;                     //单通道图像高度


            if (FrameHeight <= ImageOffset) {
                qDebug()<<"图片太小，不能多场分离！";
                return (CameraNameSpace::HSCameraError::INNER_ERROR);
            }

            if (data.uFrameID > 1) {
                cv::vconcat(offsetBuffer0, data.buffer0, data.buffer0);
                cv::vconcat(offsetBuffer1, data.buffer1, data.buffer1);
                cv::vconcat(offsetBuffer2, data.buffer2, data.buffer2);
            }

            cv::Rect rect0(0, data.buffer0.rows - ImageOffset, data.buffer0.cols, ImageOffset);
            cv::Rect rect1(0, data.buffer1.rows - ImageOffset, data.buffer1.cols, ImageOffset);
            cv::Rect rect2(0, data.buffer2.rows - ImageOffset, data.buffer2.cols, ImageOffset);
            offsetBuffer0 = data.buffer0(rect0);
            offsetBuffer1 = data.buffer1(rect1);
            offsetBuffer2 = data.buffer2(rect2);

            imageunit.buffers.push_back(data.buffer0);
            imageunit.buffers.push_back(data.buffer1);
            imageunit.buffers.push_back(data.buffer2);
            QString path;
            path = "D:/testopencv/camera/handle"+QString::number(m_handle) +"_Field0_FrameID"+QString::number(data.uFrameID) + ".jpg";
            DushenBasicFunc::SyncSaveCurrentTimeImage(data.buffer0,path);
            qDebug() <<"handle:("<<m_handle<<")"<<",Field[0],"
                            <<"data.uFrameID["<<data.uFrameID
                            <<"] => { FieldNumberSet = "<<FieldNumberSet
                            <<",FrameWidth = " <<FrameWidth
                            <<",FrameHeight = "<<FrameHeight
                            <<",ImageOffset = "<<ImageOffset
                            <<",path = "<<path
                            <<",imageunit.buffers.size() = "<<imageunit.buffers.size()<<"}";
            path = "D:/testopencv/camera/handle"+QString::number(m_handle) +"_Field1_FrameID"+QString::number(data.uFrameID) + ".jpg";
            DushenBasicFunc::SyncSaveCurrentTimeImage(data.buffer1,path);
            qDebug() <<"handle:("<<m_handle<<")"<<",Field[1],"
                     <<"data.uFrameID["<<data.uFrameID
                     <<"] => { FieldNumberSet = "<<FieldNumberSet
                     <<",FrameWidth = " <<FrameWidth
                     <<",FrameHeight = "<<FrameHeight
                     <<",ImageOffset = "<<ImageOffset
                     <<",path = "<<path
                     <<",imageunit.buffers.size() = "<<imageunit.buffers.size()<<"}";
            path = "D:/testopencv/camera/handle"+QString::number(m_handle) +"_Field2_FrameID"+QString::number(data.uFrameID) + ".jpg";
            DushenBasicFunc::SyncSaveCurrentTimeImage(data.buffer2,path);
            qDebug() <<"handle:("<<m_handle<<")"<<",Field[2],"
                     <<"data.uFrameID["<<data.uFrameID
                     <<"] => { FieldNumberSet = "<<FieldNumberSet
                     <<",FrameWidth = " <<FrameWidth
                     <<",FrameHeight = "<<FrameHeight
                     <<",ImageOffset = "<<ImageOffset
                     <<",path = "<<path
                     <<",imageunit.buffers.size() = "<<imageunit.buffers.size()<<"}";
        } catch(...) {
            qDebug()<<"catch a unknow exception";
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
        return CameraNameSpace::HSCameraError::SUCCESS;
    }
    return (CameraNameSpace::HSCameraError::INNER_ERROR);
}

dvpInt32  DushenBasicFunc::OnGetFrame(dvpHandle handle, dvpStreamEvent event, void* pContext, dvpFrame* pFrame, void* pBuffer)
{
    if (pFrame->iHeight % 3 != 0) {
        pFrame->iHeight = pFrame->iHeight - (pFrame->iHeight % 3);
    }

    // callbackDataStruct data;
    deepCopyStruct data;
    data.format = pFrame->format;
    data.uFrameID = pFrame->uFrameID;
    data.iHeight = pFrame->iHeight;
    data.iWidth = pFrame->iWidth;
    data.uBytes = pFrame->uBytes;
    data.uTimestamp = pFrame->uTimestamp;

    qDebug()<<"data.iHeight/3 ="<<data.iHeight/3<<", data.iWidth ="<<data.iWidth;
    cv::Mat projectionLMat(data.iHeight/3,data.iWidth,CV_8UC1);
    cv::Mat reflectionLMat(data.iHeight/3,data.iWidth,CV_8UC1);
    cv::Mat reflectionDMat(data.iHeight/3,data.iWidth,CV_8UC1);
    // 图片重组
    for (int HeightCount = 0; HeightCount < data.iHeight; HeightCount++) {
        const byte* destBufferScanLine = reinterpret_cast<const byte*>((byte*)pBuffer + HeightCount * ImageLineSize);// 原始图像上一行数据
        byte* cvMatScanLine;
        if (HeightCount % 3 == 0) {// 投射亮场
            cvMatScanLine = projectionLMat.ptr<byte>(HeightCount/3);// 透射场图片一行图片
        }
        if (HeightCount % 3 == 1) {// 反射亮场
            cvMatScanLine = reflectionLMat.ptr<byte>(HeightCount/3);// 透射场图片一行图片
        }
        if (HeightCount % 3 == 2) {// 反射暗场
            cvMatScanLine = reflectionDMat.ptr<byte>(HeightCount/3);// 透射场图片一行图片
        }
        memcpy(cvMatScanLine, destBufferScanLine, data.iWidth * sizeof(byte));
    }
    data.buffer0 = projectionLMat;
    data.buffer1 = reflectionLMat;
    data.buffer2 = reflectionDMat;

    DushenBasicFunc::MapDC.push(handle, data);
    return 0;
}


QString DushenBasicFunc::SyncSaveCurrentTimeImage(cv::Mat& region,QString path/*=""*/)
{
    try{
        if (path == "") {
            int randomNumber = std::rand() % 123567;
            QString time = QDateTime::currentDateTime().toString("hh-mm-ss");
            path = "D:/testopencv/camera/"+time +"-"+ QString::number(randomNumber)+".jpg";
        }
        std::thread th1(&DushenBasicFunc::saveMatToImage,this,path,region);
        th1.detach();
        return path;
    } catch(...) {
        qDebug() << " ProcessTile::SyncSaveCurrentTimeImage =>An unknown error occurred.";
        // 获取当前的异常信息
        std::exception_ptr eptr = std::current_exception();
        if (eptr) {
            try {
                std::rethrow_exception(eptr);
            } catch (const std::exception& ex) {
                qDebug() << "Exception: " << ex.what();
            }
        }
        return "";
    }
}

void DushenBasicFunc::saveMatToImage(QString fullpath,cv::Mat region )
{
    std::string filename = fullpath.toStdString();
    cv::imwrite(filename, region);
}
