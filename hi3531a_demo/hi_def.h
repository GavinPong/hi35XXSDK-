#ifndef __HI_DEF_H__
#define __HI_DEF_H__


#define GET_VO_LAYER(voLayer, voDev) do{\
	if((voDev) < 2) voLayer = voDev;\
	else	\
	voLayer = voDev + 1;\
}while(0);

#ifdef __cplusplus
extern "C"{
#endif


#ifdef __cplusplus
};
#endif

#endif