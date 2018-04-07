#include"interrupt.h"
#include"generic.h"
#include"led.h"
#include"uart.h"
extern uint8_t uart1_read_data;
extern unsigned char uart1_write_data[255];
char *name1 = "anant kumar singh";
void interrupt_init(void)
{
	/*clear any pending interrupt for irq 30*/
	NVIC_ClearPendingIRQ(GPIOF_IRQn);
	/*set priority for irq 30 to lowest*/
	NVIC_SetPriority(GPIOF_IRQn,0x7u);
	/*enable irq 30*/
	NVIC_EnableIRQ(GPIOF_IRQn);
	
	/*clear any pending interrupt for irq -1*/
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	/*set priority for irq -1 to lowest*/
	NVIC_SetPriority(SysTick_IRQn,0x6u);
	/*enable irq -1*/
	NVIC_EnableIRQ(SysTick_IRQn);
	
	
	/*clear any pending interrupt for irq 6*/
	NVIC_ClearPendingIRQ(UART5_IRQn);
	/*set priority for irq 6 to lowest*/
	NVIC_SetPriority(UART5_IRQn,0x5u);
	/*enable irq 6*/
	NVIC_EnableIRQ(UART5_IRQn);
		
}

void GPIOF_Handler(void)
{
	int_num num = (int_num)((GPIOF_AHB->MIS) & 0xFF);
	pin_num pin;
	switch(num)
	{
		case INT0:
			pin = PIN0;
			break;
		case INT1:
			pin = PIN1;
			break;
		case INT2:
			pin = PIN2;
			break;
		case INT3:
			pin = PIN3;
			break;
		case INT4:
			pin = PIN4;
			break;
		case INT5:
			pin = PIN5;
			break;
		case INT6:
			pin = PIN6;
			break;
		case INT7:
			pin = PIN7;
			break;
		default:
			break;
	}
	GPIOF_AHB->ICR = SET << pin;
	gen_gpiof_handler(pin);
}
void SysTick_Handler(void)
{
		led_toggle(GREEN);
		//if(uart_array[USART5]->state == READY)
	  //uart_tx_data(USART5,name1,18);
}
void UART5_Handler(void)
{
	//uart1_read_data = ((UART5->DR) & 0xFF);
	//UART5->DR = uart1_read_data;
	/*rx interrupt*/
	if( uart_array[USART5]->ptr_uart->MIS & (SET << SHIFT4BIT))
	{
		/*rx handler*/
		UART_rx_handler(USART5);
		
	}
	/*tx interrupt*/
	else if( uart_array[USART5]->ptr_uart->MIS &(SET << SHIFT5BIT))
	{
		/*tx handler*/
		UART_tx_handler(USART5);
	}
	/*any other inerrupt*/
	else 
	{
		uart1_read_data = uart_array[USART5]->ptr_uart->MIS;
		//while(1);
	}
}


