#ifndef SIMULADOR_SENOIDE_H
#define SIMULADOR_SENOIDE_H

#include <stdint.h>
#include <math.h>

/**
 * Gera valores simulados de um sensor, seguindo uma senoide no tempo:
 *
 *   valor(t) = media + amplitude * sin(2*pi * t / periodo + fase) + ruido
 *
 * Não depende de Arduino.h: o tempo (ms) é passado por quem chama, o que
 * permite testar a classe fora do ESP8266.
 */
class SimuladorSenoide {
 public:
  /**
   * @param media       valor central da onda (ex.: 105 cm)
   * @param amplitude   variação para cima e para baixo da média (ex.: 90 cm)
   * @param periodoMs   duração de um ciclo completo, em ms (ex.: 120000 = 2 min)
   * @param faseRad     deslocamento inicial da onda, em radianos
   * @param ruido       amplitude do ruído aleatório somado ao valor (0 = sem ruído)
   */
  SimuladorSenoide(float media = 50.0f, float amplitude = 25.0f, uint32_t periodoMs = 60000,
                   float faseRad = 0.0f, float ruido = 0.0f)
      : _media(media), _amplitude(amplitude), _periodoMs(periodoMs ? periodoMs : 1),
        _fase(faseRad), _ruido(ruido) {}

  /** Valor simulado no instante `agoraMs` (normalmente millis()). */
  float valor(uint32_t agoraMs) {
    // Usa só o resto da divisão para não perder precisão quando millis() cresce.
    const float ciclo = static_cast<float>(agoraMs % _periodoMs) / static_cast<float>(_periodoMs);
    float v = _media + _amplitude * sinf(kDoisPi * ciclo + _fase);
    if (_ruido > 0.0f) v += _ruido * proximoRuido();
    return v;
  }

 private:
  static constexpr float kDoisPi = 6.28318530718f;

  // Gerador congruencial simples: devolve valores em [-1, 1].
  float proximoRuido() {
    _semente = _semente * 1664525u + 1013904223u;
    return (static_cast<float>(_semente >> 8) / 8388607.5f) - 1.0f;
  }

  float _media;
  float _amplitude;
  uint32_t _periodoMs;
  float _fase;
  float _ruido;
  uint32_t _semente = 12345u;
};

#endif
