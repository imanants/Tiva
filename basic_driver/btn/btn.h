#ifndef __BTN__H
#define __BTN__H
#include "TM4C123.h"                    // Device header
#include "generic\generic.h"

typedef enum
{
	BTN2,
	REV1,
	REV2,
	REV3,
	BTN1
}btn_no;

typedef enum
{
	PRESS,
	NOT_PRESS
}btn_status;



extern void btn_init(btn_no no,is_int mode,int_type type);
extern btn_status btn_get_status(btn_no no);
#endif
