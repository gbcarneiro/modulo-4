#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFi.h>

#include <stdio.h>
#include <String>

const char* SSIDS = "Inteli-COLLEGE";
const char* PWD = "QazWsx@123";


char * mensagem; 

char converter(char ch, int chave) {
  if (!isalpha(ch)) return ch;
  char offset = isupper(ch) ? 'A' : 'a';
  return (char)((((ch + chave) - offset) % 26) + offset);
}

String criptografar(String entrada, int chave) {
  String saida = "";
  size_t len = entrada.length();
  for (size_t i = 0; i < len; i++)
    saida += converter(entrada[i], chave);
  return saida;
}

void postDataToServer() {
 
  Serial.println("Posting JSON data to server...");
  String mensagem_cripto = criptografar("Eu Odeio o ESP", 11);
  // Block until we are able to connect to the WiFi access point
  HTTPClient http;   
     
    http.begin("https://ur524n-3000.preview.csb.app/teobaldo");  
    http.addHeader("Content-Type", "application/json");         
     
    StaticJsonDocument<200> doc;
    // Add values in the document
    //
    doc["nome"] = "Gabriel Elias Carneiro";
    doc["turma"] = 1;
    doc["grupo"] = 1; 
    doc["mensagem_texto"] = "Eu Odeio o ESP"; 
    doc["mensagem_cripto"] = mensagem_cripto;

     // Add an array.
    //
    JsonArray data = doc.createNestedArray("data");
    
     
    String requestBody;
    serializeJson(doc, requestBody);
     
    int httpResponseCode = http.POST(requestBody);
 
    if(httpResponseCode>0){
       
      String response = http.getString();                       
       
      Serial.println(httpResponseCode);   
      Serial.println(response);
     
    }
     
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(SSIDS, PWD);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  postDataToServer();
  delay(8000);
}
