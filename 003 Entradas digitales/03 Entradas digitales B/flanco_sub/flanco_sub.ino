void setup() {
  pinMode (9,INPUT);
  pinMode (12,OUTPUT);
}
boolean Eant = 0, Fl = 0, Fs = 0, Fb = 0;
void loop() {
  Eant = digitalRead (9);
  delay (10);
  Fl = (Eant ^ (digitalRead (9)));
  digitalWrite (12,Fl);
  if (Fl){
    if (digitalRead (9)){
      Fs = 1;
      Fb = 0;
    }else{
      Fs = 0;
      Fb = 1;
    }    
  }    
  Fs = 0;
  Fb = 0;
}
