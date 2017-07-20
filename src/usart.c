#include "../headers/usart.h"

ring_buffer_t transmit_buffer;
ring_buffer_t receive_buffer;

void USART0_init(uint16_t baud_rate) {
	SREG &= ~BIT(7);
	//Setting baud rate
	UBRR0 = baud_rate;

	//Enabling double speed mode
	UCSR0A |= (BIT(U2X0) & DSPEED_MODE);

	//Setting up frame format
	//Setting character size to 8
	UCSR0C |= BIT(UCSZ00) | BIT(UCSZ01);

	//Enabling transmitter and receiver
	UCSR0B |= BIT(TXEN0) | BIT (RXEN0) | BIT(RXCIE0);

	transmit_buffer.start = 0;
	transmit_buffer.end = 0;

	receive_buffer.start = 0;
	receive_buffer.end = 0;

	SREG |= BIT(7);
}

uint8_t USART0_print(const char * format, ...) {
	uint8_t result = 1;

	va_list arg_list; 

	char * result_str = (char*)(malloc(DEF_SIZE*sizeof(char)));
	uint8_t _strlen = 0;
	uint8_t i = 0;

	va_start(arg_list,format); //saving list of arguments
	vsnprintf(result_str,DEF_SIZE-1,format,arg_list); //generating final string
	
	//printf("Result string: %s",result_str);
	_strlen = strlen(result_str);

	for(i=0 ; i<_strlen ; i++) {
		if(!push((uint8_t)(result_str[i]),&transmit_buffer)) {
			result = 0;
			clean(&transmit_buffer);
			break;
		}
	}

	free(result_str);

	va_end(arg_list);

	UCSR0B |= BIT(UDRIE0); //turning on USART0 Data Register Empty Interrupt

	return result;
}

ISR(USART0_UDRE_vect) {
	UCSR0B &= ~BIT(UDRIE0);
	if(pop(&UDR0,&transmit_buffer)) {
		UCSR0B |= BIT(UDRIE0);
	}	
}

ISR(USART0_RX_vect) {
	push((UDR0-128),&receive_buffer);
}