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

static uint32_t s_u32Stride = 0;	//根据上实际显示设备设置
static uint32_t s_u32PhyAddr = 0;	//屏幕虚拟地址
static void *s_pVirAddr;			//屏幕物理地址

int32_t DrawLine(point_t stOriginal, point_t stDestination)
{
	int32_t i, j;
	double k = (double)(stDestination.m_i32YPos - stOriginal.m_i32YPos) / (stDestination.m_i32XPos - stOriginal.m_i32XPos);
	int32_t i32OrigiX = 0, i32EndX = 0;
	int32_t i32OrigiY = 0/*, i32EndY = 0*/;
#if 0
	printf("=====================\n");
	printf("k:%lf [%d,%d] [%d,%d]\n",k, stOriginal.m_i32XPos,stOriginal.m_i32YPos, stDestination.m_i32XPos,stDestination.m_i32YPos);
	printf("=====================\n");
#endif
	if (stOriginal.m_i32XPos <= stDestination.m_i32XPos)
	{
		i32OrigiX = stOriginal.m_i32XPos;
		i32EndX = stDestination.m_i32XPos;
		i32OrigiY = stOriginal.m_i32YPos;
		//i32EndY = stDestination.m_i32YPos;
	}
	else
	{
		i32OrigiX = stDestination.m_i32XPos;
		i32EndX = stOriginal.m_i32XPos;
		i32OrigiY = stDestination.m_i32YPos;
		//i32EndY = stOriginal.m_i32YPos;
	}
	for (i = i32OrigiX;i < i32EndX;i++)
	{
		j = k * (i - i32OrigiX) + i32OrigiY;
#if 0	
		printf("[%d,%d]\t",i, j);
#endif	
		*((HI_U16 *)s_pVirAddr + j * (s_u32Stride / 2)+ i) = GREEN_16;
	}
#if 0
	printf("\n");
#endif
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
	int32_t dYCoor = 0;

	if(i32X < i32Radius && i32Y < i32Radius) 
	{
		if (i32X > i32Y)
		{
			i32Radius = i32Y;
		}
		else
		{
			i32Radius = i32X;
		}	
	}
	else if (i32X < i32Radius)
	{
		i32Radius = i32X;
	}
	else if (i32Y < i32Radius)
	{
		i32Radius = i32Y;
	}
	
	double dRadius2 = i32Radius * i32Radius;
	double dXRangeStart = i32X - i32Radius, dXRangeEnd = i32X + i32Radius; 

	for(i = dXRangeStart; i < dXRangeEnd;i++)
	{
		//圆形下半部分的圆周
		dYCoor = sqrt(dRadius2 - (i - i32X) * (i - i32X)) + i32Y;
		*((HI_U16 *)s_pVirAddr + (s_u32Stride/2) * dYCoor + i) = BLUE_16;
		//圆形上半部分的圆周
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
	point_t stRectangleOriginal = {300, 300};
	point_t stLineOriginal = {660,588}, stLineDestination = {130, 100};

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
	DrawLine(stLineOriginal, stLineDestination);
#if 0
	printf("=====================\n");
	printf("[%d,%d] [%d,%d]\n",stLineOriginal.m_i32XPos,stLineOriginal.m_i32YPos, stLineDestination.m_i32XPos,stLineDestination.m_i32YPos);
	printf("=====================\n");
#endif
	stLineOriginal.m_i32XPos = 888;stLineOriginal.m_i32YPos = 58;
	stLineDestination.m_i32XPos = 88; stLineDestination.m_i32YPos = 688;
#if	0
	printf("=====================\n");
	printf("[%d,%d] [%d,%d]\n",stLineOriginal.m_i32XPos,stLineOriginal.m_i32YPos, stLineDestination.m_i32XPos,stLineDestination.m_i32YPos);
	printf("=====================\n");
#endif
	Msleep(1000 * 2);
	DrawLine(stLineOriginal, stLineDestination);
	Msleep(1000 * 2);
	DrawCircle(50, 68, 100, (HI_U32 *)s_pVirAddr);
	Msleep(1000 * 2);
	DrawCircle(960, 540, 10, (HI_U32 *)s_pVirAddr);
	Msleep(1000 * 2);
	DrawCircle(960, 540, 20, (HI_U32 *)s_pVirAddr);
	Msleep(1000 * 2);
	DrawCircle(960, 540, 40, (HI_U32 *)s_pVirAddr);
	Msleep(1000 * 2);
	DrawCircle(960, 540, 80, (HI_U32 *)s_pVirAddr);
	Msleep(1000 * 2);
	DrawCircle(960, 540, 160, (HI_U32 *)s_pVirAddr);
	Msleep(1000 * 2);
	DrawCircle(960, 540, 320, (HI_U32 *)s_pVirAddr);
	Msleep(1000 * 2);
	DrawRectangular(stRectangleOriginal, 100, 100, (HI_U16 *)s_pVirAddr);
	Msleep(1000 * 2);
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
	stVoDevParam.m_u32Height = 1080;
	stVoDevParam.m_u32Width = 1920;
	stVoDevParam.m_u32BgColor = 0x0;
	stVoDevParam.m_bInterlaced = 0;
	stVoDevParam.m_u32VoDevID = 1;//HD0
	//设备操作
	HI_VO_StartDev(&stVoDevParam);

	//视频层操作
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

	//HDMI操作
	stHdmiParam.m_bEnableAudio = 1;
	stHdmiParam.m_bHDCPEnable = 0;
	stHdmiParam.m_i32AudioBitDepth = 16;
	stHdmiParam.m_i32HdmiID = 0;
	memset(stHdmiParam.m_strIntfSync, 0, sizeof(stHdmiParam.m_strIntfSync));
	plat_sprintf(stHdmiParam.m_strIntfSync, sizeof(stHdmiParam), "1080P60");
	HI_VO_StartHdmi(&stHdmiParam);
	//fb操作
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