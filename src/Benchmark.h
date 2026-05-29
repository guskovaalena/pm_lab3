/**
 * @file Benchmark.h
 * @brief Шаблонная функция для измерения времени генерации n чисел.
 */

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "Timer.h"

/**
 * @brief Замеряет время, затраченное на генерацию n чисел.
 * @tparam RNG Тип генератора (должен иметь метод next()).
 * @param rng Ссылка на генератор.
 * @param n Количество генерируемых чисел.
 * @return double Время в миллисекундах.
 */
template<typename RNG>
double benchmark(RNG& rng, size_t n) {
    Timer timer;
    for (size_t i = 0; i < n; ++i) {
        volatile uint32_t x = rng.next();
        (void)x;
    }
    return timer.elapsed();
}

#endif