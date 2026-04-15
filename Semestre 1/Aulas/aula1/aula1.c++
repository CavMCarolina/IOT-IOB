// Bibliotecas
#include<ArduinoJson.h>

// Definindo Variáveis
#define trigger 7
#define echo 8
#define ledG 6
#define ledY 5
#define ledR 4

int dist = 0;

void setup() {
  // Velocidade de resposta do arduíno
  Serial.begin(9600);

  // Definindo Entradas e Saídas
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledR, OUTPUT);
}

void loop() {
  // Disparar o trigger, para pegar o valor do ultrassônico
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Armazenar o valor do echo
  dist = pulseIn(echo, HIGH);
  dist = dist / 58; // Transformar em cm

  // Criando o doc JSON (definido como json) 
  // 100 = tamanho em bytes do documento json. Não tem problema colocar um valor alto, ele usa o mínimo
  StaticJsonDocument<100>json;

  // Definindo o nome para o valor dist 
  json["Distância"] = dist;

  // Serializar o json
  serializeJson(json, Serial);
  Serial.println();

  if(Serial.available() > 0) {
    // Comando = input do usuário
    char comando = Serial.read();

    if (comando == 'g') {
        digitalWrite(ledG, HIGH);
    } else if (comando == 'y') {
        digitalWrite(ledY, HIGH);
    } else if (comando == 'r') {
        digitalWrite(ledR, HIGH);
    }
  }
}