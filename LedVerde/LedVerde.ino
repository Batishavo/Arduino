int contador=0;
boolean b1=0,b2=0,led=0;
void setup() {
  pinMode(12, OUTPUT);
  pinMode(7,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  b2=digitalRead(7);
  if((b1^b2)&(!b2)){
    contador++;
  }
  if(contador>=5){
    led=!led;
    contador=0;  
  }
  digitalWrite(12,led);
  b1=b2;
}
