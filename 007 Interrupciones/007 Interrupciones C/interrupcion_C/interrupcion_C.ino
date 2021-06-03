void setup() {
  DDRB |= B00111000;    //PB0-PB2 ENTRADA PB3-PB5 SALIDA
  PORTB |= B00000111;   // SALIDAS "0" Y ENTRADAS PULLUP
  PCMSK0 |= B00000111;  // Activamos PB0-PB2 D8-D10
  PCICR |= B00000001;   // Activamos PCINT0
}
volatile boolean b1 = 1, b2 = 1, b3 = 1;
volatile boolean led1 = 0, led2 = 0, led3 = 0;
ISR (PCINT0_vect){
  b1 = (PINB & (1<<PB0));
  b2 = (PINB & (1<<PB1));
  b3 = (PINB & (1<<PB2));
  if (!b1)               // flanco de bajada
  led1 = !led1;
  if (!b2)
  led2 = !led2;
  if (!b3)
  led3 = !led3;
  delayMicroseconds (100000);
}

void loop() {
  digitalWrite (11,led1);
  digitalWrite (12,led2);
  digitalWrite (13,led3);
}
