#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <DispositivoBase.h>
#include <Wire.h>

/**
 * Fechadura com leitor NFC/RFID PN532 (I2C).
 *
 *  - atuador(): "UNLOCK" aciona a fechadura; qualquer outro comando é negado.
 *  - sensor():  lê o UID da chave e publica em <base>/acesso.
 */
class SensorBase : public DispositivoBase {
 public:
  SensorBase(const ConfigDispositivo& config,
               const PinosSinalizacao& pinos = PinosSinalizacao());

 protected:
  void atuador(const String& payload) override;
  void sensor() override;

  void aoIniciar() override;
  void montarEstado(JsonDocument& doc) override;

 private:

  bool _pn532Falhou = true;
  bool _temLeitura = false;
  uint32_t _ultimaLeitura = 0;

  static const uint32_t kIntervaloEntreLeituras = 5000;  // ms entre duas leituras válidas
  static const uint32_t kTempoAcionamento = 500;         // ms de pulso na fechadura
};

#endif
