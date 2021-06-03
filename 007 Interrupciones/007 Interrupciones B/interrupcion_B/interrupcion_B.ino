void setup() {
  DDRB = DDRB|B00111000;  //PB0-PB2 ENTRADA PB3-PB5 SALIDA
  PORTB = PORTB|B00000111; // SALIDAS "0" Y ENTRADAS PULLUP
  DDRD = DDRD|B00000000;  //D2 COMO ENTRADA
  PORTD =(1<<PD2); //ACTIVA EL PULLUP 
  attachInterrupt (0, boton, FALLING);  // Interrupción
}
volatile boolean b1 = 1, b2 = 1, b3 = 1;
volatile boolean led1 = 0, led2 = 0, led3 = 0;
void boton (){
  b1 = (PINB & (1<<PB0));
  b2 = (PINB & (1<<PB1));
  b3 = (PINB & (1<<PB2));
  if (!b1)
  led1 = !led1;
  if (!b2)
  led2 = !led2;
  if (!b3)
  led3 = !led3;
  delayMicroseconds (10000);
}
void loop() {
  digitalWrite (11,led1);
  digitalWrite (12,led2);
  digitalWrite (13,led3); 
}
