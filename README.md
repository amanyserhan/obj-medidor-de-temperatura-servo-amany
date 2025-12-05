# 🌡️ Monitoramento Térmico IoT com Atuação Ativa (ODS 3)

Este projeto utiliza um **ESP32**, um sensor **DHT22**, LEDs de indicação, um **buzzer** e um **Servo Motor** para criar um sistema completo de monitoramento de estresse térmico ocupacional.

O diferencial deste projeto é o foco na **ODS 3 (Saúde e Bem-Estar)**: o sistema não apenas monitora, mas possui **atuação ativa**. Ao detectar calor excessivo, ele aciona automaticamente o Servo Motor (simulando um umidificador ou ventilação) para mitigar o risco à saúde.

![Protótipo](imagens/prototipo.png)

---

## 📦 Estrutura do Projeto

```text
monitor-termico-iot/
│── sketch.ino       # Código fonte (Firmware)
│── diagram.json     # Arquivo de diagrama do Wokwi
│── libraries.txt    # Lista de bibliotecas necessárias
│── README.md        # Documentação do projeto
