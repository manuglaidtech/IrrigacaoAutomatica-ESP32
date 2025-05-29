//Projeto Irrigação Automática - Umidade de solo
//Aplicando Aula 04 - Objetos Inteligentes Conectados
//Emanuelle Lima /MCKZ RA: 10415449
//Data: 25.05.2025 

#include <WiFi.h>
#include <PubSubClient.h>

// Configurações de hardware
#define PIN_POTENCIOMETRO 32
#define PIN_RELE 26
#define PIN_LED 25
#define PIN_BUZZER 27
#define PIN_SENSORDI 34
#define LIMIAR_UMIDADE 2000

// Configurações de rede
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com"; // Broker público

WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis globais
int umidade;
unsigned long lastMsgTime = 0;

void setup() {
  Serial.begin(115200);
  
  // Configuração dos pinos
  pinMode(PIN_RELE, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_SENSORDI, INPUT);
  
  digitalWrite(PIN_RELE, LOW);
  digitalWrite(PIN_LED, LOW);
  noTone(PIN_BUZZER);

  conectarWiFi();
  client.setServer(mqtt_server, 1883); // Porta TCP padrão MQTT
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Publica a cada 2 segundos
  if (millis() - lastMsgTime > 2000) {
    lastMsgTime = millis();
    
    umidade = analogRead(PIN_SENSORDI);
    Serial.print("Umidade: ");
    Serial.println(umidade);

    // Controle da irrigação
    if (umidade < LIMIAR_UMIDADE) {
      ativarIrrigacao();
    } else {
      desativarIrrigacao();
    }

    // Publica no MQTT (formato JSON)
    char msg[50];
    snprintf(msg, 50, "{\"umidade\":%d,\"status\":\"%s\"}", 
             umidade, 
             (umidade < LIMIAR_UMIDADE) ? "IRRIGANDO" : "DESLIGADO");
             
    if (client.publish("emanuelle/umidade", msg)) {
      Serial.println("Mensagem publicada!");
    } else {
      Serial.println("Falha ao publicar");
    }
  }
}

// Função chamada quando chega mensagem MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void conectarWiFi() {
  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    
    // Gera um ClientID único
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado!");
      client.subscribe("emanuelle/controle"); // Tópico para comandos
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5s...");
      delay(5000);
    }
  }
}

void ativarIrrigacao() {
  digitalWrite(PIN_RELE, HIGH);
  digitalWrite(PIN_LED, HIGH);
  tone(PIN_BUZZER, 1000, 200); // Bip curto
  Serial.println("Irrigação ATIVADA");
}

void desativarIrrigacao() {
  digitalWrite(PIN_RELE, LOW);
  digitalWrite(PIN_LED, LOW);
  noTone(PIN_BUZZER);
  Serial.println("Irrigação DESATIVADA");
}