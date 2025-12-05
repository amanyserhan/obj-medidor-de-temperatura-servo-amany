# 🌡️ Monitoramento de Temperatura com ESP32 + DHT22 + MQTT + Servo

Este projeto utiliza um **ESP32**, um sensor **DHT22**, LEDs de indicação, um **buzzer** e um **Servo Motor** para criar um sistema completo de monitoramento de estresse térmico (ODS 3).  
As leituras são enviadas via **MQTT** e acompanhadas por alertas visuais e sonoros. Se o calor for excessivo, o sistema atua fisicamente ligando o servo.

![Protótipo](imagens/prototipo.jpg)

---

## 📦 Estrutura do Projeto

```text
projeto-temperatura-esp32/
│── sketch.ino
│── diagram.json
│── libraries.txt
│── README.md
