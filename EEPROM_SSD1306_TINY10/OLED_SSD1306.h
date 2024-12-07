/*
	OLED_SSD1306.h
	
*/

///////////////////////////////////////////////////////////////////
////////////////////  REGISTROS DE OLED  //////////////////////////

#define ADDR_SSD1306 0x78 // direccion + escritura

///////////////////////////////////////////////////////////////////
/////////////////////  FUNCIONES PROTOTIPO  ///////////////////////

void OLED_init(); // parametros de inicializacion del OLED 
void Dato_(); // inicio de trama para envior datos
void Comando_(); // inicio de trama para enviar comandos
void OLED_clear(); 
void Print_OLED(const char* DATA); 
void OLED_cursor(uint8_t xpos, uint8_t ypos); // xpos= 0 a 127 ; ypos= 0 a 63
void CONTEO_0_99(uint8_t NUM);
void imprimir_num(uint8_t dat);