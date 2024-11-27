#include <WiFi.h>              // Biblioteca para conexão Wi-Fi
#include <PubSubClient.h>      // Biblioteca para comunicação MQTT

// Definições de pinos
#define LED_PIN 15             // Pino conectado ao LED

// Configurações de Wi-Fi
const char* ssid = "Wokwi-GUEST";  // Nome da rede Wi-Fi para o Wokwi
const char* password = "";         // Sem senha para Wokwi

// Configurações do MQTT
const char* mqtt_server = "broker.hivemq.com";  // Broker MQTT público HiveMQ
const int mqtt_port = 1883;
const char* topic_temperature = "projeto/temperatura";
const char* topic_humidity = "projeto/umidade";
const char* topic_command = "projeto/comando";

// Inicialização dos objetos Wi-Fi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis para armazenar os dados recebidos
float temperature = NAN;
float humidity = NAN;

// Função para conectar ao Wi-Fi
void setup_wifi() {
  Serial.begin(115200); // Inicializa a comunicação serial
  Serial.println();
  Serial.print("Conectando-se ao Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // Inicia a conexão Wi-Fi

  // Aguarda até que a conexão seja estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

// Callback para processar mensagens MQTT
void callback(char* topic, byte* message, unsigned int length) {
  String msg;

  // Converte a mensagem recebida para String
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)message[i];
  }

  // Verifica o tópico e processa os dados
  if (String(topic) == topic_temperature) {
    temperature = msg.toFloat();
    Serial.print("Temperatura recebida: ");
    Serial.println(temperature);
  } else if (String(topic) == topic_humidity) {
    humidity = msg.toFloat();
    Serial.print("Umidade recebida: ");
    Serial.println(humidity);
  } else if (String(topic) == topic_command) {
    Serial.print("Comando recebido: ");
    Serial.println(msg);

    if (msg.equalsIgnoreCase("ligar")) {
      digitalWrite(LED_PIN, HIGH);        // Liga o LED
      Serial.println("LED ligado");
    } else if (msg.equalsIgnoreCase("desligar")) {
      digitalWrite(LED_PIN, LOW);         // Desliga o LED
      Serial.println("LED desligado");
    } else {
      Serial.println("Comando desconhecido");
    }
  }
}

// Função para conectar ao broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    String clientId = "ESP32Client_";
    clientId += String(random(0xffff), HEX); // Gera um ID de cliente único

    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado ao MQTT");
      // Assina os tópicos relevantes
      client.subscribe(topic_temperature);
      client.subscribe(topic_humidity);
      client.subscribe(topic_command);
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  // Inicializa o pino do LED como saída e o mantém desligado
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Conecta ao Wi-Fi
  setup_wifi();

  // Configura o broker MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Mensagem inicial no Serial Monitor
  Serial.println("Sistema inicializado. Aguardando dados via MQTT...");
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Mantém a conexão MQTT ativa

  // Verifica se os dados de temperatura foram recebidos
  if (!isnan(temperature)) {
    // Lógica para acionar o LED com base na temperatura
    if (temperature > 38.0) { // Exemplo: liga o LED se a temperatura for maior que 38°C
      digitalWrite(LED_PIN, HIGH); // Liga o LED
      Serial.println("ALERTA: Temperatura alta! LED ligado.");
    } else {
      digitalWrite(LED_PIN, LOW); // Desliga o LED
      Serial.println("Temperatura normal. LED desligado.");
    }

    // Reseta o valor da temperatura para evitar reprocessamento
    temperature = NAN;
  }

  delay(100); // Pequeno atraso para evitar uso excessivo do loop
}
