#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "hi_fb.h"
#include "hifb.h"
#include "log.h"
#include "list.h"
#include <pthread.h>
#include <sys/mman.h>

#define HI_FB_HandleToFbInfo(pstFbInfo, handle)  do{\
	if(!handle)	{\
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:fb_handle invalid", __FUNCTION__, __LINE__);\
		return -1;\
	}\
	(pstFbInfo) = (struct _hi_fb_info_s *)(handle);\
}while(0);

typedef enum _hi_fb_pixel_format_e{
	HI_FB_PIXEL_FORMAT_UNKNOWN,
	HI_FB_PIXEL_FORMAT_ARGB1555,
	HI_FB_PIXEL_FORMAT_ARGB8888,
}hi_fb_pixel_format_e;

typedef enum _hi_fb_inited_e{
	HI_FB_UNINITED,					//未初始化
	HI_FB_INITED,					//初始化
}hi_fb_inited_e;

typedef struct _hi_fb_info_s{
	struct list_head m_stListNode;	
	int32_t m_i32Fd;						//fb设备句柄
	char m_strDevName[32];					//设备名
	hi_fb_pixel_format_e m_enPixFormat;		//像素格式
	uint32_t m_u32ScreeStride;				//fb屏幕跨度（一行的宽度）
	uint32_t m_u32PhAddr;					//fb物理地址
	uint32_t m_smem_len;					//fb内存长度
	void * m_pVirAddr;						//fb虚拟地址
}hi_fb_info_t;

typedef struct _hi_fb_ctx_s{
	hi_fb_inited_e	m_enInited;				//是否初始化标记
	struct list_head m_strFbInfoListHead;	//管理fb信息链表头
	pthread_mutex_t m_FbInfoListHeadMutex;	//
}hi_fb_ctx_t;

static hi_fb_ctx_t s_stHifbCtx = {};


static struct fb_bitfield s_r16 = {10, 5, 0};
static struct fb_bitfield s_g16 = {5, 5, 0};
static struct fb_bitfield s_b16 = {0, 5, 0};
static struct fb_bitfield s_a16 = {15, 1, 0};

static struct fb_bitfield s_a32 = {24,8,0};
static struct fb_bitfield s_r32 = {16,8,0};
static struct fb_bitfield s_g32 = {8,8,0};
static struct fb_bitfield s_b32 = {0,8,0};

int32_t HI_FB_GetColorFormt(HIFB_COLOR_FMT_E *penColorFmt, char *pstrColorFmt)
{
	if (!penColorFmt || !pstrColorFmt)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:Param was null", __FUNCTION__, __LINE__);
	}
	if (!strcmp(pstrColorFmt, "rgb565"))
	{
		*penColorFmt = HIFB_FMT_RGB565;
	}
	else if (!strcmp(pstrColorFmt, "rgb888"))
	{
		*penColorFmt = HIFB_FMT_RGB888;
	}     
	else if (!strcmp(pstrColorFmt, "krgb444"))
	{
		*penColorFmt = HIFB_FMT_KRGB444;
	}  
	else if (!strcmp(pstrColorFmt, "krgb555"))
	{
		*penColorFmt = HIFB_FMT_KRGB555;
	} 
	else if (!strcmp(pstrColorFmt, "krgb888"))
	{
		*penColorFmt = HIFB_FMT_KRGB888;
	} 
	else if (!strcmp(pstrColorFmt, "argb4444"))
	{
		*penColorFmt = HIFB_FMT_ARGB4444;
	} 
	else if (!strcmp(pstrColorFmt, "argb1555"))
	{
		*penColorFmt = HIFB_FMT_ARGB1555;
	}      
	else if (!strcmp(pstrColorFmt, "argb8888"))
	{
		*penColorFmt = HIFB_FMT_ARGB8888;
	} 
	else if (!strcmp(pstrColorFmt, "argb8565"))
	{
		*penColorFmt = HIFB_FMT_ARGB8565;
	} 
	else if (!strcmp(pstrColorFmt, "rgba4444"))
	{
		*penColorFmt = HIFB_FMT_RGBA4444;
	} 
	else if (!strcmp(pstrColorFmt, "rgba5551"))
	{
		*penColorFmt = HIFB_FMT_RGBA5551;
	}
	else if (!strcmp(pstrColorFmt, "rgba5658"))
	{
		*penColorFmt = HIFB_FMT_RGBA5658;
	}
	else if (!strcmp(pstrColorFmt, "rgba8888"))
	{
		*penColorFmt = HIFB_FMT_RGBA8888;
	}
	else if (!strcmp(pstrColorFmt, "bgr565"))
	{
		*penColorFmt = HIFB_FMT_BGR565;
	}
	else if (!strcmp(pstrColorFmt, "bgr888"))
	{
		*penColorFmt = HIFB_FMT_BGR888;
	}  
	else if (!strcmp(pstrColorFmt, "abgr4444"))
	{
		*penColorFmt = HIFB_FMT_ABGR4444;
	}   
	else if (!strcmp(pstrColorFmt, "abgr1555"))
	{
		*penColorFmt = HIFB_FMT_ABGR1555;
	}  
	else if (!strcmp(pstrColorFmt, "abgr8888"))
	{
		*penColorFmt = HIFB_FMT_ABGR8888;
	}    
	else if (!strcmp(pstrColorFmt, "abgr8565"))
	{
		*penColorFmt = HIFB_FMT_ABGR8565;
	}  
	else if (!strcmp(pstrColorFmt, "kbgr444"))
	{
		*penColorFmt = HIFB_FMT_KBGR444;
	}  
	else if (!strcmp(pstrColorFmt, "kbgr555"))
	{
		*penColorFmt = HIFB_FMT_KBGR555;
	}  
	else if (!strcmp(pstrColorFmt, "kbgr888"))
	{
		*penColorFmt = HIFB_FMT_KBGR888;
	} 
	else if (!strcmp(pstrColorFmt, "1bpp"))
	{
		*penColorFmt = HIFB_FMT_1BPP;
	} 
	else if (!strcmp(pstrColorFmt, "2bpp"))
	{
		*penColorFmt = HIFB_FMT_2BPP;
	} 
	else if (!strcmp(pstrColorFmt, "4bpp"))
	{
		*penColorFmt = HIFB_FMT_4BPP;
	} 
	else if (!strcmp(pstrColorFmt, "8bpp"))
	{
		*penColorFmt = HIFB_FMT_8BPP;
	}  
	else if (!strcmp(pstrColorFmt, "aclu44"))
	{
		*penColorFmt = HIFB_FMT_ACLUT44;
	}
	else if (!strcmp(pstrColorFmt, "aclu88"))
	{
		*penColorFmt = HIFB_FMT_ACLUT88;
	}
	else if (!strcmp(pstrColorFmt, "puyvy"))
	{
		*penColorFmt = HIFB_FMT_PUYVY;
	}
	else if (!strcmp(pstrColorFmt, "pyuyv"))
	{
		*penColorFmt = HIFB_FMT_PYUYV;
	}
	else if (!strcmp(pstrColorFmt, "pyvyu"))
	{
		*penColorFmt = HIFB_FMT_PYVYU;
	}
	else if (!strcmp(pstrColorFmt, "yuv888"))
	{
		*penColorFmt = HIFB_FMT_YUV888;
	}
	else if (!strcmp(pstrColorFmt, "ayuv8888"))
	{
		*penColorFmt = HIFB_FMT_AYUV8888;
	}
	else if (!strcmp(pstrColorFmt, "yuva8888"))
	{
		*penColorFmt = HIFB_FMT_YUVA8888;
	}
	else if (!strcmp(pstrColorFmt, "butt"))
	{
		*penColorFmt = HIFB_FMT_BUTT;
	}
	else
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:pstrColorFmt unknown!", __FUNCTION__, __LINE__, pstrColorFmt);
		return -1;
	}
		
	return 0;
}

int32_t HI_FB_GetDevName(char *pstrNameBuf, int32_t i32BufSize, int32_t i32GraphicsLayerID)
{
	if (!pstrNameBuf || !i32BufSize || i32GraphicsLayerID < 0){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:pSysParam invalid", __FUNCTION__, __LINE__);
		return -1;
	}
	memset(pstrNameBuf, 0, i32BufSize);
	if (GRAPHICS_LAYER_G0 == i32GraphicsLayerID){
		plat_sprintf(pstrNameBuf, i32BufSize, "/dev/fb0");
	}else if (GRAPHICS_LAYER_G1 == i32GraphicsLayerID){
		plat_sprintf(pstrNameBuf, i32BufSize, "/dev/fb1");
	}else if (GRAPHICS_LAYER_SD0 == i32GraphicsLayerID){
		plat_sprintf(pstrNameBuf, i32BufSize, "/dev/fb2");
	}else if (GRAPHICS_LAYER_HC0 == i32GraphicsLayerID){
		plat_sprintf(pstrNameBuf, i32BufSize, "/dev/fb3");
	}else if (GRAPHICS_LAYER_HC1 == i32GraphicsLayerID){
		plat_sprintf(pstrNameBuf, i32BufSize, "/dev/fb4");
	}
	else{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:i32GraphicsLayerID[%d] was unknown type", __FUNCTION__, __LINE__, i32GraphicsLayerID);
		return -2;
	}

	return 0;
}

//检查设备是否已经开启
static int32_t HI_FB_CheckDevStatus(const char *strDevName)
{
	hi_fb_info_t *pos = NULL, *n = NULL;
	struct list_head *head = NULL;
	int32_t i32ExistFlag = 0;

	if (!strDevName){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param was null", __FUNCTION__, __LINE__);
		return 0;
	}
	if (HI_FB_UNINITED == s_stHifbCtx.m_enInited){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:hi_fb uninited", __FUNCTION__, __LINE__);
		return 0;
	}
	pthread_mutex_lock(&s_stHifbCtx.m_FbInfoListHeadMutex);
	head = &s_stHifbCtx.m_strFbInfoListHead;
	list_for_each_entry_safe(hi_fb_info_t, pos, n, head, m_stListNode){
		if (!strcmp(pos->m_strDevName, strDevName)){
			i32ExistFlag = 1;
			break;
		}
	}
	pthread_mutex_unlock(&s_stHifbCtx.m_FbInfoListHeadMutex);
	if(1 == i32ExistFlag)
		return 1;
	return 0;
}


int32_t HI_FB_Init()
{
	if (HI_FB_INITED == s_stHifbCtx.m_enInited){
		return 0;
	}
	s_stHifbCtx.m_enInited = HI_FB_INITED;//该指令放在最前面
	INIT_LIST_HEAD(&s_stHifbCtx.m_strFbInfoListHead);
	pthread_mutex_init(&s_stHifbCtx.m_FbInfoListHeadMutex, NULL);

	return 0;
}

int32_t HI_FB_UnInit()
{
	if (HI_FB_INITED != s_stHifbCtx.m_enInited){
		return 0;
	}
	hi_fb_info_t *pos, *n;
	struct list_head *head;

	pthread_mutex_lock(&s_stHifbCtx.m_FbInfoListHeadMutex);
	head = &s_stHifbCtx.m_strFbInfoListHead;
	list_for_each_entry_safe(hi_fb_info_t, pos, n, head, m_stListNode){
		list_del(&pos->m_stListNode);
		if (pos->m_i32Fd >= 0)
		{
			close(pos->m_i32Fd);
		}
		free(pos);
	}
	pthread_mutex_unlock(&s_stHifbCtx.m_FbInfoListHeadMutex);
	pthread_mutex_destroy(&s_stHifbCtx.m_FbInfoListHeadMutex);
	s_stHifbCtx.m_enInited = HI_FB_UNINITED;//该指令放在最后
	return 0;
}

//默认图形层启动后是隐藏的，需要手动显示s
int32_t HI_FB_StartGraphicsLayer(hi_fb_handle *fb_handle, hi_fb_graphics_layer_param_t *pstGraphicsLayerParam)
{
	struct fb_fix_screeninfo strFixScreenInfo;
	struct fb_var_screeninfo strVarScreenInfoVar;
	char strFbFileName[32] = "";
	hi_fb_info_t *pstfbInfo = NULL;
	int32_t i32Fd = -1;
	HI_BOOL bShow;
	void *pShowScreen = NULL;
	HIFB_POINT_S stPoint = {0};
	hi_fb_pixel_format_e enPixFormt = HI_FB_PIXEL_FORMAT_UNKNOWN;
	
	//1.初始化fb模块
	HI_FB_Init();
	if (!pstGraphicsLayerParam){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param was null", __FUNCTION__, __LINE__);
		return -1;
	}
	//2.将ID转换为设备名，并检查设备是否已经开启过
	if(HI_FB_GetDevName(strFbFileName, sizeof(strFbFileName), pstGraphicsLayerParam->m_i32GraphicsLayerID) < 0){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_FB_GetDevName[%d] failed", __FUNCTION__, __LINE__, pstGraphicsLayerParam->m_i32GraphicsLayerID);
		return -2;
	}
	if(HI_FB_CheckDevStatus(strFbFileName)){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s was inited!", __FUNCTION__, __LINE__, strFbFileName);
		return -3;
	}
	//3.打开设备，获取句柄
	i32Fd = open(strFbFileName, O_RDWR);
	if (i32Fd < 0){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s open %s failed!", __FUNCTION__, __LINE__, strFbFileName);
		return -4;
	}
	//4.隐藏图层
	bShow = HI_FALSE;
	if (ioctl(i32Fd, FBIOPUT_SHOW_HIFB, &bShow) < 0){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s hide failed!", __FUNCTION__, __LINE__, strFbFileName);
	}
	//5.设置可变屏幕信息
	if (ioctl(i32Fd, FBIOGET_VSCREENINFO, &strVarScreenInfoVar) < 0){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s get vscreen info failed!", __FUNCTION__, __LINE__, strFbFileName);
		close(i32Fd);
		return -5;
	}
	strVarScreenInfoVar.xres_virtual = pstGraphicsLayerParam->m_u32MaxVirtualResWidth;
	strVarScreenInfoVar.yres_virtual = pstGraphicsLayerParam->m_u32MaxVirtualResHeight;
	strVarScreenInfoVar.xres = pstGraphicsLayerParam->m_u32DevDisResWidth;
	strVarScreenInfoVar.yres = pstGraphicsLayerParam->m_u32DevDisResHeight;
	if (16 == pstGraphicsLayerParam->m_u32BitsPerPixel){
		strVarScreenInfoVar.transp= s_a16;
		strVarScreenInfoVar.red = s_r16;
		strVarScreenInfoVar.green = s_g16;
		strVarScreenInfoVar.blue = s_b16;
		strVarScreenInfoVar.bits_per_pixel = 16;
		enPixFormt = HI_FB_PIXEL_FORMAT_ARGB1555;
	}else if (32 == pstGraphicsLayerParam->m_u32BitsPerPixel){
		strVarScreenInfoVar.transp= s_a32;
		strVarScreenInfoVar.red = s_r32;
		strVarScreenInfoVar.green = s_g32;
		strVarScreenInfoVar.blue = s_b32;
		strVarScreenInfoVar.bits_per_pixel = 32;
		enPixFormt = HI_FB_PIXEL_FORMAT_ARGB8888;
	}else{
		strVarScreenInfoVar.transp= s_a16;
		strVarScreenInfoVar.red = s_r16;
		strVarScreenInfoVar.green = s_g16;
		strVarScreenInfoVar.blue = s_b16;
		strVarScreenInfoVar.bits_per_pixel = 16;
		enPixFormt = HI_FB_PIXEL_FORMAT_ARGB1555;
	}
#if 1
	printf("=================================\n");
	printf("xres_virtual:%u\n",strVarScreenInfoVar.xres_virtual);
	printf("yres_virtual:%u\n",strVarScreenInfoVar.yres_virtual);
	printf("xres:%u\n",strVarScreenInfoVar.xres);
	printf("yres:%u\n",strVarScreenInfoVar.yres);
	printf("bits_per_pixel:%u\n",strVarScreenInfoVar.bits_per_pixel);
	printf("=================================\n");
#endif
	strVarScreenInfoVar.activate = FB_ACTIVATE_NOW;
	if (ioctl(i32Fd, FBIOPUT_VSCREENINFO, &strVarScreenInfoVar) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s set vscreen info failed!", __FUNCTION__, __LINE__, strFbFileName);
		close(i32Fd);
		return -6;
	}
	//6.清屏并显示
    if (ioctl(i32Fd, FBIOGET_FSCREENINFO, &strFixScreenInfo) < 0)
    {
        log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s get fixscreen info failed!", __FUNCTION__, __LINE__, strFbFileName);
		close(i32Fd);
        return -7;
    }
    pShowScreen = mmap(HI_NULL, strFixScreenInfo.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, i32Fd, 0);
    if(MAP_FAILED == pShowScreen)
    {
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s mmap framebuffer failed!", __FUNCTION__, __LINE__, strFbFileName);
		close(i32Fd);
        return -8;
    }
    memset(pShowScreen, 0x00, strFixScreenInfo.smem_len);
	if (ioctl(i32Fd, FBIOPUT_SCREEN_ORIGIN_HIFB, &stPoint) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s set screen original show position failed!", __FUNCTION__, __LINE__, strFbFileName);
		close(i32Fd);
		return -9;
	}

    /* time to play*/
    bShow = HI_TRUE;
    if (ioctl(i32Fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
    {
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s show screen failed!", __FUNCTION__, __LINE__, strFbFileName);
        munmap(pShowScreen, strFixScreenInfo.smem_len);
		close(i32Fd);
		return -10;
    }
	//munmap(pShowScreen, strFixScreenInfo.smem_len);
	//7：申请存储fb设备信息的资源，并存储fb信息
	pstfbInfo = (hi_fb_info_t *)calloc(1, sizeof(hi_fb_info_t));
	if (!pstfbInfo)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:malloc failed!", __FUNCTION__, __LINE__);
		return -4;
	}
	plat_sprintf(pstfbInfo->m_strDevName, sizeof(pstfbInfo->m_strDevName), "%s", strFbFileName);
	pstfbInfo->m_i32Fd = i32Fd;
	pstfbInfo->m_enPixFormat = enPixFormt;
	pstfbInfo->m_pVirAddr = pShowScreen;
	pstfbInfo->m_u32PhAddr = (uint32_t)strFixScreenInfo.smem_start;
	pstfbInfo->m_u32ScreeStride = (uint32_t)strFixScreenInfo.line_length;
	pstfbInfo->m_smem_len = (uint32_t)strFixScreenInfo.smem_len;
	pthread_mutex_lock(&s_stHifbCtx.m_FbInfoListHeadMutex);
	list_add(&pstfbInfo->m_stListNode, &s_stHifbCtx.m_strFbInfoListHead);
	pthread_mutex_unlock(&s_stHifbCtx.m_FbInfoListHeadMutex);

	*fb_handle = (hi_fb_handle)pstfbInfo;
	return 0;
}

int32_t HI_FB_StopGraphicsLayer(hi_fb_handle fb_handle)
{
	HI_BOOL bShow;
	hi_fb_info_t *pstHiFbInfo = NULL, *pos, *n;
	struct list_head *head;

	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	bShow = HI_FALSE;
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s hide screen failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
	}
	if (pstHiFbInfo->m_i32Fd > 0)
	{
		close(pstHiFbInfo->m_i32Fd);
		pstHiFbInfo->m_i32Fd = -1;
	}
	if(pstHiFbInfo->m_pVirAddr)
		munmap(pstHiFbInfo->m_pVirAddr, pstHiFbInfo->m_smem_len);
	pthread_mutex_lock(&s_stHifbCtx.m_FbInfoListHeadMutex);
	head = &s_stHifbCtx.m_strFbInfoListHead;
	list_for_each_entry_safe(hi_fb_info_t, pos, n, head, m_stListNode){
		if (!strcmp(pstHiFbInfo->m_strDevName, pos->m_strDevName))
		{
			list_del(&pos->m_stListNode);
			free(pos);
			break;
		}
	}
	pthread_mutex_unlock(&s_stHifbCtx.m_FbInfoListHeadMutex);
	return 0;
}

int32_t HI_FB_SetScreenOrigin(hi_fb_handle fb_handle, hi_fb_point_t stPoint)
{
	HIFB_POINT_S hiPosition;
	hi_fb_info_t *pstHiFbInfo = NULL;

	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	hiPosition.s32XPos = stPoint.m_s32XPos;
	hiPosition.s32YPos = stPoint.m_s32YPos;
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOPUT_SCREEN_ORIGIN_HIFB, &hiPosition) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s set screen original show position failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}

	return 0;
}

int32_t HI_FB_ShowScreen(hi_fb_handle fb_handle, uint8_t i8ShowFlag)
{
	HI_BOOL bShow;
	hi_fb_info_t *pstHiFbInfo = NULL;

	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	if (1 == i8ShowFlag)
		bShow = HI_TRUE;
	else
		bShow = HI_TRUE;
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s show screen failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}

	return 0;
}

int32_t HI_FB_GetScreeInfo(hi_fb_handle fb_handle, hi_fb_screen_info_t *pstScreenInfo)
{
	hi_fb_info_t *pstHiFbInfo = NULL;
	struct fb_var_screeninfo stVarScreenInfo;

	if (!pstScreenInfo){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s param was null", __FUNCTION__, __LINE__);
		return -1;
	}
	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOGET_VSCREENINFO, &stVarScreenInfo) < 0){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s get screen info failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}
	pstScreenInfo->m_u32BitsPerPixel = stVarScreenInfo.bits_per_pixel;
	pstScreenInfo->m_u32DisResWidth = stVarScreenInfo.xres;
	pstScreenInfo->m_u32DisResHeight = stVarScreenInfo.yres;
	pstScreenInfo->m_u32MaxVirtualResWidth = stVarScreenInfo.xres_virtual;
	pstScreenInfo->m_u32MaxVirtualResHeight = stVarScreenInfo.yres_virtual;
	pstScreenInfo->m_u32PhyAddr = pstHiFbInfo->m_u32PhAddr;
	pstScreenInfo->m_pVirAddr = pstHiFbInfo->m_pVirAddr;
	pstScreenInfo->m_u32ScreenStride = pstHiFbInfo->m_u32ScreeStride;
	return 0;
}

int32_t HI_FB_SetScreeInfo(hi_fb_handle fb_handle, hi_fb_screen_info_t stScreenInfo)
{
	return 0;
}

int32_t HI_FB_ClearScreen(hi_fb_handle fb_handle)
{
	hi_fb_info_t *pstHiFbInfo = NULL;
	void *pShowScreen = NULL;
	struct fb_fix_screeninfo stFixScreenInfo;
	HI_BOOL bShow = HI_FALSE;

	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOGET_FSCREENINFO, &stFixScreenInfo) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s get fix screen info failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}
	pShowScreen = mmap(HI_NULL, stFixScreenInfo.smem_len, PROT_READ|PROT_WRITE, MAP_SHARED, pstHiFbInfo->m_i32Fd, 0);
	if(MAP_FAILED == pShowScreen)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s mmap framebuffer failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -3;
	}

	memset(pShowScreen, 0x00, stFixScreenInfo.smem_len);
	bShow = HI_TRUE;
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s show screen failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		munmap(pShowScreen, stFixScreenInfo.smem_len);
		return -4;
	}
	munmap(pShowScreen, stFixScreenInfo.smem_len);

	return 0;
}

int32_t HI_FB_GetAlpha(hi_fb_handle fb_handle,hi_fb_alpha_param_t *pstAplphaParam)
{
	HIFB_ALPHA_S stAlpha;
	hi_fb_info_t *pstHiFbInfo = NULL;

	if (!pstAplphaParam)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s param was null!", __FUNCTION__, __LINE__);
		return -1;
	}
	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);


	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOGET_ALPHA_HIFB,  &stAlpha) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s FBIOGET_ALPHA_HIFB failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}
	pstAplphaParam->m_bAlphaOverlay = (HI_TRUE == stAlpha.bAlphaEnable?1 : 0);
	pstAplphaParam->m_bAlphaOverlay = (HI_TRUE == stAlpha.bAlphaChannel?1 : 0);
	pstAplphaParam->m_u8OverlayValue0 = stAlpha.u8Alpha0;
	pstAplphaParam->m_u8OverlayValue1 = stAlpha.u8Alpha1;
	pstAplphaParam->m_u8OverlayValue1 = stAlpha.u8Alpha0;
	pstAplphaParam->m_u8ChnValue = stAlpha.u8GlobalAlpha;

	return 0;
}

int32_t HI_FB_SetAlpha(hi_fb_handle fb_handle,hi_fb_alpha_param_t stAplphaParam)
{
	HIFB_ALPHA_S stAlpha;
	hi_fb_info_t *pstHiFbInfo = NULL;

	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);

	if  (HI_FB_PIXEL_FORMAT_ARGB1555 == pstHiFbInfo->m_enPixFormat)
	{
	}
	stAlpha.bAlphaEnable = (1 ==stAplphaParam.m_bAlphaOverlay?HI_TRUE : HI_FALSE);
	stAlpha.u8Alpha0 = stAplphaParam.m_u8OverlayValue0;
	stAlpha.u8Alpha1 = stAplphaParam.m_u8OverlayValue1;
	stAlpha.bAlphaEnable = (1 ==stAplphaParam.m_bAlphaChn?HI_TRUE : HI_FALSE);
	stAlpha.u8GlobalAlpha = stAplphaParam.m_u8ChnValue;
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOPUT_ALPHA_HIFB,  &stAlpha) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s FBIOPUT_ALPHA_HIFB failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}
	return 0;
}

int32_t HI_FB_GetColorkey(hi_fb_handle fb_handle,hi_fb_colorkey_param_t *pstColorkeyParam)
{
	hi_fb_info_t *pstHiFbInfo = NULL;
	HIFB_COLORKEY_S stColorKey;
	int s32Ret = -1;

	if (!pstColorkeyParam)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s param was null!", __FUNCTION__, __LINE__);
		return -1;
	}
	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	s32Ret = ioctl(pstHiFbInfo->m_i32Fd, FBIOGET_COLORKEY_HIFB, &stColorKey);
	if (s32Ret < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s set colorkey failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}
	pstColorkeyParam->m_bEnable = stColorKey.bKeyEnable;
	pstColorkeyParam->m_u32ColorKeyValue = stColorKey.u32Key;
	return 0;
}

int32_t HI_FB_SetColorkey(hi_fb_handle fb_handle,hi_fb_colorkey_param_t stColorkeyParam)
{
	hi_fb_info_t *pstHiFbInfo = NULL;
	HIFB_COLORKEY_S stColorKey;
	int s32Ret = -1;

	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	stColorKey.bKeyEnable = (1 == stColorkeyParam.m_bEnable?HI_TRUE : HI_FALSE);
	stColorKey.u32Key = stColorkeyParam.m_u32ColorKeyValue;
	s32Ret = ioctl(pstHiFbInfo->m_i32Fd, FBIOPUT_COLORKEY_HIFB, &stColorKey);
	if (s32Ret < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s set colorkey failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}
	return 0;
}

int32_t HI_FB_GetPanDisplay(hi_fb_handle fb_handle, hi_fb_pan_display_param_t *pstPanDisplayParam)
{
	hi_fb_info_t *pstHiFbInfo = NULL;
	struct fb_var_screeninfo stVarScreenInfo;
	if (!pstPanDisplayParam)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s param was null!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -1;
	}
	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOGET_VSCREENINFO, &stVarScreenInfo) < 0){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s get screen info failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}
	pstPanDisplayParam->m_u32PosX = stVarScreenInfo.xoffset;
	pstPanDisplayParam->m_u32PosY = stVarScreenInfo.yoffset;
	return 0;
}

int32_t HI_FB_SetPanDisplay(hi_fb_handle fb_handle, hi_fb_pan_display_param_t stPanDisplayParam)
{
	hi_fb_info_t *pstHiFbInfo = NULL;
	struct fb_var_screeninfo stVarScreenInfo;

	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOGET_VSCREENINFO, &stVarScreenInfo) < 0){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s get screen info failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}
	stVarScreenInfo.xoffset = stPanDisplayParam.m_u32PosX;
	stVarScreenInfo.yoffset = stPanDisplayParam.m_u32PosY;
	if (ioctl(pstHiFbInfo->m_i32Fd, FBIOPUT_VSCREENINFO, &stVarScreenInfo) < 0){
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s get screen info failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}

	return 0;
}

int32_t HI_FB_RefreshRect(hi_fb_handle fb_handle, hi_fb_refresh_param_t stRefreshRectParam)
{
	HIFB_BUFFER_S stCanvasBuf;
	hi_fb_info_t *pstHiFbInfo = NULL;
	HIFB_COLOR_FMT_E enColorFmt;
	int s32Ret = -1;

	HI_FB_HandleToFbInfo(pstHiFbInfo, fb_handle);
	stCanvasBuf.stCanvas.u32PhyAddr = stRefreshRectParam.m_stCanvas.m_u32PhyAddr;
	stCanvasBuf.stCanvas.u32Width = stRefreshRectParam.m_stCanvas.m_u32Width;
	stCanvasBuf.stCanvas.u32Height = stRefreshRectParam.m_stCanvas.m_u32Height;
	stCanvasBuf.stCanvas.u32Pitch = stRefreshRectParam.m_stCanvas.m_u32Pitch;
	if(HI_FB_GetColorFormt(&enColorFmt, stRefreshRectParam.m_stCanvas.m_strColorFmt) < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s refreash failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -2;
	}
	stCanvasBuf.UpdateRect.x = stRefreshRectParam.m_stRefreshRect.m_s32XPos;
	stCanvasBuf.UpdateRect.y = stRefreshRectParam.m_stRefreshRect.m_s32YPos;
	stCanvasBuf.UpdateRect.w = stRefreshRectParam.m_stRefreshRect.m_u32Width;
	stCanvasBuf.UpdateRect.h = stRefreshRectParam.m_stRefreshRect.m_u32Height;
	s32Ret = ioctl(pstHiFbInfo->m_i32Fd, FBIO_REFRESH, &stCanvasBuf);
	if(s32Ret < 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:%s refreash failed!", __FUNCTION__, __LINE__, pstHiFbInfo->m_strDevName);
		return -3;
	}
	return 0;
}