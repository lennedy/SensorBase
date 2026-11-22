#include "SensorNivel.h"

SensorNivel::SensorNivel(const ConfigDispositivo& config, const PinosSinalizacao& pinos)
    : DispositivoBase(config, pinos) {}

// ---------------------------------------------------------------------------
// Hardware
// ---------------------------------------------------------------------------

void SensorNivel::aoIniciar() {
  pinMode(TRIG_PIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT); // Sets the echoPin as an Input

}


// ---------------------------------------------------------------------------
// Atuador
// ---------------------------------------------------------------------------

void SensorNivel::atuador(const String& payload) {
  //A pricípio não há atuador no sensor
}

// ---------------------------------------------------------------------------
// Sensor
// ---------------------------------------------------------------------------

void SensorNivel::sensor() {
  //Aqui deve ficar o código que realizará a leitura do sensor
  const float SOUND_VELOCITY = 0.034;
  const float CM_TO_INCH     = 0.393701;

  long duration;
  float distanceCm;

  // Clears the trigPin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;

}

// ---------------------------------------------------------------------------
// Estado e Home Assistant
// ---------------------------------------------------------------------------

void SensorNivel::montarEstado(JsonDocument& doc) {
  //Aque está sendo colocado os dados que serão reptidamente enviados ao broker
  JsonArray medicoes = doc["measurements"].to<JsonArray>();
  JsonObject medicao = medicoes.add<JsonObject>();
  medicao["code"] = "nivel_agua",
  medicao["data_type"] = "numeric";
  medicao["value"] = _ultimaLeitura;
  medicao["measured_at"] = "2026-11-17T16:30:00Z";
}

