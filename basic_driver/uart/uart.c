#include "uart\uart.h"
uint8_t uart1_read_data;
unsigned char uart1_write_data[255];
uart_details uart_details_array[USART_MAX];
uart_details* const uart_array[USART_MAX] = {&uart_details_array[USART0],&uart_details_array[USART1],&uart_details_array[USART2],
&uart_details_array[USART3],&uart_details_array[USART4],&uart_details_array[USART5],&uart_details_array[USART6],&uart_details_array[USART7],};
void uart_fill_uart_details(void)
{
	int8_t num;
	for(num = 0; num < USART_MAX; num++)
	{
		uart_array[num]->uart_num = (uart_num )num;
		uart_array[num]->is_uart_init = NO;
		uart_array[num]->rx_call_back = NULL_PTR;
		uart_array[num]->tx_call_back = NULL_PTR;
		
		uart_set_uart_details(uart_array[num]);
	}
}
static void uart_set_uart_details(uart_details* const ptr_details)
{
	switch(ptr_details->uart_num)
	{
		case USART0:
		{
			ptr_details->ptr_uart = UART0;
			ptr_details->port= PORTA;
			ptr_details->pin.rx = PIN0;
			ptr_details->pin.tx = PIN1;
			ptr_details->uart_alfsl_value = ONE;
			break;
		}
		case USART1:
		{
			ptr_details->ptr_uart = UART1;
			//ptr_details->port= PORTC;
			//ptr_details->pin.rx = PIN4;
			//ptr_details->pin.tx = PIN5;
			//ptr_details->uart_alfsl_value = TWO;
			ptr_details->port= PORTB;
			ptr_details->pin.rx = PIN0;
			ptr_details->pin.tx = PIN1;
			ptr_details->uart_alfsl_value = ONE;
			break;
		}
		case USART2:
		{
			ptr_details->ptr_uart = UART2;
			ptr_details->port= PORTD;
			ptr_details->pin.rx = PIN6;
			ptr_details->pin.tx = PIN7;
			ptr_details->uart_alfsl_value = ONE;
			break;
		}
		case USART3:
		{
			ptr_details->ptr_uart = UART3;
			ptr_details->port= PORTC;
			ptr_details->pin.rx = PIN6;
			ptr_details->pin.tx = PIN7;
			ptr_details->uart_alfsl_value = ONE;
			break;
		}
		case USART4:
		{
			ptr_details->ptr_uart = UART4;
			ptr_details->port= PORTC;
			ptr_details->pin.rx = PIN4;
			ptr_details->pin.tx = PIN5;
			ptr_details->uart_alfsl_value = ONE;
			break;
		}
		case USART5:
		{
			ptr_details->ptr_uart = UART5;
			ptr_details->port= PORTE;
			ptr_details->pin.rx = PIN4;
			ptr_details->pin.tx = PIN5;
			ptr_details->uart_alfsl_value = ONE;
			break;
		}
		case USART6:
		{
			ptr_details->ptr_uart = UART6;
			ptr_details->port= PORTD;
			ptr_details->pin.rx = PIN4;
			ptr_details->pin.tx = PIN5;
			ptr_details->uart_alfsl_value = ONE;
			break;
		}
		case USART7:
		{
			ptr_details->ptr_uart = UART7;
			ptr_details->port= PORTE;
			ptr_details->pin.rx = PIN0;
			ptr_details->pin.tx = PIN1;
			ptr_details->uart_alfsl_value = ONE;
			break;
		}
		default:
			break;		
	}
	ptr_details->ptr_port = gen_get_port_ptr(ptr_details->port);
}

void uart_init(uart_num num,uint32_t baud_rate)
{
	uint8_t dummy_read = 0x31;
	/*enable clock for the uart*/
	SYSCTL->RCGCUART |= SET << num;
	/*enable clock for the port*/
	SYSCTL->RCGCGPIO |= (SET << uart_array[num]->port);
	/*AHB bus is enabled for port*/
	SYSCTL->GPIOHBCTL |= (SET << uart_array[num]->port);
	/*unlock port for writing of AFSEL,DEN,DR2R*/
	uart_array[num]->ptr_port->LOCK = GPIO_UNLOCK;
	/*set commit control register*/
	uart_array[num]->ptr_port->CR |= (SET << uart_array[num]->port);
	/*set alternate fucntion select*/ 
	uart_array[num]->ptr_port->AFSEL |= ( SET << uart_array[num]->pin.rx | SET << uart_array[num]->pin.tx);
	/*set digital enable*/
	uart_array[num]->ptr_port->DEN |= ( SET << uart_array[num]->pin.rx | SET << uart_array[num]->pin.tx);
	/*clear open drain*/
	uart_array[num]->ptr_port->ODR &= ~( SET << uart_array[num]->pin.rx | SET << uart_array[num]->pin.tx);
	/*set alternate function*/
	uart_array[num]->ptr_port->PCTL |= (uart_array[num]->uart_alfsl_value << ( uart_array[num]->pin.rx * 4u) | uart_array[num]->uart_alfsl_value << ( uart_array[num]->pin.tx * 4u));
	/*lock gpio */
	uart_array[num]->ptr_port->LOCK = GPIO_LOCK;
	/*disable uart before setting of baud rate*/
	uart_array[num]->ptr_uart->CTL &= ~(SET << BIT0);
	/*set baut rate 9600 bps*/
	uart_array[num]->ptr_uart->IBRD = 325u;
	uart_array[num]->ptr_uart->FBRD = 33u;
	/*write latch register*/
	/* 8 bit, no parity bits, one stop, FIFOs*/
	uart_array[num]->ptr_uart->LCRH = 0x60;
	dummy_read = uart_array[num]->ptr_uart->DR ;
	uart_array[num]->ptr_uart->DR  = dummy_read;
	/*enable uart transmit 8th bit and receive 9th bit lookup disable */
	uart_array[num]->ptr_uart->CTL |= (SET << SHIFT8BIT | SET << SHIFT9BIT | CLEAR << SHIFT7BIT);
	/*clear any rx pending interrupt*/
	uart_array[num]->ptr_uart->ICR &= ~(SET << SHIFT4BIT);
	/*enable uart rx interrupt*/
	uart_array[num]->ptr_uart->IM |= (SET << SHIFT4BIT);
	uart_array[num]->is_uart_init =  YES;
	uart_array[num]->rx_data.state =  READY;
	uart_array[num]->tx_data.state =  READY;
	/*enable uart*/
	uart_array[num]->ptr_uart->CTL |= (SET << BIT0);
		
}
std_return uart_rx_data(uart_num uart,unsigned char *ptr_buffer,uint16_t length,void(*ptr_callback)(void))
{
	std_return ret_val = E_NOT_OK;
	/*set user data buffer pointer*/
	uart_array[uart]->rx_data.ptr_buffer = ptr_buffer;
	/*set user data length*/
	uart_array[uart]->rx_data.length = length;
	/*set call back*/
	uart_array[uart]->rx_call_back = ptr_callback;
	/*set driver state to busy*/
	uart_array[uart]->rx_data.state = BUSY;
	/*enable recevier*/
	uart_array[uart]->ptr_uart->CTL |= (SET << SHIFT9BIT);
	/*enable rx interrupt*/	
	uart_array[uart]->ptr_uart->IM |= (SET << SHIFT4BIT);
	
	return ret_val; 
}

std_return uart_tx_data(uart_num uart,unsigned char *ptr_buffer,uint16_t length)
{
	std_return ret_val = E_NOT_OK;
	/*set data buffer which need to be transmit*/
	uart_array[uart]->tx_data.ptr_buffer = ptr_buffer;
	/*set user data length*/
	uart_array[uart]->tx_data.length = length;
	/*set uart state to busy*/
	uart_array[uart]->tx_data.state = BUSY;
	/*clear EOT*/
	uart_array[uart]->ptr_uart->CTL &= ~(SET << SHIFT4BIT);
	/*enable transmitter*/
	uart_array[uart]->ptr_uart->CTL |= (SET << SHIFT8BIT);
	/*enable tx interrupt*/	
	uart_array[uart]->ptr_uart->IM |= (SET << SHIFT5BIT);
	return ret_val;
}
void UART_tx_handler(uart_num uart)
{
	
	if(!(uart_array[uart]->ptr_uart->CTL & (SET << SHIFT4BIT)))
	{
		  (uart_array[uart]->tx_data.length)--;
			/*write data in uart data register*/
			uart_array[uart]->ptr_uart->DR =*(uart_array[uart]->tx_data.ptr_buffer++); 
			/*check if no requested bytes are trasmit*/
			if((uart_array[uart]->tx_data.length) == 0)
			{
					uart_array[uart]->ptr_uart->CTL |= (SET << SHIFT4BIT);
			}
	}
	else
	{
		/*check if callback funtion is configured*/
		uart_array[uart]->ptr_uart->CTL &= ~(SET << SHIFT4BIT);
		/*disable uart interrupt*/
		uart_array[uart]->ptr_uart->IM &= ~(SET << SHIFT5BIT);
		/*disable transmitter*/
		uart_array[uart]->ptr_uart->CTL &= ~(SET << SHIFT8BIT);
		/*set uart state to free*/
		uart_array[uart]->tx_data.state =  READY;
		/*check if callback function configured*/
		if(uart_array[uart]->tx_call_back)
		{
			/*call callback function*/
			uart_array[uart]->tx_call_back();
		}
		else
		{
			/*do nothing*/
		}
	}
}

void UART_rx_handler(uart_num uart)
{
	/*read data from rx register*/
	*(uart_array[uart]->rx_data.ptr_buffer++) = uart_array[uart]->ptr_uart->DR;
	/*check no. requested bytes are received*/
	if( (--uart_array[uart]->rx_data.length) ==  0u)
	{
		/*enable uart rx interrupt*/
		uart_array[uart]->ptr_uart->IM |= (SET << SHIFT4BIT);
		/*disable rx receiver*/
		uart_array[uart]->ptr_uart->CTL &= ~(SET << SHIFT9BIT);
		uart_array[uart]->rx_data.state = READY;
		/*check if callback funtion is configured*/
		if(uart_array[uart]->rx_call_back)
		{
			/*call callback function*/
			uart_array[uart]->rx_call_back();
		}
		else
		{
			/*do nothing*/
		}
		
	}
	else
	{
		/*do nothing*/
	}
	
}
