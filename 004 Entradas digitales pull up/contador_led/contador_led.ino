void setup() {
  pinMode (9,INPUT);
  pinMode (12,OUTPUT);
}
boolean Eant = 0, Fl = 0, Fs = 0, Fb = 0;
int cont = 0, led = 0;
void loop() {
  Eant = digitalRead (9);
  delay (10);
  Fl = (Eant ^ (digitalRead (9)));
  if (Fl){
    if (digitalRead(9)){
      Fs = 1;
      Fb = 0;
    }else{
      Fs = 0;
      Fb = 1;
    }    
  }
  cont = cont + Fs;
  if (cont >= 5){
    led = !led;
    digitalWrite (12, led);
    //digitalWrite (12,!digitalRead (12));
    cont = 0;
  }  
  Fs = 0;
  Fb = 0;
}
