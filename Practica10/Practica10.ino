#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7,rayos=36;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
volatile int con=0,seg=0;
void imp(){
  lcd.clear();
  lcd.print("RPM =");
 // lcd.print(con/rayos/m); 
}
void setup() {
  // Paramos todas las interrupciones antes de contigurar un timer
  noInterrupts();
  DDRB |= B00010000;   
  PORTB |= B00001111;   
  PCMSK0 |= B00001111;  
  PCICR |= B00000001;
  
   //-------------------TIMER------------------------
    // El registro de control A queda todo en 0
  TCCR1A = 0;

  // Activamos el modo CTC en Timer1
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12);

  // y nuestro pre-escalador en 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  
  // Inicializamos el contador en 0
  TCNT1 = 0;
  
  // El registro comparador de salida segun nuestra formula deberia ser 7812,5
  OCR1A = 7812;
  //OCR1A = 782;
  
  // Inicializamos el comparador para el registro A
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
  lcd.print("RPM= 0");
  ////Sensor
  Serial.begin(9600); //Configuracion de la velocidad serial
  
}
volatile boolean button_0=1,button_1=1,button_2=1,button_3=1;
ISR (PCINT0_vect){
  // lcd.clear();
  button_0=(PINB & (1<<PB0));
  if(!button_0){
    con++;        
    
  }
  //delay(100);
}
ISR(TIMER1_COMPA_vect) {
  seg++;
  lcd.clear();
  lcd.print("RPM=");
  double total=con*7.5;
  double tiempo=(seg);
  lcd.print(total/tiempo); 
}

void loop() {

}
