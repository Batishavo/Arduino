void setup() {
  DDRD |= B11111111;  //PUERTO D SALIDA
  DDRB |= B00001111;  //B0-B3 SALIDA
}
int cont = 0, u = 0, d=0, c=0, um = 0;

void loop() {
  u = cont%10;
  d = (cont/10)%10;
  c = (cont/100)%10;
  um = cont/1000;
  if (cont >=10000)        
  cont = 0;
  for (int i=0;i<5;i++){
    PORTB =B00000111;
    seg (u);  
    PORTB =B00001011;
    seg (d);  
    PORTB =B00001101;
    seg (c);  
    PORTB =B00001110;
    seg (um); 
  }  
  cont += 1;
}
  
void seg (int valor){
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
  default:  PORTD = 63;    break;   } 
  delay (5);}
