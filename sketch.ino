#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ESP32Servo.h>

// --- Configurações de Pinos ---
#define DHTPIN 15       // Pino do Sensor DHT22
#define SERVOPIN 13     // Pino do Servo Motor
#define LED_VERMELHO 5  // LED de Perigo (Calor)
#define LED_AMARELO 2   // LED de Atenção (Frio)
#define BUZZERPIN 25    // Buzzer

// --- Configurações do Sensor e Servo ---
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
Servo umidificador; 

// --- Configurações de Wi-Fi e MQTT ---
const char* ssid = "Wokwi-GUEST"; 
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  // Inicializa componentes
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  
  dht.begin();
  umidificador.attach(SERVOPIN);
  umidificador.write(0); // Começa desligado

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando em ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("Mackenzie_Amany_ProjetoFinal")) { 
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // 1. Ler Sensor
  float temp = dht.readTemperature(); 
  float hum = dht.readHumidity();     
  
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Falha no DHT!");
    return;
  }

  // 2. Calcular Sensação Térmica
  float hic = dht.computeHeatIndex(temp, hum, false);

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" | Umid: "); Serial.print(hum);
  Serial.print(" | Sensacao: "); Serial.println(hic);

  // 3. Publicar no MQTT (Organizado na pasta 'clima')
  char msg[10];
  
  // Temperatura
  sprintf(msg, "%.2f", temp);
  client.publish("mackenzie/amany/clima/temperatura", msg);
  
  // Umidade (NOVO!)
  sprintf(msg, "%.2f", hum);
  client.publish("mackenzie/amany/clima/umidade", msg);

  // Sensação Térmica
  sprintf(msg, "%.2f", hic);
  client.publish("mackenzie/amany/clima/sensacao", msg);
  
  // --- LÓGICA DE ATUAÇÃO ---
  if (temp > 30.0) {
    // CALOR
    digitalWrite(LED_VERMELHO, HIGH); 
    digitalWrite(LED_AMARELO, LOW);
    tone(BUZZERPIN, 1000); // Som agudo
    umidificador.write(90); // Servo liga
    
    client.publish("mackenzie/amany/clima/status", "PERIGO - Calor");
  } 
  else if (temp < 16.0) {
    // FRIO
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, HIGH); 
    tone(BUZZERPIN, 500); // Som grave
    umidificador.write(0); 
    
    client.publish("mackenzie/amany/clima/status", "ATENCAO - Frio");
  } 
  else {
    // NORMAL
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    noTone(BUZZERPIN);
    umidificador.write(0); 
    
    client.publish("mackenzie/amany/clima/status", "NORMAL");
  }

  delay(2000); 
}
