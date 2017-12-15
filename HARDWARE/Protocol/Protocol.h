#ifndef __PROTOCOL_H
#define __PROTOCOL_H	

#include "sys.h"
#include "usart.h"

#define	MACHINE_ADDR 					0x01
#define	PACK_HEAD 					0x80		//包头
#define	PACK_TAIL 					0x88		//包尾

//下位机 --> 上位机
#define	CMD_UA_CAL_STATUS			0x02
#define	CMD_LOADBIN_STATUS			0x03
#define	CMD_VA_VAL					0x04
#define	CMD_SYS_ERR					0x05
#define	CMD_VERSION					0x40

#define	CMD_UA_CAL_STATUS_LEN		0x01
#define	CMD_LOADBIN_STATUS_LEN		0x01
#define	CMD_VA_VAL_LEN				0x04
#define	CMD_VERSION_LEN				0x02
#define	CMD_SYS_ERR_LEN				0x01

//上位机  --> 下位机
#define	CMD_POWER_SEQ				0x41
#define	CMD_INIT_STATUS				0x42
#define	CMD_VA_STATUS				0x43
//#define	CMD_SYS_STATUS				0x44

#define	CMD_POWER_SEQ_LEN			0x01
#define	CMD_INIT_STATUS_LEN			0x01
#define	CMD_VA_STATUS_LEN			0x01
//#define	CMD_SYS_STATUS_LEN			0x01


int UnPack(u8 *package,u8 len);

void protocol_pachk(void);












#endif
