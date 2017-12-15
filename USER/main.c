
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
u8 bufer[512];

typedef  void (*pFunction0)(void);


void Ymode(void)
{
	Main_Menu();
}


u32 *Interface_addr = (u32*)0x20000550;

void load_interface(void)
{
	*Interface_addr = (u32)interface;

	printf("\r\nInterface_addr=0x%x   0x%x  0x%x\r\n",(u32)&Interface_addr,(u32)(Interface_addr),(u32)interface);
}

int main(void)
{ 
	//u32 i;
	//int len;
	
  NVIC_Configuration();
	delay_init();	    	 //��ʱ������ʼ��
	System_GPIO_Config();	
	InitUart();
 	
	usmart_dev.init(72); 	//��ʼ��USMART				 	
	mem_init(SRAMIN);
	load_interface();	//�ṩ�ӿڸ��ϲ�ʹ��

	//pp = mymalloc(0,1024);
	
	IIC_Init();
	Flicker_init();//ʹ���ڴ����

	i2c1_Detect();

	TL35825_init();
	Set_Voutp(5.11);//4.95v~12.75v
	Set_Voutn(-2.3);//-1.2v~-13.95v
	Voutp_Upfirst();
	
	printf("\r\nEnable ACT8846....\r\n");
	act8846_init(); 
	Delay_ms(50);
	printf("int ACT8846_ON();\r\n");
	ACT8846_Switch_Allon();
	
	TPS22993_Init();							//���ٷŵ�
	TPS22993_Set_All_Mode(1);			//���ø��ؿ���Ϊio����
	TPS22993_TPVDD_ON_OFF(1);
	TPS22993_TPVIO_ON_OFF(1);
	TPS22993_VDDH_ON_OFF(1);
	TPS22993_EXT1_ON_OFF(1);
	TPS22993_IOVCC_ON_OFF(1);
	TPS22993_VSP_VSN_ON_OFF(1);
	
	Delay_ms(50);
	
	OTP_P_ON_OFF(1);					//MOS�ܿ���

	OLEDLCD_MAIN_POWER_OFF(); 	//LCD OLED ��ѹ�л�   ����mos��  ͨ���̵����л���Դ

	BL_POWER_ON(); 	//mos�� ����  ��bl��5V��Դ
	Delay_ms(100);
	BL_ADJ_OFF();	//����BLģ��
	BL_DETECT_ON();	//�������mos�ܿ��ر���ģ��BL+ 
	printf("���⣺\r\n");
	LM36923_Init(20);
	
	
	VSP_ON();	//��ʹ�� vsp  vsn
	VSP_PWR_ON();	//	
	VSN_ON();
	
	Delay_ms(10);
	Tps65132_Init(Get_Volt_Val(PWR5_VSP_AVDD_INDEX), Get_Volt_Val(PWR6_VSN_AVEE_INDEX)); //����VSP VSN��ѹ
	Delay_ms(10);

	RELAY_UA_ALL_ON_OFF(1);
	Delay_ms(500);
	INA226_Volt();
	
	//Ymode();
  while(1) 
	{
		//Current_Volt();
		//printf_para();
// 		len = UnPack(bufer,64);
// 		//printf("len: %d",len);
// 		if(len>0){
// 			for(i=0;i<len;i++)
// 			{
// 				printf(" 0x%x",bufer[i]);
// 			}
// 			printf("\r\n");
// 		}
		
		protocol_pachk();
		//Delay_ms(1000);
		//len = ReadUart(USART_PORT_COM2,bufer,1);
		//if(len)
			//printf("read uart:%d   0x%x  \r\n",len,bufer[0]);
	}			
	
}	




