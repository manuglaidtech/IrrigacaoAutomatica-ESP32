 Sistema Inteligente de Irrigação com ESP32 e MQTT
Este projeto propõe um sistema de irrigação automatizado e sustentável que utiliza a plataforma ESP32, sensores de umidade do solo e comunicação via protocolo MQTT. A proposta visa combater o desperdício de água na agricultura, alinhando-se ao Objetivo de Desenvolvimento Sustentável 6 (ODS 6) da ONU.

📌 Objetivo
Desenvolver uma solução de irrigação inteligente que:

Monitore a umidade do solo em tempo real;

Acione automaticamente a irrigação quando necessário;

Permita o monitoramento remoto via MQTT;

Seja validada por meio de simulação no ambiente Wokwi.

Componentes Utilizados
Componente	Função	Pino no ESP32
ESP32	Microcontrolador principal	—
Sensor de Umidade	Detecta umidade do solo	GPIO 34
Módulo Relé	Aciona bomba de irrigação	GPIO 26
Buzzer	Emite alertas sonoros	GPIO 27
LED	Indica o status do sistema	GPIO 25
Potenciômetro	Simula e calibra umidade	GPIO 32
Resistor 220Ω	Protege o LED	—
Jumpers/Protoboard	Conexões	—

Ferramentas e Tecnologias
ESP32 (Wi-Fi + Bluetooth)

Wokwi (simulação virtual)

Fritzing (modelagem visual do circuito)

Arduino IDE (linguagem C++)

Bibliotecas: WiFi.h, PubSubClient.h

Funcionamento
O ESP32 conecta-se à rede Wi-Fi e ao broker MQTT.

O potenciômetro simula a umidade do solo.

O sistema compara a leitura com um limite pré-definido.

Se a umidade estiver baixa:

O relé é acionado e liga a bomba de irrigação.

LED e buzzer indicam o status do sistema.

Os dados são enviados ao broker MQTT.

O ciclo se repete periodicamente para monitoramento contínuo.

Fluxo de Funcionamento
mermaid
Copiar
Editar
graph TD
A[Início] --> B[Conectar Wi-Fi e MQTT]
B --> C[Verificar Umidade do Solo]
C -->|Abaixo do Limite| D[Ativar Relé + LED + Buzzer]
C -->|Acima do Limite| E[Manter Sistema Inativo]
D --> F[Enviar Dados via MQTT]
E --> F
F --> G[Esperar e Repetir Ciclo]
🔧 Instruções de Simulação no Wokwi
Acesse: https://wokwi.com/

Importe ou recrie o circuito baseado na montagem apresentada no artigo.

Faça upload do código na IDE online.

Acompanhe o comportamento dos sensores e atuadores em tempo real.

📚 Referências
ONU ODS 6: https://brasil.un.org/pt-br/sdgs

Espressif (ESP32): https://www.espressif.com

Wokwi: https://wokwi.com/

Fritzing: https://fritzing.org

Futuras Melhorias
Inclusão de sensores de temperatura e luminosidade;

Integração com nuvem (dashboard);

Criação de aplicativo móvel para controle remoto;

Sistema de alertas automatizados por notificação.
