#include "hi_includes.h"
#include "hi_sys.h"
#include "hi_fb.h"
#include "hi_av_core.h"
#include "log.h"
#include <math.h>
#include "stdlib.h"
#include "hi_vo.h"
#include "stddef.h"

#define RED_16 0xFC00
#define GREEN_16 0x83E0
#define BLUE_16 0x801F

#define GetVOLayer(voLayer, voDev) do{\
	if (voDev < 2) voLayer = voDev;\
	else voLayer = voDev + 1;\
}while(0);

#define GetVoGraphics(voGraphics, voDev) do{\
	if (0 == voDev) voGraphics = GRAPHICS_LAYER_G0;\
	else if(1 == voDev) voGraphics = GRAPHICS_LAYER_G1;\
	else if(2 == voDev) voGraphics = GRAPHICS_LAYER_SD0;\
	else if(3 == voDev) voGraphics = GRAPHICS_LAYER_HC0;\
	else if(4 == voDev) voGraphics = GRAPHICS_LAYER_HC1;\
}while(0);

#define _DRAW_LINE_TEST
#ifdef _DRAW_LINE_TEST

typedef struct _point_s{
	int32_t m_i32XPos;
	int32_t m_i32YPos;
}point_t;

static uint32_t s_u32Stride = 0;	//������ʵ����ʾ�豸����
static uint32_t s_u32PhyAddr = 0;	//��Ļ�����ַ
static void *s_pVirAddr;			//��Ļ�����ַ

int32_t DrawLine()
{
	int32_t i = 1080, y = 800;

	for (;i < 1900;i++)
	{
		*((HI_U16 *)s_pVirAddr + y * (s_u32Stride / 2)+ i) = RED_16;
	}

	return 0;
}

int32_t DrawRectangular(point_t original, int32_t i32W, int32_t i32H, HI_U16 *u32VirtualAddr)
{
	int32_t i = 0, j = 0;
	point_t destination;
	int step = s_u32Stride/2;
	
	destination.m_i32XPos = original.m_i32XPos + i32W;
	destination.m_i32YPos = original.m_i32YPos + i32H;

	for (i = original.m_i32XPos; i < destination.m_i32XPos; i++)
	{
		for (j = original.m_i32YPos; j < destination.m_i32YPos; j++)
		{
			*((HI_U16 *)s_pVirAddr + j * step + i) = GREEN_16;
		}
	}
	return 0;
}
//Radius * Radius = (x - circleCenterX) * (x - circleCenterX) + (y - circleCenterY) * (y - circleCenterY)
int32_t DrawCircle(int32_t i32X, int32_t i32Y, int32_t i32Radius, HI_U32 *u32VirtualAddr)
{
	int32_t i = 0;
	double dRadius2 = i32Radius * i32Radius;
	double dXRangeStart = i32X - i32Radius, dXRangeEnd = i32X + i32Radius; 
	int32_t dYCoor = 0;

	for(i = dXRangeStart; i < dXRangeEnd;i++)
	{
		//Բ���°벿�ֵ�Բ��
		dYCoor = sqrt(dRadius2 - (i - i32X) * (i - i32X)) + i32Y;
		*((HI_U16 *)s_pVirAddr + (s_u32Stride/2) * dYCoor + i) = BLUE_16;
		//Բ���ϰ벿�ֵ�Բ��
		dYCoor = i32Y - (dYCoor - i32Y);
		*((HI_U16 *)s_pVirAddr + (s_u32Stride/2) * dYCoor + i) = BLUE_16;
	}

	return 0;
}

int32_t fb_test_start(hi_fb_handle *fb_handle)
{
	hi_fb_graphics_layer_param_t stGraphicsLayerParam;
	hi_fb_handle handle;
	hi_fb_point_t stPoint = {0,0};
	hi_fb_screen_info_t stScreenInfo;
	point_t original = {300, 300};

	if (!fb_handle)
	{
		return -1;
	}
	GetVoGraphics(stGraphicsLayerParam.m_i32GraphicsLayerID, 1);
	stGraphicsLayerParam.m_u32BitsPerPixel = 16;
	stGraphicsLayerParam.m_u32DevDisResWidth = 1920;
	stGraphicsLayerParam.m_u32DevDisResHeight = 1080;
	stGraphicsLayerParam.m_u32MaxVirtualResWidth = stGraphicsLayerParam.m_u32DevDisResWidth;
	stGraphicsLayerParam.m_u32MaxVirtualResHeight = stGraphicsLayerParam.m_u32DevDisResHeight * 2;
	HI_FB_Init();
	HI_FB_StartGraphicsLayer(&handle, &stGraphicsLayerParam);
	HI_FB_GetScreeInfo(handle, &stScreenInfo);
	s_u32PhyAddr = stScreenInfo.m_u32PhyAddr;
	s_u32Stride = stScreenInfo.m_u32ScreenStride;
	s_pVirAddr = stScreenInfo.m_pVirAddr;
	HI_FB_ShowScreen(handle, 0);
	HI_FB_SetScreenOrigin(handle, stPoint);
	DrawLine();
	DrawCircle(960, 540, 10, (HI_U32 *)s_pVirAddr);
	DrawCircle(960, 540, 20, (HI_U32 *)s_pVirAddr);
	DrawCircle(960, 540, 40, (HI_U32 *)s_pVirAddr);
	DrawCircle(960, 540, 80, (HI_U32 *)s_pVirAddr);
	DrawCircle(960, 540, 160, (HI_U32 *)s_pVirAddr);
	DrawCircle(960, 540, 320, (HI_U32 *)s_pVirAddr);
	DrawRectangular(original, 100, 100, (HI_U16 *)s_pVirAddr);
	*fb_handle = handle;

	return 0;
}

int32_t fb_test_stop(hi_fb_handle fb_handle)
{
	HI_FB_StopGraphicsLayer(fb_handle);
	HI_FB_UnInit();
	
	return 0;
}

int32_t main(int argc, char *argv[])
{
	char strSdkVersion[128] = "";
	hi_sys_param_t stSysParam;
	int32_t i = 0;
	hi_vo_dev_param_t stVoDevParam;
	hi_vo_layer_param_t stVoLayerParam;
	hi_hdmi_param_t stHdmiParam;
	hi_fb_handle fb_handle = 0;

	HI_SYS_GetvVersion(strSdkVersion, sizeof(strSdkVersion));
	log_output(LOG_LEVEL_FILE_SCREEN, "%s", strSdkVersion);

	stSysParam.m_i32StrideAlignWidth = 16;
	stSysParam.m_i32VideoBlockParamCnt = 3;
	stSysParam.m_stVideoBlockParamPtr = (video_block_param_t *)calloc(1, sizeof(video_block_param_t) * stSysParam.m_i32VideoBlockParamCnt);	
	for (i = 0;i < stSysParam.m_i32VideoBlockParamCnt; i++)
	{
		stSysParam.m_stVideoBlockParamPtr[i].m_i32Width = 1920 + (8 - 1920%8)%8;
		stSysParam.m_stVideoBlockParamPtr[i].m_i32Height = 1080 + (8 - 1080%8)%8;
		stSysParam.m_stVideoBlockParamPtr[i].m_i32BlockCnt = 6;
	}
	HI_SYS_Init(&stSysParam);

	memset(stVoDevParam.m_strIntfTypeName, 0, sizeof(stVoDevParam.m_strIntfTypeName));
	plat_sprintf(stVoDevParam.m_strIntfTypeName, sizeof(stVoDevParam.m_strIntfTypeName), "vga&hdmi");
	stVoDevParam.m_u32FrameRate = 60;
	stVoDevParam.m_u32Width = 1920;
	stVoDevParam.m_u32Height = 1080;	
	stVoDevParam.m_u32BgColor = 0x0;
	stVoDevParam.m_bInterlaced = 0;
	stVoDevParam.m_u32VoDevID = 1;//HD0
	//�豸����
	HI_VO_StartDev(&stVoDevParam);

	//��Ƶ�����
	stVoLayerParam.m_i32DispPosX = 0;
	stVoLayerParam.m_i32DispPosY = 0;
	GetVOLayer(stVoLayerParam.m_i32VoLayerID, stVoDevParam.m_u32VoDevID);
	memset(stVoLayerParam.m_strPixelFormat, 0, sizeof(stVoLayerParam.m_strPixelFormat));
	plat_sprintf(stVoLayerParam.m_strPixelFormat, sizeof(stVoLayerParam.m_strPixelFormat), "yuv_splanar_420");
	stVoLayerParam.m_u32DispWidth  = stVoDevParam.m_u32Width;
	stVoLayerParam.m_u32DispHeight = stVoDevParam.m_u32Height;
	stVoLayerParam.m_u32FrameRate = stVoDevParam.m_u32FrameRate;
	stVoLayerParam.m_u32Width = stVoDevParam.m_u32Width;
	stVoLayerParam.m_u32Height = stVoDevParam.m_u32Height;
	HI_VO_StartVoLayer(&stVoLayerParam);

	//HDMI����
	stHdmiParam.m_bEnableAudio = 1;
	stHdmiParam.m_bHDCPEnable = 0;
	stHdmiParam.m_i32AudioBitDepth = 16;
	stHdmiParam.m_i32HdmiID = 0;
	memset(stHdmiParam.m_strIntfSync, 0, sizeof(stHdmiParam.m_strIntfSync));
	plat_sprintf(stHdmiParam.m_strIntfSync, sizeof(stHdmiParam), "1080P60");
	HI_VO_StartHdmi(&stHdmiParam);
	//fb����
	fb_test_start(&fb_handle);
	while(1)
	{
		Msleep(100);
	}
	fb_test_stop(fb_handle);
	HI_VOStopVoLayer(stVoLayerParam.m_i32VoLayerID);
	HI_VO_StopHdmi(stHdmiParam.m_i32HdmiID);
	HI_VO_StopDev(stVoDevParam.m_u32VoDevID);
	HI_SYS_UnInit();

	return 0;
}

#endif