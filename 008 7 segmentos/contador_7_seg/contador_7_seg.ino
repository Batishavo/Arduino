void setup() {
  DDRD = DDRD|B11111111;  //PUERTO D SALIDA
  DDRB = DDRD|B11111011;  //B2 COMO ENTRADA
  PORTB =(1<<PB2); //ACTIVA EL PULLUP 
  PCMSK0 |= B00000100;    // Activamos PB2 O D10
  PCICR |= B00000001;     // Activamos PCINT0
}
volatile boolean b = 1;
volatile int cont = 0;
ISR (PCINT0_vect){
  b = (PINB & (1<<PB2));
  if (!b)               // flanco de bajada
  cont += 1;
  if (cont >9)
  cont = 0;
  delayMicroseconds (100000);   }
void loop() {
  switch (cont){
  case 0:   PORTD = 63;   break;
  case 1:   PORTD = 06;   break;
  case 2:   PORTD = 91;   break;
  case 3:   PORTD = 79;   break;
  case 4:   PORTD = 102;  break;
  case 5:   PORTD = 109;  break;
  case 6:   PORTD = 124;  break;
  case 7:   PORTD = 7;    break;
  case 8:   PORTD = 127;  break;
  case 9:   PORTD = 103;  break;
  default:  PORTD = 0;    break;    
  } 
}
