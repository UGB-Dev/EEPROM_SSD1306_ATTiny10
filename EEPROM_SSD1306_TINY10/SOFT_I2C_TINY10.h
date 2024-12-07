
/*
	SOFT_I2C_TINY10.h
	
*/

/*            ______
	   PB0 __| O	|___ PB3
	   GND __|		|___ VCC
(SDA)  PB1 __|		|___ PB2  (SCL)
             |______|
	
*/

///////////////////////////////////////////////////////////////////
////////////////////  VELOCIDAD DEL PROTOCOLO  ////////////////////

#define CLK_I2C (( F_CPU / (2*50000 ))-1) //100 KHz en SCL // tiempo de bit a 10us
#define Time_HL ((CLK_I2C*68)/100)

///////////////////////////////////////////////////////////////////
//////////////////  ETIQUETAS PARA LOS PINES  /////////////////////

// PB2 ES SCL :  PB1 ES SDA
#define SCL_ON (DDRB &= ~(1<<PORTB2)) // ENTRADA Z (VCC)
#define SCL_OFF (DDRB |= (1<<PORTB2)) // SALIDA  (GND) 
#define SDA_ON (DDRB &= ~(1<<PORTB1)) // ENTRADA Z (VCC)
#define SDA_OFF (DDRB |= (1<<PORTB1)) // SALIDA  (GND)

///////////////////////////////////////////////////////////////////
/////////////////////  VARIABLES GLOBALES  ////////////////////////

volatile bool RECONOCIMIENTO=0; // ACK(valor en 0) o NACK(valor en 1)
volatile char Byte_copia; // almacena el dato para enviar o recibir
volatile uint8_t Byte_contador; // variable para recorrer bit a bit


///////////////////////////////////////////////////////////////////
////////////////////  FUNCIONES PROTOTIPO  ////////////////////////

void Set_FCPU_8MHz(void); // ajusta la frecuencia a 13 MHz aprox
void config_PWM_COMPA(void); // configura el modo CTC por comparacion A
void config_PWM_COMPB(void); // configura el modo CTC por comparacion B
void reset_PWM_(void); // deshabilita el modo CTC
void inicio_Trama(void); 
void fin_Trama(void);
void Enviar_Dato(uint8_t Byte);
uint8_t leer(bool ACK);







