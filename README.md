# Sensor de NPK com Arduino

Este projeto utiliza um sensor de NPK com comunicação RS485 para medir os níveis de nitrogênio, fósforo e potássio no solo. Os valores obtidos são exibidos em um display LCD 16x2 e enviados ao monitor serial para visualização.

## Componentes Utilizados

- Arduino Uno
- Display LCD 16x2
- Sensor NPK (RS485)
- Conversor RS485 para TTL
- Módulo de Comunicação RS485
- Jumpers e Protoboard

## Pinos Utilizados

- **Display LCD 16x2:**
  - RS no pino 12
  - E no pino 11
  - D4 no pino 10
  - D5 no pino 9
  - D6 no pino 6
  - D7 no pino 5
- **RS485:**
  - RE no pino 8
  - DE no pino 7
  - RX no pino 2
  - TX no pino 3

## Funcionamento

O código lê os valores de nitrogênio, fósforo e potássio do sensor NPK usando a comunicação RS485. Esses valores são exibidos em um display LCD 16x2 e enviados ao monitor serial. A comunicação com o sensor é feita enviando comandos modbus, e o Arduino espera receber os dados de volta, que são decodificados para exibição.

## Bibliotecas Necessárias

- `LiquidCrystal` para controlar o display LCD.
- `SoftwareSerial` para criar uma comunicação serial com o módulo RS485.

## Instruções

1. Conecte todos os componentes conforme descrito.
2. Carregue o código no Arduino.
3. Observe os valores de nitrogênio, fósforo e potássio no display LCD e no monitor serial.
