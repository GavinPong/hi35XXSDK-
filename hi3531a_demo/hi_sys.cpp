#include <string.h>
#include "sample_comm.h"
#include "hi_sys.h"

//清理系统
static void HI_SYS_CleanSystem()
{
	int32_t i;

	HI_MPI_SYS_Exit();
	for (i = 0;i < VB_MAX_USER;i++)
	{
		HI_MPI_VB_ExitModCommPool(i);
	}
	for (i = 0;i < VB_MAX_POOLS;i++)
	{
		HI_MPI_VB_DestroyPool(i);
	}
	HI_MPI_VB_Exit();
}

int32_t HI_SYS_Init(hi_sys_param_t *pstSysParam)
{
	VB_CONF_S       stVbConf;
	HI_U32 u32BlkSize;
	int32_t i = 0, vb_pool_max_cnt = 16;
	HI_S32 s32Ret = HI_SUCCESS;
	MPP_SYS_CONF_S stSysConf = {0};

	if (!pstSysParam)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:pSysParam was null", __FUNCTION__, __LINE__);
		return -1;
	}
	//step1:清理系统
	HI_SYS_CleanSystem();
	//step2:
	memset(&stVbConf, 0, sizeof(stVbConf));
	if (pstSysParam->m_i32VideoBlockParamCnt > vb_pool_max_cnt)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:Excessive number of coompools specified by users", __FUNCTION__, __LINE__);
	}
	for (i = 0;i < pstSysParam->m_i32VideoBlockParamCnt; i++)
	{
		u32BlkSize = CEILING_2_POWER(pstSysParam->m_stVideoBlockParamPtr[i].m_i32Width, pstSysParam->m_i32StrideAlignWidth)\
			* CEILING_2_POWER(pstSysParam->m_stVideoBlockParamPtr[i].m_i32Height, pstSysParam->m_i32StrideAlignWidth) *2;
		stVbConf.astCommPool[i].u32BlkSize = u32BlkSize;
		stVbConf.astCommPool[i].u32BlkCnt = pstSysParam->m_stVideoBlockParamPtr[i].m_i32BlockCnt;
		if (strlen(pstSysParam->m_stVideoBlockParamPtr[i].m_strMmzName)
		{
			snprintf(stVbConf.astCommPool[i].acMmzName, sizeof(stVbConf.astCommPool[i].acMmzName), "%s", pstSysParam->m_stVideoBlockParamPtr[i].m_strMmzName);
		}
	}
	stVbConf.u32MaxPoolCnt = 128;
	s32Ret = HI_MPI_VB_SetConf(&stVbConf);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:failed with 0x%x", __FUNCTION__, __LINE__, s32Ret);
		return -2;
	}

	s32Ret = HI_MPI_VB_Init();
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:failed with 0x%x", __FUNCTION__, __LINE__, s32Ret);
		return -3;
	}

	stSysConf.u32AlignWidth = pstSysParam->m_i32StrideAlignWidth;
	s32Ret = HI_MPI_SYS_SetConf(&stSysConf);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:failed with 0x%x", __FUNCTION__, __LINE__, s32Ret);
		return -4;
	}

	s32Ret = HI_MPI_SYS_Init();
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:failed with 0x%x", __FUNCTION__, __LINE__, s32Ret);
		return -5;
	}
	log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:success!", __FUNCTION__, __LINE__);
	return 0;
}

int32_t HI_SYS_UnInit()
{
	HI_SYS_CleanSystem();
}

int32_t HI_SYS_GetvVersion(char *pstrOutBuf, int32_t i32BufSize)
{
	HI_S32 s32Ret = HI_SUCCESS;
	MPP_VERSION_S stMppVersion;

	if (!pstrOutBuf || i32BufSize <= 0)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:param invalid!", __FUNCTION__, __LINE__);
		return -1;
	}
	s32Ret = HI_MPI_SYS_GetVersion(&stMppVersion);
	if (HI_SUCCESS != s32Ret)
	{
		log_output(LOG_LEVEL_NET_SCREEN, "%s->%d:HI_MPI_SYS_GetVersion failed width:0x%x!", __FUNCTION__, __LINE__, s32Ret);
		return -2;
	}
	return 0;
}