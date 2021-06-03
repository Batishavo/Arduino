const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
int data_pins[4] = {d4,d5,d6,d7};
void setup() {
  lcdInit ();  
  escribir (72);   //H
  escribir (79);   //O
  escribir (76);   //L
  escribir (65);   //A
  salto ();
  escribir (77);   //M
  escribir (85);   //U
  escribir (78);   //N
  escribir (68);   //D
  escribir (79);   //O
  for (int i=0; i<11; i++){
    delay (400);
    pantallaDer ();}
  for (int i=0; i<11; i++){
    delay (400);
    pantallaIzq ();}
}

void loop() {  
}

void lcdInit(){
  pinMode (rs, OUTPUT);
  pinMode (en, OUTPUT);
  for (int i=0; i<4;i++){
    pinMode (data_pins[i],OUTPUT);
  }
  delayMicroseconds(50000); // Espera 50 ms
// Poner RS y en en bajo por default ya estan así
// Enviar 0011
        digitalWrite (d4,1);
        digitalWrite (d5,1);  
  delayMicroseconds(5000); // Espera por mas de 4.1 ms
// Enviar 0011
  //delayMicroseconds(150); // Espera por mas de 100 us
  comando (50);
  comando (40);  
  comando (8);    
  comando (1);            // Esta instrucción tarda mas
  delayMicroseconds(2000);// Espera por mas de 1.2 ms
  comando (6);  
  //  ya se inicializo el LCD pero no muestra la pantalla 
  comando (12);    // muestra la pantalla
}

void comando  (uint8_t valor){envio(valor, 0);}
void escribir (uint8_t valor){envio(valor, 1);}

void envio(uint8_t valor, uint8_t modo){
digitalWrite(rs, modo);         // RW debe estar a tierra
  for (int i = 4; i < 8; i++)                 
  //-----"valor >> i" desplaza i bits a la derecha-----//
  digitalWrite(data_pins[i-4],(valor>>i)&0x01);
pulseEnable ();  
  for (int i = 0; i < 4; i++)  
  digitalWrite(data_pins[i], (valor >> i) & 0x01);
pulseEnable ();
}

void pulseEnable(void) {    
  digitalWrite(en, HIGH);
  delayMicroseconds(1);   //debe durar mas de 450ns
  digitalWrite(en, LOW);
  delayMicroseconds(100); //comando necesitan al menos 37us
}

void limpiar()          {comando (1); delayMicroseconds(2000);}
void inicio()           {comando (2); delayMicroseconds(2000);}
void cursorDerecho()    {comando (6);}
void cursorIzquierdo()  {comando (4);}
void Display()          {comando (12);}
void NoDisplay()        {comando (8);}
void cursorOn()         {comando (14);}
void cursorOff()        {comando (12);}
void blinkOn()          {comando (15);}
void blinkOff()         {comando (13);}
void retrocedeCursor()  {comando (16);}
void avanzaCursor()     {comando (20);}
void pantallaIzq()      {comando (24);}
void pantallaDer()      {comando (28);}
void salto()            {comando (192);}
void posicionCursor (int col, int ren){
  if (ren == 1)       comando(((col)-1)|(128));
  else                comando(((col)-1)|(192));
}
