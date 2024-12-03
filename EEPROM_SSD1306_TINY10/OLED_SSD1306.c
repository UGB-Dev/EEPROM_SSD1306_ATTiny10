/*
	OLED_SSD1306.c
	
*/

#include "OLED_SSD1306.h"

///////////////////////////////////////////////////////////////////
/////////////  INICIALIZACION DE PARAMETROS AL OLED  //////////////

void OLED_init(){
	for(uint8_t i=0; i<27; i++){ // se envian 27 registros de configuracion
		Leer_Registro(i); // se obtiene el dato del registro x de la eeprom
		Comando_(); // inicio de trama para enviar comandos al OLED
		Enviar_Dato(Dato_EEPROM); 
		fin_Trama(); 
	}
}

///////////////////////////////////////////////////////////////////
//////////  INICIALIZACION PARA ENVIAR DATO O COMANDO  ////////////

void Dato_(){
	inicio_Trama();
	Enviar_Dato(ADDR_SSD1306); // se envia direccion + escritura (0x78)
	Enviar_Dato(0x40); // se envia 0x40 para datos
}

void Comando_(){
	inicio_Trama();
	Enviar_Dato(ADDR_SSD1306); // se envia direccion + escritura (0x78)
	Enviar_Dato(0x00); // se envia 0x00 para comandos
}

///////////////////////////////////////////////////////////////////
///////////////  FUNCIONES PARA CONTROLAR EL OLED  ////////////////

void OLED_clear(){
	Dato_(); // inicio de trama para envior datos
	for (uint16_t i=0; i<1024; i++){ Enviar_Dato(0); }// envia 8 byte 128 veces para cubrir 128x64 pixeles
	fin_Trama();
}

/*
	estructura del registro del tipo de letra:
													ascii	|	EEPROM	
	dat1, dat2, dat3, dat4, dat5, dat6,		// space (32)	|	29 a 34	
	dat7, dat8, dat9, dat10, dat11, dat12,	// ..... (33)	|	35 a 40
	datn,'''''''''''''''''''''''''''''''',	// ..... (34)	|	41 a 47
	 '''''''''''''''''''''''''''''''''''',	''''''''''''	|	48 a 53
	 '''''''''''''''''''''''''''''''''''',	''''''''''''	|

	 formula:
					Reg_EEPROM[i] = [( Dato_in - 32 )*6]+ 29 + i 
	 donde:
		Dato_in: dato de entrada del string en ascii
		i: recorrido de la eeprom (0 a 5)
						
*/

void Print_OLED(const char* DATA){
	while(*DATA!=0){ // ciclo infinito si el dato es diferente de 0
		for (uint8_t i=0; i<6; i++){ 
			Leer_Registro((*DATA-32)*6+i+29); // se obtiene el dato del registro x de la eeprom 
			Dato_(); // inicio de trama para envior datos al OLED
			Enviar_Dato(Dato_EEPROM);
			fin_Trama();
		}
		DATA++; // incrementa a la siguiente posicion del string
	}
}

void OLED_cursor(uint8_t xpos, uint8_t ypos){
	Comando_(); // inicio de trama para enviar comandos al OLED
	Enviar_Dato(xpos & 0x0F); //  nibble bajo para posicionarse en la columna
	Enviar_Dato(0x10 | (xpos >> 4)); // nibble alto para posicionarse en la columna
	Enviar_Dato(0xB0 | (ypos & 0x07)); // byte para posicionarse en la pagina (0 a 7)
	fin_Trama();
}