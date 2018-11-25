#ifndef __HI_FB_H__
#define __HI_FB_H__

#include "cross_platform.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define GRAPHICS_LAYER_G0  0
#define GRAPHICS_LAYER_G1  4
#define GRAPHICS_LAYER_SD0 2
#define GRAPHICS_LAYER_HC0 2
#define GRAPHICS_LAYER_HC1 3

typedef hi_fb_handle void*;

typedef struct _hi_fb_point_s{
	int32_t m_s32XPos;         /**<  horizontal position */
	int32_t m_s32YPos;         /**<  vertical position */
}hi_fb_point_t;

typedef struct _hi_fb_screen_info_s{
	uint32_t m_u32DisResWidth;				//设备显示分辨率宽
	uint32_t m_u32DisResHeight;				//设备显示分辨率高
	uint32_t m_u32MaxVirtualResWidth;		//最大虚拟分辨率宽
	uint32_t m_u32MaxVirtualResHeight;		//最大虚拟分辨率高
	uint32_t m_u32BitsPerPixel;				//位深 8bit - 16bit - 32bit
}hi_fb_screen_info_t;

typedef struct __hi_fb_graphics_layer_param_s{
	int32_t m_i32GraphicsLayerID;			//图形层ID
	uint32_t m_u32DevDisResWidth;			//设备显示分辨率宽
	uint32_t m_u32DevDisResHeight;			//设备显示分辨率高
	uint32_t m_u32MaxVirtualResWidth;		//最大虚拟分辨率宽
	uint32_t m_u32MaxVirtualResHeight;		//最大虚拟分辨率高
	uint32_t m_u32BitsPerPixel;				//位深 8bit - 16bit - 32bit
}hi_fb_graphics_layer_param_t;

/********************************************************************************************
* 函 数 名：	HI_FB_Init
* 功    能：	初始化hifb模块
* 参数：无
* 返回值：0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_Init();
/********************************************************************************************
* 函 数 名：	HI_FB_UnInit
* 功    能：	反初始化hifb模块
* 参数：无
* 返回值：0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_UnInit();

/********************************************************************************************
* 函 数 名：	HI_FB_StartGraphicsLayer
* 功    能：	启动图形层
* 参数：
		|--fb_handle：存储图层资源句柄的缓存区指针
		|--pstGraphicsLayerParam：图层参数
* 返回值：0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_StartGraphicsLayer(hi_fb_handle *fb_handle, hi_fb_graphics_layer_param_t *pstGraphicsLayerParam);
/********************************************************************************************
* 函 数 名：	HI_FB_StopGraphicsLayer
* 功    能：启动图形层
* 参数：
		|--fb_handle：存储图层资源的句柄
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_StopGraphicsLayer(hi_fb_handle fb_handle);
/********************************************************************************************
* 函 数 名：	HI_FB_SetScreenOrigin
* 功    能：设置屏幕显示位置
* 参数：
		|--fb_handle：存储图层资源的句柄
		|--stPoint	：位置坐标
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_SetScreenOrigin(hi_fb_handle fb_handle, hi_fb_point_t stPoint);
/********************************************************************************************
* 函 数 名：	HI_FB_ShowScreen
* 功    能：显示/隐藏屏幕
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--i8ShowFlag	：0-隐藏 1-显示
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_ShowScreen(hi_fb_handle fb_handle, uint8_t i8ShowFlag);
/********************************************************************************************
* 函 数 名：	HI_FB_ShowScreen
* 功    能：显示/隐藏屏幕
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--pstScreenInfo：存储屏幕信息
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_GetScreeInfo(hi_fb_handle fb_handle, hi_fb_screen_info_t *pstScreenInfo);
/********************************************************************************************
* 函 数 名：	HI_FB_ClearScreen
* 功    能：暂时无效
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--stScreenInfo	：屏幕信息
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_SetScreeInfo(hi_fb_handle fb_handle, hi_fb_screen_info_t stScreenInfo);
/********************************************************************************************
* 函 数 名：	HI_FB_ShowScreen
* 功    能：清屏
* 参数：
		|--fb_handle	：存储图层资源的句柄
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_ClearScreen(hi_fb_handle fb_handle);

#ifdef __cplusplus
#if __cplusplus
};
#endif
#endif

#endif