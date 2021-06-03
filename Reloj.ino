#include <LiquidCrystal.h>

const int lim=1e10;
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
volatile boolean button_0=1,button_1=1;
volatile int contP1=0,contP2=0;
ISR (PCINT0_vect){
  button_0=(PINB & (1<<PB0));
  button_1=(PINB & (1<<PB1));
  if(!button_0){
    
  }
  else if(!button_1){
     
  }
   
}
void setup() {
  PORTB |= B00001111;   
  PCMSK0 |= B00001111;  
  PCICR |= B00000001;
  interrupts();  
}
void loop() {
  for(int i=0;i<lim;i++){
  }
  contP1++;
  //lcd.clear();
  lcd.print(contP1);
}
