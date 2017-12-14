#ifndef __USERR_H
#define __USERR_H

#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "boardcfg.h"
#include "arm_math.h"
#include "math.h"
#include "Fricker.h"
#include "LT35825.h"
#include "LT3582.h"
#include "act8846.h"
#include "parm.h"

#include "GPIO_Config.h"
#include "TPS22993.h"
#include "LM36923.h"
#include "tps65132.h"

#include "INA226.h"
#include "AD715.h"
#include "Uart.h"
#include "VoltCurrentProc.h"
#include "appInterface.h"
#include "common.h"


#define	PACK_HEAD 					0x80		//包头
#define	PACK_TAIL 					0x88		//包尾

//下位机 --> 上位机
#define	CMD_UA_CAL_STATUS			0x02
#define	CMD_LOADBIN_STATUS			0x03
#define	CMD_VA_VAL					0x04
#define	CMD_SYS_ERR					0x05
#define	CMD_VERSION					0x40

#define	CMD_UA_CAL_STATUS_LEN		0x01
#define	CMD_LOADBIN_STATUS_LEN		0x01
#define	CMD_VA_VAL_LEN				0x04
#define	CMD_VERSION_LEN				0x02
#define	CMD_SYS_ERR_LEN				0x01

//上位机  --> 下位机
#define	CMD_POWER_SEQ				0x41
#define	CMD_INIT_STATUS				0x42
#define	CMD_VA_STATUS				0x43
//#define	CMD_SYS_STATUS				0x44

#define	CMD_POWER_SEQ_LEN			0x01
#define	CMD_INIT_STATUS_LEN			0x01
#define	CMD_VA_STATUS_LEN			0x01
//#define	CMD_SYS_STATUS_LEN			0x01


typedef char * va_list; 

#define _INTSIZEOF(n) \
((sizeof(n)+sizeof(int)-1)&~(sizeof(int) - 1) ) 

#define va_start(ap,v) ( ap = (va_list)&v + _INTSIZEOF(v) ) 

#define va_arg(ap,t) \
( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) ) 

#define va_end(ap) ( ap = (va_list)0 ) 

void printf_fun(int reg,...);

int UnPack(u8 *package,u8 len);
void ACT8846_Switch_Allon(void);


#endif











