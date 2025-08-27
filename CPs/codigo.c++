// Bibliotecas
#include<ArduinoJson.h>
#include<Servo.h>

// Definindo Variáveis
#define trigger 7
#define echo 8

#define servo_motor 3

// Objeto servo do tipo Servo (biblioteca reconhece como servo motor)
Servo servo;
int dist = 0;

void setup() {
  // Velocidade de resposta do arduíno
  Serial.begin(9600);

  // Anexar a variável ao objeto
  servo.attach(servo_motor);

  // Definindo Entradas e Saídas
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // Disparar o trigger, para pegar o valor do ultrassônico
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Armazenar o valor do echo
  dist = pulseIn(echo, HIGH);
  dist = dist / 58; // Transformar em cm

  StaticJsonDocument<100>json;

  // Definindo o nome para o valor dist   
  json["Distância"] = dist;

  // Serializar o json
  serializeJson(json, Serial);
  Serial.println();
  delay(200);

  // Comparação para servo motor
  if(Serial.available() > 0) {
    // Comando = input do usuário
    char comando = Serial.read();

    if (comando == 'g') {
        servo.write(180);
    } else if (comando == 'p') {
        servo.write(0);
    } 
  }
}