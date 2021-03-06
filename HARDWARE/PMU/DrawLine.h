/*********************************************************************************************************
* 文件名称: DrawLine.h
* 文件作者:相信未来
* 当前版本: 01.00.00
* 所属模块: CMS
* 创建日期: 2017年02月22日
* 文件摘要: 
* 注意事项: 
* 更改说明: 初始创建
**********************************************************************************************************/
#ifndef __DrawLine_H
#define __DrawLine_H



/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include "stm32f10x.h"




/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
#define	DRAW_LINE_TEST_EN		0x00		   //仅仅使能测试，如果需要具体功能，时机可能不对




/*********************************************************************************************************
*                                              结构体定义
*********************************************************************************************************/





/*********************************************************************************************************
*                                              API函数定义
*********************************************************************************************************/
u8 Draw_Line_Init(u32 fr_color,u32 bk_color,u8 pen_size,u8 h_line,u8 v_line);
u8 Is_Draw_Line_OK(void);
void Clear_Draw_Line(void);
void Draw_Line_Handle(void);
























#endif




