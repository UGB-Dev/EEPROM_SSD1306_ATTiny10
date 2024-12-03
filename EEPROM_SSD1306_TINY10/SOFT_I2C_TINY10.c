
/*
	SOFT_I2C_TINY10.c
	
*/

#include "SOFT_I2C_TINY10.h"

///////////////////////////////////////////////////////////////////
///////////////////  CONFIGURACION OVERCLOCK  /////////////////////

void Set_FCPU_8MHz(){
	sei(); // habilitacion de interrupciones globales
	CCP = 0xD8; // habilita la manipulacion del registro CLKPSR
	CLKPSR = 0x00; // prescalador a 1 (8MHz/1 = 8MHz)
	OSCCAL = 0xFF; // calibracion de oscilador RC al maximo (aprox 13 MHz)
	OCR0A = CLK_I2C; // registro OCR0A = 134 
}

///////////////////////////////////////////////////////////////////
/////////////  CONFIGURACION DEL TIMER MODO CTC  //////////////////

void config_PWM_COMPA(){
	TCCR0B = 0x09; // modo CTC sin prescalador
	TIMSK0 = 0x02; // habilita la interrupcion por comparacion A
}


void config_PWM_COMPB(){
	TCCR0B = 0x09; // modo CTC sin prescalador
	TIMSK0 = 0x04; // habilita la interrupcion por comparacion B
}

void reset_PWM_(){
	TCCR0B = TIMSK0  = 0;
}

///////////////////////////////////////////////////////////////////
/////////////  CONDICIONES DE INICIO Y FIN DE TRAMA  //////////////

void inicio_Trama(){
	SDA_ON;		// PB1(SDA) a "1" logico
	_delay_us(1.25);
	SCL_ON;		// PB2(SCL) a "1" logico
	_delay_us(1.25);
	SDA_OFF;	// PB1(SDA) a "0" logico
	_delay_us(5);
	SCL_OFF;	// PB2(SCL) a "0" logico
}

void fin_Trama(){
	SDA_OFF;	// PB1(SDA) a "0" logico
	SCL_ON;		// PB2(SCL) a "1" logico
	_delay_us(5);
	SDA_ON;		// PB1(SDA) a "1" logico
	_delay_us(2.5);
}

///////////////////////////////////////////////////////////////////
////////////////   ENVIO Y RECEPCION DE DATOS  ////////////////////

void Enviar_Dato(uint8_t Byte){
	config_PWM_COMPA(); // configura el modo CTC por comparacion A
	Byte_copia=Byte; // realiza una copia del dato
	Byte_contador=1; // se inicializa el contador
	while(Byte_contador); // mantenemos hasta recibir el ACK
	reset_PWM_(); // deshabilita el modo CTC
}

uint8_t leer(bool ACK){
	config_PWM_COMPB(); // configura el modo CTC por comparacion B
	RECONOCIMIENTO = ACK; // se inicializa para determinar un ACK(1) o NACK(0)
	Byte_copia = 0; // se inicializa Byte_copia 
	Byte_contador = 1; // se inicializa el contador
	SDA_ON; // pin PB1(SDA) como entrada
	while(Byte_contador); // mantenemos hasta enviar el NACK
	reset_PWM_(); // deshabilita el modo CTC
	return Byte_copia; // retorna el valor de Byte_copia
}

///////////////////////////////////////////////////////////////////
////////////////////  RUTINAS DE INTERRUPCION  ////////////////////

ISR(TIM0_COMPA_vect){ // rutina para envio de datos
	switch(Byte_contador){ 
		case 1 ... 8: // envia el valor logico de cada bit
			if (Byte_copia & 0x80){ // si el valor del bit presente es 1
				SDA_ON;		// PB1(SDA) a "1" logico
				_delay_us(1.5);
				SCL_ON;		// PB2(SCL) a "1" logico
				_delay_us(5);
				SCL_OFF;	// PB2(SCL) a "0" logico
			}
			else{ // de lo contrario (bit presente es 0)
				SDA_OFF;	// PB1(SDA) a "0" logico
				_delay_us(1.5);
				SCL_ON;		// PB2(SCL) a "1" logico
				_delay_us(5);
				SCL_OFF;	// PB2(SCL) a "0" logico
			}
			
			Byte_copia <<= 1; // recorre el byte actual hacia la izquierda una posicion
			Byte_contador++; // incrementa Byte_contador
			break;
	
		case 9: // recepcion del "ACK"
			SDA_ON; // pin PB1(SDA) como entrada
			while ( PINB & (1<<PINB1)); // mantenemos hasta recibir el ACK en PB1(SDA) 
			_delay_us(1.5);
			SCL_ON;		// PB2(SCL) a "1" logico
			Byte_contador = 0;	// se asigna 0 al contador para salir de la funcion enviar
			_delay_us(5);
			SCL_OFF;	// PB2(SCL) a "0" logico
			SDA_OFF;	// PB1(SDA) a "0" logico
			break;
	}
}


ISR(TIM0_COMPB_vect){ // rutina para recepcion de datos
	switch(Byte_contador){
		case 1 ... 8: // registra el valor logico para cada bit
			_delay_us(1);
			SCL_ON;		// PB2(SCL) a "1" logico
			if (PINB & (1<<PINB1)){ // si en PB1(SDA) es "1" logico
				Byte_copia |= (1 << (8-Byte_contador)); // almacena el bit desde MSB a LSB
			}
			_delay_us(8);
			SCL_OFF;	// PB2(SCL) a "0" logico
			Byte_contador++; // incrementa Byte_contador
			break;
		
		case 9:
			if (RECONOCIMIENTO == 1){ // envia ACK 
				SDA_OFF; 
			}
			else{ // envia NACK 
				SDA_ON; 
			}
			_delay_us(1);
			SCL_ON;		// PB2(SCL) a "1" logico
			_delay_us(8);
			Byte_contador = 0; // se asigna 0 al contador para salir de la funcion enviar
			SCL_OFF;	// PB2(SCL) a "0" logico
			break;
	}
}






