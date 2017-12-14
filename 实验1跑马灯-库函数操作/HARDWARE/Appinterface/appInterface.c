#include "appInterface.h"



Interface IAP_W25QXX_Init = NULL;
u32 *addr_interface = NULL;

INTERFACE_FUN(printff);
INTERFACE_FUN(delay_ms);
INTERFACE_FUN(delay_us);
INTERFACE_FUN(Delay_ms);
INTERFACE_FUN(Delay_us);
INTERFACE_FUN(mymemset);
INTERFACE_FUN(mymemcpy);
INTERFACE_FUN(mem_init);
INTERFACE_FUN(mem_malloc);
INTERFACE_FUN(mem_free);
INTERFACE_FUN(mem_perused);
INTERFACE_FUN(myfree);
//INTERFACE_FUN(mymalloc);
//INTERFACE_FUN(myrealloc);
INTERFACE_FUN(IIC_Init);
INTERFACE_FUN(IIC_Start);
INTERFACE_FUN(IIC_Stop);
INTERFACE_FUN(IIC_Send_Byte);
INTERFACE_FUN(IIC_Read_Byte);
INTERFACE_FUN(IIC_Wait_Ack);
INTERFACE_FUN(IIC_Ack);
INTERFACE_FUN(IIC_NAck);
INTERFACE_FUN(Set_Voutp);
INTERFACE_FUN(Set_Voutn);
INTERFACE_FUN(Voutp_Upfirst);
INTERFACE_FUN(LM36923_Init);

#define POINT_INTERFACE(fun,port)	\
fun = (inface_##fun)(((u32*)(*addr_interface))[port])\

void load_interface(void)
{
	addr_interface = (u32*)INTERFACE_ADDR;	//接口函数入口指针
	
	printf("\r\nInterface_addr=0x%x   0x%x \r\n",(u32)addr_interface,(u32)(*addr_interface));
	
	IAP_W25QXX_Init = (Interface)(((u32*)(*addr_interface))[2]);
	
	POINT_INTERFACE(delay_ms,0);
	POINT_INTERFACE(delay_us,1);
	POINT_INTERFACE(printff,2);
	POINT_INTERFACE(mymemset,3);
	POINT_INTERFACE(mymemcpy,4);
	POINT_INTERFACE(mem_malloc,5);
	POINT_INTERFACE(mem_free,6);
	POINT_INTERFACE(mem_perused,7);
	POINT_INTERFACE(IIC_Start,8);
	POINT_INTERFACE(IIC_Stop,9);
	POINT_INTERFACE(IIC_Send_Byte,10);
	POINT_INTERFACE(IIC_Read_Byte,11);
	POINT_INTERFACE(IIC_Wait_Ack,12);
	POINT_INTERFACE(IIC_Ack,13);
	POINT_INTERFACE(IIC_NAck,14);
	POINT_INTERFACE(Set_Voutp,15);
	POINT_INTERFACE(Set_Voutn,16);
	POINT_INTERFACE(Voutp_Upfirst,17);
	POINT_INTERFACE(LM36923_Init,18);
	
	Set_Voutp(4.45);
	IAP_W25QXX_Init("\r\n############Interface OK$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\r\n");
}










