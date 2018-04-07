#ifndef __UART__H
#define __UART__H
#include "generic\generic.h"

/*
UART0 - connected to debugger port
PA0 - Rx
PA1 - Tx

UART1
PC4 - Rx
PC5- Tx

UART2
PD6 - Rx
PD7 - Tx

UART6 - USB
*/
typedef enum
{
	USART0,
	USART1,
	USART2,
	USART3,
	USART4,
	USART5,
	USART6,
	USART7,
	USART_MAX
}uart_num;
typedef struct
{
	pin_num rx;
	pin_num tx;
}uart_pin;
typedef enum
{
	NO,
	YES,
}uart_initialize;
typedef enum
{
	READY,
	BUSY,
}uart_state;

typedef struct 
{
	uint16_t length;
	unsigned char *ptr_buffer;
	uart_state state;
}uart_rx_tx_data;

typedef struct
{
	uart_num uart_num;
	uart_pin pin;
	port_num port;
	alfsl_value uart_alfsl_value;
	GPIOA_Type *ptr_port;
	UART0_Type *ptr_uart;
	uart_initialize is_uart_init;
	uart_rx_tx_data rx_data;
	uart_rx_tx_data tx_data;
	void (*rx_call_back)(void);
	void (*tx_call_back)(void);
}uart_details;


static void uart_set_uart_details(uart_details * const uart_details);
extern void uart_fill_uart_details(void);
extern void uart_init(uart_num num,uint32_t baud_rate);

extern std_return uart_rx_data(uart_num uart,unsigned char *ptr_buffer,uint16_t length,void(*ptr_callback)(void));
extern std_return uart_tx_data(uart_num uart,unsigned char *ptr_buffer,uint16_t length);
extern void UART_rx_handler(uart_num uart);
extern void UART_tx_handler(uart_num uart);
extern uint8_t uart1_read_data;
extern unsigned char uart1_write_data[255];

extern uart_details* const uart_array[USART_MAX];
#endif
