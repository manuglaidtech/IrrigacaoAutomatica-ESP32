# Sistema de Irrigação Automática com ESP32

[![Simulador Wokwi](https://img.shields.io/badge/Simular-Wokwi-blue)](https://wokwi.com/projects/431979887661363201)

Projeto de IoT para controle de irrigação baseado na umidade do solo, desenvolvido para Objetos Inteligentes Conectados - Universidade Presbiteriana Mackenzie.

## 📸 Demonstração
| Solo Úmido | Solo Seco |
|------------|-----------|
| ![Solo Úmido](imagens/imagem_sol_úmido.jpg) | ![Solo Seco](imagens/imagem_Solo_Seco.jpg) |

## 🔌 Circuito
```plaintext
Sensor de Umidade → GPIO34
Potenciômetro → GPIO32 (ajuste manual)
Relé → GPIO26
LED → GPIO25
Buzzer → GPIO27
```

## 📚 Bibliotecas
- `PubSubClient` (MQTT)
- `WiFi` (conexão Wi-Fi)

## 🛠 Como Executar
1. Simule no [Wokwi](https://wokwi.com/projects/431979887661363201)
2. Clone o repositório:
   ```bash
   git clone https://github.com/manuglaidtech/IrrigacaoAutomatica-ESP32.git
   ```

## 📝 Licença
MIT License - Disponível para fins acadêmicos.
