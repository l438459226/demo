#include "ssd2828.h"
//#include "lcd_drvv.h"
//#include "lcd_drv.h"
#include "gxnussd2828.h"
#include "stdio.h"	

//extern vidinfo_t panel_info;
unsigned int Dsi_LANE;
unsigned int Dsi_mbps;//mbps
unsigned int Lcd_PCLK;
unsigned int Lcd_fps;
#if 0
u16 dsi_clock(u16 speed)//DSI	speed
{
		u16 pll;
		if(speed<1000)		pll = 0xc300;
		else if(speed<500)	pll = 0x8300;
			else if(speed<250)	pll = 0x4300;
				else if(speed<125)	pll = 0x0300;
	pll |= ((speed>>3)&0xff);	// ³ý8
	return pll;
}


void hs_settime(u16 pll)
{
		u16 hzd,hpd,czd,nibble;
		u16 czdcpd,cpedtd,chtd,wud;
	
		hzd = (pll/32) + 8;
		if(hzd < 3)	hzd = hzd;
			else if(hzd < 15)	hzd -= 1;
				else if(hzd < 17)	hzd -= 2;
					else if(hzd < 27)	hzd -= 3;
	
		hpd = (pll/80) + 1;
		nibble = (hzd<<8) | (hpd & 0xFF);
	
		if(pll>125)	czd = (pll/16) + 0x0A;
		else 	czd = 0x28;
		czdcpd = (czd<<8) | 0x0A;
		cpedtd = 0x0844;
	
		if(pll>125)	chtd = 0x0309;
		else chtd = (((pll/64)+3)<<8) | (((pll/64)+9));
		wud = 0x2ebb;
	
	Write_SSPI_REG(0xC9, nibble);
	Write_SSPI_REG(0xCA, czdcpd);
	Write_SSPI_REG(0xCB, cpedtd);
	Write_SSPI_REG(0xCC, chtd);
	Write_SSPI_REG(0xCD, wud);
}


void SSD_LANE(u8 lane,u16 clock)
{
	Write_SSPI_REG(0xB9, 0x0000);
	Write_SSPI_REG(0xB8, 0x0000);
	Write_SSPI_REG(0xB6, 0x000B);	//non burst sync event, 24bpp
	 
	if(clock)
			Dsi_mbps = clock;//Write_SSPI_REG(0xBA, dsi_clock(clock));//  0xC367--824
	else 	Dsi_mbps = Lcd_DCLK*24/Dsi_LANE + 8;//Write_SSPI_REG(0xBA, dsi_clock(Lcd_DCLK*24/Dsi_LANE + 8));
	
	Write_SSPI_REG(0xBA, dsi_clock(Dsi_mbps));//
	Write_SSPI_REG(0xDE, (lane-1));	//LANE  0--1 lane  1--2 lane  2--3 lane  3--4 lane
	Write_SSPI_REG(0x00B9,0x0001);
	Delay_ms(20);
	print_panelinfo(); //´òÓ¡panelÐÅÏ¢
}

void SSD_LANE(u8 lane,u16 clock)
{
	unsigned int Dsi_mbpss;
	Write_SSPI_REG(0xB9, 0x0000);
	Write_SSPI_REG(0xB8, 0x0000);
	Write_SSPI_REG(0xB6, 0x000B);	//non burst sync event, 24bpp
	if(clock)
			Dsi_mbpss = clock;//  0xC367--824
	else 	Dsi_mbpss = panel_info.pclk*24/panel_info.dsi_lane + 8;
	
	Write_SSPI_REG(0xBA, dsi_clock(Dsi_mbps));//
	Write_SSPI_REG(0xDE, (lane-1));	//LANE  0--1 lane  1--2 lane  2--3 lane  3--4 lane
	Write_SSPI_REG(0x00B9,0x0001);
	Delay_ms(20);
}
	//	//Tips:	SSD_MODE([0], [1])
	//		[0]	Video Mode:	0 - Non burst mode with sync pulses
	//						1 - Non burst mode with sync events
	//						2 - Burst mode
	//						3 - Command mode
	//		[1]	HS Mode:		0 - No operation
	//						1 - Enable HS mode
void SSD_MODE(u8 vido_mode,u8 mode)
{
	W_REG(0x00b1,Lcd_VSPW, Lcd_HSPW);
	W_REG(0x00b2, Lcd_VBPD, Lcd_HBPD);
	W_REG(0x00b3,Lcd_VFPD, Lcd_HFPD);
	W_REG(0xb4,(Lcd_LCDH >> 8) & 0xff, Lcd_LCDH & 0xff);	
	W_REG(0xb5,(Lcd_LCDV >> 8) & 0xff, Lcd_LCDV & 0xff);
	
	
	hs_settime(Dsi_mbps);
	
	Write_SSPI_REG(0xB6, 0x0D0|(vido_mode<<2)|0x03);	//non burst sync event, 24bpp
	
	if(mode)	Write_SSPI_REG(0xB7, 0x030B);
	else 	Write_SSPI_REG(0xB7, 0x0301);
}
void SSD_MODE(u8 vido_mode,u8 mode)
{
		
	Write_SSPI_REG(0xB1, (panel_info.vsync<<8)|panel_info.hsync);			//VSA  HAS
	Write_SSPI_REG(0xB2, (panel_info.vbp<<8)|panel_info.hbp);			//VBP+10 HBP						
	Write_SSPI_REG(0xB3, (panel_info.vfp<<8)|(panel_info.hfp));			//VFP HFP								
	Write_SSPI_REG(0xB4, panel_info.width);					//						        	
	Write_SSPI_REG(0xB5, panel_info.height);				//
	hs_settime(panel_info.dsi_mbps);
	
	Write_SSPI_REG(0xB6, 0x0D0|(vido_mode<<2)|0x03);	//non burst sync event, 24bpp
	
	if(mode)	Write_SSPI_REG(0xB7, 0x030B);
	else 	Write_SSPI_REG(0xB7, 0x0301);
}

#endif








