/*********************************************************************************************************
* 文件名称: LM36923.h
* 文件作者:相信未来
* 当前版本: 01.00.00
* 所属模块: CMS
* 创建日期: 2016年03月22日
* 文件摘要: 
* 注意事项: 
* 更改说明: 初始创建
**********************************************************************************************************/
#ifndef __LM36923_H
#define __LM36923_H



/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "stm32f10x.h"




/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#define  LM36923_ADD		0x36			








/*********************************************************************************************************
*                                              结构体定义
*********************************************************************************************************/
typedef enum 
{
	BL_CHN1_NONE = 0,
	BL_CHN1 = 0x01, 
	BL_CHN2 = 0x02, 
	BL_CHN3 = 0x03,
	BL_CHN_ALL	= 0x0E,
	BL_CHN_MAX = 0,
}BL_CHN_TypeDef;



typedef enum 
{
	BL_MODE_I2C = 0,
	BL_MODE_PWM,
	BL_MODE_I2C_PWM_MODE10,
	BL_MODE_I2C_PWM_MODE11,
}BL_MODE_TypeDef;



typedef enum 
{
	LIN_MAP = 0,
	EXP_MAP,
}MAP_TypeDef;









/*********************************************************************************************************
*                                              API函数定义
*********************************************************************************************************/
void LM36923_Reset(void);
void LM36923_Set_Mode(BL_MODE_TypeDef mode,MAP_TypeDef map);
void LM36923_On(BL_CHN_TypeDef chn);
void LM36923_Off(BL_CHN_TypeDef chn);
void LM36923_Set_Current(u16 val);
void LM36923_Init(u16 val);
//int LM36923_I2c_write(u8 reg,u8 val);
void LM36923_AllOn(void);
void LM36923_AllOff(void);
void LM36923_Set_Val(u8 val);





















#endif


