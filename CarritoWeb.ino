#include <WiFi.h>

//------------------Servidor Web en puerto 80---------------------

WiFiServer server(80);

//---------------------Credenciales de WiFi-----------------------

const char* ssid     =  "INFINITUMA8A2_2.4";
const char* password = "svh2m2h23W";



//---------------------VARIABLES GLOBALES-------------------------
int contconexion = 0;

String header; // Variable para guardar el HTTP request


const int PinIN1 = 22;//entradas del aurduino 
const int PinIN2 = 23;
const int PinIN3 = 19;
const int PinIN4 = 21;

//------------------------CODIGO HTML------------------------------
String pagina ="<!Doctype html>"
"<html lang='es'>"
    "<head>"
    "<meta charset='utf-8'>"
"<meta name='viewport' content='width-device-width, user-scalable=no, initial-scale=1, maximum-scale=1, minumum-scale=1'>"
        "<title></title>"
    "<link rel='stylesheet' href='estilos/estilos.css'>"
        "<!--Libreria para grafico-->"
        "<script src='https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.js' integrity='sha512-hZf9Qhp3rlDJBvAKvmiG+goaaKRZA6LKUO35oK6EsM0/kjPK32Yw7URqrq3Q+Nvbbt8Usss+IekL7CRn83dYmw==' crossorigin='anonymous'></script>"
    "</head>"
    "<body>"
       "<header class='header'>"
       "<div class='contenedor'>"  
           "<h1 class='titulo'>ROBOT EXPLORADOR</h1>"
        "<span class=icon-menu id='btn-menu'></span>"
           "<nav class='nav' id='nav'>"
           "<ul class='menu'>"
            "<li class='menu__item'><a class='menu__link select' href='index.html'>Inicio</a></li>"
            "<li class='menu__item'><a class='menu__link' href='Noticias.html'>Noticias</a></li>"   
            "<li class='menu__item'><a class='menu__link' href=''>Desarrolladores</a></li>"  
            "<li class='menu__item'><a class='menu__link' href='Contacto.html'>Concacto</a></li>"    
           "</ul>"
           "</nav>"
        "</div>"    
    "</header>"
        "<div class='Controles'>"
        "<input type='button' class='botones' id='MotorHorario' value='↑'>"
         "<div class='Controles2'>"
        "<input type='button' class='botones' id='MotorVuelta1' value='←'>"
        "<input type='button' class='botones' id='MotorStop' value='‖'>"
        "<input type='button' class='botones' id='MotorVuelta2' value='→'>"
        "</div>"
         
        "<input type='button' class='botones' id='MotorAntihorario' value='↓'>"
        
     "</div>"
        "<div class='estadisticas'>"
        "<div class='tabla'>"
            "<h1 id='a'>Estadisticas de Velocidad</h1>"
            "<canvas id='myChart' width='600'></canvas>"
            "</div>"
        "<div class='atributo'>"
            "<h1>Temperatura</h1>"
            "<div class='Contenedorpe'>"
            "<h2>38°C</h2></div>"
            "</div>"
        "</div>"
        
       "<footer class='footer'>"
      "<div class='contenedor'>"
        "<div class='social'>"
          "<a href='#' class='icon-facebook'></a>"
          "<a href='#' class='icon-twitter'></a>"
          "</div>" 
        "</div>"
      
    "</footer>"
        "<script src='js/menu.js'></script>"
    "</body>"
    "<!--Script para grafico-->"
    "<script>"
        "var ctx = document.getElementById('myChart').getContext('2d');"
        "var myChart = new Chart(ctx, {"
        "type: 'line',"
        "data: {"
            "//labels: ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange'],"
            "labels: ['', '', '', '', '', '', '', '', '', ''],"
            "datasets: [{"
                "label: 'Velocidad',"
                "data: [12, 19, 31, 53, 33, 21,13,75,23,43],"
               " backgroundColor: ["
                   " 'rgb(119, 27, 245)'"
              "  ],"
                "borderColor: ["
                    "'rgb(119, 27, 245)'"
               " ],"
               " borderWidth: 1"
            "}]"
       " },"
        "options: {"
            "scales: {"
               " yAxes: [{"
                  "  ticks: {"
                       " beginAtZero: true"
                  "  }"
               " }]"
            "}"
        "}"
   " });"
    "</script>"
"</html>";


//---------------------------SETUP--------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("");
  pinMode(PinIN1, OUTPUT);
  pinMode(PinIN2, OUTPUT);
  pinMode(PinIN3, OUTPUT);
  pinMode(PinIN4, OUTPUT); 

  // Conexión WIFI
  WiFi.begin(ssid, password);
  //Cuenta hasta 50 si no se puede conectar lo cancela
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { 
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
      server.begin(); // iniciamos el servidor
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
}

//----------------------------LOOP----------------------------------

void loop(){
  WiFiClient client = server.available();   // Escucha a los clientes entrantes

  if (client) {                             // Si se conecta un nuevo cliente
    Serial.println("New Client.");          // 
    String currentLine = "";                //
    while (client.connected()) {            // loop mientras el cliente está conectado
      if (client.available()) {             // si hay bytes para leer desde el cliente
        char c = client.read();             // lee un byte
        Serial.write(c);                    // imprime ese byte en el monitor serial
        header += c;
        if (c == '\n') {                    // si el byte es un caracter de salto de linea
          // si la nueva linea está en blanco significa que es el fin del 
          // HTTP request del cliente, entonces respondemos:
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // enciende y apaga el GPIO
            if (header.indexOf("GET /MotorHorario") >= 0) 
            {
              Serial.println("MotorHorario");
              MotorHorario();
            } 
            else if (header.indexOf("GET /MotorAntihorario") >= 0)
            {
              Serial.println("MotorAntihorario");
              MotorAntihorario();
            }
            else if (header.indexOf("GET /MotorVuelta1") >= 0)
            {
              Serial.println("MotorVuelta1");
              MotorVuelta1();
            }
            else if (header.indexOf("GET /MotorVuelta2") >= 0)
            {
              Serial.println("MotorVuelta2");
              MotorVuelta2();
            }
            else if (header.indexOf("GET /MotorStop") >= 0)
            {
              Serial.println("MotorStop");
               MotorStop();
            }
            
            // Muestra la página web
            client.println(pagina);
            
            // la respuesta HTTP temina con una linea en blanco
            client.println();
            break;
          } else { // si tenemos una nueva linea limpiamos currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // si C es distinto al caracter de retorno de carro
          currentLine += c;      // lo agrega al final de currentLine
        }
      }
    }
    // Limpiamos la variable header
    header = "";
    // Cerramos la conexión
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
//------------------Metodos del motor---------------------
void MotorHorario()
{
  digitalWrite (PinIN1, HIGH);
  digitalWrite (PinIN2, LOW);
  digitalWrite (PinIN4, HIGH);
  digitalWrite (PinIN3, LOW);
}
void MotorAntihorario()
{
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, HIGH);
  digitalWrite (PinIN4, LOW);
  digitalWrite (PinIN3, HIGH);
}
void MotorVuelta1(){
  digitalWrite (PinIN1, HIGH);
  digitalWrite (PinIN2, LOW);
  digitalWrite (PinIN4, LOW);
  digitalWrite (PinIN3, HIGH);
}
void MotorVuelta2(){
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, HIGH);
  digitalWrite (PinIN4, HIGH);
  digitalWrite (PinIN3, LOW);
}
void MotorStop()
{
  digitalWrite (PinIN1, LOW);
  digitalWrite (PinIN2, LOW);
  digitalWrite (PinIN3, LOW);
  digitalWrite (PinIN4, LOW);
}
