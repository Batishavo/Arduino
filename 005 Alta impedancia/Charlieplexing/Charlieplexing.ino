byte pins []={11,12,13};
const int num_pin = sizeof(pins);
const int num_led = num_pin*(num_pin-1);
byte pairs [num_led/2][2]={ {0,1}, {1,2}, {0,2}};

void setup() {}

void loop (){
  for (int i=0; i < num_led; i++){
  lightLed (i);
  delay (1000);
}
}

void lightLed (int led){
// Selecciona el indice {0,1},{1,2} o {0,2}
  int indexA = pairs[led/2][0];
  int indexB = pairs[led/2][1];
  int pinA = pins[indexA];
  int pinB = pins[indexB];
// pone en alta impedancia los pines no usados
  for (int i=0; i < num_pin; i++){
    if (pins[i] != pinA && pins[i] != pinB){
      // si este pin no es uno de nuestros pines
      pinMode (pins[i], INPUT);
      digitalWrite(pins[i],LOW); // quitando pull-up
    }
  }
    // pone los pines usados como salida
    pinMode (pinA, OUTPUT);
    pinMode (pinB, OUTPUT);
    if (led % 2 == 0){// selecciona cual es alto y cual bajo
      digitalWrite (pinA, LOW);
      digitalWrite (pinB, HIGH);  
    }else{
      digitalWrite (pinB, LOW);
      digitalWrite (pinA, HIGH);
    }
}
