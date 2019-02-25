#ifndef __ZAL_AI_INTERFACE__
#define __ZAL_AI_INTERFACE__

#include <stdint.h>


// 目标系统数据类型选择（定义）
#define ZAL_DATA_TYPE_Q7	0
#define ZAL_DATA_TYPE_Q15	0
#define ZAL_DATA_TYPE_F32	1

#if ZAL_DATA_TYPE_Q7
typedef int8_t DateType;
#elif ZAL_DATA_TYPE_Q15
typedef int16_t DateType;
#else
typedef float DateType;
#endif


typedef void**  ZalAiHandle_t;

typedef struct{
	
	uint16_t model_type;
	uint16_t labels;
	uint16_t layer_num;
	uint16_t input_shape_len;
	uint16_t input_shape[4];

	uint16_t fc_nums;
	uint16_t lstm_nums;
	uint16_t conv_nums;
	uint16_t pool_nums;

}ZalAiModelInfo_t;


typedef struct {
	int       len;
	DateType *p_data;
}ZalWeightInfo_t;


#ifdef __cplusplus
extern "C" {
#endif

	ZalAiHandle_t zal_ai_create(char *p_filename);

	ZalAiModelInfo_t zal_ai_model_info_get(ZalAiHandle_t handle);

	int zal_ai_calc(DateType *p_input, DateType *p_output, ZalAiHandle_t handle);

	void zal_ai_release(ZalAiHandle_t handle);

#ifdef __cplusplus
}
#endif

#endif