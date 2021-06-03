#include <LiquidCrystal.h>
const int rs=2,en=3,d4=4,d5=5,d6=6,d7=7;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
volatile int cont2;
volatile boolean inicio;
void setup() {
  // Paramos todas las interrupciones antes de contigurar un timer
  noInterrupts();
  inicio=false;
  DDRB |= B00000000;    //Salida PB4 entrada PB0-PB3
  PORTB |= B00011111;    //Entradas pullup
  PCMSK0 |= B00011111;  //Activacion de PB0-PB3
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
  pantalla1();
  interrupts();
  
} 
volatile boolean b1=1,b2=1,b3=1,b4=1;
volatile int cont=0,pant=1,pantalla=1;
volatile int horaP1,minutoP1,segundoP1,horaP2,minutoP2,segundoP2;
volatile bool quien;
int winner=0;
ISR(TIMER1_COMPA_vect) {
  if(inicio){
      if(quien){
        segundoP1--;
        if(segundoP1==-1){
          segundoP1=59;
          minutoP1--;
          if(minutoP1==-1){
            minutoP1=59;
            horaP1--;
            if(horaP1==-1){
               winner=1;  
            }
          }
        }
      }else{
        segundoP2--;
        if(segundoP2==-1){
          segundoP2=59;
          minutoP2--;
          if(minutoP2==-1){
            minutoP2=59;
            horaP2--;
            if(horaP2==-1){
               winner=2;  
            }
          }
        }
      }
      pantalla1();
  }
}

volatile int contaInicio;
volatile int player=1;
void suma(){
  if(player==1){
    if(contaInicio==0){
      horaP1++;
    }else if(contaInicio==1){
      minutoP1++;
    }else{
      segundoP1++;
    }
  }
  else{
    if(contaInicio==3){
      horaP2++;
    }else if(contaInicio==4){
      minutoP2++;
    }else{
      segundoP2++;
    }
  }
  //pantalla1();
}
ISR(PCINT0_vect){
  b1=(PINB & (1<<PB1));
  b2=(PINB & (1<<PB2));
  b3=(PINB & (1<<PB3));
  b4=(PINB & (1<<PB4));
  if(!b1){
    quien=!quien;
  }
  if(!b2){
    contaInicio++;
    if(contaInicio==3){
      player=2;
      pantalla1();
    }
    if(contaInicio==6){
       inicio=true;
       pantalla1();
    }
  }
  if(!b3){
    suma();
    pantalla1();
  }
  if(!b4){
    inicio=!inicio;
  }
}

void pantalla1(){
  //lcd.clear();
  if(winner>0){
    lcd.clear();
    if(winner==1){
        lcd.print("The winner is Player2");
    }
    else{
      lcd.print("The winner is Player1");
    }
  }
  else{
    lcd.begin(16,2);  
    if(contaInicio<3){
      lcd.print("P1Hour:");
      if(horaP1<=9){
        lcd.print(0);
      }
      lcd.print(horaP1);
      lcd.print("|min:");
      if(minutoP1<=9){
        lcd.print(0);
      }
      lcd.print(minutoP1);
      lcd.setCursor(0,1);
      lcd.print("Sec ");
      if(segundoP1<=9){
        lcd.print(0);
      }
      lcd.print(segundoP1);
    }
    else if(contaInicio<6){
      lcd.print("P2Hour:");
      if(horaP2<=9){
        lcd.print(0);
      }
      lcd.print(horaP2);
      lcd.print("|min:");
      if(minutoP2<=9){
        lcd.print(0);
      }
      lcd.print(minutoP2);
      lcd.setCursor(0,1);
      lcd.print("Sec ");
      if(segundoP2<=9){
        lcd.print(0);
      }
      lcd.print(segundoP2);

    }
     else{
        lcd.print("Player1:");
        if(horaP1<=9){
          lcd.print(0);
        }
        lcd.print(horaP1);
        lcd.print(":");
        if(minutoP1<=9){
          lcd.print(0);
        }
        lcd.print(minutoP1);
        lcd.print(":");
        if(segundoP1<=9){
          lcd.print(0);
        }
        lcd.print(segundoP1);
        lcd.setCursor(0,1);
        lcd.print("Player2:");
        if(horaP2<=9){
          lcd.print(0);
        }
        lcd.print(horaP2);
        lcd.print(":");
        if(minutoP2<=9){
          lcd.print(0);
        }
        lcd.print(minutoP2);
        lcd.print(":");
        if(segundoP2<=9){
          lcd.print(0);
        }
        lcd.print(segundoP2);
       
    } 
  }
}



void loop() {
  digitalWrite(12,led);
}
