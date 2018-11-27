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

typedef struct _hi_fb_rect_s{
	int32_t m_s32XPos;         /**<  horizontal position */
	int32_t m_s32YPos;         /**<  vertical position */
	uint32_t m_u32Width;	   /**<  horizontal width */
	uint32_t m_u32Height;	   /**<  vertical height */
}hi_fb_rect_t;

//画布参数
typedef struct _hi_fb_canvas_s{
	uint32_t  m_u32PhyAddr;     /**<  start physical address */
	uint32_t  m_u32Width;       /**<  width pixels */
	uint32_t  m_u32Height;      /**<  height pixels */   
	uint32_t  m_u32Pitch;       /**<  line pixels */         
	char m_strColorFmt[16];		/**<  color format */ 
}hi_fb_canvas_t;

typedef struct _hi_fb_alpha_param_s{
	uint8_t m_bAlphaOverlay;	//叠加使能
	uint8_t m_bAlphaChn;		//通道使能
	uint8_t m_u8OverlayValue0;	//RGB1555最高位为1时叠加的alpha值
	uint8_t m_u8OverlayValue1;	//RGB1555最高位为0时叠加的alpha值
	uint8_t m_u8ChnValue;		//通道alpha值
}hi_fb_alpha_param_t;

typedef struct _hi_fb_colorkey_param_s{
	uint8_t m_bEnable;				//使能colorkey功能
	uint32_t m_u32ColorKeyValue;	//colorkey值
}hi_fb_colorkey_param_t;

//标准显示参数
typedef struct _hi_fb_pan_display_param_s{
	uint32_t m_u32PosX;				//显示的起始位置X坐标posx + 实际分辨率 不能大于最大虚拟分辨率
	uint32_t m_u32PosY;				//显示的起始位置Y坐标posx + 实际分辨率 不能大于最大虚拟分辨率
}hi_fb_pan_display_param_t;

//拓展显示参数
typedef struct _hi_fb_refresh_param_s{
	hi_fb_canvas_t m_stCanvas;				//画布参数
	hi_fb_rect_t m_stRefreshRect;			//刷新区域
}hi_fb_refresh_param_t;

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
/********************************************************************************************
* 函 数 名：	HI_FB_GetAlpha
* 功    能：获取alpha参数
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--pstAplphaParam：存储alpha参数地址
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_GetAlpha(hi_fb_handle fb_handle,hi_fb_alpha_param_t *pstAplphaParam);
/********************************************************************************************
* 函 数 名：	HI_FB_SetAlpha
* 功    能：设置alpha参数
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--stAplphaParam: alpha参数
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_SetAlpha(hi_fb_handle fb_handle,hi_fb_alpha_param_t stAplphaParam);

/********************************************************************************************
* 函 数 名：	HI_FB_GetColorkey
* 功    能：获取colorkey参数
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--pstColorkeyParam：存储colorkey参数地址
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_GetColorkey(hi_fb_handle fb_handle,hi_fb_colorkey_param_t *pstColorkeyParam);
/********************************************************************************************
* 函 数 名：	HI_FB_SetColorkey
* 功    能：设置colorkey参数
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--stColorkeyParam: colorkey参数
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_SetColorkey(hi_fb_handle fb_handle,hi_fb_colorkey_param_t stColorkeyParam);
/********************************************************************************************
* 函 数 名：	HI_FB_PanDisplay
* 功    能：获取屏幕在显存缓存区显示的位置
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--stPanDisplayParam: 平移显示的位置参数地址
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_GetPanDisplay(hi_fb_handle fb_handle, hi_fb_pan_display_param_t *pstPanDisplayParam);
/********************************************************************************************
* 函 数 名：	HI_FB_PanDisplay
* 功    能：平移显示虚拟显存区的数据
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--stColorkeyParam: colorkey参数
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_SetPanDisplay(hi_fb_handle fb_handle, hi_fb_pan_display_param_t stPanDisplayParam);
/********************************************************************************************
* 函 数 名：	HI_FB_RefreshRect
* 功    能：刷新指定区域的内容
* 参数：
		|--fb_handle	：存储图层资源的句柄
		|--stColorkeyParam: colorkey参数
* 返回值：	0-成功，其他值-失败
********************************************************************************************/
int32_t HI_FB_RefreshRect(hi_fb_handle fb_handle, hi_fb_refresh_param_t stRefreshRectParam);

#ifdef __cplusplus
#if __cplusplus
};
#endif
#endif

#endif