#include <Arduino.h>
#include "DadosMqtt.h"
#include "SensorBase.h"

static ConfigDispositivo criarConfig() {
  ConfigDispositivo cfg;

  cfg.ssid = SSD_WIFI;
  cfg.senhaWifi = SENHA_WIFI;

  cfg.brokerHost = ENDERECO_IP_BROKER;
  cfg.brokerPorta = PORTA_BROKER;
  cfg.brokerUsuario = LOGIN_BROKER;
  cfg.brokerSenha = SENHA_BROKER;

  cfg.nomeCliente = NOME_CLIENTE;
  cfg.topicoBase = NOME_TOPICO;

  cfg.nomeHA = "Trancas das Portas";
  cfg.versaoSw = "1.0.0";

  // Leitura do NFC a cada 100 ms (a própria filha aplica o intervalo de 5 s entre chaves)
  cfg.intervaloSensorMs = 100;

  cfg.ota = true;
  cfg.senhaOta = SENHA_BROKER;

  return cfg;
}

SensorBase sensor(criarConfig());

void setup() {
  Serial.begin(115200);
  sensor.habilitarDepuracao(true);
  sensor.iniciar();
}

void loop() {
  sensor.loop();
}
