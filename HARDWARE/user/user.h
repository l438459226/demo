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











