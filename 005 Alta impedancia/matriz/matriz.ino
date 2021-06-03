#define A 11
#define B 12
#define C 13
int Matriz[6][2][3]={
//   pinMode               digitalWrite
  {{OUTPUT,OUTPUT,INPUT},{LOW,HIGH,LOW}},
  {{OUTPUT,OUTPUT,INPUT},{HIGH,LOW,LOW}},
  {{INPUT,OUTPUT,OUTPUT},{LOW,LOW,HIGH}},
  {{INPUT,OUTPUT,OUTPUT},{LOW,HIGH,LOW}},
  {{OUTPUT,INPUT,OUTPUT},{LOW,LOW,HIGH}},
  {{OUTPUT,INPUT,OUTPUT},{HIGH,LOW,LOW}}
};
void setup() {}

void loop() {
  for (int i=0; i < 6; i++){
  lightLed (i);
  delay (2);
  }
}
void lightLed (int led){
  pinMode(A,Matriz[led][0][0]);
  pinMode(B,Matriz[led][0][1]);
  pinMode(C,Matriz[led][0][2]);
  digitalWrite(A,Matriz[led][1][0]);
  digitalWrite(B,Matriz[led][1][1]);
  digitalWrite(C,Matriz[led][1][2]);
}
