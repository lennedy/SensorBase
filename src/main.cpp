#include <Arduino.h>
#include "DadosMqtt_casa.h"
#include "SensorNivel.h"

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

  // OTA por HTTP — escolha um, os dois ou nenhum:
  // Cliente: o dispositivo baixa o .bin de um servidor ao receber "UPDATE <url>" via MQTT.
  cfg.otaHttp = false;
  cfg.otaUrlPermitida = URL_FIRMWARE_PERMITIDA;
  // Servidor: envie o .bin por upload em http://<ip-do-dispositivo>/update (usuário/senha abaixo).
  cfg.otaServidor = true;
  cfg.otaServidorSenha = SENHA_BROKER;

  cfg.ntpServidor1 = SERVIDOR_NTP;

  return cfg;
}

static PinosSinalizacao criarPinagem() {
  PinosSinalizacao pinos;

  pinos.rgbHabilitado=false;

  return pinos;
}

SensorNivel sensor(criarConfig(), criarPinagem());

void setup() {
  Serial.begin(115200);
  sensor.habilitarDepuracao(true);
  sensor.iniciar();
}

void loop() {
  sensor.loop();
}
