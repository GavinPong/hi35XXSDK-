#ifndef __HI_VO_H__
#define __HI_VO_H__

#ifdef __cplusplus
extern "C"
{
#endif

//vo�豸����
typedef struct _hi_vo_dev_param_s{
	uint32_t m_u32VoDevID;		//�豸ID
	uint32_t m_u32Width;		//ͼ���
	uint32_t m_u32Height;		//ͼ���
	uint32_t m_u32FrameRate;	//֡��
	uint32_t m_u32BgColor;		//����ɫ
	char m_strIntfTypeName[16];	//�ӿ�����������vga,hdmi,cvbs,btt1120	
	uint8_t m_bInterlaced;		//�Ƿ����
}hi_vo_dev_param_t;

//vo��Ƶ�ɲ���
typedef struct _hi_vo_layer_param_s{
	int32_t m_i32VoLayerID;			//��Ƶ��ID
	uint32_t m_u32Width;			//��Ƶ���ȣ��豸��ȣ�
	uint32_t m_u32Height;			//��Ƶ��߶ȣ��豸�߶ȣ�
	uint32_t m_u32FrameRate;		//ˢ��֡��
	int32_t m_i32DispPosX;			//��ʾ�������X����
	int32_t m_i32DispPosY;			//��ʾ�������Y����
	uint32_t m_u32DispWidth;		//��ʾ������
	uint32_t m_u32DispHeight;		//��ʾ����߶�	
	char m_strPixelFormat[16];		//���ظ�ʽ,example "yuvsp420"��"rgb_p888"
}hi_vo_layer_param_t;

//hdmi����
typedef struct _hi_hdmi_param_s{
	int32_t m_i32HdmiID;			//HDMI ID
	char m_strIntfSync[16];			//�ӿ�ʱ�� ��720p50/pal/ntsc
	uint8_t m_bHDCPEnable;			//HDCPʹ��
	uint8_t m_bEnableAudio;			//ʹ����Ƶ
	int32_t m_i32AudioBitDepth;		//��Ҫ��AOһ��
}hi_hdmi_param_t;

//�豸����
int32_t HI_VO_StartDev(hi_vo_dev_param_t *pstVoDevParam);
int32_t HI_VO_StopDev(int32_t i32VoDevID);

//��Ƶ�����
int32_t HI_VO_StartVoLayer(hi_vo_layer_param_t *pstVoLayerParam);
int32_t HI_VOStopVoLayer(int32_t i32VoLayerID);

//HDMI����
int32_t HI_VO_StartHdmi(hi_hdmi_param_t *pstHdmiParam);
int32_t HI_VO_StopHdmi(int32_t i32HdmiID);

#ifdef __cplusplus
};
#endif

#endif