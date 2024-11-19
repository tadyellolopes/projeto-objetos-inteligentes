import paho.mqtt.client as mqtt
import time
import random

# Configurações do MQTT
mqtt_broker = "broker.hivemq.com"
mqtt_port = 1883
topic_temperature = "projeto/temperatura"
topic_humidity = "projeto/umidade"
topic_command = "projeto/comando"

# Callback para conexão
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Conectado ao broker MQTT!")
        client.subscribe(topic_command)
    else:
        print(f"Falha na conexão, código de resultado: {rc}")

# Callback para mensagens recebidas
def on_message(client, userdata, msg):
    comando = msg.payload.decode()
    print(f"Comando recebido: {comando}")
    if comando.lower() == "ligar":
        print("Dispositivos ligados. (Simulação)")
    elif comando.lower() == "desligar":
        print("Dispositivos desligados. (Simulação)")
    else:
        print("Comando desconhecido.")

# Configurar o cliente MQTT
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(mqtt_broker, mqtt_port, 60)
client.loop_start()

try:
    while True:
        # Simular valores de sensores
        temperatura = round(random.uniform(20.0, 30.0), 2)
        umidade = round(random.uniform(40.0, 60.0), 2)

        # Publicar dados no MQTT
        client.publish(topic_temperature, temperatura)
        client.publish(topic_humidity, umidade)

        print(f"Temperatura publicada: {temperatura}°C")
        print(f"Umidade publicada: {umidade}%")

        time.sleep(5)  # Aguarda 5 segundos
except KeyboardInterrupt:
    print("Simulação interrompida.")
    client.loop_stop()
    client.disconnect()