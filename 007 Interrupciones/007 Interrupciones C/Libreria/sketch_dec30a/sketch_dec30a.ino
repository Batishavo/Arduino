#define PCINT_PIN 8
 
#include <YetAnotherPcInt.h>
volatile boolean b1 = 1, b2 = 1, b3 = 1;
volatile boolean led1 = 0, led2 = 0, led3 = 0;
void pinChanged() {    
  b1 = (PINB & (1<<PB0));
  if (!b1)               // flanco de bajada
  led1 = !led1;   
  delayMicroseconds (10000);  
}
 
void setup() {
  pinMode (11, OUTPUT);
  pinMode(PCINT_PIN, INPUT_PULLUP);
  PcInt::attachInterrupt(PCINT_PIN, pinChanged,CHANGE);
}
 
void loop() {
  digitalWrite (11,led1);
}
