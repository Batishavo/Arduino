void setup() {
  DDRB = DDRB|B00111111;
  DDRD = DDRD|B11111000;  //D2 COMO ENTRADA
  PORTD =(1<<PD2); //ACTIVA EL PULLUP 
}
boolean Eant = 1, Eact = 1, Fl = 0, Fs = 0, Fb = 0;
int cont = 0;
void loop() {
  Eant = (PIND & (1<<PD2));
  delay (10);
  Eact = (PIND & (1<<PD2));
  Fl = (Eant ^ Eact);
if (Fl){
    if (!Eact){
      Fb = 1;
      Fs = 0;
    }else{
      Fb = 0;
      Fs = 1;
    }    
  }
  cont = cont + Fb;
  Fs = 0;
  Fb = 0;
  
  switch (cont){
  case 1:
    PORTB = (1<<PB0);
    //PORTB = B00000001; 
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
