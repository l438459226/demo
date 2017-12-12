#include "led.h"
#include "sys.h"
#include "stdio.h"
#include "appInterface.h"

//上层应用  调用底层接口完成上层应用功能	（预留指定接口给底层回调）


void led_flash(void)
{
	u8 i=5;
	LED_Init();		  	//初始化与LED连接的硬件接口
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
	LED_Init();		  	//初始化与LED连接的硬件接口
	
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
	LED_Init();		  	//初始化与LED连接的硬件接口
	while(i--)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);

		delay_ms(200);
		GPIO_SetBits(GPIOB,GPIO_Pin_3);

		delay_ms(500);
	}
}

