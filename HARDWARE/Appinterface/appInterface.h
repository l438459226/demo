#ifndef __APPINTERFACE_H
#define __APPINTERFACE_H
#include "sys.h"


#define 		INTERFACE_ADDR				0x20000550

extern void simple_va_fun(int i,...);
extern  u32 *interface[];

struct function{
  void *delay_ms;
	void *delay_us;
	void *printf;
	void *mymemset;
	void *mymemcpy;
};











#endif
