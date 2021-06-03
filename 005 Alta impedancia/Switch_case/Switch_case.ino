#define A 11
#define B 12
#define C 13

void setup() {}

void loop() {
  for (int i=0; i < 6; i++){
  lightLed (i);
  delay (1000);
  }
}

void lightLed (int led){
  switch (led){
    case 0:
      pinMode (A, OUTPUT);
      pinMode (B, OUTPUT);
      pinMode (C, INPUT);
      digitalWrite (A, LOW);
      digitalWrite (B, HIGH);
      digitalWrite (C, LOW);
      break;
    case 1:
      pinMode (A, OUTPUT);
      pinMode (B, OUTPUT);
      pinMode (C, INPUT);
      digitalWrite (A, HIGH);
      digitalWrite (B, LOW);
      digitalWrite (C, LOW);
      break;
    case 2:
      pinMode (A, INPUT);
      pinMode (B, OUTPUT);
      pinMode (C, OUTPUT);
      digitalWrite (A, LOW);
      digitalWrite (B, LOW);
      digitalWrite (C, HIGH);
      break;
    case 3:
      pinMode (A, INPUT);
      pinMode (B, OUTPUT);
      pinMode (C, OUTPUT);
      digitalWrite (A, LOW);
      digitalWrite (B, HIGH);
      digitalWrite (C, LOW);
      break;
    case 4:
      pinMode (A, OUTPUT);
      pinMode (B, INPUT);
      pinMode (C, OUTPUT);
      digitalWrite (A, LOW);
      digitalWrite (B, LOW);
      digitalWrite (C, HIGH);
      break;
    case 5:
      pinMode (A, OUTPUT);
      pinMode (B, INPUT);
      pinMode (C, OUTPUT);
      digitalWrite (A, HIGH);
      digitalWrite (B, LOW);
      digitalWrite (C, LOW);
      break;
    default:
      pinMode (A, OUTPUT);
      pinMode (B, OUTPUT);
      pinMode (C, OUTPUT);
      digitalWrite (A, LOW);
      digitalWrite (B, LOW);
      digitalWrite (C, LOW);
      break;
  }
}
