void setup() {
  DDRB = DDRB|B00111111;
  DDRD = DDRD|B11111000;  //D2 COMO ENTRADA
  PORTD =(1<<PD2); //ACTIVA EL PULLUP 
  attachInterrupt (0, boton, FALLING);  // Interrupción
}
volatile int cont = 0;
void boton (){
  cont++;
  delayMicroseconds (10000);
}
void loop() {
  switch (cont){
  case 1:
    PORTB = (1<<PB0);
    break;
  case 2:
    PORTB = B00000010;     
    break;
  case 3:
    PORTB = B00000100; 
    break;
  case 4:
    PORTB = B00001000; 
    break;
  case 5:
    PORTB = B00010000;
    break;
  case 6:
    PORTB = B00100000;
    break;
  case 7:
    PORTB = B00000000;
    cont = 0; 
    break;
  default:
    PORTB = B00000000;
    break;    
  } 
}
