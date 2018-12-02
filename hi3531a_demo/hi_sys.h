#ifndef __HI__SYS__
#define __HI_SYS__

#include "cross_platform.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _video_block_param_s{
	int32_t m_i32Width;			//图像宽度
	int32_t m_i32Height;		//图像高度
	int32_t m_i32BlockCnt;		//内存块数-可以用来缓存对应大小视频缓存块的个数
	char m_strMmzName[32];		//内存块的名称
}video_block_param_t;

typedef struct _hi_sys_param_s{
	int32_t m_i32StrideAlignWidth;//系统使用图像的stride字节对齐数
	video_block_param_t *m_stVideoBlockParamPtr;//视频缓存块参数数组首地址
	int32_t m_i32VideoBlockParamCnt;//视频缓存块参数数组大小
}hi_sys_param_t;

int32_t HI_SYS_Init(hi_sys_param_t *pstSysParam);
int32_t HI_SYS_UnInit();
int32_t HI_SYS_GetvVersion(char *pstrOutBuf, int32_t i32BufSize);

#ifdef __cplusplus
};
#endif

#endif