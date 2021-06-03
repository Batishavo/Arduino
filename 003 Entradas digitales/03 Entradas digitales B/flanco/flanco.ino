void setup() {
  pinMode (9,INPUT);
  pinMode (12,OUTPUT);
}
boolean Eant = 0, Fl = 0;
void loop() {
  Eant = digitalRead (9);
  delay (10);
  Fl = (Eant ^ (digitalRead (9)));
  digitalWrite (12,Fl);
  if (Fl){
    delay (300);
  }    
}
