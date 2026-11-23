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

  lerSensor();
  procuraErro();
  calcValorMedia();

}

void SensorNivel::lerSensor(){
#ifdef SENSOR_SIMULADO
  // Sem o sensor ultrassônico conectado: gera uma senoide em vez de chamar pulseIn()
  // (que ficaria bloqueado aguardando o eco).
  _valor = _simulador.valor(millis());
  return;
#endif

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
  _valor = distanceCm;
}


void SensorNivel::procuraErro(){
  if(_valor > 210 || _valor == 0){
    _sensorFalhou = true;
  }
  else{
    _sensorFalhou = false;
  }
}


void SensorNivel::calcValorMedia() {
  static unsigned int amostrasTotais = 0;  //variável para realizar o filtro de média
  static unsigned int amostrasValidas = 0; //variável para realizar o filtro de média
  static float acumulador = 0;       //variável para acumular a média

  //Realização de tratamento de erros
  if( _sensorFalhou == false ){
    float temp  = _valor;
    acumulador += temp; //somente os valores sem erro serão utilizados na média
    amostrasValidas++;  //incremento das amostras onde não foram encontradas erros
  }
  amostrasTotais++;  //incremento de amostras total

  //realização do calculo de média
  if (amostrasTotais >= JANELA_FILTRO){

    //se amostras válidas forem diferentes das amostras totais houve erro em alguma aquisição de dados
    if(amostrasTotais != amostrasValidas){
      if(amostrasValidas > 0){
        _valorMedia = acumulador/amostrasValidas;
      }
      else{ //Se amostras válidas for igual a 0 o valor será zero e o conjunto de dados inválidos
        _valorMedia = 0;
        _mediaInvalida = true;
      }
      
      _sensorFalhou = true;
    }
    else{ //todos os dados são válidos
      _valorMedia = acumulador/JANELA_FILTRO;
      _sensorFalhou  = false;
    }

    amostrasTotais = 0; 
    amostrasValidas = 0;
    acumulador = 0;
  }
}

// ---------------------------------------------------------------------------
// Estado e Home Assistant
// ---------------------------------------------------------------------------

void SensorNivel::montarMedicao(JsonDocument& doc) {
  //Medições publicadas em <base>/<nome>/medicao (o id é adicionado pela DispositivoBase)
  JsonArray medicoes = doc["measurements"].to<JsonArray>();
  JsonObject medicao1 = medicoes.add<JsonObject>();
  JsonObject medicao2 = medicoes.add<JsonObject>();
  medicao1["code"] = "nivel_agua",
  medicao1["data_type"] = "numeric";
  medicao1["value"] = _valor;
  medicao1["erro"] = _sensorFalhou;
  medicao1["measured_at"] = horarioEpoch();
  medicao2["code"] = "nivel_media",
  medicao2["data_type"] = "numeric";
  medicao2["value"] = _valorMedia;
  medicao2["erros"] = _mediaInvalida;
  medicao2["janel"] = JANELA_FILTRO;
  medicao2["measured_at"] = horarioEpoch();
}

