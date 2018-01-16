
#ifndef _GXNUSSD2828_H_
#define _GXNUSSD2828_H_

//#include "systick.h"

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
#include "myiic.h"
#include "INA226.h"
#include "AD715.h"
#include "Uart.h"
#include "VoltCurrentProc.h"
#include "appInterface.h"
#include "common.h"
#include "user.h"
#include "Protocol.h"
#include "ssd2828.h"
#include "lcm.h"


extern unsigned int Dsi_LANE;
extern unsigned int Dsi_mbps;//mbps
extern unsigned int Lcd_PCLK;
extern unsigned int Lcd_fps;

void SSD_LANE(u8 lane,u16 clock);
void SSD_MODE(u8 vido_mode,u8 mode);
void print_panelinfo(void);

#endif

