# Projeto Objetos Inteligentes

![Banner do Projeto](https://i.imgur.com/qvQmnEu.png)

Este projeto simula a publicação de dados de temperatura e umidade via MQTT utilizando um script Python (`simulador_esp32.py`) e visualiza os dados em tempo real através do Node-RED Dashboard. Além disso, permite enviar comandos para ligar e desligar dispositivos simulados diretamente pelo dashboard.

## Índice

- [Visão Geral](#visão-geral)
- [Tecnologias Utilizadas](#tecnologias-utilizadas)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Pré-requisitos](#pré-requisitos)
- [Instalação](#instalação)
  - [1. Clonar o Repositório](#1-clonar-o-repositório)
  - [2. Configurar o Ambiente Python](#2-configurar-o-ambiente-python)
  - [3. Instalar Dependências Python](#3-instalar-dependências-python)
  - [4. Configurar o Node-RED](#4-configurar-o-node-red)
    - [4.1. Instalar o Node-RED](#41-instalar-o-node-red)
    - [4.2. Instalar o node-red-dashboard](#42-instalar-o-node-red-dashboard)
  - [5. Importar o Fluxo Node-RED](#5-importar-o-fluxo-node-red)
- [Uso](#uso)
  - [1. Executar o Script Python](#1-executar-o-script-python)
  - [2. Acessar o Dashboard do Node-RED](#2-acessar-o-dashboard-do-node-red)
  - [3. Interagir com o Sistema](#3-interagir-com-o-sistema)
- [Contribuição](#contribuição)
- [Licença](#licença)
- [Autor](#autor)

## Visão Geral

O **Projeto Objetos Inteligentes** é uma aplicação IoT que consiste em:

- **Simulação de Sensores**: Um script Python que publica dados de temperatura e umidade em tópicos MQTT.
- **Visualização em Tempo Real**: Utilização do Node-RED Dashboard para exibir gráficos dos dados recebidos.
- **Controle de Dispositivos**: Envio de comandos (`ligar` e `desligar`) através do dashboard, que são recebidos pelo script Python para simular ações de controle.

## Tecnologias Utilizadas

- **Python 3.7+**
- **Paho-MQTT**
- **Node.js**
- **Node-RED**
- **node-red-dashboard**
- **MQTT Broker**: [HiveMQ](https://www.hivemq.com/)

## Estrutura do Projeto

