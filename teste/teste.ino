#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>


const char* ssid = "Gih";
const char* password = "gizinha01";

const char* serverName = "https://jsonplaceholder.typicode.com/todos/1" ;

void setup(){
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConectado com sucesso!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED){
    WiFiClientSecure *client = new WiFiClientSecure;
  
  if(client) {
    client->setInsecure();

    HTTPClient https;
    Serial.print("[HTTPS] Iniciando requisição...\n");

  
  if(https.begin(*client, serverName)) {
    int httpCode = https.GET();

    if(httpCode > 0){
      Serial.printf("[HTTPS] Código de resposta: %d\n", httpCode);

      if(httpCode == HTTP_CODE_OK){
        String payload = https.getString();
        Serial.println("Conteúdo recebido:");
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTPS] Falha na requisição, erro: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  } else {
    Serial.printf("[HTTPS] Não foi possível conectar ao servidor\n");
  }
   delete client;
  }
}
 delay(10000);
 }
  









