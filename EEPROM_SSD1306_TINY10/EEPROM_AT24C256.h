/*
	EEPROM_AT24C256.h
	
*/

///////////////////////////////////////////////////////////////////
//////////////////  REGISTROS DE EEPROM  ////////////////////////

#define ADDR_EEPROM_W 0xA0  // direccion + escritura
#define ADDR_EEPROM_R 0xA1	// direccion + lectura

///////////////////////////////////////////////////////////////////
/////////////////////  VARIABLES GLOBALES  ////////////////////////

uint8_t Dato_EEPROM;// Letra[5];

///////////////////////////////////////////////////////////////////
/////////////////////  FUNCIONES PROTOTIPO  ///////////////////////


void Leer_Registro(uint16_t REGISTRO); // obtiene el valor del registro de la EEPROM
//void Escribir_Registro(uint16_t REGISTRO, uint8_t DATO);


