#include "ssd2828.h"
#include "usart.h"
#include "spi.h"	
#include "Uart.h"
#include "user.h"


unsigned int Lcd_DCLK = 135;	  //DCLKƵ������ ��λΪMHz ���ֵ150MH����
unsigned int Lcd_LCDH = 1080;	  //�ֱ���.��
unsigned int Lcd_LCDV = 1920;	  //�ֱ���.��
unsigned int Lcd_HBPD = 100;
unsigned int Lcd_HFPD = 100;
unsigned int Lcd_HSPW = 10;
unsigned int Lcd_VBPD = 7;
unsigned int Lcd_VFPD = 9;
unsigned int Lcd_VSPW = 2;
unsigned int Lcd_DCLK_EDGE = 1;		//lcd��������ʱ��DCLK����	 ��������ĺ궨������ֵ
unsigned int Lcd_HSYNC_POLARITY = 0;  //HSYNC���弫��			  	 ��������ĺ궨������ֵ
unsigned int Lcd_VSYNC_POLARITY = 0;  //VSYNC���弫��			  	 ��������ĺ궨������ֵ
unsigned int Lcd_DE_POLARITY = 0;	 //DE�ź���Ч��ƽ			 ��������ĺ궨������ֵ

unsigned int Lcd_MODE = 0X00;  //�ӿڷ�ʽ MIPI_8LANE �� MIPI_4LANE	 ��������ĺ궨������ֵ
                               //1,2,3,4LANE�Ķ���ֵΪMIPI_4LANE
															 
#define MIPI_SINGLE 0X00	  //����1,2,3,4LANE�Ľӿ�
#define MIPI_DOUBLE 0X01      //��8LANE	MIPI�ӿ�															 
						

/*---------------------------LP or HS or Video------------------------------*/
#define LP 0
#define HS 1
#define VD 2
unsigned int mode = 0; 


/*----------------------------------------------------------------------------*/
void SSD2828GPIOConfig(void)	//PA3-SPI_CS    PA5-SPI_CLK   PA6-MISO   PA7-MOSI
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); //??PORTA,?AFIO??
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15|GPIO_Pin_0;	   ///PORTC 3 5 6 7 ??????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //GPIOA	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	   ///PORTC 3 5 6 7 ??????
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //GPIOA	
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_14|GPIO_Pin_1;//PA6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //???????
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//???GPIOA6
	

	SSD_CS = 1;
	SPI_SDI = 1;
	SPI_SCLK = 1;
	SSD_RESET = 1;
	
}


void SSD2828GPIOFree(void)	//PA3-SPI_CS    PA5-SPI_CLK   PA6-MISO   PA7-MOSI
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); //ʹ��PORTA,��AFIOʱ��
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_6;	   ///PORTA 3 5 6 7 �����������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 				//GPIOA	

	SSD_CS =		 1;
	SPI_SDI = 	 1;
	SPI_SCLK =	 1;
	SSD_RESET =  0;
	
}

void SPI_SDIN(u8 bit)   	//0 or 1 ���͸�оƬ
{
	
  SPI_SDI = bit;//����ʱ�ӿ�ʼ���ݴ���
	SPI_SDI = bit;
	
	if(RDAD_SPI_SDI != bit)
		printf("SPI_SDI error\r\n");
}

void SPI_SCK(u8 bit)   	//0 or 1 ���͸�оƬ
{
	
  SPI_SCLK = bit;//����ʱ�ӿ�ʼ���ݴ���
	SPI_SCLK = bit;
	
	if(RDAD_SPI_SCLK != bit)
		printf("RDAD_SPI_SCLK error\r\n");
}
#if 0
void W_byte(unsigned char cmd)
{   
		u8 i;
	
		SPI_SDI = 1;
		SPI_SCLK = 1;
    for (i=0;i<8;i++)
    {
			delay_us(3); 
			SPI_SCLK = 0;
			if((cmd & 0x80) != 0)	SPI_SDI = 1;
				else  SPI_SDI = 0;
			delay_us(3); 
			SPI_SCLK = 1;
			cmd = cmd<<1;
    }  
		SPI_SDI = 1;
}
#else
void W_byte(unsigned char cmd)
{   
		u8 i;
	
		SPI_SDIN(1);
		SPI_SCK(1);
    for (i=0;i<8;i++)
    {
			delay_us(1); 
			SPI_SCK(0);
			if((cmd & 0x80) != 0)	SPI_SDIN(1);
				else  SPI_SDIN(0);
			delay_us(1); 
			SPI_SCK(1);
			cmd = cmd<<1;
    }
		SPI_SDIN(1);
}
#endif

u8 SSD2828Read(void)
{
	u8 i;
	u8 tmp = 0;
	
	SPI_SCLK = 1;
  for(i = 0; i < 8; i++)
	{
		tmp <<= 1;
		SPI_SCLK = 0;
    SPI_SCLK = 1;
		delay_us(1); 
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
		if(SPI_SDO) tmp |= 0x01;
	}
	SPI_SCLK = 1;
	return tmp;
}

void ssd_wparme(u8 cmd,u8 dat1,u8 dat2)//cmd=0x70д�Ĵ���     cmd=0x72д����ָ��
{
	SSD_CS = 0;
	W_byte(cmd);	//д�Ĵ���  W_REG
	W_byte(dat1);
	W_byte(dat2);
	SSD_CS = 1;
	delay_us(10);
}

void ssd_wuparme(u8 cmd,u16 parmer)		//cmd=0x70д�Ĵ���     cmd=0x72д����ָ��
{
	SSD_CS = 0;
	W_byte(cmd);	//д�Ĵ���  W_REG
	W_byte(parmer>>8);
	W_byte(parmer);
	SSD_CS = 1;
	//delay_us(10);
}

void ssd_wdata(u8 reg,u16 parmer)		//
{
	
	SSD_CS = 0;
	//delay_us(3);
	W_byte(0x70);	//д�Ĵ���  W_REG
	W_byte(0x00);
	W_byte(reg);
	//delay_us(3);
	SSD_CS = 1;
	
	//delay_us(3);
	
	SSD_CS = 0;
	//delay_us(3);
	W_byte(0x72);	//д����ָ��
	W_byte(parmer>>8);
	W_byte(parmer);
	//delay_us(3);
	SSD_CS = 1;
	//delay_us(1);
}



void W_REG(u8 reg,u8 dat_h,u8 dat_l)
{

	SSD_CS = 0;
	W_byte(0x70);	//д�Ĵ���  W_REG
	W_byte(0x00);
	W_byte(reg);
	SSD_CS = 1;
	//delay_us(10);
	
	SSD_CS = 0;
	W_byte(0x72);	//д����ָ��
	W_byte(dat_h);
	W_byte(dat_l);
	SSD_CS = 1;
	
	//delay_us(10);
}

void Write_SSPI_REG(u8 reg,u16 index)
{
		u8 dat_h;
		u8 dat_l;
		dat_h = index>>8;
		dat_l = index;
		W_REG(reg,dat_h,dat_l);
		delay_us(100);
}



u16 ssd_rdata(u8 reg)
{
	u16 parmer;
	
	SSD_CS = 0;		//GPIO_ResetBits(GPIOB,GPIO_Pin_12);	//SSD_CS = 0;
	W_byte(0x70);	//д�Ĵ���
	W_byte(0x00);
	W_byte(reg);
	SSD_CS = 1;		//GPIO_SetBits(GPIOB,GPIO_Pin_12);	//SSD_CS = 1;
	
	delay_us(1);
	
	SSD_CS = 0;		//GPIO_ResetBits(GPIOB,GPIO_Pin_12);	//SSD_CS = 0;
	W_byte(0x73);	//������ָ��
	parmer = SSD2828Read();
	parmer = (parmer<<8)|SSD2828Read();
	SSD_CS = 1; 	//GPIO_SetBits(GPIOB,GPIO_Pin_12);	//SSD_CS = 1;

	return parmer;
}

//DCS �̰�д �� 
//DT = 0x05, 0x15
//n - ���ݸ����� 
void DCS_SP(unsigned char n)
{
	if(mode == LP)
	{	
		ssd_wdata(0x00b7,0x0250);	  //EOT Packet Enable,ECC CRC Check Enable, DCS, Short packer, LP
	}
	else if(mode == HS)
	{
		ssd_wdata(0x00b7, (0x50&0XEF)|0x0203); //EOT Packet Enable,ECC CRC Check Enable, DCS, Short packer, HS
	} 
	else if(mode == VD)
	{
		ssd_wdata(0x00b7, (0x50&0XEF)|0x030B); //EOT Packet Enable,ECC CRC Check Disable, DCS, Short packer, HS Video
	}
	delay_us(10);
	ssd_wdata(0xbc,n);
	ssd_wdata(0xbd,0x0000);
	ssd_wdata(0xbe,n);
}


void DCS_LP(unsigned long n)
{
	if(mode == LP)
	{
		ssd_wdata(0x00b7,0x0650);  //EOT Packet Enable,ECC CRC Check Enable, DCS Long Write, LP
	}
	else if(mode == HS)
	{
		ssd_wdata(0x00b7,(0x0650&0XEF)|0X03);  //EOT Packet Enable,ECC CRC Check Enable, DCS Long Write, HS
	}
	else if(mode == VD)
	{
		ssd_wdata(0x00b7,(0x0750&0XEF)|0X0B);  //EOT Packet Enable,ECC CRC Check Disable, DCS Long Write, HS Video
	}

	delay_us(10);
	ssd_wdata(0xbc,n);
	ssd_wdata(0xbd,(n>>16));
	ssd_wdata(0xbe,0x0fff);
}


void GP_SP(unsigned char n)
{
	if(mode == LP)
	{
		ssd_wdata(0x00b7,0x0210); //EOT Packet Enable,ECC CRC Check Enable, Generic Short Write, LP
	}
	else if(mode == HS)
	{
		ssd_wdata(0x00b7,(0x0210&0xEF)|0X03);  //EOT Packet Enable,ECC CRC Check Enable, Generic Short Write, HS
	}
	else if(mode == VD)
	{
		ssd_wdata(0x00b7,(0x0310&0xEF)|0X0B);  //EOT Packet Enable,ECC CRC Check Disable, Generic Short Write, HS Video
	}

	delay_us(10);
	ssd_wdata(0xbc,n);
	ssd_wdata(0xbd,0x0000);
	ssd_wdata(0xbe,n);
}


void GP_LP(unsigned long n)
{
	
  if(mode == LP)
	{	
		ssd_wdata(0xb7,0x0610); //EOT Packet Enable,ECC CRC Check Enable, Generic Long Write, LP; 
	}
	else if(mode == HS)
	{
		ssd_wdata(0xb7,0x0610&(0XEF|0X03)); //EOT Packet Enable,ECC CRC Check Enable, Generic Long Write, HS;
	}
	else if(mode == VD)
	{
		ssd_wdata(0xb7,0x0710&(0XEF|0X0B));//EOT Packet Enable,ECC CRC Check Disable, Generic Long Write, HS Video
	}
	//ssd_wdata(0xb7,0x0550);
	//delay_us(10);
	ssd_wdata(0xbc,n);
	//ssd_wdata(0xbd,n>>16);
	//ssd_wdata(0xbe,0x0fff);
}

u8 DCS_Short_Read_NP(u16 cmd, u8 cnt, u8 *val)
{
	u16 state;
	u8 i;
	u8 timeout_cnt=0;
	u8 hdat;
	u8 datl;
	do
	{
		ssd_wdata(0xb7,0x03c2);					//LP
		//ssd_wdata(0xb7,(0x03c2&0xEF)|0x03);		//HS
		//ssd_wdata(0xb7,(0x03c2&0xEF)|0x0B);		//VD	
		
		
		ssd_wdata(0xc1,cnt);		//Maximum Return Size
		
		ssd_wdata(0xc0,0x0001);		//ȡ��SSD2828�Ĳ�������
		ssd_wdata(0xBC,0x0001);
		ssd_wdata(0xBF,cmd);	   //��Ҫ�x�ĵ�ַ�l�ͳ�ȥ

		state = ssd_rdata(0xc6);		//�� ssd2828 ��״̬�Ĵ���
		if(state & 0x01)
				break;    //�x�ɹ� ����ѭ�h
		else 
			if(++timeout_cnt > 10){
					printf("MIPI_READ_FAIL -1 \r\n");
					return MIPI_READ_FAIL;		//���r �xʧ��
			}
	}while(1);
	
	ssd_wuparme(0x70,0x00FF);			   //�x2828��0XFF�Ĵ�����ʵ���ϲ��Ǹ��Ĵ�����ֻ�Ǽ����LCM���������ݻ����0XFF
	for(i = 0; i < cnt;i++)
	{
		SSD_CS = 0;
		W_byte(0x73);	//������ָ��
		
	  hdat = SSD2828Read();
		if(hdat == 0xff)	continue;
		datl = SSD2828Read();
		*val++ = datl;
		*val++ = hdat;
		SSD_CS = 1;
	}
	ssd_wdata(0xb7,0x0159);
	return MIPI_READ_SUCCEED;
}

unsigned int GP_R(uint8_t adr, uint16_t l, uint8_t *p)
{
	uint16_t state;
	u8 hdat,datl;
	unsigned int i;
	unsigned int timeout_cnt=0;
	do
	{
		ssd_wdata(0x00b7,0x0382);		//LP generic read
		
		ssd_wdata(0x00bb,0x0008);			//PL clock
		ssd_wdata(0x00c1,l);		//Maximum Return Size
		ssd_wdata(0x00c0,0x0001);		//ȡ��SSD2828�Ĳ�������
		ssd_wdata(0x00BC,0x0001);		 // *�������� 
		ssd_wdata(0x00BF, adr);	   //��Ҫ�x�ĵ�ַ�l�ͳ�ȥ
		//delay_ms(10);					   //�x��Ҫһ���ʱ��
		state = ssd_rdata(0xc6);		//�� ssd2828 ��״̬�Ĵ���

		if(state & 0x01)	break;     //�x�ɹ� ����ѭ�h
		else if(++timeout_cnt > 10){return MIPI_READ_FAIL;}		//���r �xʧ��
	}while(1);	//ssd2828��״̬���� ��ȫ������

	ssd_wuparme(0x70,0x00FF);				   //�x2828��0XFF�Ĵ�����ʵ���ϲ��Ǹ��Ĵ�����ֻ�Ǽ����LCM���������ݻ����0XFF
	for(i = 0; i < l;i++)
	{
		SSD_CS = 0;
		W_byte(0x73);	//������ָ��
		
	  hdat = SSD2828Read();
		if(hdat == 0xff)	continue;
		datl = SSD2828Read();
		*p++ = datl;
		*p++ = hdat;
		SSD_CS = 1;
		delay_us(1);
		Write_SSPI_REG(0xB7, 0x0159);
	}
	Write_SSPI_REG(0xB7, 0x0159);
	return MIPI_READ_SUCCEED;
}


void DCS_Short_Write_1P(u8 Generic,u8 Parma)	
{
	DCS_SP(2);
	ssd_wdata(0xBF,(Parma<<8)|(Generic));
	
}
void DCS_Long_Write_2P(u8 Generic,u8 Parma1,u8 Parma2)
{
	DCS_SP(3);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,0x00,Parma2);
}
void DCS_Long_Write_3P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3)
{
	DCS_SP(4);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
}
void DCS_Long_Write_4P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4)
{
	DCS_SP(5);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
	ssd_wparme(0x72,0x00,Parma4);
}
void DCS_Long_Write_5P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5)
{
	DCS_SP(6);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
	ssd_wparme(0x72,Parma5,Parma4);
}
void DCS_Long_Write_6P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6)
{
	DCS_SP(7);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
	ssd_wparme(0x72,Parma5,Parma4);
	ssd_wparme(0x72,0x00,Parma6);
}
void DCS_Long_Write_7P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6,u8 Parma7)
{
	DCS_SP(8);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
	ssd_wparme(0x72,Parma5,Parma4);
	ssd_wparme(0x72,Parma7,Parma6);
}

void DCS_Long_Write_FIFO(u16 NUM,u16 *P)
{
	u16 i;
	
	DCS_LP(NUM);
	
	ssd_wdata(0xBF,((P[1]<<8) | P[0]));
	for(i=2;i<NUM;){
		if((i+1) == NUM)
			ssd_wparme(0x72,0x00,P[i]);
		else
			ssd_wparme(0x72,P[i+1],P[i]);
		i += 2;
	}
}


void DCS_Long_Write_8FIFO(u16 NUM,u8 *P)
{
	u16 i;
	
	DCS_LP(NUM);
	
	ssd_wdata(0xBF,((P[1]<<8)|P[0]));
	for(i=2;i<NUM;){
		if((i+1) == NUM)
			ssd_wparme(0x72,0x00,P[i]);
		else
			ssd_wparme(0x72,P[i+1],P[i]);
		i += 2;
	}
	//Write_SSPI_REG(0xB7, 0x0159);
}

void DCS_Long_Write(u16 NUM,u8 *P)//0xC1,0x04,0x40,0x00,0x00,0x26,0x15,0x19,0x0B  8
{//																	       1   2     3    4    5    6   7    8    
 	u16 i;
	
	DCS_LP(NUM+1);
	
	ssd_wdata(0xBF,((P[1]<<8)|P[0]));
	for(i=2;i<NUM;i+=2){//7   2 4 6 8 10
			ssd_wparme(0x72,P[i+1],P[i]);
			
	}
	if((i+1) == NUM)
			ssd_wparme(0x72,0x00,P[i]);	
	
	//Write_SSPI_REG(0xB7, 0x0159);
}

void DCS_Write(int reg,...)   
{   
    va_list   arg_ptr;     //����ɱ����ָ�� 
		int i,cnt;
		u8 regdata[512];
	
    va_start(arg_ptr,reg);   // iΪ���һ���̶�����������iΪ100
		regdata[0] = reg;
		cnt = va_arg(arg_ptr,int);
		printf( " 0x%x 0x%x",reg,cnt); 
		for(i=1;i<=cnt;i++)
		{
			regdata[i] = va_arg(arg_ptr,int);
			printf( " 0x%x",regdata[i]); 
		}
		printf("\r\n");
    va_end(arg_ptr);        //  ��ղ���ָ��
		
		DCS_Long_Write(cnt,regdata);
    return;   
}

void Generic_Short_Write_1P(u8 Generic,u8 Parma)	
{
	GP_LP(2);
	ssd_wdata(0xBF,(Parma<<8)|(Generic));
	printf("Generic_Short_Write_1P 0x%x  0x%x\r\n",Generic,Parma);
}
void Generic_Long_Write_2P(u8 Generic,u8 Parma1,u8 Parma2)
{
	GP_LP(3);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,0x00,Parma2);
}
void Generic_Long_Write_3P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3)
{
	GP_LP(4);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
}
void Generic_Long_Write_4P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4)
{
	GP_LP(5);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
	ssd_wparme(0x72,0x00,Parma4);
}
void Generic_Long_Write_5P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5)
{
	u16 par;
	
	par = ((u16)Parma1<<8)|(Generic);
	GP_LP(6);
	ssd_wdata(0xBF,par);//((u16)Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
	ssd_wparme(0x72,Parma5,Parma4);
		
// 	ssd_wdata(0xb7,0x0550); //EOT Packet Enable,ECC CRC Check Enable, Generic Long Write, LP; 
// 	ssd_wdata(0xbc,0x0006);//01DE

// 	par = ((u16)Parma1<<8)|(Generic);
// 	ssd_wdata(0xBF,par);//01DE
//  	ssd_wparme(0x72,Parma3,Parma2);
//  	ssd_wparme(0x72,Parma5,Parma4);
	Write_SSPI_REG(0xB7, 0x0159);
}
void Generic_Long_Write_6P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6)
{
	GP_LP(7);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
	ssd_wparme(0x72,Parma5,Parma4);
	ssd_wparme(0x72,0x00,Parma6);
}
void Generic_Long_Write_7P(u8 Generic,u8 Parma1,u8 Parma2,u8 Parma3,u8 Parma4,u8 Parma5,u8 Parma6,u8 Parma7)
{
	GP_LP(8);
	ssd_wdata(0xBF,(Parma1<<8)|(Generic));
	ssd_wparme(0x72,Parma3,Parma2);
	ssd_wparme(0x72,Parma5,Parma4);
	ssd_wparme(0x72,Parma7,Parma6);
}
void Generic_Long_Write_FIFO(u16 NUM,u16 *P)
{
	u16 i;
	
	GP_LP(NUM);
	
	ssd_wdata(0xBF,((P[1]<<8) | P[0]));
	for(i=2;i<NUM;){
		if((i+1) == NUM)
			ssd_wparme(0x72,0x00,P[i]);
		else
			ssd_wparme(0x72,P[i+1],P[i]);
		i += 2;
	}
}

void Generic_Long_Write_8FIFO(u16 NUM,u8 *P)
{
	u16 i;
	
	GP_LP(NUM);
	
	ssd_wdata(0xBF,((P[1]<<8) | P[0]));
	for(i=2;i<NUM;){
		if((i+1) == NUM)
			ssd_wparme(0x72,0x00,P[i]);
		else
			ssd_wparme(0x72,P[i+1],P[i]);
		i += 2;
	}
}

void  Generic_Write(int reg,...)   
{   
    va_list   arg_ptr;     //����ɱ����ָ�� 
		int i,cnt;
		u8 regdata[512];
	
    va_start(arg_ptr,reg);   // iΪ���һ���̶�����������iΪ100
		regdata[0] = reg;
		cnt = va_arg(arg_ptr,int);
		printf( " 0x%x 0x%x",reg,cnt); 
		for(i=1;i<=cnt;i++)
		{
			regdata[i] = va_arg(arg_ptr,int);
			printf( " 0x%x",regdata[i]); 
		}
		printf("\r\n");

    va_end(arg_ptr);        //  ��ղ���ָ��
		Generic_Long_Write_8FIFO(cnt-1,regdata);
    return;   
}

void LCD_INIT(void)			//
{
	
}

void SSD2828Init(void)
{
	

}







