#include"btn.h"
void btn_init(btn_no num,is_int mode,int_type type)
{
	gen_set_gpio(PORTF,(pin_num) num, IN);
	if(mode == INT_MODE)
	{
		gen_enable_int(PORTF,(pin_num) num ,type);
	}
	else
	{
		
	}
}

btn_status btn_get_status(btn_no num)
{
	return ((btn_status)gen_get_gpio(PORTF,(pin_num) num));
	
}
