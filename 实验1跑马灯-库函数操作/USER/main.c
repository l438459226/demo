#include "led.h"
#include "sys.h"
#include "appInterface.h"

//上层应用  调用底层接口完成上层应用功能	（预留指定接口给底层回调）


void led_flash(void)
{
	u8 i=5;
	u8 per;
	u32 *bufer;
	
	load_interface();
	Set_Voutp(4.78);
	Set_Voutn(-5.87);

	per = mem_perused(0);
	printff("using diceng function mem perused:%d  0x%x\r\n",per,bufer);
	while(i--)
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
		delay_ms(1000);
		GPIO_SetBits(GPIOB,GPIO_Pin_3);
		delay_ms(1000);
	}
}

int main(void)
{
	while(1)
	{
		printff("error appmain\r\n");
	}
}


