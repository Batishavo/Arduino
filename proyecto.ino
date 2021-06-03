void setup() {
  // put your setup code here, to run once:
  DDRD |= B11111111;
  DDRC |= B00001111;

  DDRB = DDRB|B11111011;
  PORTB = (1<<PB2);
  PCMSK0 |= B00000100;
  PCICR |= B00000001;
}

int cont=0,u=0,d=0,c=0,um=0;
volatile boolean b=1;
ISR (PCINT0_vect){
 b = (PINB & (1<<PB2));
 if (!b){
  cont+=5;
  u = cont%10;
  d = (cont/10)%10;
  c = (cont/100)%10;
  um = cont/1000;     
 }
  
 if (cont >=10000){
  cont = 0;
 }
 delayMicroseconds (100000);   
}
void seg(int valor){
  switch (valor){
    case 1:   PORTD = 06;   break;
    case 2:   PORTD = 91;   break;
    case 3:   PORTD = 79;   break;
    case 4:   PORTD = 102;  break;
    case 5:   PORTD = 109;  break;
    case 6:   PORTD = 124;  break;
    case 7:   PORTD = 7;    break;
    case 8:   PORTD = 127;  break;
    case 9:   PORTD = 103;  break;
    default:  PORTD = 63;    break;   
  }
  delay(1);
}

void loop() {
  PORTC=B00000111;
  seg(u);
  PORTC=B00001011;
  seg(d);
  PORTC=B00001101;
  seg(c);
  PORTC=B00001110;
  seg(um);
}
