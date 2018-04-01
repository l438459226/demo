
#include "lcmburn.h"	//50286
#ifdef LCMBRUN

#include "delay.h"
#include "math.h"
#include "usart.h"
#include "ssd2828.h"
#include "lcd.h"
#include "LCM.h"

extern u8 fb_buffer[128];

U16 B1[0x0B] = {0xB1,0x48,0x0D,0x6D,0x09,0x33,0x54,0x71,0x71,0x2E,0x45};

U16 B4[0x16] = {0xB4,0x78,0x72,0x78,0x72,0x78,0x72,0x01,0x0C,0x86,0x75,0x00,0x3F,0x78,0x72,0x78,0x72,0x78,0x72,0x01,0x0C,0x86};

U16 D3[0x22] = {0xD3,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x32,0x10,0x02,0x00,0x02,0x32,0x13,0xC0,0x00,0x00,0x32,0x10,0x08,
			0x00,0x00,0x47,0x04,0x04,0x04,0x47,0x05,0x05,0x47,0x0A,0x40};
		
U16 D5[0x2D] = {0xD5,0x18,0x18,0x18,0x18,0x04,0x05,0x06,0x07,0x00,0x01,0x02,0x03,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
			0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x19,0x19,0x19,0x19,0x20,0x21,0x22,0x23};
				
U16 D6[0x2D] = {0xD6,0x18,0x18,0x19,0x19,0x03,0x02,0x01,0x00,0x07,0x06,0x05,0x04,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
			0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x19,0x19,0x18,0x18,0x23,0x22,0x21,0x20};
				
U16 E0[0x3B] = {0xE0,0x18,0x04,0x0B,0x13,0x19,0x1C,0x22,0x22,0x49,0x5A,0x6B,0x69,0x72,0x84,0x84,0x88,0x92,0x8D,0x88,0x92,0xA5,0x52,0x51,0x54,0x59,0x5E,0x61,0x71,0x71,
			     0x03,0x1F,0x1C,0x22,0x25,0x25,0x28,0x27,0x4D,0x5B,0x6C,0x68,0x71,0x82,0x85,0x8C,0x99,0x9A,0x98,0xA5,0xBA,0x5D,0x5C,0x61,0x67,0x6A,0x6E,0x71,0x71};

U16 B2[13] = {0xB2,0x00,0x80,0x64,0x0E,0x0A,0x2F,0x00,0x00,0x00,0x00,0xC0,0x18};


u8 write_otp(u8 vcom)
{
		u16 ssdreg;
		u8 rvcom;

		DCS_Short_Write_1P(0xB6,vcom);
	
		ssdreg = ssd_rdata(0xB7);
		sprintf((char*)fb_buffer,"SSD conf:%04X",ssdreg);	//?LCD ID???lcd_id???				 	
		LCD_ShowString(0,12,176,16,16,fb_buffer);
	
		DCS_Short_Read_NP(0xB6, 1, &rvcom);	
		return rvcom;
}

u8 Read_otp(void)//��ȡOTPֵ
{    
	u8 rvcom; 
	DCS_Short_Read_NP(0xDA, 1, &rvcom);
	return 0;
}


u8 before_otp_read(void)//��ȡOTPֵ
{ 
	u8 BUFFER[8];
	BUFFER[0]=0;
	DCS_Short_Read_NP(0xB6, 3, BUFFER+0);
	
	sprintf((char*)fb_buffer,"VC:%X OVC:%X MK:%X ",BUFFER[0],BUFFER[1],BUFFER[2]);
	LCD_ShowString(0,6,176,16,16,fb_buffer);
	return 0;
}

u8 after_otp_read(void)//��ȡOTPֵ
{    
	/*
	u8 rvcom; 
	u8 BUFFER[8];
	
	Generic_Long_Write_3P(0xFF,0x98,0x81,0x00);
	DCS_Short_Read_NP(0xDA, 1, BUFFER+0);	
	
	Generic_Long_Write_3P(0xFF,0x98,0x81,0x01);
	DCS_Short_Read_NP(0x53, 1, BUFFER+1);
	DCS_Short_Read_NP(0xE6, 1, BUFFER+2);	//ID_MK
 	DCS_Short_Read_NP(0xE8, 1, BUFFER+3);	
	
	DCS_Long_Write_3P(0xFF,0x98,0x81,0x04);
	DCS_Short_Read_NP(0xC5, 1, BUFFER+4);

	sprintf((char*)fb_buffer,"A ID:%X MK:%X ",BUFFER[0],BUFFER[2]);
	LCD_ShowString(0,7,176,16,16,fb_buffer);
	sprintf((char*)fb_buffer,"VC:%X OVC:%X MK:%X ",BUFFER[1],BUFFER[4],BUFFER[3]);
	LCD_ShowString(0,8,176,16,16,fb_buffer);*/
	return 0;
}

void burn_otp(u8 best)
{
		//Sleep out
	DCS_Short_Write_1P(0x11,0x00);
	delay_ms(150);

	// Set EXTC
	DCS_Long_Write_3P(0xB9,0xFF,0x83,0x94);

	//Optimized VCOM
	 DCS_Short_Write_1P(0xB6, best);

	//Enter OTP program mode
	DCS_Long_Write_7P(0xBB,0x00,0x00,0x00,0x00,0x00,0xAA,0x55);

	//internal power mode on
	DCS_Long_Write_7P(0xBB,0x80,0x00,0x00,0x00,0x00,0xAA,0x55);
	delay_ms(20);	//>100ms

	//Specify OTP_index VCOM_F 0x0D
	DCS_Long_Write_7P(0xBB,0x80,0x0D,0x00,0x00,0x00,0xAA,0x55);

	//Set OTP_PROG = 1
	DCS_Long_Write_7P(0xBB,0x80,0x0D,0x00,0x01,0x00,0xAA,0x55);
	delay_ms(60);	//10ms/byte

	//Set OTP_PROG = 0 OTP_index programming action done
	DCS_Long_Write_7P(0xBB,0x80,0x0D,0x00,0x00,0x00,0xAA,0x55);

	// Leave OTP program mode & Remove  power
	DCS_Long_Write_7P(0xBB,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
	delay_ms(100);
}


void yassylcd_init(void)
{
	
	panel_info.width = 720;
	panel_info.height = 1280;
	panel_info.pixel = 24;
	panel_info.fps = 60;		//60����
	
	panel_info.hsync = 20;
	panel_info.hbp = 20;
	panel_info.hfp = 48;
	
	panel_info.vsync = 10;
	panel_info.vbp = 10;
	panel_info.vfp = 20;
	panel_info.dsi_lane = 3;			//
	
	panel_info.pclk = panel_info.fps * ((panel_info.width + panel_info.hsync + panel_info.hbp + panel_info.hfp) * (panel_info.height + panel_info.vsync + panel_info.vbp + panel_info.vfp))/1000000;
	panel_info.dsi_mbps = panel_info.pclk*24/panel_info.dsi_lane + 8;		//��8mУ������
	
	
	SSD_LANE(3,0);

		// Set EXTC
	DCS_Long_Write_3P(0xB9, 0xFF, 0x83, 0x94);
	Generic_Long_Write_3P(0xB9, 0xFF, 0x83, 0x94);
	delay_ms(20);
	DCS_Long_Write_FIFO(0x0B,B1);	//
	delay_ms(20);
	
  Generic_Long_Write_6P(0xBA, 0x62, 0x03, 0x68, 0x6B, 0xB2, 0xC0);

	// Set MIPI
	DCS_Long_Write_6P(0xBA, 0x62, 0x03, 0x68, 0x6B, 0xB2, 0xC0);
	delay_ms(20);
	Generic_Long_Write_6P(0xBA, 0x62, 0x03, 0x68, 0x6B, 0xB2, 0xC0);
	// Set Display
	DCS_Long_Write_6P(0xB2, 0x00, 0x80, 0x64, 0x0E, 0x0A, 0x2F);
	delay_ms(20);

	// Set CYC
	DCS_Long_Write_FIFO(0x16,B4);
	delay_ms(20);

	// Set D3
	DCS_Long_Write_FIFO(0x22,D3);
	delay_ms(20);

	// Set GIP
	DCS_Long_Write_FIFO(0x2D,D5);
	delay_ms(20);

	// Set D6
	DCS_Long_Write_FIFO(0x2D,D6);
	delay_ms(20);

	// Set Gamma
	DCS_Long_Write_FIFO(0x3B,E0);
	delay_ms(20);

	// Set Panel
	DCS_Short_Write_1P(0xCC, 0x03);
	delay_ms(20);

	// Set C0
	DCS_Long_Write_2P(0xC0, 0x1F, 0x73);
	delay_ms(20);

	// Set D4h
	DCS_Short_Write_1P(0xD4, 0x02);
	delay_ms(20);

	// Set BD
	DCS_Short_Write_1P(0xBD, 0x01);
	delay_ms(20);

	// Set GAS
	DCS_Short_Write_1P(0xB1, 0x00);
	delay_ms(20);

	// Set BD
	DCS_Short_Write_1P(0xBD, 0x00);
	delay_ms(20);

	DCS_Long_Write_2P(0xB6, 0x6A, 0x6A);	//8A

	DCS_Short_Write_1P(0x36, 0x02);

	// Set BD
	DCS_Short_Write_1P(0xC6, 0xEF);


	DCS_Short_Write_1P(0x11,0x00);
	DCS_Short_Write_1P(0x35,0x01);
	delay_ms(150);
	DCS_Short_Write_1P(0x29,0x00);
	
	SSD_MODE(0,1);
}

#endif


