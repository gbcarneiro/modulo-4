//Importando as bibliotecas, ArduinoJSON precisa ser instalado
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

//Conectando ao WIFI
const char* SSID = "C3PO";
const char* PWD = "a1b2c3d4";

//Esta função irá conectar a rota GET criada, via HTTP, e a medida que o ganhador seja mandado para o servidor node o resultado será retornado na forma de string
String getDataFromServer() {
 
  Serial.println("Pegando dados do Servidor...");
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
    http.begin("http://192.168.1.106:3000/esp/resultado");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> res;
     
    int httpResponseCode = http.GET();
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
      deserializeJson(res, response);
    
      String resultado = res["ganhador"]; //Aqui são possiveis 3 tipos de retorno: X , O ou DEU EMPATE
      return resultado;
    }
     
}

void setup() {
  // put your setup code here, to run once:

  pinMode(16, OUTPUT); 
  pinMode(18, OUTPUT); 

  WiFi.begin(SSID, PWD); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Tentando novamente!");
    delay(500);
  }

  Serial.println("WiFi connected");
}

void loop() {
  // put your main code here, to run repeatedly:
  String resultado = getDataFromServer();

  //De acordo com o resultado, o led será ligado... Em caso de empate os dois leds ligam
  if (resultado == "X") {
    digitalWrite(16, HIGH);
  } else if (resultado == "O") {
    digitalWrite(18, HIGH); 
  } else if (resultado == "DEU EMPATE") {
    digitalWrite(18, HIGH); 
    digitalWrite(16, HIGH);
  } else {
    digitalWrite(18, LOW); 
    digitalWrite(16, LOW);
  }
}