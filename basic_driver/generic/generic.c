#include "TM4C123.h"                    // Device header
#include"generic\generic.h"
#include"led\led.h"
#include"uart\uart.h"

GPIOA_Type* gen_get_port_ptr(port_num port)
{
	GPIOA_Type *ptr_port;
	switch(port)
	{
		case PORTA:
		{
			ptr_port = GPIOA_AHB;
		}
		break;
		case PORTB:
		{
			ptr_port = GPIOB_AHB;
		}
		break;
		case PORTC:
		{
			ptr_port = GPIOC_AHB;
		}
		break;
		case PORTD:
		{
			ptr_port = GPIOD_AHB;
		}
		break;
		case PORTE:
		{
			ptr_port = GPIOE_AHB;
		}
		break;
		case PORTF:
		{
			ptr_port = GPIOF_AHB;
		}
		break;
		default:
		{
		}
		break;
	}
	return ptr_port;
}
void gen_delay(const uint32_t num)
{
	uint32_t count =0;
	for( count = 0; count < num; count++ )
	{
	}
}

void gen_set_gpio(port_num port,pin_num pin,dir_type type)
{
	GPIOA_Type *ptr_port;
	ptr_port = gen_get_port_ptr(port);
	/*enable port clock*/
	SYSCTL->RCGCGPIO |= SET << port;
	/*unlock port for writing of AFSEL,DEN,DR2R*/
	ptr_port->LOCK = GPIO_UNLOCK;
	/*set commit control register*/
	ptr_port->CR |= SET << pin;
	ptr_port->DIR |= OUT << pin;
	if(type == IN)
	{
		ptr_port->DIR &= ~(SET << pin); 
	}
	else if(type == OUT)
	{
		ptr_port->DIR |= SET << pin;
	}
	else
	{
	}
	ptr_port->AFSEL |= GPIO_FUN << pin;
	ptr_port->ODR |= ORD_DN << pin;
	ptr_port->DEN |= DEN_EN << pin;
	ptr_port->DR2R |= SET << pin;
	ptr_port->PUR |= SET << pin;
	ptr_port->LOCK = GPIO_LOCK;				
}

pin_status gen_get_gpio(port_num port,pin_num pin)
{
	GPIOA_Type *ptr_port;
	ptr_port = gen_get_port_ptr(port);
	return((ptr_port->DATA &(SET << pin) ? SET : CLEAR));
}

void gen_enable_int(port_num port,pin_num pin,int_type type)
{
	GPIOA_Type *ptr_port;
	switch(port)
	{
		case PORTA:
		{
			ptr_port = GPIOA_AHB;
		}
		break;
		case PORTB:
		{
			ptr_port = GPIOB_AHB;
		}
		break;
		case PORTC:
		{
			ptr_port = GPIOC_AHB;
		}
		break;
		case PORTD:
		{
			ptr_port = GPIOD_AHB;
		}
		break;
		case PORTE:
		{
			ptr_port = GPIOE_AHB;
		}
		break;
		case PORTF:
		{
			ptr_port = GPIOF_AHB;
		}
		break;
		default:
		{
		}
		break;
	}
	if(type == LEVEL)
	{
		ptr_port->IS |= SET << pin; 
	}
	else if(type == BOTH)
	{
		ptr_port->IBE |= SET << pin;
	}
	else if(type == RISING)
	{
		ptr_port->IEV |= SET << pin;
	}
	else if(type == FALLING)
	{
		ptr_port->IEV &= ~(SET << pin);
	}
	else
	{
		//do nothing
	}
	
	/*clear any pending interrupt*/
	ptr_port->ICR |= SET << pin;
	/*enable interrupt*/
	ptr_port->IM |= SET << pin;		
}
void gen_gpiof_handler(pin_num pin)
{
	unsigned char name1[20] = "Anant kumar Singh";
	static uint8_t temp =0;
	uart_tx_data(USART5,name1,18);
	if(pin == PIN0)
	{
		if(temp ==0 )
		{
			temp =1;
			led_on(RED);
		}
		else
		{
			temp =0;
			led_off(RED);
		}
	}
}
