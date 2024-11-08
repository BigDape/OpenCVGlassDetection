/** @mainpage ����
*
*@section �����ѧ
*-# �����ã��ȶ��ɿ�
*-# �ӿ�ϸ������������һ�����������;����������ַ���C/C++��Ϊ��̬���ԣ��ڱ�����ǿ������������
*-# ��Ȼ�����ӿ��ڶ࣬���߶��������б�Ҫ���ɽ�������������ĺ��������õ�һ�����ƺͺ���ָ���Ӧ��map�У���ʵ�ָ������Ķ�̬����
*
*@section ��������
*-# ��@link #DVP_INFORMATION ��Ԥ��@endlink������£���ȷ�����б�׼API����@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink��Ʃ�磬����Ժڰ�������ò�ɫ������е����ԣ�������������߳���Ľ�׳��
*-# ����<a href="C:/Program Files (x86)/Do3think/BasedCam2">Basedcam2</a>�ٷ���ʾ����ġ�������ģʽ�����������ڼ����ÿ��API�ӿڵĹ��ܺ�Ӧ�õ�����
*-# �������API�ӿڶ�������@link #DVP2_API_BASE ��������@endlink�����¡��������ڿ��ٰ�������ĺ��Ĺ���
*-# �ο�@link #CaptureImage CaptureImage@endlinkʾ�����������ڿ�������
*-# Ӧ���ѻ�õ�@link #dvpHandle dvpHandle@endlink ֵ���������
*-# ����ֱ���Ķ�ͷ�ļ����ο�chm�ĵ�����ø����Ѻõ�����
*
*@section ��˾��ַ
* http://www.do3think.com
*
*@section ��ǰAPI
* @version Version 2.24.42.1248(build: Nov 18 2021 13:45:58)
*
*
*@section �ĵ�������¼
*@subsection Ver1 2016-4-1(2.5.12)
*-# ������һ���汾
*@subsection Ver2 2016-10-31(2.7.8)
*-# ����@link #dvpGetCurveLut ����LUT@endlink����
*-# ����@link #dvpColorCorrection ��ɫУ������@endlink�Ķ�д����
*-# ����@link #dvpCaptureFile ��ָ���ֱ���ģʽ��ROI��ץͼ������ͼ��@endlink�Ĺ���
*-# ����@link #dvpGetRotateOpposite ͼ�����/��90����ת@endlink�Ĺ���
*-# ��չ��@link #dvpFrame ֡��Ϣ�ṹ��@endlink�������˷�ת����ת�ȱ�ʶ
*@subsection Ver3 2016-11-29(2.8.9)
*-# ����@link #dvpSetAeConfig �Զ��ع�����@endlink����
*-# ����@link #dvpEventCallback �¼�֪ͨ�ص�����@endlink����
*-# ����@link #dvpGetFrameBuffer ͬʱ����ԭʼ�ɼ�֡��Ŀ�����֡@endlink�Ĺ���
*@subsection Ver4 2017-02-08(2.9.13)
*-# ����@link #dvpResetDevice ��λ�豸@endlink�Ĺ���
*@subsection Ver5 2017-03-22(2.10.16)
*-# ����@link #dvpSetAutoDefectFixState ʹ���Զ������ʵ�@endlink�Ĺ���
*@subsection Ver6 2017-05-12(2.11.18)
*-# ����@link #dvpHold �жϴ�������ͼ��ɼ�@endlink�Ĺ���
*-# ����@link #dvpSetHardwareIspState ���Ӳ��ISPʹ��@endlink�Ĺ���
*@subsection Ver7 2017-06-16(2.12.19)
*-# ����@link #dvpGetFunctionInfo ��ȡ�������������Ϣ@endlink�Ľӿ�
*-# ����@link #dvpImageFormat::FORMAT_RGB32 RGB32ͼ���ʽ@endlink�����֧��
*@subsection Ver8 2017-06-30(2.13.20)
*-# ����@link #dvpSetConfigString ��������ַ�������@endlink�Ľӿ�
*@subsection Ver9 2017-07-17(2.14.21)
*-# ������@link #dvpStreamFormat ��������ʽ@endlink�Ķ���
*@subsection Ver 2017-09-15(2.15.24)
*-# �����˸���@link #dvpCameraInfo::UserID �û�����@endlink��@link #dvpOpenByUserId �����@endlink�Ĺ���
*-# �����˼���@link #dvpLoadUserSet �û�����@endlink�Ĺ���
*@subsection Ver10 2018-04-11(2.16.32)
*-# ���������û��߳���@link #dvpProcessImage ����ͼ��@endlink�Ĺ���
*@subsection Ver11 2018-08-3(2.17.33)
*-# ������һ��@link #dvpLine �������@endlink������صĽӿڣ��������ʹ��dvpInputIo��dvpOutputIoϵ�еĽӿ�
*-# ������@link #dvpSetTriggerSource ���ô���Դ@endlink�Ľӿ�
*@subsection Ver12 2019-03-12(2.18.35)
*-# ������@link #dvpSetBufferQueueSize ����֡�������@endlink�Ľӿ�
*@subsection Ver13 2019-08-6(2.19.37)
*-# ������@link #dvpSetBufferConfig ����֡�������@endlink�Ľӿ�
*@subsection Ver14 2019-09-3(2.20.38)
*-# ������@link #dvpDebugReport �����������״̬@endlink�Ľӿ�
*@subsection Ver15 2021-11-15(2.24.42)
*-# ������@link #dvpSetLineRate ������ɨ�����Ƶ����@endlink�Ľӿ�
*-# ������@link #dvpSetLineTriggerConfig ������ɨ�����������@endlink�Ľӿ�
*/
#ifndef __DVPCAMERA_H__
#define __DVPCAMERA_H__

#define dvpPtr(ptr) ptr*

#ifndef __cplusplus
#define bool unsigned char
#define false (0)
#define true  (1)
#endif

#ifndef _WIN32
#ifndef __cplusplus
#define dvp2api extern
#else
#define dvp2api extern "C"
#endif
#else
#include <windows.h>
#ifndef __cplusplus
#define dvp2api extern     __declspec(dllimport)
#else
#define dvp2api extern "C" __declspec(dllimport)
#endif
#endif

dvp2api const unsigned int dvpVersion[4];
/** @brief ͼ���ʽ
*@see dvpGetFrame*/
typedef enum dvpImageFormat
{
    /** @brief �ڰ�ͼ�� */
    FORMAT_MONO = 0,

    /** @brief BGGRͼ�� */
    FORMAT_BAYER_BG = 1,

    /** @brief GBRGͼ�� */
    FORMAT_BAYER_GB = 2,

    /** @brief GRBGͼ�� */
    FORMAT_BAYER_GR = 3,

    /** @brief RGGBͼ�� */
    FORMAT_BAYER_RG = 4,

    /** @brief BGR��ͨ��24����ͼ�� */
    FORMAT_BGR24 = 10,

    /** @brief BGRA��ͨ��32����ͼ�� */
    FORMAT_BGR32 = 11,

    /** @brief BGR��ͨ��48����ͼ�� */
    FORMAT_BGR48 = 12,

    /** @brief BGRA��ͨ��64����ͼ�� */
    FORMAT_BGR64 = 13,

    /** @brief RGB��ͨ��24����ͼ�� */
    FORMAT_RGB24 = 14,

    /** @brief RGBA��ͨ��32����ͼ�� */
    FORMAT_RGB32 = 15,

    /** @brief RGB��ͨ��48����ͼ�� */
    FORMAT_RGB48 = 16,

    /** @brief YUV411 */
    FORMAT_YUV411 = 20,

    /** @brief YUV422 */
    FORMAT_YUV422 = 21,

    /** @brief YUV444 */
    FORMAT_YUV444 = 22,

    /** @brief YUV420 */
    FORMAT_YUV420 = 23,

    /** @brief BGR��ͨ��8���ز�ֵ�ͼ�� */
    FORMAT_B8_G8_R8 = 40,

    /** @brief BGR��ͨ��16���ز�ֵ�ͼ�� */
    FORMAT_B16_G16_R16 = 44,

} dvpImageFormat;


/** @brief ��������ʽ
*@see dvpSetSourceFormat
*@see dvpSetTargetFormat
*@warning ��һ�����и�ʽ��֧��
*@note����������Ƽ�ʹ�� #dvpSetSourceFormatSel �� #dvpSetTargetFormatSel ϵ�нӿ�*/
typedef enum dvpStreamFormat
{
    /** @brief 8λͼ�� */
    S_RAW8 = 0,

    /** @brief 10λͼ�� */
    S_RAW10 = 1,

    /** @brief 12λͼ�� */
    S_RAW12 = 2,

    /** @brief 14λͼ�� */
    S_RAW14 = 3,

    /** @brief 16λͼ�� */
    S_RAW16 = 4,

    /** @brief BGR��ͨ��24����ͼ�� */
    S_BGR24 = 10,

    /** @brief BGRA��ͨ��32����ͼ�� */
    S_BGR32 = 11,

    /** @brief BGRA��ͨ��48����ͼ�� */
    S_BGR48 = 12,

    /** @brief BGRA��ͨ��64����ͼ�� */
    S_BGR64 = 13,

    /** @brief RGB��ͨ��24����ͼ�� */
    S_RGB24 = 14,

    /** @brief RGBA��ͨ��32����ͼ�� */
    S_RGB32 = 15,

    /** @brief RGBA��ͨ��48����ͼ�� */
    S_RGB48 = 16,

    /** @brief RGBA��ͨ��64����ͼ�� */
    S_RGB64 = 17,

    /** @brief YUV411 */
    S_YUV411 = 20,

    /** @brief YUV422 */
    S_YUV422 = 21,

    /** @brief YUV444 */
    S_YUV444 = 22,

    /** @brief YUV444 */
    S_YUV420 = 23,

    /** @brief 8λ�Ҷ�ͼ�� */
    S_MONO8 = 30,

    /** @brief 10λ�Ҷ�ͼ�� */
    S_MONO10 = 31,

    /** @brief 12λ�Ҷ�ͼ�� */
    S_MONO12 = 32,

    /** @brief 14λ�Ҷ�ͼ�� */
    S_MONO14 = 33,

    /** @brief 16λ�Ҷ�ͼ�� */
    S_MONO16 = 34,

    /** @brief BGR��ͨ��8���ز�ֵ�ͼ�� */
    S_B8_G8_R8 = 40,

    /** @brief BGR��ͨ��16���ز�ֵ�ͼ�� */
    S_B16_G16_R16 = 44,

} dvpStreamFormat;


/** @brief ͼ��λ��
*@see dvpGetFrame*/
typedef enum dvpBits
{
    /** @brief 8�������� */
    BITS_8 = 0,

    /** @brief 10�������� */
    BITS_10 = 1,

    /** @brief 12�������� */
    BITS_12 = 2,

    /** @brief 14�������� */
    BITS_14 = 3,

    /** @brief 16�������� */
    BITS_16 = 4,

} dvpBits;


/** @brief �Զ��ع�ģʽ*/
typedef enum dvpAeMode
{
    /** @brief �Զ��ع⣬�Զ�����ͬʱ�������ع����� */
    AE_MODE_AE_AG = 0,

    /** @brief �Զ��ع⣬�Զ�����ͬʱ�������������� */
    AE_MODE_AG_AE = 1,

    /** @brief �Զ��ع� */
    AE_MODE_AE_ONLY = 2,

    /** @brief �Զ����� */
    AE_MODE_AG_ONLY = 3,

} dvpAeMode;


/** @brief �Զ��ع����*/
typedef enum dvpAeOperation
{
    /** @brief ���ܹر� */
    AE_OP_OFF = 0,

    /** @brief ����һ�� */
    AE_OP_ONCE = 1,

    /** @brief �������� */
    AE_OP_CONTINUOUS = 2,

} dvpAeOperation;


/** @brief �Զ���ƽ�����*/
typedef enum dvpAwbOperation
{
    /** @brief ���ܹر� */
    AWB_OP_OFF = 0,

    /** @brief ����һ�� */
    AWB_OP_ONCE = 1,

    /** @brief �������� */
    AWB_OP_CONTINUOUS = 2,

} dvpAwbOperation;


/** @brief �ƹ�Ƶ��*/
typedef enum dvpAntiFlick
{
    /** @brief ��ֹ����Ƶ�� */
    ANTIFLICK_DISABLE = 0,

    /** @brief ����50hzƵ�� */
    ANTIFLICK_50HZ = 1,

    /** @brief ����60hzƵ�� */
    ANTIFLICK_60HZ = 2,

} dvpAntiFlick;


/** @brief ����������*/
typedef enum dvpSensorType
{
    /** @brief CMOSͼ�񴫸��� */
    SENSOR_TYPE_CMOS = 0,

    /** @brief CCDͼ�񴫸��� */
    SENSOR_TYPE_CCD = 1,

} dvpSensorType;


/** @brief ��������������*/
typedef enum dvpSensorPixel
{
    /** @brief �ڰ����� */
    SENSOR_PIXEL_MONO = 0,

    /** @brief RGGB��ɫ���� */
    SENSOR_PIXEL_BAYER_RG = 1,

    /** @brief GBRG��ɫ���� */
    SENSOR_PIXEL_BAYER_GB = 2,

    /** @brief GRBG��ɫ���� */
    SENSOR_PIXEL_BAYER_GR = 3,

    /** @brief BGGR��ɫ���� */
    SENSOR_PIXEL_BAYER_BG = 4,

} dvpSensorPixel;


/** @brief ��Ƶ���ص��¼�*/
typedef enum dvpStreamEvent
{
    /** @brief ͼ��ﵽ�� */
    STREAM_EVENT_ARRIVED = 0,

    /** @brief ͼ��У���� */
    STREAM_EVENT_CORRECTED = 1,

    /** @brief ͼ������ */
    STREAM_EVENT_PROCESSED = 2,

    /** @brief ����һ��ר�ŵ��߳���@link #dvpGetFrame dvpGetFrame@endlink �ķ�ʽ��ȡͼ�񣬲����������û��������� 
*@warning ����@link #dvpStart ������Ƶ��@endlink֮ǰ���ú�
*@see dvpProcessImage */
    STREAM_EVENT_FRAME_THREAD = 3,

} dvpStreamEvent;


/** @brief ��ͨ�¼�*/
typedef enum dvpEvent
{
    /** @brief δ֪�� */
    EVENT_UNKNOW = 0,

    /** @brief ���ӳɹ� */
    EVENT_CONNECTED = 1,

    /** @brief �Ͽ����� */
    EVENT_DISCONNECTED = 2,

    /** @brief �������Ѿ����� */
    EVENT_STREAM_STARTRD = 3,

    /** @brief �������Ѿ�ֹͣ */
    EVENT_STREAM_STOPPED = 4,

    /** @brief ��֡(����֡) */
    EVENT_FRAME_LOST = 5,

    /** @brief �ȴ�֡��ʱ */
    EVENT_FRAME_TIMEOUT = 6,

    /** @brief ʧȥ���� */
    EVENT_LOST_CONNECTION = 7,

    /** @brief �������� */
    EVENT_RECONNECTED = 8,

    /** @brief ֡��ʼ���� */
    EVENT_FRAME_START = 9,

    /** @brief ֡�������� */
    EVENT_FRAME_END = 10,

} dvpEvent;


/** @brief ���������ź�����*/
typedef enum dvpTriggerInputType
{
    /** @brief ��������ر� */
    TRIGGER_IN_OFF = 0,

    /** @brief �½��ش��� */
    TRIGGER_NEG_EDGE = 1,

    /** @brief �͵�ƽ���� */
    TRIGGER_LOW_LEVEL = 2,

    /** @brief �����ش��� */
    TRIGGER_POS_EDGE = 3,

    /** @brief �ߵ�ƽ���� */
    TRIGGER_HIGH_LEVEL = 4,

} dvpTriggerInputType;


/** @brief Strobe����ź�����*/
typedef enum dvpStrobeOutputType
{
    /** @brief Strobe����ر� */
    STROBE_OUT_OFF = 0,

    /** @brief ����͵�ƽ */
    STROBE_OUT_LOW = 1,

    /** @brief ����ߵ�ƽ */
    STROBE_OUT_HIGH = 2,

} dvpStrobeOutputType;


/** @brief Strobe�ź�������ʽ*/
typedef enum dvpStrobeDriver
{
    /** @brief ����֡���ڶ���Ч */
    FRAME_DURATION = 0,

    /** @brief �ɶ�ʱ������ */
    TIMER_LOGIC = 1,

    /** @brief ����SENSOR��Strobe�ź� */
    SENSOR_STROBE = 2,

} dvpStrobeDriver;


/** @brief ���ģʽ
*@deprecated*/
typedef enum dvpOutputIoFunction
{
    /** @brief ��ͨ��� */
    OUTPUT_FUNCTION_NORMAL = 0x0000,

    /** @brief �������� */
    OUTPUT_FUNCTION_STROBE = 0x0001,

} dvpOutputIoFunction;


/** @brief ����ģʽ
*@deprecated*/
typedef enum dvpInputIoFunction
{
    /** @brief ��ͨ���� */
    INPUT_FUNCTION_NORMAL = 0x8001,

    /** @brief �������� */
    INPUT_FUNCTION_TRIGGER = 0x8002,

} dvpInputIoFunction;


/** @brief ���IO
*@deprecated*/
typedef enum dvpOutputIo
{
    /** @brief ���1 */
    OUTPUT_IO_1 = 0x0001,

    /** @brief ���2 */
    OUTPUT_IO_2 = 0x0002,

    /** @brief ���3 */
    OUTPUT_IO_3 = 0x0003,

    /** @brief ���4 */
    OUTPUT_IO_4 = 0x0004,

    /** @brief ���5 */
    OUTPUT_IO_5 = 0x0005,

    /** @brief ���6 */
    OUTPUT_IO_6 = 0x0006,

    /** @brief ���7 */
    OUTPUT_IO_7 = 0x0007,

    /** @brief ���8 */
    OUTPUT_IO_8 = 0x0008,

    /** @brief ���9 */
    OUTPUT_IO_9 = 0x0009,

    /** @brief ���10 */
    OUTPUT_IO_10 = 0x000a,

    /** @brief ���11 */
    OUTPUT_IO_11 = 0x000b,

    /** @brief ���12 */
    OUTPUT_IO_12 = 0x000c,

    /** @brief ���13 */
    OUTPUT_IO_13 = 0x000d,

    /** @brief ���14 */
    OUTPUT_IO_14 = 0x000e,

    /** @brief ���15 */
    OUTPUT_IO_15 = 0x000f,

    /** @brief ���16 */
    OUTPUT_IO_16 = 0x0010,

} dvpOutputIo;


/** @brief ����IO
*@deprecated*/
typedef enum dvpInputIo
{
    /** @brief ����1 */
    INPUT_IO_1 = 0x8001,

    /** @brief ����2 */
    INPUT_IO_2 = 0x8002,

    /** @brief ����3 */
    INPUT_IO_3 = 0x8003,

    /** @brief ����4 */
    INPUT_IO_4 = 0x8004,

    /** @brief ����5 */
    INPUT_IO_5 = 0x8005,

    /** @brief ����6 */
    INPUT_IO_6 = 0x8006,

    /** @brief ����7 */
    INPUT_IO_7 = 0x8007,

    /** @brief ����8 */
    INPUT_IO_8 = 0x8008,

} dvpInputIo;


/** @brief �豸����*/
typedef enum dvpLine
{
    /** @brief ����1 */
    LINE_1 = 0x10001,

    /** @brief ����2 */
    LINE_2 = 0x10002,

    /** @brief ����3 */
    LINE_3 = 0x10003,

    /** @brief ����4 */
    LINE_4 = 0x10004,

    /** @brief ����5 */
    LINE_5 = 0x10005,

    /** @brief ����6 */
    LINE_6 = 0x10006,

    /** @brief ����7 */
    LINE_7 = 0x10007,

    /** @brief ����8 */
    LINE_8 = 0x10008,

} dvpLine;


/** @brief ����ģʽ*/
typedef enum dvpLineMode
{
    /** @brief �����ź����� */
    LINE_MODE_INPUT = 0,

    /** @brief ����ź����� */
    LINE_MODE_OUTPUT = 1,

} dvpLineMode;


/** @brief ��������ź�Դ*/
typedef enum dvpLineSource
{
    /** @brief �û����Ƶ�ƽ */
    OUTPUT_SOURCE_NORMAL = 0,

    /** @brief ������ź� */
    OUTPUT_SOURCE_STROBE = 1,

    /** @brief PWM�ź� */
    OUTPUT_SOURCE_PWM = 2,

    /** @brief PULSE�ź� */
    OUTPUT_SOURCE_PULSE = 0x10,

} dvpLineSource;


/** @brief ���Ŵ���ģʽ*/
typedef enum dvpTriggerLineMode
{
    /** @brief ��ͨ */
    TRIGGER_LINE_MODE_NORMAL = 0,

    /** @brief �ع�ʱ����������Ⱦ��� */
    TRIGGER_LINE_MODE_BULB = 1,

} dvpTriggerLineMode;


/** @brief ����Դ*/
typedef enum dvpTriggerSource
{
    /** @brief @link #dvpTriggerFire ����@endlink���� */
    TRIGGER_SOURCE_SOFTWARE = 0,

    /** @brief @link #dvpLine::LINE_1 ����1@endlink���� */
    TRIGGER_SOURCE_LINE1 = 1,

    /** @brief @link #dvpLine::LINE_2 ����2@endlink���� */
    TRIGGER_SOURCE_LINE2 = 2,

    /** @brief @link #dvpLine::LINE_3 ����3@endlink���� */
    TRIGGER_SOURCE_LINE3 = 3,

    /** @brief @link #dvpLine::LINE_4 ����4@endlink���� */
    TRIGGER_SOURCE_LINE4 = 4,

    /** @brief @link #dvpLine::LINE_5 ����5@endlink���� */
    TRIGGER_SOURCE_LINE5 = 5,

    /** @brief @link #dvpLine::LINE_6 ����6@endlink���� */
    TRIGGER_SOURCE_LINE6 = 6,

    /** @brief @link #dvpLine::LINE_7 ����7@endlink���� */
    TRIGGER_SOURCE_LINE7 = 7,

    /** @brief @link #dvpLine::LINE_8 ����8@endlink���� */
    TRIGGER_SOURCE_LINE8 = 8,

} dvpTriggerSource;


/** @brief ��һ�����ض�Ӧ��λ��*/
typedef enum dvpFirstPosition
{
    /** @brief ���Ͻ� */
    UP_LEFT = 0,

    /** @brief ���Ͻ� */
    UP_RIGHT = 1,

    /** @brief ���½� */
    BOTTOM_LEFT = 2,

    /** @brief ���½� */
    BOTTOM_RIGHT = 3,

} dvpFirstPosition;


/** @brief �豸��ģʽ
*@note ֧��"��"���㣬���磺@code dvpOpen(0, dvpOpenMode(OPEN_NORMAL | OPEN_DEBUG), &handle) @endcode*/
typedef enum dvpOpenMode
{
    /** @brief ���ߴ� */
    OPEN_OFFLINE = 0,

    /** @brief ��ʵ���豸 */
    OPEN_NORMAL = 1<<0,

    /** @brief �Ե��Է�ʽ���豸������ǧ������������Ա��ⵥ�����Ի�ϵ��������������ʱ */
    OPEN_DEBUG = 1<<3,

    /** @brief ͼ��ɼ��ʹ����߳�ʹ�ýϸߵ����ȼ� */
    HIGH_PRIORITY = 1<<4,

} dvpOpenMode;


/** @brief ��Ƶ��״̬@see dvpGetStreamState*/
typedef enum dvpStreamState
{
    /** @brief ��ֹͣ@see dvpStop */
    STATE_STOPED = 0,

    /** @brief ������@see dvpStart */
    STATE_STARTED = 2,

} dvpStreamState;


/** @brief ������Ϸ��*/
typedef enum dvpCurveStyle
{
    /** @brief ֱ����� */
    CURVE_STYLE_LINE = 0,

    /** @brief ƽ����� */
    CURVE_STYLE_WAVE = 1,

} dvpCurveStyle;


/** @brief �û�����
*@note ͨ���洢������洢����*/
typedef enum dvpUserSet
{
    /** @brief Ĭ��ֻ������
*@note ֻ�ܶ�ȡ����ֹд�� */
    USER_SET_DEFAULT = 0,

    /** @brief �û�����1 */
    USER_SET_1 = 1,

    /** @brief �û�����2 */
    USER_SET_2 = 2,

} dvpUserSet;


/** @brief ����ģʽ*/
typedef enum dvpBufferMode
{
    /** @brief ����֡�������֡�������� */
    BUFFER_MODE_NEWEST = 0,

    /** @brief �Ƚ��ȳ����� */
    BUFFER_MODE_FIFO = 1,

} dvpBufferMode;


/** @brief �豸����*/
typedef enum dvpDeviceType
{
    /** @brief δ֪���� */
    DEVICE_TYPE_UNKNOWN = 0,

    /** @brief USB2.0�ӿڵ���� */
    DEVICE_TYPE_USB2_CAMERA = 10,

    /** @brief USB3.0�ӿڵ���� */
    DEVICE_TYPE_USB3_CAMERA = 20,

    /** @brief ǧ�����ӿڵ���� */
    DEVICE_TYPE_GLAN_CAMERA = 30,

    /** @brief �������ӿڵ���� */
    DEVICE_TYPE_XGIGE_CAMERA = 40,

    /** @brief �������ɼ��� */
    DEVICE_TYPE_XGIGE_GRABBER = 100,

} dvpDeviceType;


/** @brief ������Ϣ���棬����ģ�����*/
typedef enum dvpReportPart
{
    /** @brief Ĭ�ϻ�δ�����ܷ��� */
    PART_DEFAULT = 0x00,

    /** @brief ͨѶ��� */
    PART_LINK = 0x10,

    /** @brief ������� */
    PART_CONTROL = 0x20,

    /** @brief ��������ɼ���� */
    PART_STREAM = 0x30,

    /** @brief ����������� */
    PART_TRIG = 0x40,

    /** @brief GPIO������� */
    PART_GPIO = 0x50,

    /** @brief ͼ��Ч����� */
    PART_IMAGE = 0x60,

} dvpReportPart;


/** @brief ������Ϣ����ļ���*/
typedef enum dvpReportLevel
{
    /** @brief ��Ϣ����ʾ */
    LEVEL_INFO = 0x10,

    /** @brief �������� */
    LEVEL_PROBLEM = 0x40,

} dvpReportLevel;


/** @brief ���б�׼�ӿڵ�״̬��
*@note ����DVP_STATUS_OK��ʾ����
*@note ����DVP_STATUS_OKͨ����ʾ����
*@warning С��DVP_STATUS_OK���ʾ����*/
typedef enum dvpStatus
{
    /** @brief �������Ե��ˣ�����Ҫ�κζ��� */
    DVP_STATUS_IGNORED = 7,

    /** @brief ��Ҫ�������ݺͲ��� */
    DVP_STATUS_NEED_OTHER = 6,

    /** @brief ���������һ�׶Σ�ֻ����˲��ֶ��� */
    DVP_STATUS_NEXT_STAGE = 5,

    /** @brief ��æ���˴β������ܽ��� */
    DVP_STATUS_BUSY = 4,

    /** @brief ��Ҫ�ȴ��������ٴγ��� */
    DVP_STATUS_WAIT = 3,

    /** @brief ���ڽ��У��Ѿ��������� */
    DVP_STATUS_IN_PROCESS = 2,

    /** @brief �����ɹ� */
    DVP_STATUS_OK = 1,

    /** @brief ����ʧ�� */
    DVP_STATUS_FAILED = 0,

    /** @brief δ֪���� */
    DVP_STATUS_UNKNOW = -1,

    /** @brief ��֧�ָù��� */
    DVP_STATUS_NOT_SUPPORTED = -2,

    /** @brief ��ʼ��δ��� */
    DVP_STATUS_NOT_INITIALIZED = -3,

    /** @brief ������Ч */
    DVP_STATUS_PARAMETER_INVALID = -4,

    /** @brief ����Խ�� */
    DVP_STATUS_PARAMETER_OUT_OF_BOUND = -5,

    /** @brief ����δ�� */
    DVP_STATUS_UNENABLED = -6,

    /** @brief δ���ӵ��豸 */
    DVP_STATUS_UNCONNECTED = -7,

    /** @brief ������Ч */
    DVP_STATUS_NOT_VALID = -8,

    /** @brief �豸û�� */
    DVP_STATUS_UNPLAY = -9,

    /** @brief δ���� */
    DVP_STATUS_NOT_STARTED = -10,

    /** @brief δֹͣ */
    DVP_STATUS_NOT_STOPPED = -11,

    /** @brief δ׼���� */
    DVP_STATUS_NOT_READY = -12,

    /** @brief ��Ч������վ����Ұ�������ͨ�������δ������ */
    DVP_STATUS_INVALID_HANDLE = -13,

    /** @brief ��������� */
    DVP_STATUS_DESCR_FAULT = -20,

    /** @brief ��������� */
    DVP_STATUS_NAME_FAULT = -21,

    /** @brief ����ĸ�ֵ */
    DVP_STATUS_VALUE_FAULT = -22,

    /** @brief ������ */
    DVP_STATUS_LIMITED = -28,

    /** @brief ������Ч */
    DVP_STATUS_FUNCTION_INVALID = -29,

    /** @brief ���Զ������У��ֶ���ʽ��Ч */
    DVP_STATUS_IN_AUTO = -30,

    /** @brief �������ܾ� */
    DVP_STATUS_DENIED = -31,

    /** @brief ƫ�ƻ��ַδ���� */
    DVP_STATUS_BAD_ALIGNMENT = -40,

    /** @brief ��ַ��Ч */
    DVP_STATUS_ADDRESS_INVALID = -41,

    /** @brief ���ݿ��С��Ч */
    DVP_STATUS_SIZE_INVALID = -42,

    /** @brief ���������� */
    DVP_STATUS_OVER_LOAD = -43,

    /** @brief ���������� */
    DVP_STATUS_UNDER_LOAD = -44,

    /** @brief ��飬У��ʧ�� */
    DVP_STATUS_CHECKED_FAILED = -50,

    /** @brief ������ */
    DVP_STATUS_UNUSABLE = -51,

    /** @brief ҵ��ID��Ч��ƥ�� */
    DVP_STATUS_BID_INVALID = -52,

    /** @brief ʹ�ò��� */
    DVP_STATUS_IMPROPER = -53,

    /** @brief ֻ��������д */
    DVP_STATUS_READ_ONLY = -54,

    /** @brief ����ʶ������� */
    DVP_STATUS_UNRECOGNIZED_DATA = -55,

    /** @brief ��ʱ���� */
    DVP_STATUS_TIME_OUT = -1000,

    /** @brief Ӳ��IO���� */
    DVP_STATUS_IO_ERROR = -1001,

    /** @brief ͨѶ���� */
    DVP_STATUS_COMM_ERROR = -1002,

    /** @brief ���ߴ��� */
    DVP_STATUS_BUS_ERROR = -1003,

    /** @brief ��ʽ���� */
    DVP_STATUS_FORMAT_INVALID = -1004,

    /** @brief ������Ч */
    DVP_STATUS_CONTENT_INVALID = -1005,

    /** @brief I2C���ߴ��� */
    DVP_STATUS_I2C_FAULT = -1010,

    /** @brief I2C�ȴ�Ӧ��ʱ */
    DVP_STATUS_I2C_ACK_TIMEOUT = -1011,

    /** @brief I2C�ȴ����߶�����ʱ������SCL���ⲿ������Ϊ�͵�ƽ */
    DVP_STATUS_I2C_BUS_TIMEOUT = -1012,

    /** @brief SPI���ߴ��� */
    DVP_STATUS_SPI_FAULT = -1020,

    /** @brief UART���ߴ��� */
    DVP_STATUS_UART_FAULT = -1030,

    /** @brief GPIO���ߴ��� */
    DVP_STATUS_GPIO_FAULT = -1040,

    /** @brief USB���ߴ��� */
    DVP_STATUS_USB_FAULT = -1050,

    /** @brief PCI���ߴ��� */
    DVP_STATUS_PCI_FAULT = -1060,

    /** @brief ��������� */
    DVP_STATUS_PHY_FAULT = -1070,

    /** @brief ��·����� */
    DVP_STATUS_LINK_FAULT = -1080,

    /** @brief �������� */
    DVP_STATUS_TRANS_FAULT = -1090,

    /** @brief û�з����豸 */
    DVP_STATUS_NO_DEVICE_FOUND = -1100,

    /** @brief δ�ҵ��߼��豸 */
    DVP_STATUS_NO_LOGIC_DEVICE_FOUND = -1101,

    /** @brief �豸�Ѿ��� */
    DVP_STATUS_DEVICE_IS_OPENED = -1102,

    /** @brief �豸�Ѿ��ر� */
    DVP_STATUS_DEVICE_IS_CLOSED = -1103,

    /** @brief �豸�Ѿ��Ͽ����� */
    DVP_STATUS_DEVICE_IS_DISCONNECTED = -1104,

    /** @brief �豸�Ѿ������������� */
    DVP_STATUS_DEVICE_IS_OPENED_BY_ANOTHER = -1105,

    /** @brief �豸�Ѿ������� */
    DVP_STATUS_DEVICE_IS_STARTED = -1106,

    /** @brief �豸�Ѿ���ֹͣ�豸�Ѿ������������� */
    DVP_STATUS_DEVICE_IS_STOPPED = -1107,

    /** @brief û���㹻ϵͳ�ڴ� */
    DVP_STATUS_INSUFFICIENT_MEMORY = -1200,

    /** @brief �洢����д����������޷�������д */
    DVP_STATUS_MEMORY_FAULT = -1201,

    /** @brief д����������д */
    DVP_STATUS_WRITE_PROTECTED = -1202,

    /** @brief �����ļ�ʧ�� */
    DVP_STATUS_FILE_CREATE_FAILED = -1300,

    /** @brief �ļ���ʽ��Ч */
    DVP_STATUS_FILE_INVALID = -1301,

    /** @brief ��ȡ�ļ�ʧ�� */
    DVP_STATUS_FILE_READ_FAILED = -1302,

    /** @brief д���ļ�ʧ�� */
    DVP_STATUS_FILE_WRITE_FAILED = -1303,

    /** @brief ���ļ�ʧ�� */
    DVP_STATUS_FILE_OPEN_FAILED = -1304,

    /** @brief ��ȡ���ݽϼ�ʧ�� */
    DVP_STATUS_FILE_CHECKSUM_FAILED = -1305,

    /** @brief ���ݲɼ�ʧ�ܣ�ָ����ʱ����δ������� */
    DVP_STATUS_GRAB_FAILED = -1600,

    /** @brief ���ݶ�ʧ�������� */
    DVP_STATUS_LOST_DATA = -1601,

    /** @brief δ���յ�֡������ */
    DVP_STATUS_EOF_ERROR = -1602,

    /** @brief ���ݲɼ������Ѿ��� */
    DVP_STATUS_GRAB_IS_OPENED = -1603,

    /** @brief ���ݲɼ������Ѿ��ر� */
    DVP_STATUS_GRAB_IS_CLOSED = -1604,

    /** @brief ���ݲɼ��Ѿ����� */
    DVP_STATUS_GRAB_IS_STARTED = -1605,

    /** @brief ���ݲɼ��Ѿ�ֹͣ */
    DVP_STATUS_GRAB_IS_STOPPED = -1606,

    /** @brief ���ݲɼ��������� */
    DVP_STATUS_GRAB_IS_RESTARTING = -1607,

    /** @brief ���õ�ROI������Ч */
    DVP_STATUS_ROI_PARAM_INVALID = -1610,

    /** @brief ROI���ܲ�֧�� */
    DVP_STATUS_ROI_NOT_SUPPORTED = -1611,

} dvpStatus;


#ifndef _WIN32

#include <stdint.h>

/** @brief 8λ�޷������� */
typedef uint8_t dvpByte;

/** @brief 32λ�з������� */
typedef int32_t dvpInt32;

/** @brief 32λ�޷������� */
typedef uint32_t dvpUint32;

/** @brief 64λ�з������� */
typedef int64_t dvpInt64;

/** @brief 64λ�޷������� */
typedef uint64_t dvpUint64;

#else
/** @brief 8λ�޷������� */
typedef BYTE dvpByte;

/** @brief 32λ�з������� */
typedef INT32 dvpInt32;

/** @brief 32λ�޷������� */
typedef UINT32 dvpUint32;

/** @brief 64λ�з������� */
typedef INT64 dvpInt64;

/** @brief 64λ�޷������� */
typedef UINT64 dvpUint64;

#endif // _WIN32
/** @brief 128�ֽڱ����ռ� */
typedef dvpUint32 dvpReserved[32];

/** @brief 64�ֽڳ����ַ��� */
typedef char dvpString64[64];

/** @brief 128�ֽڳ����ַ��� */
typedef char dvpString128[128];

/** @brief 32�ֽڳ��Ĳ������� */
typedef bool dvpBool32[32];

/** @brief 4��3�м򵥾��� */
typedef float dvpMatrix[4][3];

/** @brief 3Ԫ�򵥸������� */
typedef float dvpFloat3c[3];

/** @brief 3Ԫ���������� */
typedef dvpUint32 dvpSize3c[3];

/** @brief ������
*@see dvpOpen
*@see dvpOpenByName */
typedef dvpUint32 dvpHandle;

/** @brief ��Ƶ���������
*@see dvpStartVideoRecord */
typedef dvpUint32 dvpRecordHandle;

/** @brief �ַ���ָ�� */
typedef const char* dvpStr;

/** @brief ��ɫ���� */
typedef struct dvpColorMatrix
{
    /** @brief ���� */
    dvpMatrix matrix;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpColorMatrix;


/** @brief ��ɫУ����Ϣ */
typedef struct dvpColorCorrection
{
    /** @brief BGR��ɫУ��ϵ�� */
    dvpFloat3c bgr;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpColorCorrection;


/** @brief ��ά���������� */
typedef struct dvpPoint2f
{
    /** @brief ������ */
    float X;

    /** @brief ������ */
    float Y;

} dvpPoint2f;


/** @brief BGR��ɫ256��ê�� */
typedef struct dvpPoint2f dvpPoint3c[3][256];

/** @brief BGR�������� */
typedef struct dvpCurveArray
{
    /** @brief BGR��������ռ� */
    dvpPoint3c point;

    /** @brief BGR��Чͨ���������3�� */
    dvpUint32 rows;

    /** @brief BGR��ͨ������Ч������ÿͨ�����256�� */
    dvpSize3c cols;

} dvpCurveArray;


/** @brief �����߶����LUT
*@warning �˽ṹ���ֽ����϶࣬�������ջ����������� new dvpCurveLut() �ķ�ʽ�ڶ��Ϲ��� */
typedef struct dvpCurveLut
{
    /** @brief ʹ��״̬ */
    bool enable;

    /** @brief ���߷�� */
    dvpCurveStyle style;

    /** @brief ê�����飬����������ê�����ȷ��һ��������LUT */
    dvpCurveArray array;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpCurveLut;


/** @brief �����Ϣ 
*@see dvpGetCameraInfo
*@see dvpEnum */
typedef struct dvpCameraInfo
{
    /** @brief ��Ƴ��� */
    dvpString64 Vendor;

    /** @brief �������� */
    dvpString64 Manufacturer;

    /** @brief �ͺ� */
    dvpString64 Model;

    /** @brief ϵ�� */
    dvpString64 Family;

    /** @brief ������ */
    dvpString64 LinkName;

    /** @brief ���������� */
    dvpString64 SensorInfo;

    /** @brief Ӳ���汾 */
    dvpString64 HardwareVersion;

    /** @brief �̼��汾 */
    dvpString64 FirmwareVersion;

    /** @brief �ں������汾 */
    dvpString64 KernelVersion;

    /** @brief �豸�����汾 */
    dvpString64 DscamVersion;

    /** @brief �Ѻ��豸���� */
    dvpString64 FriendlyName;

    /** @brief �ӿ����� */
    dvpString64 PortInfo;

    /** @brief ���к�
*@note һ����Ը��� */
    dvpString64 SerialNumber;

    /** @brief ������� */
    dvpString128 CameraInfo;

    /** @brief �û����� */
    dvpString128 UserID;

    /** @brief ԭʼ���к� */
    dvpString64 OriginalSerialNumber;

    /** @brief �����ֽ� */
    dvpString64 reserved;
} dvpCameraInfo;


/** @brief �������� */
typedef struct dvpRegionDescr
{
    /** @brief ��С���� */
    dvpInt32 iMinW;

    /** @brief ��С�߶� */
    dvpInt32 iMinH;

    /** @brief ������ */
    dvpInt32 iMaxW;

    /** @brief ���߶� */
    dvpInt32 iMaxH;

    /** @brief ���Ȳ��� */
    dvpInt32 iStepW;

    /** @brief �߶Ȳ��� */
    dvpInt32 iStepH;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpRegionDescr;


/** @brief ��ʼ�����Ͻǵĸ���Ȥ������
*@see dvpGetRoi
*@see dvpGetAwbRoi
*@see dvpGetAeRoi
*@warning ���ݳ�Աͨ��Ϊż����������ο��豸�ֲ� */
typedef struct dvpRegion
{
    /** @brief ������ʼλ�� */
    dvpInt32 X;

    /** @brief ������ʼλ�� */
    dvpInt32 Y;

    /** @brief ���ȣ�����0�� */
    dvpInt32 W;

    /** @brief �߶ȣ�����0�� */
    dvpInt32 H;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpRegion;


/** @brief ֡��Ϣ
*@see dvpGetFrame */
typedef struct dvpFrame
{
    /** @brief ��ʽ */
    enum dvpImageFormat format;

    /** @brief λ�� */
    enum dvpBits bits;

    /** @brief �ֽ��� */
    dvpUint32 uBytes;

    /** @brief ���� */
    dvpInt32 iWidth;

    /** @brief �߶� */
    dvpInt32 iHeight;

    /** @brief ֡��� */
    dvpUint64 uFrameID;

    /** @brief ʱ��� */
    dvpUint64 uTimestamp;

    /** @brief �ع�ʱ�䣨��λΪ΢�룩
*@see dvpGetExposure */
    double fExposure;

    /** @brief ģ������
*@see dvpGetAnalogGain */
    float fAGain;

    /** @brief ��һ�����ص��λ��
*@see dvpGetFirstPosition */
    enum dvpFirstPosition position;

    /** @brief �Ƿ�ˮƽ��ת
*@see dvpGetFlipHorizontalState */
    bool bFlipHorizontalState;

    /** @brief �Ƿ�ֱ��ת
*@see dvpGetFlipVerticalState */
    bool bFlipVerticalState;

    /** @brief �Ƿ���ת90��
*@see dvpGetRotateState */
    bool bRotateState;

    /** @brief �Ƿ���ʱ����ת
*@see dvpGetRotateOpposite */
    bool bRotateOpposite;

    /** @brief �ڲ���־λ */
    dvpUint32 internalFlags;

    /** @brief �ڲ���Ϣ */
    dvpUint32 internalValue;

    /** @brief ÿ�δ�������Ӧ��һ֡���֡�Ĵ���ID
*@see dvpGetFramesPerTrigger */
    dvpUint64 uTriggerId;

    /** @brief �û����Ƶ����ݣ�Ϊ��ֵ��ָ�� */
    dvpUint64 userValue;

    /** @brief �����ֽ� */
    dvpUint32 reserved[24];
} dvpFrame;


/** @brief ֡��Ϣ��ͼ������
*@see dvpGetFrameBuffer */
typedef struct dvpFrameBuffer
{
    /** @brief ֡��Ϣ */
    struct dvpFrame frame;

    /** @brief ͼ�������׵�ַ
*@warning �����ֶ��ͷ� */
    dvpPtr(dvpByte) pBuffer;

} dvpFrameBuffer;


/** @brief ͨ������
*@see dvpEventCallback */
typedef struct dvpVariant
{
    /** @brief �����׵�ַ */
    dvpPtr(dvpByte) pData;

    /** @brief �����ֽ��� */
    dvpUint32 uSize;

    /** @brief ������������ */
    dvpString64 name;

} dvpVariant;


/** @brief ������������ */
typedef struct dvpIntDescr
{
    /** @brief ���� */
    dvpInt32 iStep;

    /** @brief ��Сֵ */
    dvpInt32 iMin;

    /** @brief ���ֵ */
    dvpInt32 iMax;

    /** @brief Ĭ��ֵ */
    dvpInt32 iDefault;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpIntDescr;


/** @brief �޷��������������� */
typedef struct dvpUintDescr
{
    /** @brief ���� */
    dvpUint32 uStep;

    /** @brief ��Сֵ */
    dvpUint32 uMin;

    /** @brief ���ֵ */
    dvpUint32 uMax;

    /** @brief Ĭ��ֵ */
    dvpUint32 uDefault;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpUintDescr;


/** @brief �������������� */
typedef struct dvpFloatDescr
{
    /** @brief ���� */
    float fStep;

    /** @brief ��Сֵ */
    float fMin;

    /** @brief ���ֵ */
    float fMax;

    /** @brief Ĭ��ֵ */
    float fDefault;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpFloatDescr;


/** @brief ˫�������������� */
typedef struct dvpDoubleDescr
{
    /** @brief ���� */
    double fStep;

    /** @brief ��Сֵ */
    double fMin;

    /** @brief ���ֵ */
    double fMax;

    /** @brief Ĭ��ֵ */
    double fDefault;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpDoubleDescr;


/** @brief 64λ�޷��������������� */
typedef struct dvpUint64Descr
{
    /** @brief ���� */
    dvpUint64 uStep;

    /** @brief ��Сֵ */
    dvpUint64 uMin;

    /** @brief ���ֵ */
    dvpUint64 uMax;

    /** @brief Ĭ��ֵ */
    dvpUint64 uDefault;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpUint64Descr;


/** @brief ѡ�������� */
typedef struct dvpSelectionDescr
{
    /** @brief Ĭ������ */
    dvpUint32 uDefault;

    /** @brief �������� */
    dvpUint32 uCount;

    /** @brief �Ƿ�Ӧֹͣ��Ƶ�� */
    bool bNeedStop;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpSelectionDescr;


/** @brief ѡ���� */
typedef struct dvpSelection
{
    /** @brief �ַ������� */
    dvpString64 string;

    /** @brief ���� */
    dvpInt32 iIndex;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpSelection;


/** @brief �ֱ���ģʽ
*@see dvpGetTriggerModeSelDetail */
typedef struct dvpResolutionMode
{
    /** @brief �ֱ���ģʽѡ���� */
    struct dvpSelection selection;

    /** @brief ���� */
    struct dvpRegionDescr region;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpResolutionMode;


/** @brief ����Roi
*@see dvpGetQuickRoiSelDetail */
typedef struct dvpQuickRoi
{
    /** @brief ѡ���� */
    struct dvpSelection selection;

    /** @brief ����Ȥ������ */
    struct dvpRegion roi;

    /** @brief �ֱ���ģʽ */
    struct dvpResolutionMode mode;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpQuickRoi;


/** @brief ͼ���ʽ */
typedef struct dvpFormatSelection
{
    /** @brief �ֱ���ģʽѡ���� */
    struct dvpSelection selection;

    /** @brief ��Ӧ��ö������ */
    enum dvpStreamFormat format;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpFormatSelection;


/** @brief ֡����
*@see dvpGetFrameCount */
typedef struct dvpFrameCount
{
    /** @brief ����֡����һ��Ϊ���䵽���Ե�֡ */
    dvpUint32 uFrameCount;

    /** @brief ��ʧ֡������������ȡ�� */
    dvpUint32 uFrameDrop;

    /** @brief �����ģ��ɼ��󱻶����� */
    dvpUint32 uFrameIgnore;

    /** @brief ����֡���� */
    dvpUint32 uFrameError;

    /** @brief ���ɼ�������ȷ֡ */
    dvpUint32 uFrameOK;

    /** @brief ���ύ / �������Ч֡ */
    dvpUint32 uFrameOut;

    /** @brief �ش�֡ */
    dvpUint32 uFrameResend;

    /** @brief ͼ����֡���� */
    dvpUint32 uFrameProc;

    /** @brief �ɼ�֡�� */
    float fFrameRate;

    /** @brief ͼ����֡�� */
    float fProcRate;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpFrameCount;


/** @brief �û�IO��Ϣ
*@see dvpGetUserIoInfo */
typedef struct dvpUserIoInfo
{
    /** @brief ���õ�����IO */
    dvpBool32 inputValid;

    /** @brief ���õ����IO */
    dvpBool32 outputValid;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpUserIoInfo;


/** @brief �û�IO��Ϣ
*@see dvpGetLineInfo */
typedef struct dvpLineInfo
{
    /** @brief ���õ�IO */
    dvpBool32 valid;

    /** @brief ˫���IO */
    dvpBool32 bidir;

    /** @brief �Ƿ�֧�ַ����� */
    dvpBool32 inverter;

    /** @brief �Ƿ�֧���������������ƽ */
    dvpBool32 user;

    /** @brief �Ƿ�֧��strobe�ź� */
    dvpBool32 strobe;

    /** @brief �Ƿ�֧��pwm�ź� */
    dvpBool32 pwm;

    /** @brief �Ƿ�֧��timer�ź� */
    dvpBool32 timer;

    /** @brief �Ƿ�֧��uart�ź� */
    dvpBool32 uart;

    /** @brief �Ƿ�֧��pulse�ź� */
    dvpBool32 pulse;

    /** @brief �����ֽ� */
    dvpUint32 reserved[24];
} dvpLineInfo;


/** @brief �Զ��ع�����
*@see dvpGetAeConfig */
typedef struct dvpAeConfig
{
    /** @brief ��С�Զ��ع�ʱ�䣨��λΪ΢�룩 */
    double fExposureMin;

    /** @brief ����Զ��ع�ʱ�䣨��λΪ΢�룩 */
    double fExposureMax;

    /** @brief ����ֵ1 */
    double reserved1;

    /** @brief ��С�Զ�����ֵ */
    float fGainMin;

    /** @brief ����Զ�����ֵ */
    float fGainMax;

    /** @brief ����ֵ2 */
    float reserved2;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpAeConfig;


/** @brief Sensor(ͼ�񴫸���)��Ϣ
*@see dvpGetSensorInfo */
typedef struct dvpSensorInfo
{
    /** @brief �ַ������� */
    dvpString64 descr;

    /** @brief ���������� */
    enum dvpSensorType sensor;

    /** @brief ԭʼ�������� */
    enum dvpSensorPixel pixel;

    /** @brief ���� */
    struct dvpRegionDescr region;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpSensorInfo;


/** @brief �������������Ϣ
*@see dvpGetFunctionInfo */
typedef struct dvpFunctionInfo
{
    /** @brief �Ƿ�֧�ִ������� */
    bool bTrigger;

    /** @brief �Ƿ�֧��Ӳ��ISP���� */
    bool bHardwareIsp;

    /** @brief �Ƿ�֧��UserSet���� */
    bool bUserSet;

    /** @brief �Ƿ�֧��ˮƽ��ת���� */
    bool bHflip;

    /** @brief �Ƿ�֧�ִ�ֱ��ת���� */
    bool bVflip;

    /** @brief �Ƿ�֧�ָ�Ƭ���� */
    bool bInverse;

    /** @brief �Ƿ�֧�ַ���gige��׼��@link #dvpLine �������@endlink���� */
    bool bLine;

    /** @brief �Ƿ�֧��������
*@see dvpGetCoolerState */
    bool bCooler;

    /** @brief �Ƿ�֧���¶ȼƹ��� */
    bool bTemperature;

    /** @brief ���� */
    bool bReserved3;

    /** @brief �����ֽ� */
    dvpUint32 reserved[30];
} dvpFunctionInfo;


/** @brief �豸�¶�
*@see dvpGetTemperatureInfo */
typedef struct dvpTemperatureInfo
{
    /** @brief �豸���¶� */
    float fDevice;

    /** @brief ���������¶� */
    float fSensor;

    /** @brief оƬ1���¶� */
    float fChip1;

    /** @brief оƬ2���¶� */
    float fChip2;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpTemperatureInfo;


/** @brief ֡��������
*@see dvpGetBufferConfig */
typedef struct dvpBufferConfig
{
    /** @brief ���湤��ģʽ */
    enum dvpBufferMode mode;

    /** @brief ������д�С
*@see dvpGetBufferQueueSizeDescr
*@warning ���ܻ�����һ�����ڴ�ռ䣬�����ϵͳ�����ڴ��������� */
    dvpUint32 uQueueSize;

    /** @brief ���������ʱ���Ƿ����²�����֡
* @note true Ϊ������֡�� false Ϊ���ǵ����������ϵ�֡ */
    bool bDropNew;

    /** @brief ���ջ�����ڴ�����
*@note�Ƿ���ݵ�ǰ�ֱ��ʴ�С������λ���������ڴ棬��������sensor���ֱ��ʣ����λ��������������ڴ� */
    bool bLite;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpBufferConfig;


/** @brief �д�������
*@see dvpGetLineTriggerConfig
* @noteһ��ֻ����ɨ�����Ч */
typedef struct dvpLineTriggerConfig
{
    /** @brief Ԥ��Ƶ */
    dvpUint32 uPreDiv;

    /** @brief ��Ƶ */
    dvpUint32 uMult;

    /** @brief ��Ƶ */
    dvpUint32 uDiv;

    /** @brief �����ֽ� */
    dvpReserved reserved;
} dvpLineTriggerConfig;


/**
*@brief ��ȡ�����Ϣ
*@param[in] handle ������
*@param[out] pCameraInfo �����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_INFORMATION
*@see dvpGetDeviceType
*/
dvp2api dvpStatus dvpGetCameraInfo(dvpHandle handle, dvpCameraInfo *pCameraInfo);


/**
*@brief ��ȡ��������Ϣ
*@param[in] handle ������
*@param[out] pSensorInfo ��������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_INFORMATION
*/
dvp2api dvpStatus dvpGetSensorInfo(dvpHandle handle, dvpSensorInfo *pSensorInfo);


/**
*@brief ��ȡ֡����
*@param[in] handle ������
*@param[out] pFrameCount ֡����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_INFORMATION
*/
dvp2api dvpStatus dvpGetFrameCount(dvpHandle handle, dvpFrameCount *pFrameCount);


/**
*@brief ��ȡ�û�IO��Ч��־
*@param[in] handle ������
*@param[out] pUserIoInfo �û�IO��Ч��־
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_INFORMATION
*@deprecated
*/
dvp2api dvpStatus dvpGetUserIoInfo(dvpHandle handle, dvpUserIoInfo *pUserIoInfo);


/**
*@brief ��ȡ����������־
*@param[in] handle ������
*@param[out] pLineInfo ����������־
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*/
dvp2api dvpStatus dvpGetLineInfo(dvpHandle handle, dvpLineInfo *pLineInfo);


/**
*@brief ��ȡ��һ�����ض�Ӧ��λ��
*@param[in] handle ������
*@param[out] pFirstPosition ��һ�����ض�Ӧ��λ��
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_INFORMATION
*/
dvp2api dvpStatus dvpGetFirstPosition(dvpHandle handle, dvpFirstPosition *pFirstPosition);


/**
*@brief ��ȡ������Ϣ
*@param[in] handle ������
*@param[out] pFunctionInfo ������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_INFORMATION
*@note ����ݹ���������������Ӧ��API��Ʃ�磬��Ҫ�Ժڰ����ʹ�ò�ɫ������е����ԣ������������Ҫ�Ĵ���״̬��
*/
dvp2api dvpStatus dvpGetFunctionInfo(dvpHandle handle, dvpFunctionInfo *pFunctionInfo);


/**
*@brief ��ȡ�豸����
*@param[in] handle ������
*@param[out] pDeviceType �豸����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_INFORMATION
*@see dvpGetCameraInfo
*/
dvp2api dvpStatus dvpGetDeviceType(dvpHandle handle, dvpDeviceType *pDeviceType);


/**
*@brief ��ȡ�豸�¶���Ϣ
*@param[in] handle ������
*@param[out] pTemperatureInfo �豸�¶���Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_INFORMATION
*@see dvpGetCoolerState
*/
dvp2api dvpStatus dvpGetTemperatureInfo(dvpHandle handle, dvpTemperatureInfo *pTemperatureInfo);


/**
*@brief �������������ź�
*@param[in] handle ������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@note ����@link #dvpSetTriggerSource ����@endlink��@link #dvpTriggerSource::TRIGGER_SOURCE_SOFTWARE ��������Դ@endlink
*/
dvp2api dvpStatus dvpTriggerFire(dvpHandle handle);


/**
*@brief �����ʵ�У����Ϣ
*@param[in] handle ������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION
*@see dvpSetDefectFixState
*@see dvpSetAutoDefectFixState
*@note ����������Sensor��һ���̶ȴ��������ȹ̶��������ʵ�
*@note ������Щ��Ϣ�洢�ڵ����ϣ����Բ���������
*/
dvp2api dvpStatus dvpCreateDefectFixInfo(dvpHandle handle);


/**
*@brief ����ƽ��У����Ϣ
*@param[in] handle ������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION
*@note ���û����ض��ĳ����;�ͷ�´���ƽ����Ϣ
*@note ������Щ��Ϣ�洢�ڵ����ϣ����Բ���������
*/
dvp2api dvpStatus dvpCreateFlatFieldInfo(dvpHandle handle);


/**
*@brief ��λ�豸
*@param[in] handle ������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP2_API_BASE
*@note �����ɹ����Զ��ָ�����λǰ���豸״̬
*/
dvp2api dvpStatus dvpResetDevice(dvpHandle handle);


/**
*@brief ��������/�ָ���Ƶ��
*@param[in] handle ������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP2_API_BASE
*@see dvpHold
*����֮ǰ����@link #dvpHold ��ͣ@endlink��Ƶ��
*/
dvp2api dvpStatus dvpRestart(dvpHandle handle);


/**
*@brief ������ͣ��Ƶ��
*@param[in] handle ������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP2_API_BASE
*@see dvpRestart
*@see dvpIsHold
*@note ��������Ƶ��֮ǰ�Ϳ���ִ�иö���������Ƶ��@link #dvpStart �������൱�ڴ���ˮբ��@endlink����ִ��@link #dvpRestart �ָ����൱�ڴ�ˮ��ͷ��@endlink��Ƶ���������������ͼ������
*/
dvp2api dvpStatus dvpHold(dvpHandle handle);


/**
*@brief ��ȡ٤���ֵ
*@param[in] handle ������
*@param[out] pGamma ٤���ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetColorSolutionSel
*@see dvpSetGammaState
*@see dvpGetGammaState
*@see dvpGetGammaDescr
*@see dvpSetGamma
*@note ��ʹͼ�����ȷ������۵������Ӿ�
*/
dvp2api dvpStatus dvpGetGamma(dvpHandle handle, dvpInt32 *pGamma);


/**
*@brief ����٤���ֵ
*@param[in] handle ������
*@param[in] Gamma ٤���ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetColorSolutionSel
*@see dvpSetGammaState
*@see dvpGetGammaState
*@see dvpGetGammaDescr
*@see dvpGetGamma
*@note ��ʹͼ�����ȷ������۵������Ӿ�
*/
dvp2api dvpStatus dvpSetGamma(dvpHandle handle, dvpInt32 Gamma);


/**
*@brief ��ȡ٤���������Ϣ
*@param[in] handle ������
*@param[out] pGammaDescr ٤���������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetColorSolutionSel
*@see dvpSetGammaState
*@see dvpGetGammaState
*@see dvpSetGamma
*@see dvpGetGamma
*/
dvp2api dvpStatus dvpGetGammaDescr(dvpHandle handle, dvpIntDescr *pGammaDescr);


/**
*@brief ��ȡ٤�깦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pGammaState ٤�깦�ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetColorSolutionSel
*@see dvpSetGamma
*@see dvpGetGamma
*@see dvpGetGammaDescr
*@see dvpSetGammaState
*/
dvp2api dvpStatus dvpGetGammaState(dvpHandle handle, bool *pGammaState);


/**
*@brief ����٤�깦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] GammaState ٤�깦�ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetColorSolutionSel
*@see dvpSetGamma
*@see dvpGetGamma
*@see dvpGetGammaDescr
*@see dvpGetGammaState
*/
dvp2api dvpStatus dvpSetGammaState(dvpHandle handle, bool GammaState);


/**
*@brief ��ȡ�Աȶȵ�ֵ
*@param[in] handle ������
*@param[out] pContrast �Աȶȵ�ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetBlackLevel
*@see dvpSetContrastState
*@see dvpGetContrastState
*@see dvpGetContrastDescr
*@see dvpSetContrast
*@note ����ͨ͸��
*/
dvp2api dvpStatus dvpGetContrast(dvpHandle handle, dvpInt32 *pContrast);


/**
*@brief ���öԱȶȵ�ֵ
*@param[in] handle ������
*@param[in] Contrast �Աȶȵ�ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetBlackLevel
*@see dvpSetContrastState
*@see dvpGetContrastState
*@see dvpGetContrastDescr
*@see dvpGetContrast
*@note ����ͨ͸��
*/
dvp2api dvpStatus dvpSetContrast(dvpHandle handle, dvpInt32 Contrast);


/**
*@brief ��ȡ�Աȶȵ�������Ϣ
*@param[in] handle ������
*@param[out] pContrastDescr �Աȶȵ�������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetBlackLevel
*@see dvpSetContrastState
*@see dvpGetContrastState
*@see dvpSetContrast
*@see dvpGetContrast
*/
dvp2api dvpStatus dvpGetContrastDescr(dvpHandle handle, dvpIntDescr *pContrastDescr);


/**
*@brief ��ȡ�Աȶȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pContrastState �Աȶȹ��ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetBlackLevel
*@see dvpSetContrast
*@see dvpGetContrast
*@see dvpGetContrastDescr
*@see dvpSetContrastState
*/
dvp2api dvpStatus dvpGetContrastState(dvpHandle handle, bool *pContrastState);


/**
*@brief ���öԱȶȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] ContrastState �Աȶȹ��ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetBlackLevel
*@see dvpSetContrast
*@see dvpGetContrast
*@see dvpGetContrastDescr
*@see dvpGetContrastState
*/
dvp2api dvpStatus dvpSetContrastState(dvpHandle handle, bool ContrastState);


/**
*@brief ��ȡͼ��Roi(�������������������)
*@param[in] handle ������
*@param[out] pRoi ͼ��Roi(�������������������)
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@see dvpGetResolutionModeSel
*@see dvpGetQuickRoiSel
*@see dvpSetRoiState
*@see dvpGetRoiState
*@see dvpGetRoiDescr
*@see dvpSetRoi
*/
dvp2api dvpStatus dvpGetRoi(dvpHandle handle, dvpRegion *pRoi);


/**
*@brief ����ͼ��Roi(�������������������)
*@param[in] handle ������
*@param[in] Roi ͼ��Roi(�������������������)
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@see dvpGetResolutionModeSel
*@see dvpGetQuickRoiSel
*@see dvpSetRoiState
*@see dvpGetRoiState
*@see dvpGetRoiDescr
*@see dvpGetRoi
*/
dvp2api dvpStatus dvpSetRoi(dvpHandle handle, dvpRegion Roi);


/**
*@brief ��ȡͼ��Roi(�������������������)��������Ϣ
*@param[in] handle ������
*@param[out] pRoiDescr ͼ��Roi(�������������������)��������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@see dvpGetResolutionModeSel
*@see dvpGetQuickRoiSel
*@see dvpSetRoiState
*@see dvpGetRoiState
*@see dvpSetRoi
*@see dvpGetRoi
*/
dvp2api dvpStatus dvpGetRoiDescr(dvpHandle handle, dvpRegionDescr *pRoiDescr);


/**
*@brief ��ȡͼ��Roi(�������������������)���ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pRoiState ͼ��Roi(�������������������)���ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@see dvpGetResolutionModeSel
*@see dvpGetQuickRoiSel
*@see dvpSetRoi
*@see dvpGetRoi
*@see dvpGetRoiDescr
*@see dvpSetRoiState
*/
dvp2api dvpStatus dvpGetRoiState(dvpHandle handle, bool *pRoiState);


/**
*@brief ����ͼ��Roi(�������������������)���ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] RoiState ͼ��Roi(�������������������)���ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@see dvpGetResolutionModeSel
*@see dvpGetQuickRoiSel
*@see dvpSetRoi
*@see dvpGetRoi
*@see dvpGetRoiDescr
*@see dvpGetRoiState
*/
dvp2api dvpStatus dvpSetRoiState(dvpHandle handle, bool RoiState);


/**
*@brief ��ȡɫ�µ�ֵ����λΪK��
*@param[in] handle ������
*@param[out] pColorTemperature ɫ�µ�ֵ����λΪK��
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetColorTemperatureState
*@see dvpGetColorTemperatureState
*@see dvpGetColorTemperatureDescr
*@see dvpSetColorTemperature
*@note ������ůɫ��
*/
dvp2api dvpStatus dvpGetColorTemperature(dvpHandle handle, dvpInt32 *pColorTemperature);


/**
*@brief ����ɫ�µ�ֵ����λΪK��
*@param[in] handle ������
*@param[in] ColorTemperature ɫ�µ�ֵ����λΪK��
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetColorTemperatureState
*@see dvpGetColorTemperatureState
*@see dvpGetColorTemperatureDescr
*@see dvpGetColorTemperature
*@note ������ůɫ��
*/
dvp2api dvpStatus dvpSetColorTemperature(dvpHandle handle, dvpInt32 ColorTemperature);


/**
*@brief ��ȡɫ�µ�������Ϣ
*@param[in] handle ������
*@param[out] pColorTemperatureDescr ɫ�µ�������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetColorTemperatureState
*@see dvpGetColorTemperatureState
*@see dvpSetColorTemperature
*@see dvpGetColorTemperature
*/
dvp2api dvpStatus dvpGetColorTemperatureDescr(dvpHandle handle, dvpIntDescr *pColorTemperatureDescr);


/**
*@brief ��ȡɫ�¹��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pColorTemperatureState ɫ�¹��ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetColorTemperature
*@see dvpGetColorTemperature
*@see dvpGetColorTemperatureDescr
*@see dvpSetColorTemperatureState
*/
dvp2api dvpStatus dvpGetColorTemperatureState(dvpHandle handle, bool *pColorTemperatureState);


/**
*@brief ����ɫ�¹��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] ColorTemperatureState ɫ�¹��ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetColorTemperature
*@see dvpGetColorTemperature
*@see dvpGetColorTemperatureDescr
*@see dvpGetColorTemperatureState
*/
dvp2api dvpStatus dvpSetColorTemperatureState(dvpHandle handle, bool ColorTemperatureState);


/**
*@brief ��ȡ��ȵ�ֵ
*@param[in] handle ������
*@param[out] pSharpness ��ȵ�ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetSharpnessState
*@see dvpGetSharpnessState
*@see dvpGetSharpnessDescr
*@see dvpSetSharpness
*@note ����������
*/
dvp2api dvpStatus dvpGetSharpness(dvpHandle handle, dvpInt32 *pSharpness);


/**
*@brief ������ȵ�ֵ
*@param[in] handle ������
*@param[in] Sharpness ��ȵ�ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetSharpnessState
*@see dvpGetSharpnessState
*@see dvpGetSharpnessDescr
*@see dvpGetSharpness
*@note ����������
*/
dvp2api dvpStatus dvpSetSharpness(dvpHandle handle, dvpInt32 Sharpness);


/**
*@brief ��ȡ��ȵ�������Ϣ
*@param[in] handle ������
*@param[out] pSharpnessDescr ��ȵ�������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetSharpnessState
*@see dvpGetSharpnessState
*@see dvpSetSharpness
*@see dvpGetSharpness
*/
dvp2api dvpStatus dvpGetSharpnessDescr(dvpHandle handle, dvpIntDescr *pSharpnessDescr);


/**
*@brief ��ȡ��ȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pSharpnessState ��ȹ��ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetSharpness
*@see dvpGetSharpness
*@see dvpGetSharpnessDescr
*@see dvpSetSharpnessState
*/
dvp2api dvpStatus dvpGetSharpnessState(dvpHandle handle, bool *pSharpnessState);


/**
*@brief ������ȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] SharpnessState ��ȹ��ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetSharpness
*@see dvpGetSharpness
*@see dvpGetSharpnessDescr
*@see dvpGetSharpnessState
*/
dvp2api dvpStatus dvpSetSharpnessState(dvpHandle handle, bool SharpnessState);


/**
*@brief ��ȡ���Ͷȵ�ֵ
*@param[in] handle ������
*@param[out] pSaturation ���Ͷȵ�ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetSaturationState
*@see dvpGetSaturationState
*@see dvpGetSaturationDescr
*@see dvpSetSaturation
*@note ����������
*/
dvp2api dvpStatus dvpGetSaturation(dvpHandle handle, dvpInt32 *pSaturation);


/**
*@brief ���ñ��Ͷȵ�ֵ
*@param[in] handle ������
*@param[in] Saturation ���Ͷȵ�ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetSaturationState
*@see dvpGetSaturationState
*@see dvpGetSaturationDescr
*@see dvpGetSaturation
*@note ����������
*/
dvp2api dvpStatus dvpSetSaturation(dvpHandle handle, dvpInt32 Saturation);


/**
*@brief ��ȡ���Ͷȵ�������Ϣ
*@param[in] handle ������
*@param[out] pSaturationDescr ���Ͷȵ�������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetSaturationState
*@see dvpGetSaturationState
*@see dvpSetSaturation
*@see dvpGetSaturation
*/
dvp2api dvpStatus dvpGetSaturationDescr(dvpHandle handle, dvpIntDescr *pSaturationDescr);


/**
*@brief ��ȡ���Ͷȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pSaturationState ���Ͷȹ��ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetSaturation
*@see dvpGetSaturation
*@see dvpGetSaturationDescr
*@see dvpSetSaturationState
*/
dvp2api dvpStatus dvpGetSaturationState(dvpHandle handle, bool *pSaturationState);


/**
*@brief ���ñ��Ͷȹ��ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] SaturationState ���Ͷȹ��ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetSaturation
*@see dvpGetSaturation
*@see dvpGetSaturationDescr
*@see dvpGetSaturationState
*/
dvp2api dvpStatus dvpSetSaturationState(dvpHandle handle, bool SaturationState);


/**
*@brief ��ȡ2D�����ֵ
*@param[in] handle ������
*@param[out] pNoiseReduct2d 2D�����ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetSharpness
*@see dvpGetNoiseReduct3d
*@see dvpSetNoiseReduct2dState
*@see dvpGetNoiseReduct2dState
*@see dvpGetNoiseReduct2dDescr
*@see dvpSetNoiseReduct2d
*@note ��ͼ�����ƽ������������Ӱ�����
*/
dvp2api dvpStatus dvpGetNoiseReduct2d(dvpHandle handle, dvpInt32 *pNoiseReduct2d);


/**
*@brief ����2D�����ֵ
*@param[in] handle ������
*@param[in] NoiseReduct2d 2D�����ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetSharpness
*@see dvpGetNoiseReduct3d
*@see dvpSetNoiseReduct2dState
*@see dvpGetNoiseReduct2dState
*@see dvpGetNoiseReduct2dDescr
*@see dvpGetNoiseReduct2d
*@note ��ͼ�����ƽ������������Ӱ�����
*/
dvp2api dvpStatus dvpSetNoiseReduct2d(dvpHandle handle, dvpInt32 NoiseReduct2d);


/**
*@brief ��ȡ2D�����������Ϣ
*@param[in] handle ������
*@param[out] pNoiseReduct2dDescr 2D�����������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetSharpness
*@see dvpGetNoiseReduct3d
*@see dvpSetNoiseReduct2dState
*@see dvpGetNoiseReduct2dState
*@see dvpSetNoiseReduct2d
*@see dvpGetNoiseReduct2d
*/
dvp2api dvpStatus dvpGetNoiseReduct2dDescr(dvpHandle handle, dvpIntDescr *pNoiseReduct2dDescr);


/**
*@brief ��ȡ2D���빦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pNoiseReduct2dState 2D���빦�ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetSharpness
*@see dvpGetNoiseReduct3d
*@see dvpSetNoiseReduct2d
*@see dvpGetNoiseReduct2d
*@see dvpGetNoiseReduct2dDescr
*@see dvpSetNoiseReduct2dState
*/
dvp2api dvpStatus dvpGetNoiseReduct2dState(dvpHandle handle, bool *pNoiseReduct2dState);


/**
*@brief ����2D���빦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] NoiseReduct2dState 2D���빦�ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetSharpness
*@see dvpGetNoiseReduct3d
*@see dvpSetNoiseReduct2d
*@see dvpGetNoiseReduct2d
*@see dvpGetNoiseReduct2dDescr
*@see dvpGetNoiseReduct2dState
*/
dvp2api dvpStatus dvpSetNoiseReduct2dState(dvpHandle handle, bool NoiseReduct2dState);


/**
*@brief ��ȡ3D�����ֵ
*@param[in] handle ������
*@param[out] pNoiseReduct3d 3D�����ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetNoiseReduct3dState
*@see dvpGetNoiseReduct3dState
*@see dvpGetNoiseReduct3dDescr
*@see dvpSetNoiseReduct3d
*@note ����Ч���Ϻã����������Ӱ
*/
dvp2api dvpStatus dvpGetNoiseReduct3d(dvpHandle handle, dvpInt32 *pNoiseReduct3d);


/**
*@brief ����3D�����ֵ
*@param[in] handle ������
*@param[in] NoiseReduct3d 3D�����ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetNoiseReduct3dState
*@see dvpGetNoiseReduct3dState
*@see dvpGetNoiseReduct3dDescr
*@see dvpGetNoiseReduct3d
*@note ����Ч���Ϻã����������Ӱ
*/
dvp2api dvpStatus dvpSetNoiseReduct3d(dvpHandle handle, dvpInt32 NoiseReduct3d);


/**
*@brief ��ȡ3D�����������Ϣ
*@param[in] handle ������
*@param[out] pNoiseReduct3dDescr 3D�����������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetNoiseReduct3dState
*@see dvpGetNoiseReduct3dState
*@see dvpSetNoiseReduct3d
*@see dvpGetNoiseReduct3d
*/
dvp2api dvpStatus dvpGetNoiseReduct3dDescr(dvpHandle handle, dvpIntDescr *pNoiseReduct3dDescr);


/**
*@brief ��ȡ3D���빦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pNoiseReduct3dState 3D���빦�ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetNoiseReduct3d
*@see dvpGetNoiseReduct3d
*@see dvpGetNoiseReduct3dDescr
*@see dvpSetNoiseReduct3dState
*/
dvp2api dvpStatus dvpGetNoiseReduct3dState(dvpHandle handle, bool *pNoiseReduct3dState);


/**
*@brief ����3D���빦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] NoiseReduct3dState 3D���빦�ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetNoiseReduct2d
*@see dvpSetNoiseReduct3d
*@see dvpGetNoiseReduct3d
*@see dvpGetNoiseReduct3dDescr
*@see dvpGetNoiseReduct3dState
*/
dvp2api dvpStatus dvpSetNoiseReduct3dState(dvpHandle handle, bool NoiseReduct3dState);


/**
*@brief ��ȡ�ڳ���ֵ
*@param[in] handle ������
*@param[out] pBlackLevel �ڳ���ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetContrast
*@see dvpSetBlackLevelState
*@see dvpGetBlackLevelState
*@see dvpGetBlackLevelDescr
*@see dvpSetBlackLevel
*@note ��϶Աȶȿ��Ը��õĵ���ͨ͸��
*/
dvp2api dvpStatus dvpGetBlackLevel(dvpHandle handle, float *pBlackLevel);


/**
*@brief ���úڳ���ֵ
*@param[in] handle ������
*@param[in] BlackLevel �ڳ���ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetContrast
*@see dvpSetBlackLevelState
*@see dvpGetBlackLevelState
*@see dvpGetBlackLevelDescr
*@see dvpGetBlackLevel
*@note ��϶Աȶȿ��Ը��õĵ���ͨ͸��
*/
dvp2api dvpStatus dvpSetBlackLevel(dvpHandle handle, float BlackLevel);


/**
*@brief ��ȡ�ڳ���������Ϣ
*@param[in] handle ������
*@param[out] pBlackLevelDescr �ڳ���������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetContrast
*@see dvpSetBlackLevelState
*@see dvpGetBlackLevelState
*@see dvpSetBlackLevel
*@see dvpGetBlackLevel
*/
dvp2api dvpStatus dvpGetBlackLevelDescr(dvpHandle handle, dvpFloatDescr *pBlackLevelDescr);


/**
*@brief ��ȡ�ڳ����ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pBlackLevelState �ڳ����ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetContrast
*@see dvpSetBlackLevel
*@see dvpGetBlackLevel
*@see dvpGetBlackLevelDescr
*@see dvpSetBlackLevelState
*/
dvp2api dvpStatus dvpGetBlackLevelState(dvpHandle handle, bool *pBlackLevelState);


/**
*@brief ���úڳ����ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] BlackLevelState �ڳ����ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetContrast
*@see dvpSetBlackLevel
*@see dvpGetBlackLevel
*@see dvpGetBlackLevelDescr
*@see dvpGetBlackLevelState
*/
dvp2api dvpStatus dvpSetBlackLevelState(dvpHandle handle, bool BlackLevelState);


/**
*@brief ��ȡѭ������������ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pSoftTriggerLoop ѭ������������ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopDescr
*@see dvpSetSoftTriggerLoop
*/
dvp2api dvpStatus dvpGetSoftTriggerLoop(dvpHandle handle, double *pSoftTriggerLoop);


/**
*@brief ����ѭ������������ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] SoftTriggerLoop ѭ������������ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopDescr
*@see dvpGetSoftTriggerLoop
*/
dvp2api dvpStatus dvpSetSoftTriggerLoop(dvpHandle handle, double SoftTriggerLoop);


/**
*@brief ��ȡѭ��������������Ϣ
*@param[in] handle ������
*@param[out] pSoftTriggerLoopDescr ѭ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetSoftTriggerLoopState
*@see dvpGetSoftTriggerLoopState
*@see dvpSetSoftTriggerLoop
*@see dvpGetSoftTriggerLoop
*/
dvp2api dvpStatus dvpGetSoftTriggerLoopDescr(dvpHandle handle, dvpDoubleDescr *pSoftTriggerLoopDescr);


/**
*@brief ��ȡѭ���������ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pSoftTriggerLoopState ѭ���������ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetSoftTriggerLoop
*@see dvpGetSoftTriggerLoop
*@see dvpGetSoftTriggerLoopDescr
*@see dvpSetSoftTriggerLoopState
*/
dvp2api dvpStatus dvpGetSoftTriggerLoopState(dvpHandle handle, bool *pSoftTriggerLoopState);


/**
*@brief ����ѭ���������ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] SoftTriggerLoopState ѭ���������ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetSoftTriggerLoop
*@see dvpGetSoftTriggerLoop
*@see dvpGetSoftTriggerLoopDescr
*@see dvpGetSoftTriggerLoopState
*/
dvp2api dvpStatus dvpSetSoftTriggerLoopState(dvpHandle handle, bool SoftTriggerLoopState);


/**
*@brief ��ȡ��֡�ɼ���֡��
*@param[in] handle ������
*@param[out] pMultiFrames ��֡�ɼ���֡��
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpSetMultiFramesState
*@see dvpGetMultiFramesState
*@see dvpGetMultiFramesDescr
*@see dvpSetMultiFrames
*@note ��֡�ɼ�Ϊ1ʱ���൱�ڵ�֡�ɼ�
*/
dvp2api dvpStatus dvpGetMultiFrames(dvpHandle handle, dvpUint64 *pMultiFrames);


/**
*@brief ���ö�֡�ɼ���֡��
*@param[in] handle ������
*@param[in] MultiFrames ��֡�ɼ���֡��
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpSetMultiFramesState
*@see dvpGetMultiFramesState
*@see dvpGetMultiFramesDescr
*@see dvpGetMultiFrames
*@note ��֡�ɼ�Ϊ1ʱ���൱�ڵ�֡�ɼ�
*/
dvp2api dvpStatus dvpSetMultiFrames(dvpHandle handle, dvpUint64 MultiFrames);


/**
*@brief ��ȡ��֡�ɼ���������Ϣ
*@param[in] handle ������
*@param[out] pMultiFramesDescr ��֡�ɼ���������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpSetMultiFramesState
*@see dvpGetMultiFramesState
*@see dvpSetMultiFrames
*@see dvpGetMultiFrames
*/
dvp2api dvpStatus dvpGetMultiFramesDescr(dvpHandle handle, dvpUint64Descr *pMultiFramesDescr);


/**
*@brief ��ȡ��֡�ɼ����ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pMultiFramesState ��֡�ɼ����ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpSetMultiFrames
*@see dvpGetMultiFrames
*@see dvpGetMultiFramesDescr
*@see dvpSetMultiFramesState
*/
dvp2api dvpStatus dvpGetMultiFramesState(dvpHandle handle, bool *pMultiFramesState);


/**
*@brief ���ö�֡�ɼ����ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] MultiFramesState ��֡�ɼ����ܵ�ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpSetMultiFrames
*@see dvpGetMultiFrames
*@see dvpGetMultiFramesDescr
*@see dvpGetMultiFramesState
*/
dvp2api dvpStatus dvpSetMultiFramesState(dvpHandle handle, bool MultiFramesState);


/**
*@brief ��ȡ���ݴ���������ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pStreamPackInterval ���ݴ���������ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@see dvpGetStreamPackIntervalDescr
*@see dvpSetStreamPackInterval
*@note ��������Խ�ʡ�������
*/
dvp2api dvpStatus dvpGetStreamPackInterval(dvpHandle handle, dvpInt32 *pStreamPackInterval);


/**
*@brief �������ݴ���������ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] StreamPackInterval ���ݴ���������ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@see dvpGetStreamPackIntervalDescr
*@see dvpGetStreamPackInterval
*@note ��������Խ�ʡ�������
*/
dvp2api dvpStatus dvpSetStreamPackInterval(dvpHandle handle, dvpInt32 StreamPackInterval);


/**
*@brief ��ȡ���ݴ���������������Ϣ
*@param[in] handle ������
*@param[out] pStreamPackIntervalDescr ���ݴ���������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@see dvpSetStreamPackInterval
*@see dvpGetStreamPackInterval
*/
dvp2api dvpStatus dvpGetStreamPackIntervalDescr(dvpHandle handle, dvpIntDescr *pStreamPackIntervalDescr);


/**
*@brief ��ȡ���ݴ��������ֵ����λΪ�ֽڣ�
*@param[in] handle ������
*@param[out] pStreamPackSize ���ݴ��������ֵ����λΪ�ֽڣ�
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@see dvpGetStreamPackSizeDescr
*@see dvpSetStreamPackSize
*@note �������Ӳ��֧�֣���������ݴ���Ч��
*@note ����ʹ��@link #dvpGetPixelRateSel ���ʹ������@endlink
*/
dvp2api dvpStatus dvpGetStreamPackSize(dvpHandle handle, dvpInt32 *pStreamPackSize);


/**
*@brief �������ݴ��������ֵ����λΪ�ֽڣ�
*@param[in] handle ������
*@param[in] StreamPackSize ���ݴ��������ֵ����λΪ�ֽڣ�
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@see dvpGetStreamPackSizeDescr
*@see dvpGetStreamPackSize
*@note �������Ӳ��֧�֣���������ݴ���Ч��
*@note ����ʹ��@link #dvpGetPixelRateSel ���ʹ������@endlink
*/
dvp2api dvpStatus dvpSetStreamPackSize(dvpHandle handle, dvpInt32 StreamPackSize);


/**
*@brief ��ȡ���ݴ��������������Ϣ
*@param[in] handle ������
*@param[out] pStreamPackSizeDescr ���ݴ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@see dvpSetStreamPackSize
*@see dvpGetStreamPackSize
*/
dvp2api dvpStatus dvpGetStreamPackSizeDescr(dvpHandle handle, dvpIntDescr *pStreamPackSizeDescr);


/**
*@brief ��ȡ�Զ��ع�Ŀ�����ȵ�ֵ
*@param[in] handle ������
*@param[out] pAeTarget �Զ��ع�Ŀ�����ȵ�ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAeOperation
*@see dvpGetAeTargetDescr
*@see dvpSetAeTarget
*@note �Զ��ع��㷨ͨ������@link #dvpGetExposure �ع�ʱ��@endlink��@link #dvpGetAnalogGain ģ������@endlink��Ҫ�ﵽ����������
*/
dvp2api dvpStatus dvpGetAeTarget(dvpHandle handle, dvpInt32 *pAeTarget);


/**
*@brief �����Զ��ع�Ŀ�����ȵ�ֵ
*@param[in] handle ������
*@param[in] AeTarget �Զ��ع�Ŀ�����ȵ�ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAeOperation
*@see dvpGetAeTargetDescr
*@see dvpGetAeTarget
*@note �Զ��ع��㷨ͨ������@link #dvpGetExposure �ع�ʱ��@endlink��@link #dvpGetAnalogGain ģ������@endlink��Ҫ�ﵽ����������
*/
dvp2api dvpStatus dvpSetAeTarget(dvpHandle handle, dvpInt32 AeTarget);


/**
*@brief ��ȡ�Զ��ع�Ŀ�����ȵ�������Ϣ
*@param[in] handle ������
*@param[out] pAeTargetDescr �Զ��ع�Ŀ�����ȵ�������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAeOperation
*@see dvpSetAeTarget
*@see dvpGetAeTarget
*/
dvp2api dvpStatus dvpGetAeTargetDescr(dvpHandle handle, dvpIntDescr *pAeTargetDescr);


/**
*@brief ��ȡģ�������ֵ
*@param[in] handle ������
*@param[out] pAnalogGain ģ�������ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetExposure
*@see dvpGetAnalogGainDescr
*@see dvpSetAnalogGain
*@note ģ���·�����ϵ�������ڡ�����Խ�󣬿��ܵ�������Խ��
*/
dvp2api dvpStatus dvpGetAnalogGain(dvpHandle handle, float *pAnalogGain);


/**
*@brief ����ģ�������ֵ
*@param[in] handle ������
*@param[in] AnalogGain ģ�������ֵ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetExposure
*@see dvpGetAnalogGainDescr
*@see dvpGetAnalogGain
*@note ģ���·�����ϵ�������ڡ�����Խ�󣬿��ܵ�������Խ��
*/
dvp2api dvpStatus dvpSetAnalogGain(dvpHandle handle, float AnalogGain);


/**
*@brief ��ȡģ�������������Ϣ
*@param[in] handle ������
*@param[out] pAnalogGainDescr ģ�������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetExposure
*@see dvpSetAnalogGain
*@see dvpGetAnalogGain
*/
dvp2api dvpStatus dvpGetAnalogGainDescr(dvpHandle handle, dvpFloatDescr *pAnalogGainDescr);


/**
*@brief ��ȡ�ع�ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pExposure �ع�ʱ���ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAnalogGain
*@see dvpGetExposureDescr
*@see dvpSetExposure
*@note �ع�ʱ��Խ�������ܵ���֡��Խ��
*/
dvp2api dvpStatus dvpGetExposure(dvpHandle handle, double *pExposure);


/**
*@brief �����ع�ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] Exposure �ع�ʱ���ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAnalogGain
*@see dvpGetExposureDescr
*@see dvpGetExposure
*@note �ع�ʱ��Խ�������ܵ���֡��Խ��
*/
dvp2api dvpStatus dvpSetExposure(dvpHandle handle, double Exposure);


/**
*@brief ��ȡ�ع�ʱ���������Ϣ
*@param[in] handle ������
*@param[out] pExposureDescr �ع�ʱ���������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAnalogGain
*@see dvpSetExposure
*@see dvpGetExposure
*/
dvp2api dvpStatus dvpGetExposureDescr(dvpHandle handle, dvpDoubleDescr *pExposureDescr);


/**
*@brief ��ȡ�ⲿ�����ź�����ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pTriggerJitterFilter �ⲿ�����ź�����ʱ���ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetTriggerJitterFilterDescr
*@see dvpSetTriggerJitterFilter
*@note �ⲿ���źŴ�����˲����ܴ���һ���ĵ�ѹ������������Ҫ�趨һ��ǡ��������ʱ�䣬��ȷ���źŴﵽ�ȶ�
*/
dvp2api dvpStatus dvpGetTriggerJitterFilter(dvpHandle handle, double *pTriggerJitterFilter);


/**
*@brief �����ⲿ�����ź�����ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] TriggerJitterFilter �ⲿ�����ź�����ʱ���ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetTriggerJitterFilterDescr
*@see dvpGetTriggerJitterFilter
*@note �ⲿ���źŴ�����˲����ܴ���һ���ĵ�ѹ������������Ҫ�趨һ��ǡ��������ʱ�䣬��ȷ���źŴﵽ�ȶ�
*/
dvp2api dvpStatus dvpSetTriggerJitterFilter(dvpHandle handle, double TriggerJitterFilter);


/**
*@brief ��ȡ�ⲿ�����ź�����ʱ���������Ϣ
*@param[in] handle ������
*@param[out] pTriggerJitterFilterDescr �ⲿ�����ź�����ʱ���������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetTriggerJitterFilter
*@see dvpGetTriggerJitterFilter
*/
dvp2api dvpStatus dvpGetTriggerJitterFilterDescr(dvpHandle handle, dvpDoubleDescr *pTriggerJitterFilterDescr);


/**
*@brief ��ȡ������ʱ��ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pTriggerDelay ������ʱ��ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetTriggerDelayDescr
*@see dvpSetTriggerDelay
*@note �յ�һ����Ч�Ĵ����źź���ʱ��Ӧ
*/
dvp2api dvpStatus dvpGetTriggerDelay(dvpHandle handle, double *pTriggerDelay);


/**
*@brief ���ô�����ʱ��ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] TriggerDelay ������ʱ��ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetTriggerDelayDescr
*@see dvpGetTriggerDelay
*@note �յ�һ����Ч�Ĵ����źź���ʱ��Ӧ
*/
dvp2api dvpStatus dvpSetTriggerDelay(dvpHandle handle, double TriggerDelay);


/**
*@brief ��ȡ������ʱ��������Ϣ
*@param[in] handle ������
*@param[out] pTriggerDelayDescr ������ʱ��������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetTriggerDelay
*@see dvpGetTriggerDelay
*/
dvp2api dvpStatus dvpGetTriggerDelayDescr(dvpHandle handle, dvpDoubleDescr *pTriggerDelayDescr);


/**
*@brief ��ȡStrobe�źŵ���ʱ��ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pStrobeDelay Strobe�źŵ���ʱ��ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetStrobeDelayDescr
*@see dvpSetStrobeDelay
*@note �������ʱ��Ӧ
*/
dvp2api dvpStatus dvpGetStrobeDelay(dvpHandle handle, double *pStrobeDelay);


/**
*@brief ����Strobe�źŵ���ʱ��ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] StrobeDelay Strobe�źŵ���ʱ��ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetStrobeDelayDescr
*@see dvpGetStrobeDelay
*@note �������ʱ��Ӧ
*/
dvp2api dvpStatus dvpSetStrobeDelay(dvpHandle handle, double StrobeDelay);


/**
*@brief ��ȡStrobe�źŵ���ʱ��������Ϣ
*@param[in] handle ������
*@param[out] pStrobeDelayDescr Strobe�źŵ���ʱ��������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetStrobeDelay
*@see dvpGetStrobeDelay
*/
dvp2api dvpStatus dvpGetStrobeDelayDescr(dvpHandle handle, dvpDoubleDescr *pStrobeDelayDescr);


/**
*@brief ��ȡStrobe�źŵĳ���ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pStrobeDuration Strobe�źŵĳ���ʱ���ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetStrobeDurationDescr
*@see dvpSetStrobeDuration
*@note ���������ʱ��
*/
dvp2api dvpStatus dvpGetStrobeDuration(dvpHandle handle, double *pStrobeDuration);


/**
*@brief ����Strobe�źŵĳ���ʱ���ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] StrobeDuration Strobe�źŵĳ���ʱ���ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetStrobeDurationDescr
*@see dvpGetStrobeDuration
*@note ���������ʱ��
*/
dvp2api dvpStatus dvpSetStrobeDuration(dvpHandle handle, double StrobeDuration);


/**
*@brief ��ȡStrobe�źŵĳ���ʱ���������Ϣ
*@param[in] handle ������
*@param[out] pStrobeDurationDescr Strobe�źŵĳ���ʱ���������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetStrobeDuration
*@see dvpGetStrobeDuration
*/
dvp2api dvpStatus dvpGetStrobeDurationDescr(dvpHandle handle, dvpDoubleDescr *pStrobeDurationDescr);


/**
*@brief ��ȡ���δ��������֡��
*@param[in] handle ������
*@param[out] pFramesPerTrigger ���δ��������֡��
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetFramesPerTriggerDescr
*@see dvpSetFramesPerTrigger
*@note ��һ�������ź��������֡ͼ��
*/
dvp2api dvpStatus dvpGetFramesPerTrigger(dvpHandle handle, dvpInt32 *pFramesPerTrigger);


/**
*@brief ���õ��δ��������֡��
*@param[in] handle ������
*@param[in] FramesPerTrigger ���δ��������֡��
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetFramesPerTriggerDescr
*@see dvpGetFramesPerTrigger
*@note ��һ�������ź��������֡ͼ��
*/
dvp2api dvpStatus dvpSetFramesPerTrigger(dvpHandle handle, dvpInt32 FramesPerTrigger);


/**
*@brief ��ȡ���δ��������֡����������Ϣ
*@param[in] handle ������
*@param[out] pFramesPerTriggerDescr ���δ��������֡����������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetFramesPerTrigger
*@see dvpGetFramesPerTrigger
*/
dvp2api dvpStatus dvpGetFramesPerTriggerDescr(dvpHandle handle, dvpIntDescr *pFramesPerTriggerDescr);


/**
*@brief ��ȡ����еļ�ʱ����ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[out] pTimerValue ����еļ�ʱ����ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpGetTimerValueDescr
*@see dvpSetTimerValue
*/
dvp2api dvpStatus dvpGetTimerValue(dvpHandle handle, double *pTimerValue);


/**
*@brief ��������еļ�ʱ����ֵ����λΪ΢�룩
*@param[in] handle ������
*@param[in] TimerValue ����еļ�ʱ����ֵ����λΪ΢�룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpGetTimerValueDescr
*@see dvpGetTimerValue
*/
dvp2api dvpStatus dvpSetTimerValue(dvpHandle handle, double TimerValue);


/**
*@brief ��ȡ����еļ�ʱ����������Ϣ
*@param[in] handle ������
*@param[out] pTimerValueDescr ����еļ�ʱ����������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpSetTimerValue
*@see dvpGetTimerValue
*/
dvp2api dvpStatus dvpGetTimerValueDescr(dvpHandle handle, dvpDoubleDescr *pTimerValueDescr);


/**
*@brief ��ȡ������д�С
*@param[in] handle ������
*@param[out] pBufferQueueSize ������д�С
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpGetBufferQueueSizeDescr
*@see dvpSetBufferQueueSize
*@see dvpGetBufferConfig
*@warning ���ܻ�����һ�����ڴ�ռ䣬�����ϵͳ�����ڴ���������
*@warning �˲���������@link #dvpStart ������Ƶ��@endlinkǰ���ú�
*/
dvp2api dvpStatus dvpGetBufferQueueSize(dvpHandle handle, dvpInt32 *pBufferQueueSize);


/**
*@brief ���û�����д�С
*@param[in] handle ������
*@param[in] BufferQueueSize ������д�С
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpGetBufferQueueSizeDescr
*@see dvpGetBufferQueueSize
*@see dvpGetBufferConfig
*@warning ���ܻ�����һ�����ڴ�ռ䣬�����ϵͳ�����ڴ���������
*@warning �˲���������@link #dvpStart ������Ƶ��@endlinkǰ���ú�
*/
dvp2api dvpStatus dvpSetBufferQueueSize(dvpHandle handle, dvpInt32 BufferQueueSize);


/**
*@brief ��ȡ������д�С��������Ϣ
*@param[in] handle ������
*@param[out] pBufferQueueSizeDescr ������д�С��������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpSetBufferQueueSize
*@see dvpGetBufferQueueSize
*/
dvp2api dvpStatus dvpGetBufferQueueSizeDescr(dvpHandle handle, dvpIntDescr *pBufferQueueSizeDescr);


/**
*@brief ��ȡ���������Ƶ
*@param[in] handle ������
*@param[out] pLineRate ���������Ƶ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
* @ingroup DVP_LINESCAN
*@see dvpGetLineRateDescr
*@see dvpSetLineRate
*/
dvp2api dvpStatus dvpGetLineRate(dvpHandle handle, double *pLineRate);


/**
*@brief �������������Ƶ
*@param[in] handle ������
*@param[in] LineRate ���������Ƶ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
* @ingroup DVP_LINESCAN
*@see dvpGetLineRateDescr
*@see dvpGetLineRate
*/
dvp2api dvpStatus dvpSetLineRate(dvpHandle handle, double LineRate);


/**
*@brief ��ȡ���������Ƶ��������Ϣ
*@param[in] handle ������
*@param[out] pLineRateDescr ���������Ƶ��������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
* @ingroup DVP_LINESCAN
*@see dvpSetLineRate
*@see dvpGetLineRate
*/
dvp2api dvpStatus dvpGetLineRateDescr(dvpHandle handle, dvpDoubleDescr *pLineRateDescr);


/**
*@brief ��ȡ����Ĵ���Դ
*@param[in] handle ������
*@param[out] pTriggerSource ����Ĵ���Դ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpSetTriggerSource
*/
dvp2api dvpStatus dvpGetTriggerSource(dvpHandle handle, dvpTriggerSource *pTriggerSource);


/**
*@brief ��������Ĵ���Դ
*@param[in] handle ������
*@param[in] TriggerSource ����Ĵ���Դ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetTriggerSource
*/
dvp2api dvpStatus dvpSetTriggerSource(dvpHandle handle, dvpTriggerSource TriggerSource);


/**
*@brief ��ȡLUT����
*@param[in] handle ������
*@param[out] pCurveLut LUT����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpSetCurveLut
*@note ����������ê����ȷ��һ��������ӳ������
*/
dvp2api dvpStatus dvpGetCurveLut(dvpHandle handle, dvpCurveLut *pCurveLut);


/**
*@brief ����LUT����
*@param[in] handle ������
*@param[in] CurveLut LUT����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetCurveLut
*@note ����������ê����ȷ��һ��������ӳ������
*/
dvp2api dvpStatus dvpSetCurveLut(dvpHandle handle, dvpCurveLut CurveLut);


/**
*@brief ��ȡ��ɫУ������
*@param[in] handle ������
*@param[out] pColorCorrection ��ɫУ������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION
*@see dvpSetColorCorrection
*@note ��ɫУ������һ����ȷ����ɫ�����ɫ�ʻ�ԭЧ��һ�µı�Ҫ����
*/
dvp2api dvpStatus dvpGetColorCorrection(dvpHandle handle, dvpColorCorrection *pColorCorrection);


/**
*@brief ������ɫУ������
*@param[in] handle ������
*@param[in] ColorCorrection ��ɫУ������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION
*@see dvpGetColorCorrection
*@note ��ɫУ������һ����ȷ����ɫ�����ɫ�ʻ�ԭЧ��һ�µı�Ҫ����
*/
dvp2api dvpStatus dvpSetColorCorrection(dvpHandle handle, dvpColorCorrection ColorCorrection);


/**
*@brief ��ȡ��Ƶ��״̬
*@param[in] handle ������
*@param[out] pStreamState ��Ƶ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpStart
*@see dvpStop
*@see dvpSetStreamState
*/
dvp2api dvpStatus dvpGetStreamState(dvpHandle handle, dvpStreamState *pStreamState);


/**
*@brief ������Ƶ��״̬
*@param[in] handle ������
*@param[in] StreamState ��Ƶ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpStart
*@see dvpStop
*@see dvpGetStreamState
*/
dvp2api dvpStatus dvpSetStreamState(dvpHandle handle, dvpStreamState StreamState);


/**
*@brief ��ȡ�������Ӳ��ISP��ʹ��״̬
*@param[in] handle ������
*@param[out] pHardwareIspState �������Ӳ��ISP��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@see dvpGetFunctionInfo
*@see dvpSetHardwareIspState
*@note Ӳ��ISP�ܹ���ʡ���Ե����ܿ���
*/
dvp2api dvpStatus dvpGetHardwareIspState(dvpHandle handle, bool *pHardwareIspState);


/**
*@brief �����������Ӳ��ISP��ʹ��״̬
*@param[in] handle ������
*@param[in] HardwareIspState �������Ӳ��ISP��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@see dvpGetFunctionInfo
*@see dvpGetHardwareIspState
*@note Ӳ��ISP�ܹ���ʡ���Ե����ܿ���
*/
dvp2api dvpStatus dvpSetHardwareIspState(dvpHandle handle, bool HardwareIspState);


/**
*@brief ��ȡ����ģʽ��ʹ��״̬
*@param[in] handle ������
*@param[out] pTriggerState ����ģʽ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetFunctionInfo
*@see dvpSetTriggerState
*@note �ڴ�����ͼ��������ͼģʽ֮���л�
*/
dvp2api dvpStatus dvpGetTriggerState(dvpHandle handle, bool *pTriggerState);


/**
*@brief ���ô���ģʽ��ʹ��״̬
*@param[in] handle ������
*@param[in] TriggerState ����ģʽ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetFunctionInfo
*@see dvpGetTriggerState
*@note �ڴ�����ͼ��������ͼģʽ֮���л�
*/
dvp2api dvpStatus dvpSetTriggerState(dvpHandle handle, bool TriggerState);

/**
*@brief ��ȡȥɫ��ʹ��״̬
*@param[in] handle ������
*@param[out] pMonoState ȥɫ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpSetMonoState
*@note ͨ���ǶԲ�ɫͼ�����YUV�任����ȡ���ȣ�Y������
*/
dvp2api dvpStatus dvpGetMonoState(dvpHandle handle, bool *pMonoState);


/**
*@brief ����ȥɫ��ʹ��״̬
*@param[in] handle ������
*@param[in] MonoState ȥɫ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetMonoState
*@note ͨ���ǶԲ�ɫͼ�����YUV�任����ȡ���ȣ�Y������
*/
dvp2api dvpStatus dvpSetMonoState(dvpHandle handle, bool MonoState);


/**
*@brief ��ȡ��Ƭ��ʹ��״̬
*@param[in] handle ������
*@param[out] pInverseState ��Ƭ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpSetInverseState
*@note ʵ�����������Ƭ�ķ�ɫЧ��
*/
dvp2api dvpStatus dvpGetInverseState(dvpHandle handle, bool *pInverseState);


/**
*@brief ���ø�Ƭ��ʹ��״̬
*@param[in] handle ������
*@param[in] InverseState ��Ƭ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetInverseState
*@note ʵ�����������Ƭ�ķ�ɫЧ��
*/
dvp2api dvpStatus dvpSetInverseState(dvpHandle handle, bool InverseState);


/**
*@brief ��ȡ����ת��ʹ��״̬
*@param[in] handle ������
*@param[out] pFlipHorizontalState ����ת��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetFlipVerticalState
*@see dvpGetRotateOpposite
*@see dvpSetFlipHorizontalState
*/
dvp2api dvpStatus dvpGetFlipHorizontalState(dvpHandle handle, bool *pFlipHorizontalState);


/**
*@brief ���ú���ת��ʹ��״̬
*@param[in] handle ������
*@param[in] FlipHorizontalState ����ת��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetFlipVerticalState
*@see dvpGetRotateOpposite
*@see dvpGetFlipHorizontalState
*/
dvp2api dvpStatus dvpSetFlipHorizontalState(dvpHandle handle, bool FlipHorizontalState);


/**
*@brief ��ȡ����ת��ʹ��״̬
*@param[in] handle ������
*@param[out] pFlipVerticalState ����ת��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetFlipHorizontalState
*@see dvpGetRotateOpposite
*@see dvpSetFlipVerticalState
*/
dvp2api dvpStatus dvpGetFlipVerticalState(dvpHandle handle, bool *pFlipVerticalState);


/**
*@brief ��������ת��ʹ��״̬
*@param[in] handle ������
*@param[in] FlipVerticalState ����ת��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetFlipHorizontalState
*@see dvpGetRotateOpposite
*@see dvpGetFlipVerticalState
*/
dvp2api dvpStatus dvpSetFlipVerticalState(dvpHandle handle, bool FlipVerticalState);


/**
*@brief ��ȡƽ����ʹ��״̬
*@param[in] handle ������
*@param[out] pFlatFieldState ƽ����ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION 
*@see dvpCreateFlatFieldInfo
*@see dvpSetFlatFieldState
*@note ͨ�����ڲ�����ͷ�������ġ����ǡ�ЧӦ
*/
dvp2api dvpStatus dvpGetFlatFieldState(dvpHandle handle, bool *pFlatFieldState);


/**
*@brief ����ƽ����ʹ��״̬
*@param[in] handle ������
*@param[in] FlatFieldState ƽ����ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION 
*@see dvpCreateFlatFieldInfo
*@see dvpGetFlatFieldState
*@note ͨ�����ڲ�����ͷ�������ġ����ǡ�ЧӦ
*/
dvp2api dvpStatus dvpSetFlatFieldState(dvpHandle handle, bool FlatFieldState);


/**
*@brief ��ȡ�����ʵ��ʹ��״̬
*@param[in] handle ������
*@param[out] pDefectFixState �����ʵ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION
*@see dvpCreateDefectFixInfo
*@see dvpSetAutoDefectFixState
*@see dvpSetDefectFixState
*/
dvp2api dvpStatus dvpGetDefectFixState(dvpHandle handle, bool *pDefectFixState);


/**
*@brief ���������ʵ��ʹ��״̬
*@param[in] handle ������
*@param[in] DefectFixState �����ʵ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION
*@see dvpCreateDefectFixInfo
*@see dvpSetAutoDefectFixState
*@see dvpGetDefectFixState
*/
dvp2api dvpStatus dvpSetDefectFixState(dvpHandle handle, bool DefectFixState);


/**
*@brief ��ȡ�Զ������ʵ��ʹ��״̬
*@param[in] handle ������
*@param[out] pAutoDefectFixState �Զ������ʵ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION
*@see dvpCreateDefectFixInfo
*@see dvpSetDefectFixState
*@see dvpSetAutoDefectFixState
*@note true Ϊ�Զ���false Ϊ�ֶ�
*/
dvp2api dvpStatus dvpGetAutoDefectFixState(dvpHandle handle, bool *pAutoDefectFixState);


/**
*@brief �����Զ������ʵ��ʹ��״̬
*@param[in] handle ������
*@param[in] AutoDefectFixState �Զ������ʵ��ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_CORRECTION
*@see dvpCreateDefectFixInfo
*@see dvpSetDefectFixState
*@see dvpGetAutoDefectFixState
*@note true Ϊ�Զ���false Ϊ�ֶ�
*/
dvp2api dvpStatus dvpSetAutoDefectFixState(dvpHandle handle, bool AutoDefectFixState);


/**
*@brief ��ȡͼ����תʹ��״̬
*@param[in] handle ������
*@param[out] pRotateState ͼ����תʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetRotateOpposite
*@see dvpSetRotateState
*/
dvp2api dvpStatus dvpGetRotateState(dvpHandle handle, bool *pRotateState);


/**
*@brief ����ͼ����תʹ��״̬
*@param[in] handle ������
*@param[in] RotateState ͼ����תʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetRotateOpposite
*@see dvpGetRotateState
*/
dvp2api dvpStatus dvpSetRotateState(dvpHandle handle, bool RotateState);


/**
*@brief ��ȡͼ����ת����ı�־
*@see dvpGetRotateState
*@param[in] handle ������
*@param[out] pRotateOpposite ͼ����ת����ı�־
*@see dvpGetRotateState
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpSetRotateOpposite
*@note ˳ʱ�루true������ʱ�루false��90��
*/
dvp2api dvpStatus dvpGetRotateOpposite(dvpHandle handle, bool *pRotateOpposite);


/**
*@brief ����ͼ����ת����ı�־
*@see dvpGetRotateState
*@param[in] handle ������
*@param[in] RotateOpposite ͼ����ת����ı�־
*@see dvpGetRotateState
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ENHANCE
*@see dvpGetRotateOpposite
*@note ˳ʱ�루true������ʱ�루false��90��
*/
dvp2api dvpStatus dvpSetRotateOpposite(dvpHandle handle, bool RotateOpposite);


/**
*@brief ��ȡ��������ʹ��״̬
*@param[in] handle ������
*@param[out] pCoolerState ��������ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpGetTemperatureInfo
*@see dvpSetCoolerState
*@note һ����ָɢ�ȷ���
*/
dvp2api dvpStatus dvpGetCoolerState(dvpHandle handle, bool *pCoolerState);


/**
*@brief ������������ʹ��״̬
*@param[in] handle ������
*@param[in] CoolerState ��������ʹ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpGetTemperatureInfo
*@see dvpGetCoolerState
*@note һ����ָɢ�ȷ���
*/
dvp2api dvpStatus dvpSetCoolerState(dvpHandle handle, bool CoolerState);


/**
*@brief ��ȡ�Զ��ع�ͳ����������������ɼ�����
*@param[in] handle ������
*@param[out] pAeRoi �Զ��ع�ͳ����������������ɼ�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpSetAeOperation
*@see dvpSetAeRoi
*@note �Զ��ع��㷨������ͳ������
*/
dvp2api dvpStatus dvpGetAeRoi(dvpHandle handle, dvpRegion *pAeRoi);


/**
*@brief �����Զ��ع�ͳ����������������ɼ�����
*@param[in] handle ������
*@param[in] AeRoi �Զ��ع�ͳ����������������ɼ�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpSetAeOperation
*@see dvpGetAeRoi
*@note �Զ��ع��㷨������ͳ������
*/
dvp2api dvpStatus dvpSetAeRoi(dvpHandle handle, dvpRegion AeRoi);


/**
*@brief ��ȡ�Զ���ƽ��ͳ����������������ɼ�����
*@param[in] handle ������
*@param[out] pAwbRoi �Զ���ƽ��ͳ����������������ɼ�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetAwbOperation
*@see dvpSetAwbRoi
*@note �Զ���ƽ���㷨����ɫͳ������
*/
dvp2api dvpStatus dvpGetAwbRoi(dvpHandle handle, dvpRegion *pAwbRoi);


/**
*@brief �����Զ���ƽ��ͳ����������������ɼ�����
*@param[in] handle ������
*@param[in] AwbRoi �Զ���ƽ��ͳ����������������ɼ�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetAwbOperation
*@see dvpGetAwbRoi
*@note �Զ���ƽ���㷨����ɫͳ������
*/
dvp2api dvpStatus dvpSetAwbRoi(dvpHandle handle, dvpRegion AwbRoi);


/**
*@brief ��ȡ�Զ��ع�ģʽ
*@param[in] handle ������
*@param[out] pAeMode �Զ��ع�ģʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAwbRoi
*@see dvpGetAwbOperation
*@see dvpSetAeMode
*@note �Զ��ع��㷨�Ļ�������
*/
dvp2api dvpStatus dvpGetAeMode(dvpHandle handle, dvpAeMode *pAeMode);


/**
*@brief �����Զ��ع�ģʽ
*@param[in] handle ������
*@param[in] AeMode �Զ��ع�ģʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAwbRoi
*@see dvpGetAwbOperation
*@see dvpGetAeMode
*@note �Զ��ع��㷨�Ļ�������
*/
dvp2api dvpStatus dvpSetAeMode(dvpHandle handle, dvpAeMode AeMode);


/**
*@brief ��ȡ��Ƶ��״̬
*@param[in] handle ������
*@param[out] pAntiFlick ��Ƶ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAeRoi
*@see dvpGetAeOperation
*@see dvpSetAntiFlick
*@note ����һЩ������ڽ���Ƶ������ɵ����Ƹ���
*/
dvp2api dvpStatus dvpGetAntiFlick(dvpHandle handle, dvpAntiFlick *pAntiFlick);


/**
*@brief ���ÿ�Ƶ��״̬
*@param[in] handle ������
*@param[in] AntiFlick ��Ƶ��״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAeRoi
*@see dvpGetAeOperation
*@see dvpGetAntiFlick
*@note ����һЩ������ڽ���Ƶ������ɵ����Ƹ���
*/
dvp2api dvpStatus dvpSetAntiFlick(dvpHandle handle, dvpAntiFlick AntiFlick);


/**
*@brief ��ȡ�Զ��ع�Ĳ�����ʽ
*@param[in] handle ������
*@param[out] pAeOperation �Զ��ع�Ĳ�����ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAeConfig
*@see dvpGetAeTarget
*@see dvpGetAeMode
*@see dvpSetAeOperation
*@note �Զ����ֶ��ع�ģʽ�л�
*/
dvp2api dvpStatus dvpGetAeOperation(dvpHandle handle, dvpAeOperation *pAeOperation);


/**
*@brief �����Զ��ع�Ĳ�����ʽ
*@param[in] handle ������
*@param[in] AeOperation �Զ��ع�Ĳ�����ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAeConfig
*@see dvpGetAeTarget
*@see dvpGetAeMode
*@see dvpGetAeOperation
*@note �Զ����ֶ��ع�ģʽ�л�
*/
dvp2api dvpStatus dvpSetAeOperation(dvpHandle handle, dvpAeOperation AeOperation);


/**
*@brief ��ȡ�Զ���ƽ��Ĳ�����ʽ
*@param[in] handle ������
*@param[out] pAwbOperation �Զ���ƽ��Ĳ�����ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetAwbOperation
*@note ��ִ�а�ƽ�������������@link #dvpSetRgbGain ����RGB����@endlinkΪ1.0������@link dvpSetColorTemperatureState ����ɫ��Ч��@endlink���ܵõ������İ�ƽ��
*/
dvp2api dvpStatus dvpGetAwbOperation(dvpHandle handle, dvpAwbOperation *pAwbOperation);


/**
*@brief �����Զ���ƽ��Ĳ�����ʽ
*@param[in] handle ������
*@param[in] AwbOperation �Զ���ƽ��Ĳ�����ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpGetAwbOperation
*@note ��ִ�а�ƽ�������������@link #dvpSetRgbGain ����RGB����@endlinkΪ1.0������@link dvpSetColorTemperatureState ����ɫ��Ч��@endlink���ܵõ������İ�ƽ��
*/
dvp2api dvpStatus dvpSetAwbOperation(dvpHandle handle, dvpAwbOperation AwbOperation);


/**
*@brief ��ȡStrobe������ƣ��ź�������ʽ
*@param[in] handle ������
*@param[out] pStrobeDriver Strobe������ƣ��ź�������ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetStrobeOutputType
*@see dvpSetStrobeDriver
*/
dvp2api dvpStatus dvpGetStrobeDriver(dvpHandle handle, dvpStrobeDriver *pStrobeDriver);


/**
*@brief ����Strobe������ƣ��ź�������ʽ
*@param[in] handle ������
*@param[in] StrobeDriver Strobe������ƣ��ź�������ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetStrobeOutputType
*@see dvpGetStrobeDriver
*/
dvp2api dvpStatus dvpSetStrobeDriver(dvpHandle handle, dvpStrobeDriver StrobeDriver);


/**
*@brief ��ȡStrobe������ƣ��ź�����
*@param[in] handle ������
*@param[out] pStrobeOutputType Strobe������ƣ��ź�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetStrobeDriver
*@see dvpSetStrobeOutputType
*/
dvp2api dvpStatus dvpGetStrobeOutputType(dvpHandle handle, dvpStrobeOutputType *pStrobeOutputType);


/**
*@brief ����Strobe������ƣ��ź�����
*@param[in] handle ������
*@param[in] StrobeOutputType Strobe������ƣ��ź�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetStrobeDriver
*@see dvpGetStrobeOutputType
*/
dvp2api dvpStatus dvpSetStrobeOutputType(dvpHandle handle, dvpStrobeOutputType StrobeOutputType);


/**
*@brief ��ȡ���������ź�����
*@param[in] handle ������
*@param[out] pTriggerInputType ���������ź�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetTriggerLineMode
*@see dvpSetTriggerInputType
*/
dvp2api dvpStatus dvpGetTriggerInputType(dvpHandle handle, dvpTriggerInputType *pTriggerInputType);


/**
*@brief ���ô��������ź�����
*@param[in] handle ������
*@param[in] TriggerInputType ���������ź�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_TRIGGER
*@see dvpGetTriggerLineMode
*@see dvpGetTriggerInputType
*/
dvp2api dvpStatus dvpSetTriggerInputType(dvpHandle handle, dvpTriggerInputType TriggerInputType);


/**
*@brief ��ȡԴͼ���ʽ
*@param[in] handle ������
*@param[out] pSourceFormat Դͼ���ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@see dvpSetSourceFormatSel
*@see dvpSetSourceFormat
*@note ͨ���Ǿ�����������������ͼ���ʽ
*/
dvp2api dvpStatus dvpGetSourceFormat(dvpHandle handle, dvpStreamFormat *pSourceFormat);


/**
*@brief ����Դͼ���ʽ
*@param[in] handle ������
*@param[in] SourceFormat Դͼ���ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@see dvpSetSourceFormatSel
*@see dvpGetSourceFormat
*@note ͨ���Ǿ�����������������ͼ���ʽ
*/
dvp2api dvpStatus dvpSetSourceFormat(dvpHandle handle, dvpStreamFormat SourceFormat);


/**
*@brief ��ȡĿ��ͼ���ʽ
*@param[in] handle ������
*@param[out] pTargetFormat Ŀ��ͼ���ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@see dvpSetTargetFormatSel
*@see dvpSetTargetFormat
*@note ͨ���Ǵ����ֱ�������ԭʼ��ʽ
*/
dvp2api dvpStatus dvpGetTargetFormat(dvpHandle handle, dvpStreamFormat *pTargetFormat);


/**
*@brief ����Ŀ��ͼ���ʽ
*@param[in] handle ������
*@param[in] TargetFormat Ŀ��ͼ���ʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@see dvpSetTargetFormatSel
*@see dvpGetTargetFormat
*@note ͨ���Ǵ����ֱ�������ԭʼ��ʽ
*/
dvp2api dvpStatus dvpSetTargetFormat(dvpHandle handle, dvpStreamFormat TargetFormat);


/**
*@brief ��ȡ�û���ɫ����
*@param[in] handle ������
*@param[out] pUserColorMatrix �û���ɫ����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpSetUserColorMatrix
*@note MAT[0][0] + MAT[1][0] + MAT[2][0] ����� 1.0
*@note MAT[0][1] + MAT[1][1] + MAT[2][1] ����� 1.0
*@note MAT[0][2] + MAT[1][2] + MAT[2][2] ����� 1.0
*@note ������ɫ [B0.G0.R0]
*@note �����ɫ [B1.G1.R1]
*@note B1 = B0*MAT[0][0] + G0*MAT[1][0] + R0*MAT[2][0] + MAT[3][0]
*@note G1 = B0*MAT[0][1] + G0*MAT[1][1] + R0*MAT[2][1] + MAT[3][1]
*@note R1 = B0*MAT[0][2] + G0*MAT[1][2] + R0*MAT[2][2] + MAT[3][2]
*/
dvp2api dvpStatus dvpGetUserColorMatrix(dvpHandle handle, dvpColorMatrix *pUserColorMatrix);


/**
*@brief �����û���ɫ����
*@param[in] handle ������
*@param[in] UserColorMatrix �û���ɫ����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpGetUserColorMatrix
*@note MAT[0][0] + MAT[1][0] + MAT[2][0] ����� 1.0
*@note MAT[0][1] + MAT[1][1] + MAT[2][1] ����� 1.0
*@note MAT[0][2] + MAT[1][2] + MAT[2][2] ����� 1.0
*@note ������ɫ [B0.G0.R0]
*@note �����ɫ [B1.G1.R1]
*@note B1 = B0*MAT[0][0] + G0*MAT[1][0] + R0*MAT[2][0] + MAT[3][0]
*@note G1 = B0*MAT[0][1] + G0*MAT[1][1] + R0*MAT[2][1] + MAT[3][1]
*@note R1 = B0*MAT[0][2] + G0*MAT[1][2] + R0*MAT[2][2] + MAT[3][2]
*/
dvp2api dvpStatus dvpSetUserColorMatrix(dvpHandle handle, dvpColorMatrix UserColorMatrix);


/**
*@brief ��ȡ���ӳ�ʱʱ���ֵ ����λΪ���룩
*@param[in] handle ������
*@param[out] pLinkTimeout ���ӳ�ʱʱ���ֵ ����λΪ���룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpSetLinkTimeout
*@note �����������������Ӧ����������ʱ
*/
dvp2api dvpStatus dvpGetLinkTimeout(dvpHandle handle, dvpUint32 *pLinkTimeout);


/**
*@brief �������ӳ�ʱʱ���ֵ ����λΪ���룩
*@param[in] handle ������
*@param[in] LinkTimeout ���ӳ�ʱʱ���ֵ ����λΪ���룩
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpGetLinkTimeout
*@note �����������������Ӧ����������ʱ
*/
dvp2api dvpStatus dvpSetLinkTimeout(dvpHandle handle, dvpUint32 LinkTimeout);


/**
*@brief ��ȡ�Զ��ع�������Ϣ
*@param[in] handle ������
*@param[out] pAeConfig �Զ��ع�������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAeOperation
*@see dvpGetAeTarget
*@see dvpSetAeConfig
*@note �Զ��ع��㷨�ĸ߼����ԣ�ͨ���������û�����
*/
dvp2api dvpStatus dvpGetAeConfig(dvpHandle handle, dvpAeConfig *pAeConfig);


/**
*@brief �����Զ��ع�������Ϣ
*@param[in] handle ������
*@param[in] AeConfig �Զ��ع�������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@see dvpGetAeOperation
*@see dvpGetAeTarget
*@see dvpGetAeConfig
*@note �Զ��ع��㷨�ĸ߼����ԣ�ͨ���������û�����
*/
dvp2api dvpStatus dvpSetAeConfig(dvpHandle handle, dvpAeConfig AeConfig);


/**
*@brief ��ȡ��������
*@param[in] handle ������
*@param[out] pBufferConfig ��������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpSetBufferConfig
*@note ����֡������ԣ�����Ӧ�ض���Ӧ�ó���
*@warning �˲���������@link #dvpStart ������Ƶ��@endlinkǰ���ú�
*/
dvp2api dvpStatus dvpGetBufferConfig(dvpHandle handle, dvpBufferConfig *pBufferConfig);


/**
*@brief ���û�������
*@param[in] handle ������
*@param[in] BufferConfig ��������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@see dvpGetBufferConfig
*@note ����֡������ԣ�����Ӧ�ض���Ӧ�ó���
*@warning �˲���������@link #dvpStart ������Ƶ��@endlinkǰ���ú�
*/
dvp2api dvpStatus dvpSetBufferConfig(dvpHandle handle, dvpBufferConfig BufferConfig);


/**
*@brief ��ȡ��ɨ�����������
*@param[in] handle ������
*@param[out] pLineTriggerConfig ��ɨ�����������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
* @ingroup DVP_LINESCAN
*@see dvpSetLineTriggerConfig
* @note ������ɨ�����������
* @warning �˲���������@link #dvpStart ������Ƶ��@endlinkǰ���ú�
*/
dvp2api dvpStatus dvpGetLineTriggerConfig(dvpHandle handle, dvpLineTriggerConfig *pLineTriggerConfig);


/**
*@brief ������ɨ�����������
*@param[in] handle ������
*@param[in] LineTriggerConfig ��ɨ�����������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
* @ingroup DVP_LINESCAN
*@see dvpGetLineTriggerConfig
* @note ������ɨ�����������
* @warning �˲���������@link #dvpStart ������Ƶ��@endlinkǰ���ú�
*/
dvp2api dvpStatus dvpSetLineTriggerConfig(dvpHandle handle, dvpLineTriggerConfig LineTriggerConfig);


/**
*@brief ��ȡ��ǰ�û�����
*@param[in] handle ������
*@param[out] pUserSet ��ǰ�û�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP2_API_CONFIG
*@see dvpGetFunctionInfo
*@see dvpSetUserSet
*@note ���ϵ��ʼ���ã������ڴ��ڲ����洢�������
*/
dvp2api dvpStatus dvpGetUserSet(dvpHandle handle, dvpUserSet *pUserSet);


/**
*@brief ���õ�ǰ�û�����
*@param[in] handle ������
*@param[in] UserSet ��ǰ�û�����
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP2_API_CONFIG
*@see dvpGetFunctionInfo
*@see dvpGetUserSet
*@note ���ϵ��ʼ���ã������ڴ��ڲ����洢�������
*/
dvp2api dvpStatus dvpSetUserSet(dvpHandle handle, dvpUserSet UserSet);


/**
*@brief ��ȡ����IO�ĵ�ƽ״̬
*@param[in] handle ������
*@param[in] inputIo ����IO
*@param[out] pInputIoLevel ����IO�ĵ�ƽ״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@deprecated
*@ingroup DVP_LINE
*/
dvp2api dvpStatus dvpGetInputIoLevel(dvpHandle handle, dvpInputIo inputIo, bool *pInputIoLevel);


/**
*@brief ��ȡ@link dvpLineMode::LINE_MODE_OUTPUT �������@endlink �ĵ�ƽ
*@param[in] handle ������
*@param[in] line ����
*@param[out] pLineLevel @link dvpLineMode::LINE_MODE_OUTPUT �������@endlink �ĵ�ƽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*@see dvpSetLineLevel
*/
dvp2api dvpStatus dvpGetLineLevel(dvpHandle handle, dvpLine line, bool *pLineLevel);


/**
*@brief ����@link dvpLineMode::LINE_MODE_OUTPUT �������@endlink �ĵ�ƽ
*@param[in] handle ������
*@param[in] line ����
*@param[in] LineLevel @link dvpLineMode::LINE_MODE_OUTPUT �������@endlink �ĵ�ƽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*@see dvpGetLineLevel
*/
dvp2api dvpStatus dvpSetLineLevel(dvpHandle handle, dvpLine line, bool LineLevel);


/**
*@brief ��ȡ���ŵ�ƽ����ʹ��
*@param[in] handle ������
*@param[in] line ����
*@param[out] pLineInverter ���ŵ�ƽ����ʹ��
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*@see dvpSetLineInverter
*/
dvp2api dvpStatus dvpGetLineInverter(dvpHandle handle, dvpLine line, bool *pLineInverter);


/**
*@brief �������ŵ�ƽ����ʹ��
*@param[in] handle ������
*@param[in] line ����
*@param[in] LineInverter ���ŵ�ƽ����ʹ��
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*@see dvpGetLineInverter
*/
dvp2api dvpStatus dvpSetLineInverter(dvpHandle handle, dvpLine line, bool LineInverter);


/**
*@brief ��ȡ���ŵ�I/Oģʽ
*@param[in] handle ������
*@param[in] line ����
*@param[out] pLineMode ���ŵ�I/Oģʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*@see dvpSetLineMode
*/
dvp2api dvpStatus dvpGetLineMode(dvpHandle handle, dvpLine line, dvpLineMode *pLineMode);


/**
*@brief �������ŵ�I/Oģʽ
*@param[in] handle ������
*@param[in] line ����
*@param[in] LineMode ���ŵ�I/Oģʽ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*@see dvpGetLineMode
*/
dvp2api dvpStatus dvpSetLineMode(dvpHandle handle, dvpLine line, dvpLineMode LineMode);


/**
*@brief ��ȡ���ŵ�����ź�Դ
*@param[in] handle ������
*@param[in] line ����
*@param[out] pLineSource ���ŵ�����ź�Դ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*@see dvpSetLineSource
*/
dvp2api dvpStatus dvpGetLineSource(dvpHandle handle, dvpLine line, dvpLineSource *pLineSource);


/**
*@brief �������ŵ�����ź�Դ
*@param[in] handle ������
*@param[in] line ����
*@param[in] LineSource ���ŵ�����ź�Դ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*@see dvpGetLineSource
*/
dvp2api dvpStatus dvpSetLineSource(dvpHandle handle, dvpLine line, dvpLineSource LineSource);


/**
*@brief ��ȡ���ŵ�ƽ״̬�Ļض�
*@param[in] handle ������
*@param[in] line ����
*@param[out] pLineStatus ���ŵ�ƽ״̬�Ļض�
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_LINE
*/
dvp2api dvpStatus dvpGetLineStatus(dvpHandle handle, dvpLine line, bool *pLineStatus);


/**
*@brief ��ȡ���IO�ĵ�ƽ״̬
*@param[in] handle ������
*@param[in] outputIo ���IO
*@param[out] pOutputIoLevel ���IO�ĵ�ƽ״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@deprecated
*@ingroup DVP_LINE
*@see dvpSetOutputIoLevel
*/
dvp2api dvpStatus dvpGetOutputIoLevel(dvpHandle handle, dvpOutputIo outputIo, bool *pOutputIoLevel);


/**
*@brief �������IO�ĵ�ƽ״̬
*@param[in] handle ������
*@param[in] outputIo ���IO
*@param[in] OutputIoLevel ���IO�ĵ�ƽ״̬
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@deprecated
*@ingroup DVP_LINE
*@see dvpGetOutputIoLevel
*/
dvp2api dvpStatus dvpSetOutputIoLevel(dvpHandle handle, dvpOutputIo outputIo, bool OutputIoLevel);


/**
*@brief ��ȡ���IO�Ĺ�������
*@param[in] handle ������
*@param[in] outputIo ���IO
*@param[out] pOutputIoFunction ���IO�Ĺ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@deprecated
*@ingroup DVP_LINE
*@see dvpSetOutputIoFunction
*/
dvp2api dvpStatus dvpGetOutputIoFunction(dvpHandle handle, dvpOutputIo outputIo, dvpOutputIoFunction *pOutputIoFunction);


/**
*@brief �������IO�Ĺ�������
*@param[in] handle ������
*@param[in] outputIo ���IO
*@param[in] OutputIoFunction ���IO�Ĺ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@deprecated
*@ingroup DVP_LINE
*@see dvpGetOutputIoFunction
*/
dvp2api dvpStatus dvpSetOutputIoFunction(dvpHandle handle, dvpOutputIo outputIo, dvpOutputIoFunction OutputIoFunction);


/**
*@brief ��ȡ����IO�Ĺ�������
*@param[in] handle ������
*@param[in] inputIo ����IO
*@param[out] pInputIoFunction ����IO�Ĺ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@deprecated
*@ingroup DVP_LINE
*@see dvpSetInputIoFunction
*/
dvp2api dvpStatus dvpGetInputIoFunction(dvpHandle handle, dvpInputIo inputIo, dvpInputIoFunction *pInputIoFunction);


/**
*@brief ��������IO�Ĺ�������
*@param[in] handle ������
*@param[in] inputIo ����IO
*@param[in] InputIoFunction ����IO�Ĺ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@deprecated
*@ingroup DVP_LINE
*@see dvpGetInputIoFunction
*/
dvp2api dvpStatus dvpSetInputIoFunction(dvpHandle handle, dvpInputIo inputIo, dvpInputIoFunction InputIoFunction);


/**
*@brief ��ȡ��ǰ�����Ʒ���ѡ�������
*@param[in] handle ������
*@param[out] pStreamFlowCtrlSel ��ǰ�����Ʒ���ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@note һ�������������
*@see dvpGetStreamFlowCtrlSelDescr
*@see dvpGetStreamFlowCtrlSelDetail
*@see dvpSetStreamFlowCtrlSel
*/
dvp2api dvpStatus dvpGetStreamFlowCtrlSel(dvpHandle handle, dvpUint32 *pStreamFlowCtrlSel);


/**
*@brief ���õ�ǰ�����Ʒ���ѡ�������
*@param[in] handle ������
*@param[in] StreamFlowCtrlSel ��ǰ�����Ʒ���ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@note һ�������������
*@see dvpGetStreamFlowCtrlSelDescr
*@see dvpGetStreamFlowCtrlSelDetail
*@see dvpGetStreamFlowCtrlSel
*/
dvp2api dvpStatus dvpSetStreamFlowCtrlSel(dvpHandle handle, dvpUint32 StreamFlowCtrlSel);


/**
*@brief ��ȡ�����Ʒ���ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pStreamFlowCtrlSelDescr �����Ʒ���ѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@note һ�������������
*@see dvpGetStreamFlowCtrlSel
*@see dvpGetStreamFlowCtrlSelDetail
*/
dvp2api dvpStatus dvpGetStreamFlowCtrlSelDescr(dvpHandle handle, dvpSelectionDescr *pStreamFlowCtrlSelDescr);


/**
*@brief ��ȡ��ǰ�����Ʒ���ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] StreamFlowCtrlSel �����Ʒ���������
*@param[out] pStreamFlowCtrlSelDetail ��ǰ�����Ʒ���ѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_ADVANCED
*@note һ�������������
*@see dvpGetStreamFlowCtrlSel
*@see dvpGetStreamFlowCtrlSelDescr
*/
dvp2api dvpStatus dvpGetStreamFlowCtrlSelDetail(dvpHandle handle, dvpUint32 StreamFlowCtrlSel, dvpSelection *pStreamFlowCtrlSelDetail);


/**
*@brief ��ȡ��ǰɫ�ʷ���ѡ�������
*@param[in] handle ������
*@param[out] pColorSolutionSel ��ǰɫ�ʷ���ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpGetGamma
*@note ����ɫ�ʻ�ԭЧ����ʹ��ɫ�ʷ������۵������Ӿ�
*@see dvpGetColorSolutionSelDescr
*@see dvpGetColorSolutionSelDetail
*@see dvpSetColorSolutionSel
*/
dvp2api dvpStatus dvpGetColorSolutionSel(dvpHandle handle, dvpUint32 *pColorSolutionSel);


/**
*@brief ���õ�ǰɫ�ʷ���ѡ�������
*@param[in] handle ������
*@param[in] ColorSolutionSel ��ǰɫ�ʷ���ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpGetGamma
*@note ����ɫ�ʻ�ԭЧ����ʹ��ɫ�ʷ������۵������Ӿ�
*@see dvpGetColorSolutionSelDescr
*@see dvpGetColorSolutionSelDetail
*@see dvpGetColorSolutionSel
*/
dvp2api dvpStatus dvpSetColorSolutionSel(dvpHandle handle, dvpUint32 ColorSolutionSel);


/**
*@brief ��ȡɫ�ʷ���ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pColorSolutionSelDescr ɫ�ʷ���ѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpGetGamma
*@note ����ɫ�ʻ�ԭЧ����ʹ��ɫ�ʷ������۵������Ӿ�
*@see dvpGetColorSolutionSel
*@see dvpGetColorSolutionSelDetail
*/
dvp2api dvpStatus dvpGetColorSolutionSelDescr(dvpHandle handle, dvpSelectionDescr *pColorSolutionSelDescr);


/**
*@brief ��ȡ��ǰɫ�ʷ���ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] ColorSolutionSel ɫ�ʷ���������
*@param[out] pColorSolutionSelDetail ��ǰɫ�ʷ���ѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@see dvpGetGamma
*@note ����ɫ�ʻ�ԭЧ����ʹ��ɫ�ʷ������۵������Ӿ�
*@see dvpGetColorSolutionSel
*@see dvpGetColorSolutionSelDescr
*/
dvp2api dvpStatus dvpGetColorSolutionSelDetail(dvpHandle handle, dvpUint32 ColorSolutionSel, dvpSelection *pColorSolutionSelDetail);


/**
*@brief ��ȡ��ǰBayerתRGB�����㷨ѡ�������
*@param[in] handle ������
*@param[out] pBayerDecodeSel ��ǰBayerתRGB�����㷨ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@note Ӱ���ɫͼ���ϸ�ںͱ�ԵЧ��
*@see dvpGetBayerDecodeSelDescr
*@see dvpGetBayerDecodeSelDetail
*@see dvpSetBayerDecodeSel
*/
dvp2api dvpStatus dvpGetBayerDecodeSel(dvpHandle handle, dvpUint32 *pBayerDecodeSel);


/**
*@brief ���õ�ǰBayerתRGB�����㷨ѡ�������
*@param[in] handle ������
*@param[in] BayerDecodeSel ��ǰBayerתRGB�����㷨ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@note Ӱ���ɫͼ���ϸ�ںͱ�ԵЧ��
*@see dvpGetBayerDecodeSelDescr
*@see dvpGetBayerDecodeSelDetail
*@see dvpGetBayerDecodeSel
*/
dvp2api dvpStatus dvpSetBayerDecodeSel(dvpHandle handle, dvpUint32 BayerDecodeSel);


/**
*@brief ��ȡBayerתRGB�����㷨ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pBayerDecodeSelDescr BayerתRGB�����㷨ѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@note Ӱ���ɫͼ���ϸ�ںͱ�ԵЧ��
*@see dvpGetBayerDecodeSel
*@see dvpGetBayerDecodeSelDetail
*/
dvp2api dvpStatus dvpGetBayerDecodeSelDescr(dvpHandle handle, dvpSelectionDescr *pBayerDecodeSelDescr);


/**
*@brief ��ȡ��ǰBayerתRGB�����㷨ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] BayerDecodeSel BayerתRGB�����㷨������
*@param[out] pBayerDecodeSelDetail ��ǰBayerתRGB�����㷨ѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_COLOR
*@note Ӱ���ɫͼ���ϸ�ںͱ�ԵЧ��
*@see dvpGetBayerDecodeSel
*@see dvpGetBayerDecodeSelDescr
*/
dvp2api dvpStatus dvpGetBayerDecodeSelDetail(dvpHandle handle, dvpUint32 BayerDecodeSel, dvpSelection *pBayerDecodeSelDetail);


/**
*@brief ��ȡ��ǰԭʼͼ���ʽѡ�������
*@param[in] handle ������
*@param[out] pSourceFormatSel ��ǰԭʼͼ���ʽѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@note ��ʹ��@link dvpStreamFormat @endlink�ȼ�
*@see dvpGetSourceFormatSelDescr
*@see dvpGetSourceFormatSelDetail
*@see dvpSetSourceFormatSel
*/
dvp2api dvpStatus dvpGetSourceFormatSel(dvpHandle handle, dvpUint32 *pSourceFormatSel);


/**
*@brief ���õ�ǰԭʼͼ���ʽѡ�������
*@param[in] handle ������
*@param[in] SourceFormatSel ��ǰԭʼͼ���ʽѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@note ��ʹ��@link dvpStreamFormat @endlink�ȼ�
*@see dvpGetSourceFormatSelDescr
*@see dvpGetSourceFormatSelDetail
*@see dvpGetSourceFormatSel
*/
dvp2api dvpStatus dvpSetSourceFormatSel(dvpHandle handle, dvpUint32 SourceFormatSel);


/**
*@brief ��ȡԭʼͼ���ʽѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pSourceFormatSelDescr ԭʼͼ���ʽѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@note ��ʹ��@link dvpStreamFormat @endlink�ȼ�
*@see dvpGetSourceFormatSel
*@see dvpGetSourceFormatSelDetail
*/
dvp2api dvpStatus dvpGetSourceFormatSelDescr(dvpHandle handle, dvpSelectionDescr *pSourceFormatSelDescr);


/**
*@brief ��ȡ��ǰԭʼͼ���ʽѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] SourceFormatSel ԭʼͼ���ʽ������
*@param[out] pSourceFormatSelDetail ��ǰԭʼͼ���ʽѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@note ��ʹ��@link dvpStreamFormat @endlink�ȼ�
*@see dvpGetSourceFormatSel
*@see dvpGetSourceFormatSelDescr
*/
dvp2api dvpStatus dvpGetSourceFormatSelDetail(dvpHandle handle, dvpUint32 SourceFormatSel, dvpFormatSelection *pSourceFormatSelDetail);


/**
*@brief ��ȡ��ǰ���ͼ���ʽѡ�������
*@param[in] handle ������
*@param[out] pTargetFormatSel ��ǰ���ͼ���ʽѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@note ��ʹ��@link dvpStreamFormat @endlink�ȼ�
*@see dvpGetTargetFormatSelDescr
*@see dvpGetTargetFormatSelDetail
*@see dvpSetTargetFormatSel
*/
dvp2api dvpStatus dvpGetTargetFormatSel(dvpHandle handle, dvpUint32 *pTargetFormatSel);


/**
*@brief ���õ�ǰ���ͼ���ʽѡ�������
*@param[in] handle ������
*@param[in] TargetFormatSel ��ǰ���ͼ���ʽѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@note ��ʹ��@link dvpStreamFormat @endlink�ȼ�
*@see dvpGetTargetFormatSelDescr
*@see dvpGetTargetFormatSelDetail
*@see dvpGetTargetFormatSel
*/
dvp2api dvpStatus dvpSetTargetFormatSel(dvpHandle handle, dvpUint32 TargetFormatSel);


/**
*@brief ��ȡ���ͼ���ʽѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pTargetFormatSelDescr ���ͼ���ʽѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@note ��ʹ��@link dvpStreamFormat @endlink�ȼ�
*@see dvpGetTargetFormatSel
*@see dvpGetTargetFormatSelDetail
*/
dvp2api dvpStatus dvpGetTargetFormatSelDescr(dvpHandle handle, dvpSelectionDescr *pTargetFormatSelDescr);


/**
*@brief ��ȡ��ǰ���ͼ���ʽѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] TargetFormatSel ���ͼ���ʽ������
*@param[out] pTargetFormatSelDetail ��ǰ���ͼ���ʽѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_FORMAT
*@note ��ʹ��@link dvpStreamFormat @endlink�ȼ�
*@see dvpGetTargetFormatSel
*@see dvpGetTargetFormatSelDescr
*/
dvp2api dvpStatus dvpGetTargetFormatSelDetail(dvpHandle handle, dvpUint32 TargetFormatSel, dvpFormatSelection *pTargetFormatSelDetail);


/**
*@brief ��ȡ��ǰ�ֱ���ģʽѡ�������
*@param[in] handle ������
*@param[out] pResolutionModeSel ��ǰ�ֱ���ģʽѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@note ����sum��������ͣ���bin�����ڳ�������ģʽ����������������ֱ���
*@see dvpGetQuickRoiSel
*@see dvpGetRoi
*@see dvpGetResolutionModeSelDescr
*@see dvpGetResolutionModeSelDetail
*@see dvpSetResolutionModeSel
*/
dvp2api dvpStatus dvpGetResolutionModeSel(dvpHandle handle, dvpUint32 *pResolutionModeSel);


/**
*@brief ���õ�ǰ�ֱ���ģʽѡ�������
*@param[in] handle ������
*@param[in] ResolutionModeSel ��ǰ�ֱ���ģʽѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@note ����sum��������ͣ���bin�����ڳ�������ģʽ����������������ֱ���
*@see dvpGetQuickRoiSel
*@see dvpGetRoi
*@see dvpGetResolutionModeSelDescr
*@see dvpGetResolutionModeSelDetail
*@see dvpGetResolutionModeSel
*/
dvp2api dvpStatus dvpSetResolutionModeSel(dvpHandle handle, dvpUint32 ResolutionModeSel);


/**
*@brief ��ȡ�ֱ���ģʽѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pResolutionModeSelDescr �ֱ���ģʽѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@note ����sum��������ͣ���bin�����ڳ�������ģʽ����������������ֱ���
*@see dvpGetQuickRoiSel
*@see dvpGetRoi
*@see dvpGetResolutionModeSel
*@see dvpGetResolutionModeSelDetail
*/
dvp2api dvpStatus dvpGetResolutionModeSelDescr(dvpHandle handle, dvpSelectionDescr *pResolutionModeSelDescr);


/**
*@brief ��ȡ��ǰ�ֱ���ģʽѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] ResolutionModeSel �ֱ���ģʽ������
*@param[out] pResolutionModeSelDetail ��ǰ�ֱ���ģʽѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@note ����sum��������ͣ���bin�����ڳ�������ģʽ����������������ֱ���
*@see dvpGetQuickRoiSel
*@see dvpGetRoi
*@see dvpGetResolutionModeSel
*@see dvpGetResolutionModeSelDescr
*/
dvp2api dvpStatus dvpGetResolutionModeSelDetail(dvpHandle handle, dvpUint32 ResolutionModeSel, dvpResolutionMode *pResolutionModeSelDetail);


/**
*@brief ��ȡ��ǰ�Զ��عⷽ��ѡ�������
*@param[in] handle ������
*@param[out] pAeSchemeSel ��ǰ�Զ��عⷽ��ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@note Ӧ�����ض��Ĺ�Դ�ͳ�����������΢��
*@see dvpGetAeSchemeSelDescr
*@see dvpGetAeSchemeSelDetail
*@see dvpSetAeSchemeSel
*/
dvp2api dvpStatus dvpGetAeSchemeSel(dvpHandle handle, dvpUint32 *pAeSchemeSel);


/**
*@brief ���õ�ǰ�Զ��عⷽ��ѡ�������
*@param[in] handle ������
*@param[in] AeSchemeSel ��ǰ�Զ��عⷽ��ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@note Ӧ�����ض��Ĺ�Դ�ͳ�����������΢��
*@see dvpGetAeSchemeSelDescr
*@see dvpGetAeSchemeSelDetail
*@see dvpGetAeSchemeSel
*/
dvp2api dvpStatus dvpSetAeSchemeSel(dvpHandle handle, dvpUint32 AeSchemeSel);


/**
*@brief ��ȡ�Զ��عⷽ��ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pAeSchemeSelDescr �Զ��عⷽ��ѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@note Ӧ�����ض��Ĺ�Դ�ͳ�����������΢��
*@see dvpGetAeSchemeSel
*@see dvpGetAeSchemeSelDetail
*/
dvp2api dvpStatus dvpGetAeSchemeSelDescr(dvpHandle handle, dvpSelectionDescr *pAeSchemeSelDescr);


/**
*@brief ��ȡ��ǰ�Զ��عⷽ��ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] AeSchemeSel �Զ��عⷽ��������
*@param[out] pAeSchemeSelDetail ��ǰ�Զ��عⷽ��ѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_EXPOSURE
*@note Ӧ�����ض��Ĺ�Դ�ͳ�����������΢��
*@see dvpGetAeSchemeSel
*@see dvpGetAeSchemeSelDescr
*/
dvp2api dvpStatus dvpGetAeSchemeSelDetail(dvpHandle handle, dvpUint32 AeSchemeSel, dvpSelection *pAeSchemeSelDetail);


/**
*@brief ��ȡ��ǰ����Roiѡ�������
*@param[in] handle ������
*@param[out] pQuickRoiSel ��ǰ����Roiѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@see dvpGetResolutionModeSel
*@see dvpGetRoi
*@note �൱��һ�ֵ��͵�ROI
*@see dvpGetQuickRoiSelDescr
*@see dvpGetQuickRoiSelDetail
*@see dvpSetQuickRoiSel
*/
dvp2api dvpStatus dvpGetQuickRoiSel(dvpHandle handle, dvpUint32 *pQuickRoiSel);


/**
*@brief ���õ�ǰ����Roiѡ�������
*@param[in] handle ������
*@param[in] QuickRoiSel ��ǰ����Roiѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@see dvpGetResolutionModeSel
*@see dvpGetRoi
*@note �൱��һ�ֵ��͵�ROI
*@see dvpGetQuickRoiSelDescr
*@see dvpGetQuickRoiSelDetail
*@see dvpGetQuickRoiSel
*/
dvp2api dvpStatus dvpSetQuickRoiSel(dvpHandle handle, dvpUint32 QuickRoiSel);


/**
*@brief ��ȡ����Roiѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pQuickRoiSelDescr ����Roiѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@see dvpGetResolutionModeSel
*@see dvpGetRoi
*@note �൱��һ�ֵ��͵�ROI
*@see dvpGetQuickRoiSel
*@see dvpGetQuickRoiSelDetail
*/
dvp2api dvpStatus dvpGetQuickRoiSelDescr(dvpHandle handle, dvpSelectionDescr *pQuickRoiSelDescr);


/**
*@brief ��ȡ��ǰ����Roiѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] QuickRoiSel ����Roi������
*@param[out] pQuickRoiSelDetail ��ǰ����Roiѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_SIZE
*@see dvpGetResolutionModeSel
*@see dvpGetRoi
*@note �൱��һ�ֵ��͵�ROI
*@see dvpGetQuickRoiSel
*@see dvpGetQuickRoiSelDescr
*/
dvp2api dvpStatus dvpGetQuickRoiSelDetail(dvpHandle handle, dvpUint32 QuickRoiSel, dvpQuickRoi *pQuickRoiSelDetail);


/**
*@brief ��ȡ��ǰ���زɼ�����ѡ�������
*@param[in] handle ������
*@param[out] pPixelRateSel ��ǰ���زɼ�����ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note ͨ�����ٵ�USB2�Ľӿ�ֻ��ƥ����ٵ����زɼ�
*@see dvpGetPixelRateSelDescr
*@see dvpGetPixelRateSelDetail
*@see dvpSetPixelRateSel
*/
dvp2api dvpStatus dvpGetPixelRateSel(dvpHandle handle, dvpUint32 *pPixelRateSel);


/**
*@brief ���õ�ǰ���زɼ�����ѡ�������
*@param[in] handle ������
*@param[in] PixelRateSel ��ǰ���زɼ�����ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note ͨ�����ٵ�USB2�Ľӿ�ֻ��ƥ����ٵ����زɼ�
*@see dvpGetPixelRateSelDescr
*@see dvpGetPixelRateSelDetail
*@see dvpGetPixelRateSel
*/
dvp2api dvpStatus dvpSetPixelRateSel(dvpHandle handle, dvpUint32 PixelRateSel);


/**
*@brief ��ȡ���زɼ�����ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pPixelRateSelDescr ���زɼ�����ѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note ͨ�����ٵ�USB2�Ľӿ�ֻ��ƥ����ٵ����زɼ�
*@see dvpGetPixelRateSel
*@see dvpGetPixelRateSelDetail
*/
dvp2api dvpStatus dvpGetPixelRateSelDescr(dvpHandle handle, dvpSelectionDescr *pPixelRateSelDescr);


/**
*@brief ��ȡ��ǰ���زɼ�����ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] PixelRateSel ���زɼ����ʵ�����
*@param[out] pPixelRateSelDetail ��ǰ���زɼ�����ѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note ͨ�����ٵ�USB2�Ľӿ�ֻ��ƥ����ٵ����زɼ�
*@see dvpGetPixelRateSel
*@see dvpGetPixelRateSelDescr
*/
dvp2api dvpStatus dvpGetPixelRateSelDetail(dvpHandle handle, dvpUint32 PixelRateSel, dvpSelection *pPixelRateSelDetail);


/**
*@brief ��ȡ��ǰ���͵����ݴ������ѡ�������
*@param[in] handle ������
*@param[out] pPacketSizeSel ��ǰ���͵����ݴ������ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note ���б�Ҫ��ʹ��@link #dvpGetStreamPackSize �ǵ��ʹ������@endlink
*@see dvpGetPacketSizeSelDescr
*@see dvpGetPacketSizeSelDetail
*@see dvpSetPacketSizeSel
*/
dvp2api dvpStatus dvpGetPacketSizeSel(dvpHandle handle, dvpUint32 *pPacketSizeSel);


/**
*@brief ���õ�ǰ���͵����ݴ������ѡ�������
*@param[in] handle ������
*@param[in] PacketSizeSel ��ǰ���͵����ݴ������ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note ���б�Ҫ��ʹ��@link #dvpGetStreamPackSize �ǵ��ʹ������@endlink
*@see dvpGetPacketSizeSelDescr
*@see dvpGetPacketSizeSelDetail
*@see dvpGetPacketSizeSel
*/
dvp2api dvpStatus dvpSetPacketSizeSel(dvpHandle handle, dvpUint32 PacketSizeSel);


/**
*@brief ��ȡ���͵����ݴ������ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pPacketSizeSelDescr ���͵����ݴ������ѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note ���б�Ҫ��ʹ��@link #dvpGetStreamPackSize �ǵ��ʹ������@endlink
*@see dvpGetPacketSizeSel
*@see dvpGetPacketSizeSelDetail
*/
dvp2api dvpStatus dvpGetPacketSizeSelDescr(dvpHandle handle, dvpSelectionDescr *pPacketSizeSelDescr);


/**
*@brief ��ȡ��ǰ���͵����ݴ������ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] PacketSizeSel ���͵����ݴ������������
*@param[out] pPacketSizeSelDetail ��ǰ���͵����ݴ������ѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note ���б�Ҫ��ʹ��@link #dvpGetStreamPackSize �ǵ��ʹ������@endlink
*@see dvpGetPacketSizeSel
*@see dvpGetPacketSizeSelDescr
*/
dvp2api dvpStatus dvpGetPacketSizeSelDetail(dvpHandle handle, dvpUint32 PacketSizeSel, dvpSelection *pPacketSizeSelDetail);


/**
*@brief ��ȡ��ǰӲ��������ѡ�������
*@param[in] handle ������
*@param[out] pAccelerateSel ��ǰӲ��������ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note �������Ӳ��֧�֣���ɷ���GPU��ͼ��������
*@see dvpGetAccelerateSelDescr
*@see dvpGetAccelerateSelDetail
*@see dvpSetAccelerateSel
*/
dvp2api dvpStatus dvpGetAccelerateSel(dvpHandle handle, dvpUint32 *pAccelerateSel);


/**
*@brief ���õ�ǰӲ��������ѡ�������
*@param[in] handle ������
*@param[in] AccelerateSel ��ǰӲ��������ѡ�������
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note �������Ӳ��֧�֣���ɷ���GPU��ͼ��������
*@see dvpGetAccelerateSelDescr
*@see dvpGetAccelerateSelDetail
*@see dvpGetAccelerateSel
*/
dvp2api dvpStatus dvpSetAccelerateSel(dvpHandle handle, dvpUint32 AccelerateSel);


/**
*@brief ��ȡӲ��������ѡ��������������Ϣ
*@param[in] handle ������
*@param[out] pAccelerateSelDescr Ӳ��������ѡ��������������Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note �������Ӳ��֧�֣���ɷ���GPU��ͼ��������
*@see dvpGetAccelerateSel
*@see dvpGetAccelerateSelDetail
*/
dvp2api dvpStatus dvpGetAccelerateSelDescr(dvpHandle handle, dvpSelectionDescr *pAccelerateSelDescr);


/**
*@brief ��ȡ��ǰӲ��������ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] AccelerateSel Ӳ��������������
*@param[out] pAccelerateSelDetail ��ǰӲ��������ѡ��������Ӧ�ľ�����Ϣ
*@return ��Ԥ�ϵ�����£���ȷ������@link #dvpStatus::DVP_STATUS_OK DVP_STATUS_OK@endlink
*@ingroup DVP_PERFORMANCE
*@note �������Ӳ��֧�֣���ɷ���GPU��ͼ��������
*@see dvpGetAccelerateSel
*@see dvpGetAccelerateSelDescr
*/
dvp2api dvpStatus dvpGetAccelerateSelDetail(dvpHandle handle, dvpUint32 AccelerateSel, dvpSelection *pAccelerateSelDetail);


/**
*@brief ���ú�,��,����ɫ����������
*@param[in] handle ������
*@param[in] rGain ��ɫ��������
*@param[in] gGain ��ɫ��������
*@param[in] bGain ��ɫ��������
*@ingroup DVP_COLOR
*@see dvpGetRgbGain
*@see dvpSetRgbGainState
*@see dvpGetRgbGainState
*@note �����渽����@link #dvpSetAwbOperation ��ƽ��@endlink��Ч��֮�ϣ������߱˴˶���
*/
dvp2api dvpStatus dvpSetRgbGain(dvpHandle handle, float rGain, float gGain, float bGain);


/**
*@brief ��ȡ��,��,����ɫ����������
*@param[in] handle ������
*@param[out] prGain ��ɫ��������
*@param[out] pgGain ��ɫ��������
*@param[out] pbGain ��ɫ��������
*@ingroup DVP_COLOR
*@see dvpSetRgbGain
*@see dvpSetRgbGainState
*@see dvpGetRgbGainState
*/
dvp2api dvpStatus dvpGetRgbGain(dvpHandle handle, float *prGain, float *pgGain, float *pbGain);


/**
*@brief ���ú�,��,����ɫ���������湦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[in] state ��,��,����ɫ���������湦�ܵ�ʹ��״̬
*@ingroup DVP_COLOR
*@see dvpSetRgbGain
*@see dvpGetRgbGain
*@see dvpGetRgbGainState
*/
dvp2api dvpStatus dvpSetRgbGainState(dvpHandle handle, bool state);


/**
*@brief ��ȡ��,��,����ɫ���������湦�ܵ�ʹ��״̬
*@param[in] handle ������
*@param[out] pState ��,��,����ɫ���������湦�ܵ�ʹ��״̬
*@ingroup DVP_COLOR
*@see dvpSetRgbGain
*@see dvpGetRgbGain
*@see dvpSetRgbGainState
*/
dvp2api dvpStatus dvpGetRgbGainState(dvpHandle handle, bool *pState);



/** @defgroup DVP2_API_BASE ��������
*@{
*/
/**
*@brief ˢ�������ӵ�����б�����������������
*@param[out] pCount �������
*@see dvpEnum
*@see dvpOpen
*@see dvpOpenByName
*@note Ӧ����@link #dvpEnum ö��@endlink��@link #dvpOpen ��@endlink���ǰִ�У�����ͬ��һ���̣߳�
*/
dvp2api dvpStatus dvpRefresh(dvpUint32 *pCount);


/**
*@brief ��������ö�������Ϣ
*@param[in] index �������
*@param[out] pCameraInfo �����Ϣ
*@see dvpGetCameraInfo
*@code
dvpUint32 count = 0;
dvpRefresh(&count);
for (dvpUint32 i = 0; i < count; i++)
{
    dvpCameraInfo info;
    if(dvpEnum(i, &info) == DVP_STATUS_OK)
    {
        printf("Camera %d FriendlyName : %s\n", i, info.FriendlyName);
    }
}
*@endcode
*@note Ӧ����@link #dvpRefresh ˢ��@endlink�����ִ�У�����ͬ��һ���̣߳�
*@warning �����ź�@link #dvpHandle ������@endlink�ǽ�Ȼ��ͬ����������������
*/
dvp2api dvpStatus dvpEnum(dvpUint32 index, dvpCameraInfo *pCameraInfo);


/**
*@brief ����@link #dvpCameraInfo::FriendlyName �Ѻ�����@endlink�������
*@param[in] friendlyName �Ѻ�����
*@note ��ԭ���̻���ԭ������������
*@param[in] mode �򿪷�ʽ
*@param[out] pHandle ������
*@see dvpEnum
*@see dvpOpen
*@see dvpOpenByUserId
*@see dvpGetCameraInfo
*@note �˲������Զ�@link #dvpRefresh ˢ��@endlink�������
*@warning ������@link #dvpStreamCallback �ص�����@endlink��ʹ�ô˹���
*/
dvp2api dvpStatus dvpOpenByName(dvpStr friendlyName, dvpOpenMode mode, dvpHandle *pHandle);


/**
*@brief ����@link #dvpCameraInfo::UserID (User Defined Name) �û�����@endlink�������
*@param[in] UserId �û�����
*@note ���û��������ã��뾡�������ظ�
*@param[in] mode �򿪷�ʽ
*@param[out] pHandle ������
*@see dvpSetUserId
*@see dvpEnum
*@see dvpOpen
*@see dvpOpenByName
*@see dvpGetCameraInfo
*@note �˲������Զ�@link #dvpRefresh ˢ��@endlink�������
*@warning ������@link #dvpStreamCallback �ص�����@endlink��ʹ�ô˹���
*/
dvp2api dvpStatus dvpOpenByUserId(dvpStr UserId, dvpOpenMode mode, dvpHandle *pHandle);


/**
*@brief ����ö�ٵ������������
*@param[in] index �������
*@param[in] mode �򿪷�ʽ
*@param[out] pHandle ������
*@see dvpRefresh
*@see dvpEnum
*@see dvpOpenByName
*@see dvpGetCameraInfo
*@note Ӧ����@link #dvpRefresh ˢ��@endlink�����ִ�У�����ͬ��һ���̣߳�
*@warning ������@link #dvpStreamCallback �ص�����@endlink��ʹ�ô˹���
*/
dvp2api dvpStatus dvpOpen(dvpUint32 index, dvpOpenMode mode, dvpHandle *pHandle);


/**
*@brief ����������Ƿ���Ч
*@param[in] handle ������
*@param[out] pIsValid ��Ч״̬
*@note @link #dvpOpen ��@endlink�ɹ�������Ч��@link #dvpClose �ر�@endlink�ɹ�����ʧЧ
*/
dvp2api dvpStatus dvpIsValid(dvpHandle handle, bool *pIsValid);


/**
*@brief �������Ƿ�����
*@param[in] handle ������
*@param[out] pIsOnline ����״̬
*@note ����ʹ��@link #dvpRegisterEventCallback ע���¼��ص�����@endlink�ķ�ʽ��������һ״��
*/
dvp2api dvpStatus dvpIsOnline(dvpHandle handle, bool *pIsOnline);


/**
*@brief ������Ƶ���������Ҫ����Դ
*@param[in] handle ������
*@see dvpOpen
*@see dvpHold
*@see dvpStop
*@note Ϊ���������������ܻ����Ľϳ���ʱ�䣬��Ҫʵ�ֿ�����������ִ��@link #dvpRestart dvpRestart@endlink��ǰ�����Ѿ�ִ����@link #dvpHold dvpHold@endlink
*/
dvp2api dvpStatus dvpStart(dvpHandle handle);


/**
*@brief ֹͣ��Ƶ�����ͷ���Ӧ����Դ
*@param[in] handle ������
*@see dvpStart
*@see dvpClose
*@see dvpHold
*@note Ϊ���������������ܻ����Ľϳ���ʱ�䣬��Ҫʵ�ֿ�����ͣ����ִ��@link #dvpHold dvpHold@endlink
*@warning �����ڻص������е��ô˽ӿڣ�����ᵼ���߳�����
*/
dvp2api dvpStatus dvpStop(dvpHandle handle);


/**
*@brief ��ѯ��Ƶ���Ƿ�����ͣ״̬
*@param[in] handle ������
*@param[out] pIsHold ��ͣ״̬
*@see dvpHold
*@see dvpRestart
*/
dvp2api dvpStatus dvpIsHold(dvpHandle handle, bool *pIsHold);


/**
*@brief ��ȡһ֡ͼ��
*@param[in] handle ������
*@param[out] pFrame ֡��Ϣ
*@param[out] pBuffer ͼ�����ݵ��ڴ��׵�ַ @warning �����ֶ��ͷ�
*@param[in] timeout ��ʱʱ�䣨���룩
*@see dvpGetFrameBuffer
*@see dvpStreamCallback
*@note ����@link #dvpStart ����@endlink��Ƶ��������ʹ�ô˹���
*@warning �ɱ�������õ�ͼ�����ݻ��棬����һ�ε��ñ�����ʱ���������Ч����ˣ��ڶ��߳�ͬʱ���ͼ���Ӧ���У���Ҫ�����߳�ͬ�����ٽ�α���
*/
dvp2api dvpStatus dvpGetFrame(dvpHandle handle, dvpFrame *pFrame, void **pBuffer, dvpUint32 timeout);


/**
*@brief ͬʱ��ȡʱ�����֡ID��ͬ��ԭʼ�ɼ�֡��Ŀ�����֡
*@param[in] handle ������
*@param[out] pRaw ԭʼ�ɼ�֡
*@param[out] pOut Ŀ�����֡
*@param[in] timeout ��ʱʱ�䣨���룩
*@see dvpGetFrame
*@note ����@link #dvpStart ����@endlink��Ƶ��������ʹ�ô˹���
*@warning �ɱ�������õ�ͼ�����ݻ��棬����һ�ε��ñ�����ʱ���������Ч����ˣ��ڶ��߳�ͬʱ���ͼ���Ӧ���У���Ҫ�����߳�ͬ�����ٽ�α���
*/
dvp2api dvpStatus dvpGetFrameBuffer(dvpHandle handle, dvpFrameBuffer *pRaw, dvpFrameBuffer *pOut, dvpUint32 timeout);


/**
*@brief ���û��߳��ж�Դͼ����У�ISP���������õ�Ŀ��ͼ��
*@param[in] handle ������
*@param[in] pSourceFrame Դ֡��Ϣ
*@note ͨ����@link #dvpGetFrame dvpGetFrame@endlink ���� 
*@param[in] pSourceBuffer Դ֡ͼ�����ݵ��ڴ��׵�ַ
*@note ͨ����@link #dvpGetFrame dvpGetFrame@endlink ����
*@param[out] pTargetFrame Ŀ��֡��Ϣ
*@param[out] pTargetBuffer �ڴ��׵�ַ
*@note �����û�����������ͷ�
*@param[in] targetBufferSize �ڴ��ֽ���
*@note ����ڻ����Ŀ��ͼ���������
*@param[in] targetFormat Ŀ��ͼ���ʽ
*@see dvpGetFrame
*@note ����@link #dvpStart ����@endlink��Ƶ��������ʹ�ô˹���
*@warning �����@link #dvpStreamCallback ��Ƶ���ص�����@endlink��ʹ�ô˹��ܣ���ֻ��ע��Ϊ@link #dvpStreamEvent::STREAM_EVENT_FRAME_THREAD STREAM_EVENT_FRAME_THREAD@endlink�¼�����
*/
dvp2api dvpStatus dvpProcessImage(dvpHandle handle, const dvpFrame *pSourceFrame, const void *pSourceBuffer, dvpFrame *pTargetFrame, void *pTargetBuffer, dvpUint32 targetBufferSize, dvpStreamFormat targetFormat);


/**
*@brief ���浱ǰ���״̬
*@param[in] handle ������
*@param[in] part ������Ϣ����Ĺ��ܷ���
*@param[in] level ������Ϣ����ļ���
*@param[in] bForce �Ƿ�ǿ�Ƽ�¼���ļ��������Ƿ�����־�ļ���¼
*@param[in] text ���Ա�����ص��ı����ݣ������뵽��־�ļ�
*@param[in] param ���Ӳ�����һ��������봫0
*@warning ��������Ƶ������
*@note ���û��ڷ����쳣ʱ�����������øýӿڣ���ץȡ��ǰ���豸״̬��Ϣ������¼����־�ļ���
*/
dvp2api dvpStatus dvpDebugReport(dvpHandle handle, dvpReportPart part, dvpReportLevel level, bool bForce, dvpStr text, dvpUint32 param);


/**
*@brief �ر���������������״̬
*@param[in] handle ������
*@see dvpStop
*@see dvpIsValid
*@warning ������@link #dvpStreamCallback �ص�����@endlink��ʹ�ô˹���
*@warning �ر�����������������ٿ��á������ٴδ����ʱ���ֿ��ܻ�õ���ͬ�ľ��ֵ
*/
dvp2api dvpStatus dvpClose(dvpHandle handle);



/** @defgroup DVP2_API_CALLBACK �ص�����
*@warning �����ڻص������е����κ���Ҫ@link #dvpStop ֹͣ��Ƶ��@endlink�ĺ�����ĳЩ���������Ե��Զ�ֹͣ��Ƶ����ͬ��Ӧ������
*@{
*/
/** @brief ��Ƶ���ص�����
*@param[in] handle ������
*@param[in] event �¼�����
*@param[in] pContext �û�ָ��
*@param[in] pFrame ֡��Ϣ
*@param[in] pBuffer ͼ������
*@see dvpRegisterStreamCallback
*@see dvpUnregisterStreamCallback
*@note �����ڻص������У�@link #dvpProcessImage ����@endlink��@link #dvpDrawPicture ��ʾ@endlink��@link #dvpSavePicture �洢@endlinkͼ��
*@warning �����ڻص������У�@link #dvpOpen ��@endlink��@link #dvpClose �ر�@endlink��@link #dvpStart ����@endlink��@link #dvpStop ֹͣ@endlink������Լ�@link #dvpGetFrame ץȡͼ��@endlink  */
typedef dvpInt32(*dvpStreamCallback)(dvpHandle handle, dvpStreamEvent event, void *pContext, dvpFrame *pFrame, void *pBuffer);

/**
*@brief ע����Ƶ���ص�����
*@param[in] handle ������
*@param[in] proc �ص������ĺ���ָ��
*@param[in] event �ص��������¼�����
*@param[in] pContext �ص��������û�ָ��
*@see dvpUnregisterStreamCallback
*/
dvp2api dvpStatus dvpRegisterStreamCallback(dvpHandle handle, dvpStreamCallback proc, dvpStreamEvent event, void *pContext);


/**
*@brief ע����Ƶ���ص�����
*@param[in] handle ������
*@param[in] proc �ص������ĺ���ָ��
*@param[in] event �ص��������¼�����
*@param[in] pContext �ص��������û�ָ��
*@note ����@link #dvpRegisterStreamCallback ע��ص�����@endlink��ʹ�õĲ���һ�²���ע����Ӧ�Ļص�����
*/
dvp2api dvpStatus dvpUnregisterStreamCallback(dvpHandle handle, dvpStreamCallback proc, dvpStreamEvent event, void *pContext);


/** @brief �¼�֪ͨ�ص�����
*@param[in] handle ������
*@param[in] event �¼�����
*@param[in] pContext �û�ָ��
*@param[in] param �������¼���������
*@param[in] pVariant �������¼���������
*@see dvpRegisterEventCallback */
typedef dvpInt32(*dvpEventCallback)(dvpHandle handle, dvpEvent event, void *pContext, dvpInt32 param, struct dvpVariant *pVariant);

/**
*@brief ע���¼�֪ͨ�Ļص�����
*@param[in] handle ������
*@param[in] proc �ص������ĺ���ָ��
*@param[in] event �ص��������¼�����
*@param[in] pContext �ص��������û�ָ��
*@see dvpUnregisterEventCallback
*/
dvp2api dvpStatus dvpRegisterEventCallback(dvpHandle handle, dvpEventCallback proc, dvpEvent event, void *pContext);


/**
*@brief ע���¼�֪ͨ�Ļص�����
*@param[in] handle ������
*@param[in] proc �ص������ĺ���ָ��
*@param[in] event �ص��������¼�����
*@param[in] pContext �ص��������û�ָ��
*@note ����@link #dvpRegisterEventCallback ע��ص�����@endlink��ʹ�õĲ���һ�²���ע����Ӧ�Ļص�����
*/
dvp2api dvpStatus dvpUnregisterEventCallback(dvpHandle handle, dvpEventCallback proc, dvpEvent event, void *pContext);


/** @} end of DVP2_API_CALLBACK */

/** @defgroup DVP2_API_CONFIG �浵����
*@{
*/
/**
*@brief ����Ĭ������
*@param[in] handle ������
*@see dvpLoadConfig
*@see dvpSaveConfig
*@warning �Ḳ�ǵ�ǰ���ã����б�Ҫ��������@link #dvpSaveConfig ���ݵ�ǰ����@endlink�������ļ�
*/
dvp2api dvpStatus dvpLoadDefault(dvpHandle handle);


/**
*@brief �������ļ��м�������
*@param[in] handle ������
*@param[in] path �����ļ���·�����ļ������Զ�ѡ��·��������ָ�루�Զ�ѡ��·�����ļ�����
*@see dvpLoadDefault
*@see dvpSaveConfig
*@note �浵·��ͨ��λ��<a href="C:/ProgramData/DO3THINK/DVP2">C:/ProgramData/DO3THINK/DVP2</a>
*@warning �Ḳ�ǵ�ǰ���ã����б�Ҫ��������@link #dvpSaveConfig ���ݵ�ǰ����@endlink�������ļ�
*/
dvp2api dvpStatus dvpLoadConfig(dvpHandle handle, dvpStr path);


/**
*@brief ��ǰ���ñ��浽�����ļ�
*@param[in] handle ������
*@param[in] path �����ļ���·�����ļ������Զ�ѡ��·��������ָ�루�Զ�ѡ��·�����ļ�����
*@see dvpLoadDefault
*@see dvpLoadConfig
*@note �浵·��ͨ��λ��<a href="C:/ProgramData/DO3THINK/DVP2">C:/ProgramData/DO3THINK/DVP2</a>
*@warning ��ȷ����ǰ����ӵ�жԴ��ļ���д��Ȩ��
*/
dvp2api dvpStatus dvpSaveConfig(dvpHandle handle, dvpStr path);


/**
*@brief �����û����õ�����洢��
*@param[in] handle ������
*@param[in] UserSet Ŀ���û�����
*@see dvpLoadUserSet
*@see dvpGetUserSet
*@warning ���ɱ���Ϊ@link #dvpUserSet::USER_SET_DEFAULT Ĭ���û�����@endlink
*/
dvp2api dvpStatus dvpSaveUserSet(dvpHandle handle, dvpUserSet UserSet);


/**
*@brief ������洢�������û�����
*@param[in] handle ������
*@param[in] UserSet Ŀ���û�����
*@see dvpSaveUserSet
*@see dvpGetUserSet
*@note ���Դ�@link #dvpUserSet::USER_SET_DEFAULT Ĭ���û�����@endlink����
*/
dvp2api dvpStatus dvpLoadUserSet(dvpHandle handle, dvpUserSet UserSet);


/** @} end of DVP2_API_CONFIG */
/** @} end of DVP2_API_BASE */

/** @defgroup DVP2_API_EXTEND ʵ�ù���
*@{
*/
/**
*@brief ��ͼ�񱣴浽�ļ�
*@param[in] pFrame ֡��Ϣ
*@param[in] pBuffer ͼ�����ݵ��ڴ��׵�ַ��Ŀǰ֧�ֵ����ݸ�ʽ������RAW, RGB24��
*@param[in] file �ļ���������·����ͼ���ļ��ĸ�ʽ���ļ�����չ����������Ŀǰ֧�ֵ�ͼ���ʽ������bmp, jpeg, jpg, png, tiff, tif, gif, dat(��ͼ������)��
*@param[in] quality ͼ��Ʒ�ʣ�����jpeg��ʽ��Ч������ȡֵ��Χ��[1,100]
*@see dvpGetFrame
*@see dvpStreamCallback
*/
dvp2api dvpStatus dvpSavePicture(const dvpFrame *pFrame, const void *pBuffer, dvpStr file, dvpInt32 quality);


/**
*@brief ����ָ���ֱ���ץȡ������ͼ��
*@param[in] handle ������
*@param[in] ResoulutionModeSel �ֱ���ģʽ@link #dvpGetResolutionModeSel ����@endlink
*@param[in] roi @link #dvpGetRoi ROI@endlinkָ�룬���ΪNULLָ�룬���Ǵ˷ֱ���ģʽ�µ�������
*@param[in] timeout @link #dvpGetFrame �ɼ�@endlink��ʱʱ��
*@param[in] filePath �ļ���������·����ͼ���ļ��ĸ�ʽ���ļ�����չ����������Ŀǰ֧�ֵ�ͼ���ʽ������bmp, jpeg, jpg, png, tiff, tif, gif, dat(��ͼ������)��
*@param[in] quality ͼ��Ʒ�ʣ�����jpeg��ʽ��Ч������ȡֵ��Χ��[1,100]
*@see dvpSavePicture
*/
dvp2api dvpStatus dvpCaptureFile(dvpHandle handle, dvpUint32 ResoulutionModeSel, dvpRegion *roi, dvpUint32 timeout, dvpStr filePath, dvpInt32 quality);


#ifdef _WIN32
/**
*@brief �ڴ�������ʾͼ��
*@param[in] pFrame ֡��Ϣ
*@param[in] pBuffer ͼ�����ݵ��ڴ��׵�ַ��Ŀǰ֧�ֵ����ݸ�ʽ������@link #dvpImageFormat::FORMAT_MONO MONO@endlink��@link #dvpImageFormat::FORMAT_BAYER_BG BAYER@endlink�� @link #dvpImageFormat::FORMAT_BGR24 BGR24@endlink�� 
*@param[in] hWnd ������ʾͼ��Ĵ��ھ��
*@param[in] sRect ������ʾ��ͼ�����򣬿�ָ���������ͼ������
*@param[in] dRect ������ʾ�Ĵ������򣬿�ָ�����������������
*@note ������@link #dvpStreamCallback ��Ƶ���ص�����@endlink��ʹ�ô˹���
*/
dvp2api dvpStatus dvpDrawPicture(const dvpFrame *pFrame, const void *pBuffer, HWND hWnd, LPRECT sRect, LPRECT dRect);


/**
*@brief ����¼�񣬴�����Ƶ�ļ����������Ƶ�������ľ��
*@param[in] filePath ��Ƶ�ļ���������·������Ƶ�ļ��ĸ�ʽ���ļ�����չ����������Ŀǰ֧�ֵ���Ƶ��ʽ������wmv, avi��
*@param[in] width �˲����Ѿ���������Ϊ����ֵ
*@param[in] height �˲����Ѿ���������Ϊ����ֵ
*@param[in] quality ��Ƶ����Ʒ�ʣ�����avi��ʽ��Ч������ȡֵ��Χ��[1,100]
*@param[out] pHandle ��Ƶ���������
*@see dvpSetTargetFormat
*@see dvpVideoRecordWrite
*@see dvpStopVideoRecord
*@warning ŷ�޺ͺ����ȵ��������е�WINDOWS����ϵͳû������WMV��ʽ֧�֣�������Ҫ���е� <a href="https://www.codecguide.com/windows_media_codecs.htm">΢����˾��վ</a>���ز���װ��Ӧ�汾�ĸ���
*/
dvp2api dvpStatus dvpStartVideoRecord(dvpStr filePath, dvpUint32 width, dvpUint32 height, dvpInt32 quality, dvpRecordHandle *pHandle);


/**
*@brief �����Ƶ�������ľ���Ƿ���Ч
*@param[in] handle ��Ƶ���������
*@param[out] pValid ��Ч״̬
*@note @link #dvpStartVideoRecord ����¼��@endlink�ɹ�������Ч��@link #dvpStopVideoRecord ֹͣ¼��@endlink�ɹ�����ʧЧ
*/
dvp2api dvpStatus dvpIsVideoRecorderValid(dvpRecordHandle handle, bool *pValid);


/**
*@brief ����Ƶ������д����Ƶ�ļ�
*@param[in] handle ��Ƶ���������
*@param[in] pFrame ֡��Ϣ
*@param[in] pBuffer ͼ�����ݵ��ڴ��׵�ַ��Ŀǰ֧�ֵ����ݸ�ʽ������@link #dvpImageFormat::FORMAT_BGR24 BGR24@endlink��
*@see dvpGetFrame
*@see dvpStartVideoRecord
*@see dvpStopVideoRecord
*@note @link #dvpStartVideoRecord ����¼��@endlink֮ǰ������ȷ@link #dvpSetTargetFormat �趨Ŀ��ͼ���ʽ@endlink
*/
dvp2api dvpStatus dvpVideoRecordWrite(dvpRecordHandle handle, const dvpFrame *pFrame, const void *pBuffer);


/**
*@brief ֹͣ¼�񣬹ر���Ƶ�ļ������ͷ���Ƶ�������ľ��
*@param[in] handle ��Ƶ���������
*@see dvpVideoRecordWrite
*@see dvpStartVideoRecord
*/
dvp2api dvpStatus dvpStopVideoRecord(dvpRecordHandle handle);


/**
*@brief ��ʾ�������ģ̬�Ի���
*@param[in] handle ������
*@param[in] hParent �����ڵĴ��ھ��
*/
dvp2api dvpStatus dvpShowPropertyModalDialog(dvpHandle handle, HWND hParent);


#endif
/**
*@brief ������洢���ж�ȡ�û��Զ�������
*@param[in] handle ������
*@param[in] addr ����Ķ�ȡ��ַ
*@param[in, out] pBuffer ���ݵ��ڴ��׵�ַ
*@param[in] size ���ݳ���
*@see dvpWriteUserData
*@note ��ȡ�������ܴ��ڴ洢�������洢�ռ䣨ͨ��������4k�ֽڣ�
*@note ����@link #dvpOpen ��@endlink���������ʹ�ô˹���
*@warning ���ܻ����Ľϳ��ĵȴ�ʱ��
*/
dvp2api dvpStatus dvpReadUserData(dvpHandle handle, dvpUint32 addr, void *pBuffer, dvpUint32 size);


/**
*@brief ���û��Զ�������д��������洢��
*@param[in] handle ������
*@param[in] addr �����д���ַ
*@param[in] pBuffer ���ݵ��ڴ��׵�ַ
*@param[in] size ���ݳ���
*@see dvpReadUserData
*@note д���������ܴ��ڴ洢�������洢�ռ䣨ͨ��������4k�ֽڣ�
*@note ����@link #dvpOpen ��@endlink���������ʹ�ô˹���
*@warning ���ܻ����Ľϳ��ĵȴ�ʱ��
*/
dvp2api dvpStatus dvpWriteUserData(dvpHandle handle, dvpUint32 addr, const void *pBuffer, dvpUint32 size);


/**
*@brief Ϊ����趨һ��@link #dvpCameraInfo::UserID (User Defined Name) @endlink
*@param[in] handle ������
*@param[in] UserId �û�����
*@param[in, out] pLength �����ṩ���ַ������ȣ����ʵ��ʹ�õ��ַ�������
*@see dvpGetCameraInfo
*/
dvp2api dvpStatus dvpSetUserId(dvpHandle handle, dvpStr UserId, dvpUint32 *pLength);


/** @} end of DVP2_API_EXTEND */

/** @defgroup DVP2_API_INTERNAL �ڲ�����
*@{
*/
/**
*@brief ��ȡ����������������Ϣ
*@param[in] handle ������
*@param[in] command ������
*@param[in, out] pParam ����ָ��
*@param[in, out] pSize ����������ֽڴ�С�����ʵ�ʴ�С
*@warning �˺���Ϊ�ڲ�ʹ�õĺ���������ϸ����δ������������ʹ��
*/
dvp2api dvpStatus dvpGet(dvpHandle handle, dvpUint32 command, void *pParam, dvpUint32 *pSize);


/**
*@brief ��������������������Ϣ
*@param[in] handle ������
*@param[in] command ������
*@param[in, out] pParam ����ָ��
*@param[in, out] pSize ����������ֽڴ�С�����ʵ�ʴ�С
*@warning �˺���Ϊ�ڲ�ʹ�õĺ���������ϸ����δ������������ʹ��
*/
dvp2api dvpStatus dvpSet(dvpHandle handle, dvpUint32 command, const void *pParam, dvpUint32 *pSize);


/**
*@brief ����dvp
*@param[in] command ������
*@param[in] param ����
*@param[in] pData ����
*@warning �˺���Ϊ�ڲ�ʹ�õĺ���������ϸ����δ������������ʹ��
*/
dvp2api dvpStatus dvpConfig(dvpUint32 command, dvpUint32 param, const void* pData);


/**
*@brief ����ָ������Ĳ���
*@param[in] index �������
*@param[in] command ������
*@param[in] param ����
*@param[in] pData ����
*@see dvpEnum
*@warning �˺���Ϊ�ڲ�ʹ�õĺ���������ϸ����δ������������ʹ��
*/
dvp2api dvpStatus dvpConfigEx(dvpUint32 index, dvpUint32 command, dvpUint32 param, const void* pData);

/**
*@brief ��������Ĳ����ַ���
*@param[in] handle ������
*@param[in] szName ������
*@param[in] szValue ����ֵ
*@note ʹ�þ������demoʾ��
*/
dvp2api dvpStatus dvpSetConfigString(dvpHandle h, char const* szName, char const* szValue);

/**
*@brief ��ȡ����Ĳ����ַ���
*@param[in] handle ������
*@param[in] szName ������
*@param[out] szValue ����ֵ
*@note ʹ�þ������demoʾ��
*/
dvp2api dvpStatus dvpGetConfigString(dvpHandle h, char const* szName, char const** szValue);

/**
*@brief ��ȡָ������ѡ��������������Ϣ
*@param[in] handle ������
*@param[in] name ������
*@param[out] pSelectionDescr ָ������ѡ��������������Ϣ
*@note ʹ�þ������demoʾ��
*/
dvp2api dvpStatus dvpGetSelectionDescr(dvpHandle handle, dvpStr name, dvpSelectionDescr* pSelectionDescr);

/**
*@brief ��ȡָ������ѡ��������Ӧ�ľ�����Ϣ
*@param[in] handle ������
*@param[in] name ������
*@param[in] index ѡ��������
*@param[out] pSelection ѡ��������Ӧ�ľ�����Ϣ
*@note ʹ�þ������demoʾ��
*/
dvp2api dvpStatus dvpGetSelectionDetail(dvpHandle handle, dvpStr name, dvpUint32 index, dvpSelection* pSelection);

/** @} end of DVP2_API_INTERNAL */

/** @defgroup DVP_EXPOSURE �ع⹦��
*@{
*/
/** @} end of DVP_EXPOSURE */

/** @defgroup DVP_COLOR ɫ�ʵ���
*@{
*/
/** @} end of DVP_COLOR */

/** @defgroup DVP_ENHANCE ��ǿЧ��
*@{
*/
/** @} end of DVP_ENHANCE */

/** @defgroup DVP_SIZE ͼ��ߴ�
*@{
*/
/** @} end of DVP_SIZE */

/** @defgroup DVP_FORMAT ͼ���ʽ
*@{
*/
/** @} end of DVP_FORMAT */

/** @defgroup DVP_TRIGGER ��������
*@{
*/
/** @} end of DVP_TRIGGER */

/** @defgroup DVP_LINE ���Ź���
*@{
*/
/** @} end of DVP_LINE */

/** @defgroup DVP_CORRECTION ͼ��У��
*@{
*/
/** @} end of DVP_CORRECTION */

/** @defgroup DVP_PERFORMANCE ���ܵ���
*@{
*/
/** @} end of DVP_PERFORMANCE */

/** @defgroup DVP_INFORMATION ������Ϣ
*@{
*/
/** @} end of DVP_INFORMATION */

/** @defgroup DVP_ADVANCED �߼�����
*@{
*/
/** @} end of DVP_ADVANCED */

/** @defgroup DVP_LINESCAN ��ɨ���
*@{
*/
/** @} end of DVP_LINESCAN */

#endif /* __DVPCAMERA_H__ */

