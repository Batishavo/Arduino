boolean b1=0,b2=0;
int contador=0;
void setup() {
  // put your setup code here, to run once:
  DDRB=B00111111; //Salida PB=-PB5
  // DDRB2= 0 Por defecto
  PORTD=B00000100;
}

void loop() {
  // put your main code here, to run repeatedly:
  b1=(PIND & (1<<PD2));  //Lee PD2
  if((b1^b2)&& !b1){
    contador++; 
   }
   if(contador==1){
      PORTB=1; 
   }
   if(contador==2){
      PORTB=2; 
   }
   if(contador==3){
      PORTB=4; 
   }
   if(contador==4){
      PORTB=8; 
   }
   if(contador==5){
      PORTB=16; 
   }
   if(contador==6){
      PORTB=32; 
   }
   if(contador>=7){
      PORTB=0; 
      contador=0; 
   } 
  
   b2=B1;
}
