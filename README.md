# Sistema de Irrigação Automática com ESP32

[![Simulador: Wokwi](https://img.shields.io/badge/Simulador-Wokwi-blue)](https://wokwi.com/projects/431979887661363201)  
[![Licença](https://img.shields.io/badge/Licença-MIT-green)](LICENSE)

Projeto IoT para controlar irrigação baseado na umidade do solo, usando ESP32 e MQTT.

## 🔌 Circuito
```plaintext
Sensor de Umidade → GPIO34  
Potenciômetro → GPIO32 (ajuste manual)  
Relé → GPIO26  
LED → GPIO25  
Buzzer → GPIO27
```

## 📚 Bibliotecas Necessárias
- `PubSubClient` (para MQTT)  
- `WiFi` (para conexão Wi-Fi)  

## 🚀 Como Usar
1. Simule no Wokwi: [![Abrir no Wokwi](https://img.shields.io/badge/Simular-Agora-success)](https://wokwi.com/projects/431979887661363201)  
2. Clone o repositório:  
   ```bash
   git clone https://github.com/manuglaidtech/IrrigacaoAutomatica-ESP32.git
   ```

## 📝 Licença
Código livre sob licença MIT. Use para estudos ou projetos pessoais!




