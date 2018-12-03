#ifndef __HI_VO_H__
#define __HI_VO_H__

#ifdef __cplusplus
extern "C"
{
#endif

//vo设备参数
typedef struct _hi_vo_dev_param_s{
	uint32_t m_u32VoDevID;		//设备ID
	uint32_t m_u32Width;		//图像宽
	uint32_t m_u32Height;		//图像高
	uint32_t m_u32FrameRate;	//帧率
	uint32_t m_u32BgColor;		//背景色
	char m_strIntfTypeName[16];	//接口类型名，如vga,hdmi,cvbs,btt1120	
	uint8_t m_bInterlaced;		//是否隔行
}hi_vo_dev_param_t;

//vo视频成参数
typedef struct _hi_vo_layer_param_s{
	int32_t m_i32VoLayerID;			//视频层ID
	uint32_t m_u32Width;			//视频层宽度（设备宽度）
	uint32_t m_u32Height;			//视频层高度（设备高度）
	uint32_t m_u32FrameRate;		//刷新帧率
	int32_t m_i32DispPosX;			//显示区域起点X坐标
	int32_t m_i32DispPosY;			//显示区域起点Y坐标
	uint32_t m_u32DispWidth;		//显示区域宽度
	uint32_t m_u32DispHeight;		//显示区域高度	
	char m_strPixelFormat[16];		//像素格式,example "yuvsp420"、"rgb_p888"
}hi_vo_layer_param_t;

//hdmi参数
typedef struct _hi_hdmi_param_s{
	int32_t m_i32HdmiID;			//HDMI ID
	char m_strIntfSync[16];			//接口时序 如720p50/pal/ntsc
	uint8_t m_bHDCPEnable;			//HDCP使能
	uint8_t m_bEnableAudio;			//使能音频
	int32_t m_i32AudioBitDepth;		//需要与AO一致
}hi_hdmi_param_t;

//设备操作
int32_t HI_VO_StartDev(hi_vo_dev_param_t *pstVoDevParam);
int32_t HI_VO_StopDev(int32_t i32VoDevID);

//视频层操作
int32_t HI_VO_StartVoLayer(hi_vo_layer_param_t *pstVoLayerParam);
int32_t HI_VOStopVoLayer(int32_t i32VoLayerID);

//HDMI操作
int32_t HI_VO_StartHdmi(hi_hdmi_param_t *pstHdmiParam);
int32_t HI_VO_StopHdmi(int32_t i32HdmiID);

#ifdef __cplusplus
};
#endif

#endif