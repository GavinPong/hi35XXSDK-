#include "hi_includes.h"
#include "hi_vo.h"
#include "cross_platform.h"
#include "log.h"

int32_t HI_VO_GetIntSync(VO_INTF_SYNC_E *enIntfSync, uint32_t u32W,uint32_t u32H, uint32_t u32Frm)
{
	int32_t ret = 0;
	if (!enIntfSync)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param is null!", __FUNCTION__, __LINE__);
	}
	if (720 == u32W && 576 == u32H && u32Frm == 25)
		*enIntfSync = VO_OUTPUT_PAL;
	else if (720 == u32W && 480 == u32H && u32Frm == 30)
		*enIntfSync = VO_OUTPUT_NTSC;
	else if (720 == u32W && 576 == u32H && u32Frm == 50)
		*enIntfSync = VO_OUTPUT_576P50;
	else if (720 == u32W && 480 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_480P60;
	else if (800 == u32W && 600 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_800x600_60;
	else if (1280 == u32W && 720 == u32H && u32Frm == 50)
		*enIntfSync = VO_OUTPUT_720P50;
	else if (1280 == u32W && 720 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_720P60;
	else if (1920 == u32W && 1080 == u32H && u32Frm == 50)
		*enIntfSync = VO_OUTPUT_1080I50;
	else if (1920 == u32W && 1080 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1080I60;
	else if (1920 == u32W && 1080 == u32H && u32Frm == 24)
		*enIntfSync = VO_OUTPUT_1080P24;
	else if (1920 == u32W && 1080 == u32H && u32Frm == 25)
		*enIntfSync = VO_OUTPUT_1080P25;
	else if (1920 == u32W && 1080 == u32H && u32Frm == 30)
		*enIntfSync = VO_OUTPUT_1080P30;
	else if (1920 == u32W && 1080 == u32H && u32Frm == 50)
		*enIntfSync = VO_OUTPUT_1080P50;
	else if (1920 == u32W && 1080 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1080P60;
	else if (1024 == u32W && 768 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1024x768_60;
	else if (1280 == u32W && 1024 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1280x1024_60;
	else if (1366 == u32W && 768 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1366x768_60;
	else if (1440 == u32W && 900 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1440x900_60;
	else if (1280 == u32W && 800 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1280x800_60;
	else if (1600 == u32W && 1200 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1600x1200_60;
	else if (1680 == u32W && 1050 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1600x1200_60;
	else if (1920 == u32W && 1200 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_1920x1200_60;
	else if (3840 == u32W && 2160 == u32H && u32Frm == 30)
		*enIntfSync = VO_OUTPUT_3840x2160_30;
	else if (3840 == u32W && 2160 == u32H && u32Frm == 60)
		*enIntfSync = VO_OUTPUT_3840x2160_60;
	else if (720 == u32W && 576 == u32H && u32Frm == 25)
		*enIntfSync = VO_OUTPUT_USER;
	else
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_VO_GetIntSync failed!", __FUNCTION__, __LINE__);
		ret = -1;
	}

	return ret;
}

int32_t HI_VO_GetPixelFormat(PIXEL_FORMAT_E *penPixelFormat, const char *strPixelFormat)
{
	if (!penPixelFormat || !strPixelFormat)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param is null!", __FUNCTION__, __LINE__);
		return -1;
	}
	if (strstr(strPixelFormat, "rgb_1bpp"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_1BPP;
	}
	else if (strstr(strPixelFormat, "rgb_2bpp"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_2BPP;
	}
	else if (strstr(strPixelFormat, "rgb_4bpp"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_4BPP;
	}
	else if (strstr(strPixelFormat, "rgb_8bpp"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_8BPP;
	}
	else if (strstr(strPixelFormat, "rgb_444"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_444;
	}    
	else if (strstr(strPixelFormat, "rgb_4444"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_4444;
	}  
	else if (strstr(strPixelFormat, "rgb_555"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_555;
	}
	else if (strstr(strPixelFormat, "rgb_565"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_565;
	}
	else if (strstr(strPixelFormat, "rgb_1555"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_1555;
	}
	else if (strstr(strPixelFormat, "rgb_888"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_888;
	}
	else if (strstr(strPixelFormat, "rgb_8888"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_8888;
	}   
	else if (strstr(strPixelFormat, "rgb_planar_888"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_PLANAR_888;
	} 
	else if (strstr(strPixelFormat, "rgb_bayer_8bpp"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_BAYER_8BPP;
	} 
	else if (strstr(strPixelFormat, "rgb_bayer_10bpp"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_BAYER_10BPP;
	} 
	else if (strstr(strPixelFormat, "rgb_bayer_12bpp"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_BAYER_12BPP;
	} 
	else if (strstr(strPixelFormat, "rgb_bayer_14bpp"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_BAYER_14BPP;
	} 
	else if (strstr(strPixelFormat, "rgb_bayer"))
	{
		*penPixelFormat = PIXEL_FORMAT_RGB_BAYER;
	} 
	else if (strstr(strPixelFormat, "yuv_a422"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUV_A422;
	}
	else if (strstr(strPixelFormat, "yuv_a444"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUV_A444;
	}
	else if (strstr(strPixelFormat, "yuv_planar_444"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUV_PLANAR_422;
	}
	else if (strstr(strPixelFormat, "yuv_planar_420"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUV_PLANAR_420;
	}
	else if (strstr(strPixelFormat, "yuv_planar_444"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUV_PLANAR_444;
	}
	else if (strstr(strPixelFormat, "yuv_splanar_444"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_422;
	}
	else if (strstr(strPixelFormat, "yuv_splanar_420"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	}
	else if (strstr(strPixelFormat, "yuv_splanar_444"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_444;
	}
	else if (strstr(strPixelFormat, "uyvy_package_422"))
	{
		*penPixelFormat = PIXEL_FORMAT_UYVY_PACKAGE_422;
	}
	else if (strstr(strPixelFormat, "yuyv_package_422"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUYV_PACKAGE_422;
	}
	else if (strstr(strPixelFormat, "vyuy_package_422"))
	{
		*penPixelFormat = PIXEL_FORMAT_VYUY_PACKAGE_422;
	}
	else if (strstr(strPixelFormat, "vyuy_ycbcr_planar"))
	{
		*penPixelFormat = PIXEL_FORMAT_YCbCr_PLANAR;
	}
	else if (strstr(strPixelFormat, "vyuy_yuv_400"))
	{
		*penPixelFormat = PIXEL_FORMAT_YUV_400;
	}
	else if (strstr(strPixelFormat, "butt"))
	{
		*penPixelFormat = PIXEL_FORMAT_BUTT;
	}
	else
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s was unknown pixel format!", __FUNCTION__, __LINE__, strPixelFormat);
		return -2;
	}
		
	return 0;
}

int32_t HI_VO_GetHdmiVideoFormat(HI_HDMI_VIDEO_FMT_E *enVideoFmt, const char *strIntfSync)
{
	if (!enVideoFmt || strIntfSync)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param was null!", __FUNCTION__, __LINE__);
		return -1;
	}
	if (strstr(strIntfSync, "pal"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_PAL;
	}
	else if (strstr(strIntfSync, "ntsc"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_NTSC;
	}
	else if (strstr(strIntfSync, "1080P24"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_1080P_24;
	}
	else if (strstr(strIntfSync, "1080P25"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_1080P_25;
	}
	else if (strstr(strIntfSync, "1080P30"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_1080P_30;
	}
	else if (strstr(strIntfSync, "720P50"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_720P_50;
	}
	else if (strstr(strIntfSync, "720P60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_720P_60;
	}
	else if (strstr(strIntfSync, "1080I50"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_1080i_50;
	}
	else if (strstr(strIntfSync, "1080I60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_1080i_60;
	}
	else if (strstr(strIntfSync, "1080P50"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_1080P_50;
	}
	else if (strstr(strIntfSync, "1080P60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_1080P_60;
	}
	else if (strstr(strIntfSync, "576P50"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_576P_50;
	}
	else if (strstr(strIntfSync, "480P60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_480P_60;
	}
	else if (strstr(strIntfSync, "800x600_60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_VESA_800X600_60;
	}
	else if (strstr(strIntfSync, "1024x768_60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1024X768_60;
	}
	else if (strstr(strIntfSync, "1280x1024_60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1280X1024_60;
	}
	else if (strstr(strIntfSync, "1366x768_60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1366X768_60;
	}
	else if (strstr(strIntfSync, "1440x900_60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1440X900_60;
	}
	else if (strstr(strIntfSync, "1280x800_60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1280X800_60;
	}
	else if (strstr(strIntfSync, "1600x1200_60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_VESA_1600X1200_60;
	}
	else if (strstr(strIntfSync, "2560x1440_30"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_2560x1440_30;
	}
	else if (strstr(strIntfSync, "2560x1600_60"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_2560x1600_60;
	}
	else if (strstr(strIntfSync, "3840x2160_30"))
	{
		*enVideoFmt = HI_HDMI_VIDEO_FMT_3840X2160P_30;
	}
	else
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param %s unknown!", __FUNCTION__, __LINE__, strIntfSync);
		return -2;
	}
	return 0;
}

int32_t HI_VO_StartDev(hi_vo_dev_param_t *pstVoDevParam)
{
	VO_PUB_ATTR_S stPubAttr;
	HI_S32 s32Ret = HI_SUCCESS;
	VO_INTF_SYNC_E enIntfSync;

	if (!pstVoDevParam)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param invalid!", __FUNCTION__, __LINE__);
		return -1;
	}
	memset(&stPubAttr, 0, sizeof(stPubAttr));
	if(HI_VO_GetIntSync(&enIntfSync, pstVoDevParam->m_u32Width, pstVoDevParam->m_u32Height, pstVoDevParam->m_u32FrameRate) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:failed!", __FUNCTION__, __LINE__);
		return -2;
	}
	stPubAttr.enIntfSync = enIntfSync;
	stPubAttr.u32BgColor = pstVoDevParam->m_u32BgColor;
	if (strstr(pstVoDevParam->m_strIntfTypeName, "vga"))
	{
		stPubAttr.enIntfType = (VO_INTF_SYNC_E)VO_INTF_VGA;
	}
	if (strstr(pstVoDevParam->m_strIntfTypeName, "hdmi"))
	{
		stPubAttr.enIntfType |= (VO_INTF_SYNC_E)VO_INTF_HDMI;
	}
	if (strstr(pstVoDevParam->m_strIntfTypeName, "bt1120"))
	{
		stPubAttr.enIntfType |= (VO_INTF_SYNC_E)VO_INTF_BT1120;
	}
	if (strstr(pstVoDevParam->m_strIntfTypeName, "cvbs"))
	{
		stPubAttr.enIntfType |= (VO_INTF_SYNC_E)VO_INTF_CVBS;
	}
	s32Ret = HI_MPI_VO_SetPubAttr(pstVoDevParam->m_u32VoDevID, &stPubAttr);
	if (s32Ret != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:voDev[%d] HI_MPI_VO_SetPubAttr failed with:%#x!", __FUNCTION__, __LINE__,pstVoDevParam->m_u32VoDevID, s32Ret);
		return -3;
	}

	s32Ret = HI_MPI_VO_Enable(pstVoDevParam->m_u32VoDevID);
	if (s32Ret != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:voDev[%d] HI_MPI_VO_SetPubAttr failed with:%#x!", __FUNCTION__, __LINE__, pstVoDevParam->m_u32VoDevID, s32Ret);
		return -4;
	}

	return 0;
}

int32_t HI_VO_StopDev(int32_t i32VoDevID)
{
	HI_S32 s32Ret = HI_SUCCESS;

	s32Ret = HI_MPI_VO_Disable(i32VoDevID);
	if (s32Ret != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_VO_Disable vodev[%d] failed with:%#x!", __FUNCTION__, __LINE__, i32VoDevID, s32Ret);
		return -1;
	}
	return s32Ret;
}

int32_t HI_VO_StartVoLayer(hi_vo_layer_param_t *pstVoLayerParam)
{
	VO_VIDEO_LAYER_ATTR_S stLayerAttr;
	PIXEL_FORMAT_E enPixelFormat;
	HI_S32 s32Ret = HI_SUCCESS;

	if (!pstVoLayerParam)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param was null", __FUNCTION__, __LINE__);
		return -1;
	}
	if (HI_VO_GetPixelFormat(&enPixelFormat, pstVoLayerParam->m_strPixelFormat) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:volayer[%d] pixel format invalid", __FUNCTION__, __LINE__, pstVoLayerParam->m_i32VoLayerID);
		return -2;
	}
	memset(&stLayerAttr, 0, sizeof(stLayerAttr));
	stLayerAttr.bClusterMode = HI_FALSE;
	stLayerAttr.bDoubleFrame = HI_FALSE;
	stLayerAttr.enPixFormat = enPixelFormat;
	stLayerAttr.stImageSize.u32Width = pstVoLayerParam->m_u32Width;
	stLayerAttr.stImageSize.u32Height = pstVoLayerParam->m_u32Height;
	stLayerAttr.u32DispFrmRt = pstVoLayerParam->m_u32FrameRate ;
	if (stLayerAttr.u32DispFrmRt > 60 || stLayerAttr.u32DispFrmRt < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:volayer[%d] display frame rate %u(f/s) exception", __FUNCTION__, __LINE__, pstVoLayerParam->m_i32VoLayerID, pstVoLayerParam->m_u32FrameRate);
	}
	stLayerAttr.stDispRect.s32X = pstVoLayerParam->m_i32DispPosX;
	stLayerAttr.stDispRect.s32Y = pstVoLayerParam->m_i32DispPosY;
	stLayerAttr.stDispRect.u32Width = pstVoLayerParam->m_u32DispWidth;
	stLayerAttr.stDispRect.u32Height = pstVoLayerParam->m_u32DispHeight;

	s32Ret = HI_MPI_VO_SetVideoLayerAttr(pstVoLayerParam->m_i32VoLayerID, &stLayerAttr);
	if (s32Ret != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_VO_SetVideoLayerAttr volayer[%d] failed with %#x!", __FUNCTION__, __LINE__, pstVoLayerParam->m_i32VoLayerID, s32Ret);
		return -3;
	}

	s32Ret = HI_MPI_VO_EnableVideoLayer(pstVoLayerParam->m_i32VoLayerID);
	if (s32Ret != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_VO_EnableVideoLayer volayer[%d] failed with %#x!", __FUNCTION__, __LINE__, pstVoLayerParam->m_i32VoLayerID, s32Ret);
		return -4;
	}

	return 0;
}

int32_t HI_VOStopVoLayer(int32_t i32VoLayerID)
{
	HI_S32 s32Ret = HI_SUCCESS;

	s32Ret = HI_MPI_VO_DisableVideoLayer(i32VoLayerID);
	if (s32Ret != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_VO_DisableVideoLayer volayer[%d] failed with %#x!", __FUNCTION__, __LINE__, i32VoLayerID, s32Ret);
		return -1;
	}
	return 0;
}

int32_t HI_VO_StartHdmi(hi_hdmi_param_t *pstHdmiParam)
{
	HI_HDMI_ATTR_S      stAttr;
	HI_HDMI_VIDEO_FMT_E enVideoFmt;
	HI_HDMI_INIT_PARA_S stHdmiPara;
	HI_S32 s32Ret = HI_SUCCESS;

	if (!pstHdmiParam)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param was null!", __FUNCTION__, __LINE__);
		return -1;
	}
	HI_VO_GetHdmiVideoFormat(&enVideoFmt, pstHdmiParam->m_strIntfSync);
	stHdmiPara.pfnHdmiEventCallback = NULL;
	stHdmiPara.pCallBackArgs = NULL;
	stHdmiPara.enForceMode = HI_HDMI_FORCE_HDMI;
	s32Ret = HI_MPI_HDMI_Init(&stHdmiPara);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_HDMI_Init failed with:%#x!", __FUNCTION__, __LINE__, s32Ret);
		return -2;
	}

	s32Ret = HI_MPI_HDMI_Open((HI_HDMI_ID_E)pstHdmiParam->m_i32HdmiID);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_HDMI_Open[%d] failed with:%#x!", __FUNCTION__, __LINE__, pstHdmiParam->m_i32HdmiID, s32Ret);
		return -3;
	}
	s32Ret = HI_MPI_HDMI_GetAttr((HI_HDMI_ID_E)pstHdmiParam->m_i32HdmiID, &stAttr);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_HDMI_GetAttr[%d] failed with:%#x!", __FUNCTION__, __LINE__, pstHdmiParam->m_i32HdmiID, s32Ret);
		return -4;
	}
	stAttr.bEnableHdmi = HI_TRUE;

	stAttr.bEnableVideo = HI_TRUE;
	stAttr.enVideoFmt = enVideoFmt;

	stAttr.enVidOutMode = HI_HDMI_VIDEO_MODE_YCBCR444;
	stAttr.enDeepColorMode = HI_HDMI_DEEP_COLOR_OFF;
	stAttr.bxvYCCMode = HI_FALSE;

	stAttr.bEnableAudio = (HI_BOOL)pstHdmiParam->m_bEnableAudio;
	stAttr.enSoundIntf = HI_HDMI_SND_INTERFACE_I2S;
	stAttr.bIsMultiChannel = (HI_BOOL)HI_FALSE;

	stAttr.enBitDepth = (HI_HDMI_BIT_DEPTH_E)pstHdmiParam->m_i32AudioBitDepth;

	stAttr.bEnableAviInfoFrame = (HI_BOOL)HI_TRUE;
	stAttr.bEnableAudInfoFrame = (HI_BOOL)HI_TRUE;
	stAttr.bEnableSpdInfoFrame = (HI_BOOL)HI_FALSE;
	stAttr.bEnableMpegInfoFrame = (HI_BOOL)HI_FALSE;

	stAttr.bDebugFlag = (HI_BOOL)HI_FALSE;          
	stAttr.bHDCPEnable = (HI_BOOL)pstHdmiParam->m_bHDCPEnable;

	stAttr.b3DEnable = (HI_BOOL)HI_FALSE;

	s32Ret = HI_MPI_HDMI_SetAttr((HI_HDMI_ID_E)pstHdmiParam->m_i32HdmiID, &stAttr);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_HDMI_SetAttr[%d] failed with:%#x!", __FUNCTION__, __LINE__, pstHdmiParam->m_i32HdmiID, s32Ret);
		return -5;
	}
	s32Ret = HI_MPI_HDMI_Start((HI_HDMI_ID_E)pstHdmiParam->m_i32HdmiID);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_HDMI_Start[%d] failed with:%#x!", __FUNCTION__, __LINE__, pstHdmiParam->m_i32HdmiID, s32Ret);
		return -5;
	}
	return 0;
}

int32_t HI_VO_StopHdmi(int32_t i32HdmiID)
{
	HI_S32 s32Ret = HI_SUCCESS;

	s32Ret = HI_MPI_HDMI_Stop((HI_HDMI_ID_E)i32HdmiID);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_HDMI_Stop[%d] failed with:%#x!", __FUNCTION__, __LINE__, i32HdmiID, s32Ret);
		return -1;
	}
	s32Ret = HI_MPI_HDMI_Close(HI_HDMI_ID_0);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_HDMI_Close[%d] failed with:%#x!", __FUNCTION__, __LINE__, i32HdmiID, s32Ret);
		return -2;
	}
	s32Ret = HI_MPI_HDMI_DeInit();
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_HDMI_Close[%d] failed with:%#x!", __FUNCTION__, __LINE__, i32HdmiID, s32Ret);
		return -3;
	}

	return 0;
}