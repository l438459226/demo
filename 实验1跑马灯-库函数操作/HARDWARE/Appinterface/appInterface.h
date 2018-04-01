#ifndef __APPINTERFACE_H
#define __APPINTERFACE_H
#include "sys.h"
#include "stdio.h"

#define 		INTERFACE_ADDR				0x20000550

#define INTERFACE_FUN(funname)	\
inface_##funname funname = NULL	\

#define EXTER_INTERFACE_FUN(funname)	\
extern inface_##funname funname	\

//int printf(const char * __restrict /*format*/, ...)
typedef  u32 (*Interface)();

typedef  int (*inface_printff)(const char*__restrict, ...);

typedef  void (*inface_Set_Voutp)(float voltage);
typedef  void (*inface_delay_ms)(u16 nms);
typedef void (*inface_delay_us)(u32 nus);
typedef void (*inface_Delay_ms)(u16 nms);
typedef void (*inface_Delay_us)(u32 val);     
typedef void (*inface_mymemset)(void *s,u8 c,u32 count);	 
typedef void (*inface_mymemcpy)(void *des,void *src,u32 n);
typedef void (*inface_mem_init)(u8 memx);			 
typedef u32 (*inface_mem_malloc)(u8 memx,u32 size);		 
typedef u8  (*inface_mem_free)(u8 memx,u32 offset);		 
typedef u8  (*inface_mem_perused)(u8 memx);				 
typedef void (*inface_myfree)(u8 memx,void *ptr);  			
//typedef void *(*inface_mymalloc)(u8 memx,u32 size);	
//typedef void *(*inface_myrealloc)(u8 memx,void *ptr,u32 size);
typedef void (*inface_IIC_Init)(void);              		 
typedef int  (*inface_IIC_Start)(void);			
typedef void (*inface_IIC_Stop)(void);	  		
typedef int  (*inface_IIC_Send_Byte)(u8 txd);		
typedef u8   (*inface_IIC_Read_Byte)(void);			
typedef int  (*inface_IIC_Wait_Ack)(void); 		
typedef void (*inface_IIC_Ack)(void);				
typedef void (*inface_IIC_NAck)(void);			
typedef void (*inface_Set_Voutp)(float voltage);
typedef void (*inface_Set_Voutn)(float voltage);
typedef void (*inface_Voutp_Upfirst)(void);
typedef void (*inface_LM36923_Init)(u16 val);



EXTER_INTERFACE_FUN(printff);
EXTER_INTERFACE_FUN(delay_ms);
EXTER_INTERFACE_FUN(delay_us);
EXTER_INTERFACE_FUN(Delay_ms);
EXTER_INTERFACE_FUN(Delay_us);
EXTER_INTERFACE_FUN(mymemset);
EXTER_INTERFACE_FUN(mymemcpy);
EXTER_INTERFACE_FUN(mem_init);
EXTER_INTERFACE_FUN(mem_malloc);
EXTER_INTERFACE_FUN(mem_free);
EXTER_INTERFACE_FUN(mem_perused);
EXTER_INTERFACE_FUN(myfree);
//EXTER_INTERFACE_FUN(mymalloc);
//EXTER_INTERFACE_FUN(myrealloc);
EXTER_INTERFACE_FUN(IIC_Init);
EXTER_INTERFACE_FUN(IIC_Start);
EXTER_INTERFACE_FUN(IIC_Stop);
EXTER_INTERFACE_FUN(IIC_Send_Byte);
EXTER_INTERFACE_FUN(IIC_Read_Byte);
EXTER_INTERFACE_FUN(IIC_Wait_Ack);
EXTER_INTERFACE_FUN(IIC_Ack);
EXTER_INTERFACE_FUN(IIC_NAck);
EXTER_INTERFACE_FUN(Set_Voutp);
EXTER_INTERFACE_FUN(Set_Voutn);
EXTER_INTERFACE_FUN(Voutp_Upfirst);
EXTER_INTERFACE_FUN(LM36923_Init);


void load_interface(void);




#endif
