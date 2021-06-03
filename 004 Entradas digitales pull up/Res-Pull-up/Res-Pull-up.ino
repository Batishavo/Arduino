void setup() {
  pinMode (9,INPUT_PULLUP);
  pinMode (12,OUTPUT);
}
boolean Eant = 1, Fl = 0, Fs = 0, Fb = 0;
int cont = 0, led = 0;
void loop() {
  Eant = digitalRead (9);
  delay (10);
  Fl = (Eant ^ (digitalRead (9)));
  if (Fl){
    if (!digitalRead (9)){
      Fb = 1;
      Fs = 0;
    }else{
      Fb = 0;
      Fs = 1;
    }    
  }
  cont = cont + Fb;
  if (cont >= 5){
    led = !led;
    digitalWrite (12, led);
    cont = 0;    
  }
  Fs = 0;
  Fb = 0;
}
