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

void SensorBase::montarMedicao(JsonDocument& doc) {
  //Medições publicadas em <base>/<nome>/medicao (o id é adicionado pela DispositivoBase)
  JsonArray medicoes = doc["measurements"].to<JsonArray>();
  JsonObject medicao = medicoes.add<JsonObject>();
  medicao["code"] = "nivel_agua",
  medicao["data_type"] = "numeric";
  medicao["value"] = 75.5;
  medicao["measured_at"] = "2026-11-17T16:30:00Z";
}

