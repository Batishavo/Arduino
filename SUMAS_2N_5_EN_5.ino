//7 Segmentos de display
int a = 12;
int b = 8;
int c = 4;
int d = 6;
int e = 7;
int f = 11;
int g = 3;
 
// digitoos de Display
int dg1 = 14;
int dg2 = 9;
int dg3 = 10;
int dg4 = 13;

//Punto
int dp=5;
byte segmentos[7] = { a,b,c,d,e,f,g };
byte orden_digitos[4] = { dg1,dg2,dg3,dg4 };
byte digitos[4][4] = { { 0,0,0,1 },
                      { 0,0,1,0 },
                      { 0,1,0,0 },
                      { 1,0,0,0 }
                    };
byte siete_segmentos_digitos[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,0,0,1,1 }   // = 9
                               };
void EscribeDigito(byte digito, byte numero) {
  int secuencia = 0; 
  //Activa número
  ActivarDigito(digito); 
  //digitalWrite(dp,1);//Punto
  //Escribe Numero 
  for (byte i = 0; i < 7; i++){
    digitalWrite(segmentos[secuencia], siete_segmentos_digitos[numero][i]);
    ++secuencia;
  }
}

void ActivarDigito(int x){
  digitalWrite(dg1, HIGH);
  digitalWrite(dg2, HIGH);
  digitalWrite(dg3, HIGH);
  digitalWrite(dg4, HIGH); 
  switch(x){
    case 1: 
      digitalWrite(dg1, LOW); 
      break;
    case 2: 
      digitalWrite(dg2, LOW); 
      break;
    case 3: 
      digitalWrite(dg3, LOW); 
      break;
    default: 
      digitalWrite(dg4, LOW); 
      break;
  }
}

int cont=0,uni=0,dec=0,cen=0,um=0;
volatile boolean flag=1;
ISR (PCINT0_vect){
 flag = (PINB & (1<<PB2));
 if (!b){
  cont+=123;
  uni = cont%10;
  dec = (cont/10)%10;
  cen = (cont/100)%10;
  um = cont/1000;     
 }
  
 if (cont >=10000){
  cont = 0;
 }
 delayMicroseconds (100000);   
}
void start(){
    EscribeDigito(1,uni);
    EscribeDigito(2,dec);
    EscribeDigito(3,cen);
    EscribeDigito(4,um);
}
void setup(){
  DDRD |= B11111111;
  DDRC |= B00001111;

  DDRB = DDRB|B11111011;
  PORTB = (1<<PB2);
  PCMSK0 |= B00000100;
  PCICR |= B00000001;
  int i; 
   //Definimos entrada del boton
   pinMode(14,INPUT);
  //Inicializar Pines
  for(i=3; i <= 14;i++)     
     pinMode(i,OUTPUT);
} 
 
 void loop(){
    //boton();
   // delay();
    start();
}


