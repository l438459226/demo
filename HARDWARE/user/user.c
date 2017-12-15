#include "user.h"

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





int UnPack(u8 *package,u8 len)
{
	static u8 i = 0,start = 0;
	u8 lenth;

	if(ReadUart(USART_PORT_COM2,&package[i],1)==0)//??????
	{
			return -1;
	}
	
	if(start)	//
	{
	#if 0 
		//printf("start \r\n");
		if(package[i] == PACK_HEAD)	//
		{
			printf("package agan\r\n");
			Clear_buffer(package,len);
			
			start = 1;
			i = 0;	//
			return 0;
		}
		#endif
		
		if(package[i] == PACK_TAIL)
		{		
			lenth = i;
			start = 0;
			i = 0;
			return lenth;
		}
		else
		{
			i++;
			if(i==(len-1)) {start = 0;i = 0;mymemset(package,0,len);}	
			
		}
	}
	if((package[i] == PACK_HEAD)&&(i==0))
	{
		i = 0;
		start = 1;
		//printf("start \r\n");
		return 0 ;
	}
	return 0;
}

void printf_fun(int reg,...)   
{   
    va_list   arg_ptr;     //定义可变参数指针 
		int i,regdata,n;
	
	
    va_start(arg_ptr,reg);   // i为最后一个固定参数，这里i为100
		n = va_arg(arg_ptr,int);
		printf( " 0x%x 0x%x",reg,n); 
		for(i=0;i<n;i++)
		{
			regdata = va_arg(arg_ptr,int);
			printf( " 0x%x",regdata); 
		}
		printf("\r\n");
	
    va_end(arg_ptr);        //  清空参数指针

    return;   
}


void ACT8846_Switch_Allon(void)
{
	ACT8846_DCDC_Switch(DCDC_SW1,ACT8846_SWITCH_ON);
	ACT8846_DCDC_Switch(DCDC_SW2,ACT8846_SWITCH_ON);
	ACT8846_DCDC_Switch(DCDC_SW3,ACT8846_SWITCH_ON);	//off san lu
	ACT8846_DCDC_Switch(DCDC_SW4,ACT8846_SWITCH_ON);

	
	ACT8846_LDO_Switch(LDO_SW1,ACT8846_SWITCH_ON);				//对应OUT5。 注意 :OUT6 和 OUT10没有经过TPS22993
	ACT8846_LDO_Switch(LDO_SW2,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW3,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW4,ACT8846_SWITCH_ON);				//VSP VSN ON
	ACT8846_LDO_Switch(LDO_SW5,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW6,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW7,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW8,ACT8846_SWITCH_ON);
}














