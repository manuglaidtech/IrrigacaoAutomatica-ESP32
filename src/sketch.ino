//Projeto Irrigação Automática - Umidade de solo
//Aplicando Aula 04 - Objetos Inteligentes Conectados
//Emanuelle Lima /MCKZ RA: 10415449
//Data: 25.05.2025 

#include <WiFi.h>
#include <PubSubClient.h>

// Pinos definidos conforme sua ligação
#define PIN_POTENCIOMETRO 32  // Potenciômetro
#define PIN_RELE 26           // Módulo relé
#define PIN_LED 25            // LED indicador
#define PIN_BUZZER 27         // Buzzer
#define PIN_SENSORDI 34       // Sensor de umidade (analogico)

// Limite de umidade abaixo do qual irrigar (ajuste conforme necessário)
#define LIMIAR_UMIDADE 2000

// Configurações WiFi e MQTT
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// Variável para armazenar o valor do sensor
int umidade;

void setup() {
  Serial.begin(115200);

  // Configuração dos pinos
  pinMode(PIN_RELE, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_SENSORDI, INPUT);

  // Inicializa os dispositivos
  digitalWrite(PIN_RELE, LOW);
  digitalWrite(PIN_LED, LOW);
  noTone(PIN_BUZZER);

  // Conecta ao WiFi
  conectarWiFi();

  // Configura o MQTT
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura do sensor de umidade (potenciômetro simulado)
  umidade = analogRead(PIN_SENSORDI);
  Serial.print("Umidade do solo: ");
  Serial.println(umidade);

  if (umidade < LIMIAR_UMIDADE) {
    // Solo seco, aciona irrigação
    Serial.println("⚠️ Umidade baixa! Acionando irrigação.");
    digitalWrite(PIN_RELE, HIGH);
    digitalWrite(PIN_LED, HIGH);
    tone(PIN_BUZZER, 1000); // tom de 1kHz
  } else {
    // Solo úmido, desliga irrigação
    Serial.println("✅ Umidade suficiente. Irrigação desativada.");
    digitalWrite(PIN_RELE, LOW);
    digitalWrite(PIN_LED, LOW);
    noTone(PIN_BUZZER);
  }

  // Publica no MQTT
  char msg[50];
  snprintf(msg, 50, "Umidade: %d", umidade);
  client.publish("irrigacao/umidade", msg);

  delay(2000);
}

void conectarWiFi() {
  Serial.print("Conectando ao WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println(" Conectado!");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}
