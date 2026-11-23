#ifndef SENSOR_NIVEL_H
#define SENSOR_NIVEL_H

#include <DispositivoBase.h>
#include <Wire.h>

#define TRIG_PIN 12
#define ECHO_PIN 14

#define JANELA_FILTRO 10         // Número de amostras do filtro para realizar a média

/**
 * Fechadura com leitor NFC/RFID PN532 (I2C).
 *
 *  - atuador(): "UNLOCK" aciona a fechadura; qualquer outro comando é negado.
 *  - sensor():  lê o UID da chave e publica em <base>/acesso.
 */
class SensorNivel : public DispositivoBase {
 public:
  SensorNivel(const ConfigDispositivo& config,
               const PinosSinalizacao& pinos = PinosSinalizacao());

 protected:
  void atuador(const String& payload) override;
  void sensor() override;

  void aoIniciar() override;
  void montarMedicao(JsonDocument& doc) override;

 private:

  bool _sensorFalhou = true;
  bool _temLeitura = false;
  uint32_t _ultimaLeitura = 0;
  float _valor=0;
  float _valorMedia=0;
  float _mediaInvalida = false;

  static const uint32_t kIntervaloEntreLeituras = 5000;  // ms entre duas leituras válidas
  // static const uint32_t kTempoAcionamento = 500;         // ms de pulso na fechadura

  void lerSensor();
  void procuraErro();
  void calcValorMedia();
};

#endif
