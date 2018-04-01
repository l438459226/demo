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






void printf_fun(int reg,...)   
{   
    va_list   arg_ptr;     //����ɱ����ָ�� 
		int i,regdata,n;
	
	
    va_start(arg_ptr,reg);   // iΪ���һ���̶�����������iΪ100
		n = va_arg(arg_ptr,int);
		printf( " 0x%x 0x%x",reg,n); 
		for(i=0;i<n;i++)
		{
			regdata = va_arg(arg_ptr,int);
			printf( " 0x%x",regdata); 
		}
		printf("\r\n");
	
    va_end(arg_ptr);        //  ��ղ���ָ��

    return;   
}


void ACT8846_Switch_Allon(void)
{
	ACT8846_DCDC_Switch(DCDC_SW1,ACT8846_SWITCH_ON);
	ACT8846_DCDC_Switch(DCDC_SW2,ACT8846_SWITCH_ON);
	ACT8846_DCDC_Switch(DCDC_SW3,ACT8846_SWITCH_ON);	//off san lu
	ACT8846_DCDC_Switch(DCDC_SW4,ACT8846_SWITCH_ON);

	
	ACT8846_LDO_Switch(LDO_SW1,ACT8846_SWITCH_ON);				//��ӦOUT5�� ע�� :OUT6 �� OUT10û�о���TPS22993
	ACT8846_LDO_Switch(LDO_SW2,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW3,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW4,ACT8846_SWITCH_ON);				//VSP VSN ON
	ACT8846_LDO_Switch(LDO_SW5,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW6,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW7,ACT8846_SWITCH_ON);
	ACT8846_LDO_Switch(LDO_SW8,ACT8846_SWITCH_ON);
}













