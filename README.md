# 🌡️ Monitoramento de Temperatura com ESP32 + MQTT + Atuação Ativa (ODS 3)

Este projeto utiliza um **ESP32**, um sensor **DHT22**, LEDs, **buzzer** e um **Servo Motor** para criar um sistema inteligente de monitoramento de estresse térmico.

O grande diferencial deste projeto é o foco na **ODS 3 (Saúde e Bem-Estar)**. O sistema não olha apenas a temperatura, mas calcula a **Sensação Térmica** (usando a umidade) e **atua fisicamente** no ambiente: ao detectar calor excessivo, ele liga o Servo Motor (simulando um umidificador/ventilador) para proteger a saúde das pessoas.

![Protótipo](imagens/prototipo.jpg)

---

## 📦 Estrutura do Projeto

```text
projeto-temperatura-esp32/
│── sketch.ino       # Código C++ (Firmware)
│── diagram.json     # Circuito para o Wokwi
│── libraries.txt    # Lista de bibliotecas
│── README.md        # Documentação técnica
