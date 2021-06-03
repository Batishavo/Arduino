void setup() {
  pinMode (9,INPUT);
  pinMode (12,OUTPUT);
  Serial.begin(9600);
}
int A = 5, B = 6, OUT = 0;
void loop() {
  OUT = (A&&(!B))||((!A)&&B);
  Serial.println(OUT);      
}
