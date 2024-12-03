
/*
	EEPROM_AT24C256.c
	
*/

#include "EEPROM_AT24C256.h"

///////////////////////////////////////////////////////////////////
////////  FUNCIONES PARA ESCRIBIR UNO O VARIOS REGISTROS  /////////

/*
void Escribir_Registro(uint16_t REGISTRO, uint8_t DATO){
	inicio_Trama();
	Enviar_Dato(ADDR_EEPROM_W); // se envia 0xA0
	Enviar_Dato(REGISTRO >> 8); // se envia el byte alto de la direccion del registro
	Enviar_Dato(REGISTRO & 0xFF); // se envia el byte bajo de la direccion del registro
	Enviar_Dato(DATO); // se envia el dato para ser guardado
	fin_Trama();
}
*/

///////////////////////////////////////////////////////////////////
///////  FUNCIONES DE RECEPCION DE UNO O VARIOS REGISTROS  ////////

void Leer_Registro(uint16_t REGISTRO){
	inicio_Trama();
	Enviar_Dato(ADDR_EEPROM_W); // se envia 0xA0
	Enviar_Dato(REGISTRO >> 8); // se envia el byte alto de la direccion del registro
	Enviar_Dato(REGISTRO & 0xFF); // se envia el byte bajo de la direccion del registro
	inicio_Trama();
	Enviar_Dato(ADDR_EEPROM_R); // se envia 0xA1
	Dato_EEPROM=leer(0); // se recibe y se guarda el dato del registro
	fin_Trama();
}

/*
void Leer_Registros(uint16_t REGISTRO, uint8_t* ARREGLO){
	inicio_Trama();
	Enviar_Dato(ADDR_EEPROM_W); // se envia 0xA0
	Enviar_Dato(REGISTRO >> 8); // se envia el byte alto de la direccion del registro
	Enviar_Dato(REGISTRO & 0xFF); // se envia el byte bajo de la direccion del registro
	inicio_Trama();
	Enviar_Dato(ADDR_EEPROM_R); // se envia 0xA1
	
	for(uint8_t j=0; j<6; j++){ // se recibe y se guarda el dato del registro
		if (j == 5){
			ARREGLO[j] = leer(0); //   NACK
		}
		else{
			ARREGLO[j] = leer(1); // ACK
		}
	}
	fin_Trama();
}*/








