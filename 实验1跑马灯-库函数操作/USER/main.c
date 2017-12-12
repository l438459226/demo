#include "led.h"
#include "delay.h"
#include "sys.h"
#include "stdio.h"
//ALIENTEKս��STM32������ʵ��1
//�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾


u8 app[32];

//pFunction0 IAP_W25QXX_Init = 0;

void Delay_us(u32 val)
{
	int i = 0,j = 0;

	for(i = 0; i < val ; i++)
	{
		for(j = 0;j < 36;j++)
		{
			;
		}
	}
}
void Delay_ms(u16 nms)
{
	Delay_us(nms*1000);
}

typedef  u32 (*Interface)();
typedef  void (*iap_Set_Voutp)(float voltage);
//typedef void iap_Set_Voutp(float voltage)

#define 		INTERFACEADDR				0x20000550

Interface IAP_W25QXX_Init = NULL;
iap_Set_Voutp Set_Voutp = NULL;

u32 *addr_interface = (u32*)0x20000550;

void load_interface(void)
{
	addr_interface = (u32*)0x20000550;
	
	printf("\r\nInterface_addr=0x%x   0x%x \r\n",(u32)addr_interface,(u32)(*addr_interface));
	IAP_W25QXX_Init = (u32(*)())(((u32*)(*addr_interface))[2]);
	Set_Voutp = (iap_Set_Voutp)(((u32*)(*addr_interface))[15]);
	Set_Voutp(4.45);
	IAP_W25QXX_Init("\r\n############Interface OK$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\r\n");
}

void led_flash(void)
{
	u8 i=5;
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	load_interface();
	
	
	while(i--)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
		Delay_ms(1000);
		GPIO_SetBits(GPIOB,GPIO_Pin_3);

		Delay_ms(1000);
	}
}






//0x2000C000
int main(void)
{
	u8 i=5;
	//delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	

	app[0] = (u32)led_flash;
	
	while(i--)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
		
		Delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_3);

		Delay_ms(500);
	}
	return 0;
}




void APPmain(void)
{	
	u8 i=3;
	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	while(i--)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);

		delay_ms(200);
		GPIO_SetBits(GPIOB,GPIO_Pin_3);

		delay_ms(500);
	}
}

