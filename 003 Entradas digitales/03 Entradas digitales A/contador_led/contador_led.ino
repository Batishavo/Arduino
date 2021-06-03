void setup() {
  pinMode (9,INPUT);
  pinMode (12,OUTPUT);
}
int contador = 0, boton = 0;
void loop() {
  if (digitalRead (9) == 1)
    contador++;  
  if (contador >= 5){
    boton = !boton;
    digitalWrite (12, boton); 
    contador = 0;
  }
  delay (500);  
}
