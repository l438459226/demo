#include "led.h"
#include "sys.h"
#include "appInterface.h"

//涓婂眰搴旂敤  璋冪敤搴曞眰鎺ュ彛瀹屾垚涓婂眰搴旂敤鍔熻兘	锛堥鐣欐寚瀹氭帴鍙ｇ粰搴曞眰鍥炶皟锛?


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
	//while(1);
	while(1)
	{
		printff("error appmain\r\n");
	}
}
