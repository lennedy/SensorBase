#ifndef DADOS_MQTT_H
#define DADOS_MQTT_H

// Preencha com os dados do seu ambiente.
// Dica: não envie este arquivo preenchido para o Git.

#define SSD_WIFI            ""
#define SENHA_WIFI          ""

#define ENDERECO_IP_BROKER  ""
#define PORTA_BROKER        1883
#define LOGIN_BROKER        ""
#define SENHA_BROKER        ""

#define NOME_CLIENTE        ""   // único por dispositivo, ex.: "fechadura-sala-01"
#define NOME_TOPICO         ""   // tópico base, ex.: "campus/portas"

// Prefixo das URLs aceitas no comando "UPDATE <url>" (OTA por HTTP).
// Deixe vazio para desativar. Ex.: "http://192.168.0.10:8000/firmware/"
#define URL_FIRMWARE_PERMITIDA ""

#endif
