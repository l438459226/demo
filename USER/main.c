
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

/*----------------------------------------------------------------------------*/
void SSD2828_SDO(void)	//PA3-SPI_CS    PA5-SPI_CLK   PA6-MISO   PA7-MOSI
{
	
// 	GPIO_InitTypeDef  GPIO_InitStructure;

//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); //??PORTA,?AFIO??
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//
// 	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_0;	   ///PORTC 3 5 6 7 ??????
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure); //GPIOA	
	
// 	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	   ///PORTC 3 5 6 7 ??????
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure); //GPIOA	
	
// 	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14|GPIO_Pin_1;//PA6
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //???????
//  	GPIO_Init(GPIOB, &GPIO_InitStructure);//???GPIOA6
	
	SSD_CS = 1;
	//SPI_SDI = 1;
	//SPI_SCLK = 0;
	//SSD_RESET = 1;
	
}
int main(void)
{ 
	u16 i;
	
	
  NVIC_Configuration();
	delay_init();	    	 //ÑÓÊ±º¯Êý³õÊ¼»¯
	System_GPIO_Config();	
	InitUart();
 	
	usmart_dev.init(72); 	//³õÊ¼»¯USMART				 	
	mem_init(SRAMIN);
	load_interface();	//Ìá¹©½Ó¿Ú¸øÉÏ²ãÊ¹ÓÃ

	//pp = mymalloc(0,1024);
	
	IIC_Init();
	Flicker_init();//Ê¹ÓÃÄÚ´æ¹ÜÀí

	i2c1_Detect();

	TL35825_init();
	//Set_Voutp(5.11);	//4.95v~12.75v
	//Set_Voutn(-2.3);	//-1.2v~-13.95v
	//Voutp_Upfirst();
	
	printf("\r\nEnable ACT8846....\r\n");
	act8846_init(); 
	Delay_ms(50);
	printf("int ACT8846_ON();\r\n");
	ACT8846_Switch_Allon();
	
	TPS22993_Init();							//¿ìËÙ·Åµç
	TPS22993_Set_All_Mode(1);			//ÉèÖÃ¸ºÔØ¿ª¹ØÎªio¿ØÖÆ
	TPS22993_TPVDD_ON_OFF(1);
	TPS22993_TPVIO_ON_OFF(1);
	TPS22993_VDDH_ON_OFF(1);
	TPS22993_EXT1_ON_OFF(1);
	TPS22993_IOVCC_ON_OFF(0);
	TPS22993_VSP_VSN_ON_OFF(1);
	
	Delay_ms(50);
	
	OTP_P_ON_OFF(1);					//MOS¹Ü¿ª¹Ø

	OLEDLCD_MAIN_POWER_OFF(); 	//LCD OLED µçÑ¹ÇÐ»»   ¿ØÖÆmos¹Ü  Í¨¹ý¼ÌµçÆ÷ÇÐ»»µçÔ´

	BL_POWER_ON(); 	//mos¹Ü ¿ØÖÆ  ¸øbl¹©5VµçÔ´
	Delay_ms(100);
	BL_ADJ_ON();	//½ÓÈëBLÄ£¿é
	BL_DETECT_ON();	//±³¹â¿ØÖÆmos¹Ü¿ª¹Ø±³¹âÄ£¿éBL+ 
	printf("±³¹â£º\r\n");
	LM36923_Init(20);
	
	Delay_ms(10);
	VSP_ON();				//¬Ê¹ÄÜ vsp  vsn
	VSP_PWR_ON();		//	
	VSN_ON();
	Tps65132_Init(Get_Volt_Val(PWR5_VSP_AVDD_INDEX), Get_Volt_Val(PWR6_VSN_AVEE_INDEX)); //ÉèÖÃVSP VSNµçÑ¹
	VSP_OFF();				//¬Ê¹ÄÜ vsp  vsn
	VSP_PWR_OFF();		//	
	VSN_OFF();
	Delay_ms(10);

	RELAY_UA_ALL_ON_OFF(1);
	Delay_ms(500);
	INA226_Volt();
	

	
	RELAY_UA_IOVCC_ON_OFF(0);
	TPS22993_IOVCC_ON_OFF(1);
	Delay_ms(20);
 	VSP_ON();				//¬Ê¹ÄÜ vsp  vsn
	VSP_PWR_ON();		//
	Delay_ms(20);
	VSN_ON();
	Delay_ms(100);
		Ymode();
	SSD2828GPIOConfig();

	Write_SSPI_REG(0xC0, 0x0100);
	Delay_ms(100);
	Write_SSPI_REG(0xC0, 0x0000);
	Delay_ms(100);	 
	Write_SSPI_REG(0xB9, 0xC000);	 
	Write_SSPI_REG(0xBA, 0xC35E);		 
	Write_SSPI_REG(0xCF, 0x0000);	
	Write_SSPI_REG(0xD0, 0x0010);	
	Write_SSPI_REG(0xDE, 0x0003);
	Write_SSPI_REG(0xBB, 0x0009);	
	Write_SSPI_REG(0xD5, 0x30C0);
	Write_SSPI_REG(0xCE, 0x0405);
	Write_SSPI_REG(0xCD, 0x2DE7);
	Write_SSPI_REG(0xCC, 0x0E11);
	Write_SSPI_REG(0xCB, 0x0842);
	Write_SSPI_REG(0xCA, 0x3A08);
	Write_SSPI_REG(0xC9, 0x1B0B);
	Write_SSPI_REG(0xB7, 0x0150);
	Write_SSPI_REG(0xB9, 0x0001);
	Write_SSPI_REG(0xB8, 0x0000);
	Write_SSPI_REG(0xBD, 0x0000);
	Write_SSPI_REG(0xB1, 0x0202);
	Write_SSPI_REG(0xB2, 0x1828);
	Write_SSPI_REG(0xB3, 0x326E);
	Write_SSPI_REG(0xB4, 0x0438);
	Write_SSPI_REG(0xB5, 0x0870);
	Write_SSPI_REG(0xB6, 0x00D3);
	Write_SSPI_REG(0xB7, 0x0159);
	Delay_ms(100);	 
 
	
	
	
	
	
	
	
	
	

 	//InitMipi_PanelInit();
	//Write_SSPI_REG(0xB7, 0x0309);
	//printf("SSD ID:0xB0 = 0x%x\r\n",ssd_rdata(0xB0));	
	
	//printf("SSD ID:0xB0 = 0x%x\r\n",ssd_rdata(0xB0));	
	//printf("brige:0xB7 = 0x%x\r\n",ssd_rdata(0xB7));
	//printf("SSD ID:0xB0 = 0x%x\r\n",ssd_rdata(0xB0));	
	//printf("brige:0xB7 = 0x%x\r\n",ssd_rdata(0xB7));
	
	DETECT_LED1N_ON_OFF(1);
	DETECT_LED2N_ON_OFF(1);
	Delay_ms(100);
	Ymode();

	printf("0xB0 = 0x%x\r\n",ssd_rdata(0xB0));

	printf("SSD READ:\r\n");
	for(i=0xB0;i<0XF8;i++)
	{
		printf("0x%x=0x%x\r\n",i,ssd_rdata(i));
	}
	printf("\r\n\r\n");
	
		//Generic_Short_Write_1P(0x00, 0x00);
		//Generic_Long_Write_3P(0xFF, 0x19,0x11,0x11);
		
		//Generic_Short_Write_1P(0x00, 0x80);
		//DCS_Long_Write_7P(0xc7, 0x00,0x15,0x36,0x4a,0x59,0x65,0x77);
		// 	Generic_Short_Write_1P(0xB0, 0x04);
		// 	Generic_Long_Write_5P(0xDE, 0x01,0x00,0x0F,0xFF,0x05);

	//Generic_Short_Write_1P(0xB0, 0x04);
	//Generic_Short_Write_1P(0xB0, 0x04);

	//Generic_Short_Write_1P(0xB0, 0x04);
	//Generic_Short_Write_1P(0xDE, 0x01);
	//DCS_Long_Write_5P(0xDE, 0x01,0x00,0x0F,0xFF,0x05);
	//DCS_Short_Read_NP(0xDE,8,bufer);
	
	SSD_RESET = 1;
	Delay_ms(200);
	SSD_RESET = 0;
	Delay_ms(200);
	SSD_RESET = 1;
	
	DCS_Short_Read_NP(0xDA,1,bufer);
	DCS_Write(0x11,1,0);
	Delay_ms(200);
	DCS_Write(0x29,1,0);
	Delay_ms(200);
	DCS_Write(0xB0,1,0x04);
	//DCS_Write(0xDE,5,0x01,0x00,0x0F,0xFF,0x05);
	DCS_Write(0xC3,7,0x86,0xD8,0x6D,0x57,0x23,0x4A,0xE5);
	Delay_ms(200);
	
	while(1)
	{
		printf("0xB0 = 0x%x\r\n",ssd_rdata(0xB0));
		Delay_ms(1000);
	}
	
	
	while(1) 
	{
		//ssd_rdata(0xB0);
		//GP_R(0x0C,3,bufer);
		//DCS_Long_Write_4P(0x56,0xAA,0x55,0x33,0x7D);
		//Delay_ms(1);
	
	//Generic_Short_Write_1P(0xB0,0x04);
	//DCS_Long_Write_5P(0xDE, 0x01,0x00,0x0F,0xFF,0x05);
	//DCS_Long_Write_7P(0xc0, 0x00,0x15,0x36,0x4a,0x59,0x65,0x77);
	//DCS_Short_Read_NP(0xC1,8,bufer);
	DCS_Short_Read_NP(0xC3,8,bufer);

	printf("read lcm:0xDE ");
	for(i=0;i<12;i++){
		printf("0x%x ",bufer[i]);
		bufer[i] = 0x00;
	}
	printf("\r\n");
	Delay_ms(1000);
		//yassylcd_init();
// 		VSP_ON();				//¬Ê¹ÄÜ vsp  vsn
// 		VSP_PWR_ON();		//	
// 		VSN_ON();
// 		TPS22993_IOVCC_ON_OFF(1);
// 		Delay_ms(4000);
// 		VSP_OFF();				//¬Ê¹ÄÜ vsp  vsn
// 		VSP_PWR_OFF();		//	
// 		VSN_OFF();
// 		TPS22993_IOVCC_ON_OFF(0);
// 		Delay_ms(4000);
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
		
		//protocol_pachk();
		//Delay_ms(1000);
		//len = ReadUart(USART_PORT_COM2,bufer,1);
		//if(len)
			//printf("read uart:%d   0x%x  \r\n",len,bufer[0]);
	}			
	
}	




