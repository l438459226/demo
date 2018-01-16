
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
#include "CRC16.h"
#include "Protocol.h"


int UnPack(u8 *package,u8 len)
{
	static u8 i = 0,start = 0;
	u8 lenth;

	if(ReadUart(USART_PORT_COM2,&package[i],1)==0)	//??????
	{
			return -1;
	}
	
	if(start)	//
	{
	#if 0 
		if(package[i] == PACK_HEAD)	//
		{
			printf("package agan\r\n");
			Clear_buffer(package,len);
			
			start = 1;
			i = 0;	//
			return 0;
		}
	#endif
		
		if(package[i] == PACK_TAIL)
		{		
			lenth = i;
			start = 0;
			i = 0;
			return lenth;
		}
		else
		{
			i++;
			if(i==(len-1)) {start = 0;i = 0;mymemset(package,0,len);}	
			
		}
	}
	if((package[i] == PACK_HEAD)&&(i==0))
	{
		i = 0;
		start = 1;
		//printf("start \r\n");
		return 0 ;
	}
	return 0;
}
extern u8 bufer[];

struct packdata{
	u8 match;
	u8 len;
	u8 cmd;
	u8 *data;
	u32 crc;
};

//?1???	?2???	?3???	?4???	?4+len???	?5+len???	?6+len???	?7+len??
//PACK_HEAD	MACHINE_ADDR	len	CMD	*****	CRC??	CRC??	PACK_TAIL

//   0           1   2    2+len..  3+len    4+len 
//MACHINE_ADDR	len	 CMD	***** 	  CRC??	   CRC??

struct packdata *pack_data = NULL;

int pack_error(u8 *bufer,u8 len)
{
	pack_data = (struct packdata *)bufer;

	if(pack_data->match != MACHINE_ADDR){
		printf("match ID error\r\n");
		pack_data = NULL;
		return -1;
	}
	
	if(((pack_data->len)+5) != len){
		printf("pack data len error\r\n");
		pack_data = NULL;
		return -2;
	}
	
	pack_data->crc = (bufer[len-2]<<8) + bufer[len-1];
	pack_data->data = (u8*)(&pack_data->data);//

	if(pack_data->crc !=CRCc16(pack_data->data,pack_data->len)){
		printf("crc error:0x%x\r\n",CRCc16(pack_data->data,pack_data->len));
		pack_data = NULL;
		return -3;
	}
	printf("pack handle\r\n");
	return 1;
}



void protocol_pachk(void)
{	
	int len,i;
	
	len = UnPack(bufer,64);//接收包缓冲区  包的最大长度
	if(len>0){		//接收到一帧数据
		for(i=0;i<len;i++)
		{
				printf(" 0x%x",bufer[i]);
		}
		printf("\r\n");
		if(pack_error(bufer,len))	//包符合协议
		{
			switch(pack_data->cmd)
			{
				case CMD_POWER_SEQ:
					printf("CMD_POWER_SEQ\r\n");
				break;
				case CMD_INIT_STATUS:
					printf("CMD_INIT_STATUS\r\n");
				break;
				case CMD_VA_STATUS:
					printf("CMD_VA_STATUS\r\n");
				break;
			}
		}
	}
}















