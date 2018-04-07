#ifndef __GENERIC__H
#define __GENERIC__H
#include "TM4C123.h"                    // Device header
#include "stdint.h"
#define NULL 0u
#define NULL_PTR ((void*)0) 
typedef enum
{
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
}port_num;
typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
}pin_num;
typedef enum
{
	BIT0,
	BIT1,
	BIT2,
	BIT3,
	BIT4,
	BIT5,
	BIT6,
	BIT7,
}bit_num;
typedef enum
{
	CLEAR,
	SET,
}pin_status;

typedef enum
{
	SHIFT0BIT,
	SHIFT1BIT,
	SHIFT2BIT,
	SHIFT3BIT,
	SHIFT4BIT,
	SHIFT5BIT,
	SHIFT6BIT,
	SHIFT7BIT,
	SHIFT8BIT,
	SHIFT9BIT,
	SHIFT10BIT,
	SHIFT11BIT,
	SHIFT12BIT,
	SHIFT13BIT,
	SHIFT14BIT,
	SHIFT15BIT,
	SHIFT16BIT,
	SHIFT17BIT,
	SHIFT18BIT,
	SHIFT19BIT,
	SHIFT20BIT,
	SHIFT21BIT,
	SHIFT22BIT,
	SHIFT23BIT,
	SHIFT24BIT,
	SHIFT25BIT,
	SHIFT26BIT,
	SHIFT27BIT,
	SHIFT28BIT,
	SHIFT29BIT,
	SHIFT30BIT,
	SHIFT31BIT,
}shift;


typedef enum
{
	IN,
	OUT,
}dir_type;

typedef enum
{
	LEVEL,
	RISING,
	FALLING,
	BOTH,
	NO_INT
}int_type;

typedef enum
{
	NO_INT_MODE,
	INT_MODE,
}is_int;

typedef enum
{
	INT0 = 1u,
	INT1 = 2u,
	INT2 = 4u,
	INT3 = 8u,
	INT4 = 16u,
	INT5 = 32u,
	INT6 = 64u,
	INT7 = 128u,
}int_num;
typedef enum
{
	RESERVES,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN
}alfsl_value;

typedef enum
{
	E_OK,
	E_NOT_OK,
}std_return;
#define DW 0x03FCu

#define GPIO_UNLOCK  	0x4C4F434B
#define GPIO_LOCK  		0x00000 
#define GPIO_FUN 			0x00u
#define ALTR_FUN 			0x01u
#define ORD_DN 				0x00u
#define ORD_EN 				0x01u
#define DEN_DN 				0x00u
#define DEN_EN 				0x01u

extern void gen_delay(const uint32_t num);
extern void gen_set_gpio(port_num port,pin_num pin,dir_type type);
extern void gen_enable_int(port_num port,pin_num pin,int_type type);
extern void gen_gpiof_handler(pin_num pin);
extern pin_status gen_get_gpio(port_num port,pin_num);

GPIOA_Type* gen_get_port_ptr(port_num port);
#endif
