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
	if (720 == i32W && 576 == i32H && i32Frm == 25)
		*enIntfSync = VO_OUTPUT_PAL;
	else if (720 == i32W && 480 == i32H && i32Frm == 30)
		*enIntfSync = VO_OUTPUT_NTSC;
	else if (720 == i32W && 576 == i32H && i32Frm == 50)
		*enIntfSync = VO_OUTPUT_576P50;
	else if (720 == i32W && 480 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_480P60;
	else if (800 == i32W && 600 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_800x600_60;
	else if (1280 == i32W && 720 == i32H && i32Frm == 50)
		*enIntfSync = VO_OUTPUT_720P50;
	else if (1280 == i32W && 720 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_720P60;
	else if (1920 == i32W && 1080 == i32H && i32Frm == 50)
		*enIntfSync = VO_OUTPUT_1080I50;
	else if (1920 == i32W && 1080 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1080I60;
	else if (1920 == i32W && 1080 == i32H && i32Frm == 24)
		*enIntfSync = VO_OUTPUT_1080P24;
	else if (1920 == i32W && 1080 == i32H && i32Frm == 25)
		*enIntfSync = VO_OUTPUT_1080P25;
	else if (1920 == i32W && 1080 == i32H && i32Frm == 30)
		*enIntfSync = VO_OUTPUT_1080P30;
	else if (1920 == i32W && 1080 == i32H && i32Frm == 50)
		*enIntfSync = VO_OUTPUT_1080P50;
	else if (1920 == i32W && 1080 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1080P60;
	else if (1024 == i32W && 768 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1024x768_60;
	else if (1280 == i32W && 1024 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1280x1024_60;
	else if (1366 == i32W && 768 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1366x768_60;
	else if (1440 == i32W && 900 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1440x900_60;
	else if (1280 == i32W && 800 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1280x800_60;
	else if (1600 == i32W && 1200 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1600x1200_60;
	else if (1680 == i32W && 1050 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1600x1200_60;
	else if (1920 == i32W && 1200 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_1920x1200_60;
	else if (3840 == i32W && 2160 == i32H && i32Frm == 30)
		*enIntfSync = VO_OUTPUT_3840x2160_30;
	else if (3840 == i32W && 2160 == i32H && i32Frm == 60)
		*enIntfSync = VO_OUTPUT_3840x2160_60;
	else if (720 == i32W && 576 == i32H && i32Frm == 25)
		*enIntfSync = VO_OUTPUT_USER;
	else
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_VO_GetIntSync failed!", __FUNCTION__, __LINE__);
		ret = -1;
	}

	return ret;
}

int32_t HI_VO_GetPixelFormat(PIXEL_FORMAT_E *penPixelFormat, char *strPixelFormat)
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
		stPubAttr.enIntfSync = VO_INTF_VGA;
	}
	if (strstr(pstVoDevParam->m_strIntfTypeName, "hdmi"))
	{
		stPubAttr.enIntfSync |= VO_INTF_HDMI
	}
	if (strstr(pstVoDevParam->m_strIntfTypeName, "bt1120"))
	{
		stPubAttr.enIntfSync |= VO_INTF_BT1120
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

	s32Ret = HI_MPI_VO_DisableVideoLayer(VoLayer);
	if (s32Ret != HI_SUCCESS)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_VO_DisableVideoLayer volayer[%d] failed with %#x!", __FUNCTION__, __LINE__, i32VoLayerID, s32Ret);
		return -1;
	}
	return 0;
}

int32_t HI_VO_StartHdmi(int32_t i32HdmiID)
{

	return 0;
}

int32_t HI_VO_StopHdmi(int32_t i32HdmiID)
{

	return 0;
}