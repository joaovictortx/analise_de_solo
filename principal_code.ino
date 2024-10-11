#include <LiquidCrystal.h>
#include "SoftwareSerial.h"

// Inicializa o display LCD nos pinos especificados
LiquidCrystal lcd(12, 11, 10, 9, 6, 5);  // RS, E, D4, D5, D6, D7

// Define os pinos de controle do RS485
#define RE 8  // Recepção
#define DE 7  // Transmissão

// Comandos Modbus para ler nitrogênio, fósforo e potássio
const byte nitro[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};  // Comando para Nitrogênio
const byte phos[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};  // Comando para Fósforo
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};  // Comando para Potássio

byte values[11];  // Armazena os valores recebidos do sensor
SoftwareSerial mod(2, 3); // RX no pino 2, TX no pino 3

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  mod.begin(4800);  // Inicializa a comunicação serial com o RS485
  pinMode(RE, OUTPUT);  // Configura pino de recepção como saída
  pinMode(DE, OUTPUT);  // Configura pino de transmissão como saída

  // Inicializa o LCD 16x2
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("NPK Sensor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(3000);  // Exibe uma mensagem de inicialização
}

void loop() {
  byte val1, val2, val3;

  // Lê o valor de Nitrogênio
  val1 = nitrogen();
  delay(250);  // Atraso para estabilidade

  // Lê o valor de Fósforo
  val2 = phosphorous();
  delay(250);

  // Lê o valor de Potássio
  val3 = potassium();
  delay(250);

  // Exibe os valores no Serial Monitor
  Serial.print("Nitrogen: ");
  Serial.print(val1);
  Serial.println(" mg/kg");

  Serial.print("Phosphorous: ");
  Serial.print(val2);
  Serial.println(" mg/kg");

  Serial.print("Potassium: ");
  Serial.print(val3);
  Serial.println(" mg/kg");

  // Exibe os valores no LCD 16x2
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("N: ");
  lcd.print(val1);
  lcd.print(" mg/kg");

  lcd.setCursor(0, 1);
  lcd.print("P: ");
  lcd.print(val2);
  lcd.print(" mg/kg");
  
  delay(2000);  // Tempo para exibição

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("K: ");
  lcd.print(val3);
  lcd.print(" mg/kg");

  delay(2000);
}

// Função para ler Nitrogênio
byte nitrogen() {
  digitalWrite(DE, HIGH);  // Ativa modo de transmissão
  digitalWrite(RE, HIGH);
  delay(10);
  
  // Envia o comando Modbus para ler Nitrogênio
  if (mod.write(nitro, sizeof(nitro)) == 8) {
    digitalWrite(DE, LOW);  // Ativa modo de recepção
    digitalWrite(RE, LOW);
    
    // Lê a resposta do sensor
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
      Serial.print(values[i], HEX);  // Exibe os valores no Serial Monitor
    }
    Serial.println();
  }
  return values[4];  // Retorna o valor de Nitrogênio
}

// Função para ler Fósforo
byte phosphorous() {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  
  // Envia o comando Modbus para ler Fósforo
  if (mod.write(phos, sizeof(phos)) == 8) {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    
    // Lê a resposta do sensor
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];  // Retorna o valor de Fósforo
}

// Função para ler Potássio
byte potassium() {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);
  
  // Envia o comando Modbus para ler Potássio
  if (mod.write(pota, sizeof(pota)) == 8) {
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    
    // Lê a resposta do sensor
    for (byte i = 0; i < 7; i++) {
      values[i] = mod.read();
      Serial.print(values[i], HEX);
    }
    Serial.println();
  }
  return values[4];  // Retorna o valor de Potássio
}
