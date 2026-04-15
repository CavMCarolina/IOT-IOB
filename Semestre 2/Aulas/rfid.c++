#include<SPI.h>
#include<MFRC522.h>

#define pino_sda 10
#define pino_rst 9
#define pino_red 8
#define pino_green 7

// Criando o objeto
MFRC522 leitor(pino_sda, pino_rst);

// Controle de acesso
String tagAutorizada = "41 CA 4B 73";

void setup() {
  Serial.begin(9600);
  SPI.begin();
  leitor.PCD_Init();
  Serial.println("Aproxime o cartao...");

  // Configurar pinos
  pinMode(pino_red, OUTPUT);
  pinMode(pino_green, OUTPUT);
}

void loop() {
  if(!leitor.PICC_IsNewCardPresent()) return;
  if(!leitor.PICC_ReadCardSerial()) return;

  Serial.print("UID: ");

  String uid = "";

  // leitor.uid.size = quantidade de bytes da tag/cartao
  // converte cada byte para hexadecimal e printa
  for(byte i = 0; i < leitor.uid.size; i++) {
    uid += String(leitor.uid.uidByte[i], HEX);

    // adicionar espaço caso não seja o último byte
    if (i < leitor.uid.size - 1) uid += " ";
  }
  
  uid.toUpperCase();
  Serial.println(uid);

  // Autorização
  if (uid == tagAutorizada) {
    Serial.println("Autorizado! :)");
    digitalWrite(pino_green, HIGH);
    digitalWrite(pino_red, LOW);
  } else {
    Serial.println("Negado! :(");
    digitalWrite(pino_green, LOW);
    digitalWrite(pino_red, HIGH);
  }

  // Esperar próximo cartão
  Serial.println();
  delay(1000);
}
