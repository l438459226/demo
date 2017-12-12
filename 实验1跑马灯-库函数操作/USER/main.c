#include "led.h"
#include "sys.h"
#include "stdio.h"
#include "appInterface.h"

//�ϲ�Ӧ��  ���õײ�ӿ�����ϲ�Ӧ�ù���	��Ԥ��ָ���ӿڸ��ײ�ص���


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

int main(void)
{
	u8 i=5; 
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	
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
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	while(i--)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);

		delay_ms(200);
		GPIO_SetBits(GPIOB,GPIO_Pin_3);

		delay_ms(500);
	}
}

