#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
volatile boolean button_0=1,button_1=1,button_2=1,button_3=1;
volatile boolean led=0;
volatile int cont=0,interfaz=0;
ISR (PCINT0_vect){
  button_0=(PINB & (1<<PB0));
  button_1=(PINB & (1<<PB1));
  button_2=(PINB & (1<<PB2));
  button_3=(PINB & (1<<PB3));
  if(!button_0){
    if(interfaz==1){
        cont++;
        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("Contador");
        lcd.setCursor(10,0);
        lcd.print("Inicio");
        lcd.setCursor(0,1);
        lcd.print("Cuenta:");
        lcd.setCursor(7,1);
        lcd.print(cont);
        lcd.setCursor(10,1);
        lcd.print("Sig-->");
        
     }
     else if(interfaz==2){
        interfaz=1;  
        lcd.begin(16,2);
        lcd.print("Menu inicio");
        lcd.setCursor(10,1);
        lcd.print("Sig-->");
     }
  }
  else if(!button_1){
      if(interfaz==1){
        interfaz=0;  
        lcd.begin(16,2);
        lcd.print("Menu inicio");
        lcd.setCursor(10,1);
        lcd.print("Sig-->");
      }
   }
   else if(!button_2){
    if(interfaz==1){
      cont--;
      interfaz=1;
      lcd.begin(16,2);
      lcd.setCursor(0,0);
      lcd.print("Contador");
      lcd.setCursor(10,0);
      lcd.print("Inicio");
      lcd.setCursor(0,1);
      lcd.print("Cuenta:");
      lcd.setCursor(7,1);
      lcd.print(cont);
      lcd.setCursor(10,1);
      lcd.print("Sig-->");
    }
    else if(interfaz==2){
      interfaz=1;  
      lcd.begin(16,2);
      lcd.setCursor(0,0);
      lcd.print("Contador");
      lcd.setCursor(10,0);
      lcd.print("Inicio");
      lcd.setCursor(0,1);
      lcd.print("Cuenta:");
      lcd.setCursor(7,1);
      lcd.print(cont);
      lcd.setCursor(10,1);
      lcd.print("Sig-->");
    }
   }
   if(!button_3){
    if(interfaz==0){
      interfaz=1;
      lcd.begin(16,2);
      lcd.setCursor(0,0);
      lcd.print("Contador");
      lcd.setCursor(10,0);
      lcd.print("Inicio");
      lcd.setCursor(0,1);
      lcd.print("Cuenta:");
      lcd.setCursor(7,1);
      lcd.print(cont);
      lcd.setCursor(10,1);
      lcd.print("Sig-->");
      
    }
    else if(interfaz==1){
      interfaz=2;
        lcd.begin(16,2);
        lcd.setCursor(0,0);
        lcd.print("Inicio");
        lcd.setCursor(10,0);
        lcd.print("Motor");
      
        lcd.setCursor(0,1);
        lcd.print("Atras");
        lcd.setCursor(10,1);
        lcd.print("ON/OFF");
    }
    else if(interfaz==2){
      interfaz=2;
      led=!led;  
    }
   }
}
void setup() {
  DDRB |= B00010000;   
  PORTB |= B00001111;   
  PCMSK0 |= B00001111;  
  PCICR |= B00000001;
  interrupts();
  lcd.begin(16,2);
  lcd.print("Menu inicio");
  lcd.setCursor(10,1);
  lcd.print("Sig-->");
  
}
void loop() {
  digitalWrite(12,led);
}
