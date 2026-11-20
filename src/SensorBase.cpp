#include "SensorBase.h"

SensorBase::SensorBase(const ConfigDispositivo& config, const PinosSinalizacao& pinos)
    : DispositivoBase(config, pinos) {}

// ---------------------------------------------------------------------------
// Hardware
// ---------------------------------------------------------------------------

void SensorBase::aoIniciar() {
  // pinMode(_pinAcionamento, OUTPUT);
  // digitalWrite(_pinAcionamento, LOW);
  // pinMode(_pinReset, OUTPUT);
  // digitalWrite(_pinReset, HIGH);

  // iniciarPN532();
}


// ---------------------------------------------------------------------------
// Atuador
// ---------------------------------------------------------------------------

void SensorBase::atuador(const String& payload) {
  //A pricípio não há atuador no sensor
}

// ---------------------------------------------------------------------------
// Sensor
// ---------------------------------------------------------------------------

void SensorBase::sensor() {
  //Aqui deve ficar o código que realizará a leitura do sensor
}

// ---------------------------------------------------------------------------
// Estado e Home Assistant
// ---------------------------------------------------------------------------

void SensorBase::montarEstado(JsonDocument& doc) {
  //Aque está sendo colocado os dados que serão reptidamente enviados ao broker
  doc["valorSensor"] = "LOCKED";
  doc["SaudeSensor"] = true;
}

