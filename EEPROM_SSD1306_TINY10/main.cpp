/*
 * EEPROM_SSD1306_TINY10.cpp
 *
 * Created: 27/11/2024 12:39:43 a. m.
 * Author : UGB
 */ 

/*
		REGISTROS GUARDADOS EN LA EEPROM:
		0 a 26		==> DATOS PARA INICIALIZAR OLED
		27 y 28		==> SIN DATOS 
		29 a 349	==> DATOS TIPO DE FUENTE (SOLO LETRAS MAYUSCULAS)
*/

#define F_CPU 13485000UL  
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SOFT_I2C_TINY10.c"
#include "EEPROM_AT24C256.c"
#include "OLED_SSD1306.c"


int main(void){
	
	Set_FCPU_8MHz(); // oscilador RC a maxima frecuencia
	
	OLED_init(); // inicializa el OLED
	OLED_clear(); // limpia pantalla
	while (1){
		CONTEO_0_99();
		/*OLED_cursor(0,3);
		Print_OLED("HOLA MUNDO");*/
		//_delay_ms(500);
		//OLED_cursor(0, 3);// se posiciona en columna=10; pagina=3
		//Print_OLED("ESTO ES UNA PRUEBA DE FUNCIONAMIENTO"); // se imprime el string
		//_delay_ms(500);
		//OLED_clear(); // limpia pantalla
	}
}

