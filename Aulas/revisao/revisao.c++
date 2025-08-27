// Bibliotecas
#include<Servo.h>

// Definindo Variáveis
#define trigger 7
#define echo 8
#define ledG 6
#define ledY 5
#define ledR 4
#define servo_motor 3

// Objeto servo do tipo Servo (biblioteca reconhece como servo motor)
Servo servo;

void setup() {
  // Velocidade de resposta do arduíno
  Serial.begin(9600);

  // Anexar a variável ao objeto
  servo.attach(servo_motor);

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
  int dist = pulseIn(echo, HIGH);
  dist = dist / 58;

  Serial.println(dist);
  delay(2000);

  // Comparação para Leds
  if(dist < 50) {
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);

    servo.write(180);
  } else if(dist < 100) {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, HIGH);

    servo.write(0);
  } else {
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    digitalWrite(ledY, LOW);

    servo.write(0);
  }
}