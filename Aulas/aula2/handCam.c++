#include<Servo.h>
// cabos servo: marrom = gnd. vermelho = vcc. laranja/amarelo = porta

#define led 13
#define servo_motor 3

Servo servo;

void setup() {
  servo.attach(servo_motor);

  pinMode(led, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // Serial aberta para receber código do Python
  if(Serial.available() > 0) {
    char comando = Serial.read();
    if(comando == '1') {
      digitalWrite(led, HIGH);

      servo.write(180);
    } else if(comando == '2') {
      digitalWrite(led, LOW);

      servo.write(0);
    }
  }
}