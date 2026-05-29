/**
 * \file Timer.cpp
 * \brief Реализация класса Timer для измерения времени.
 */

#include "Timer.h"
#include <iostream>
#include <iomanip>   

/**
 * \brief Конструктор – запускает таймер.
 * \details Фиксирует текущее время с помощью high_resolution_clock.
 */
Timer::Timer() {
    start = std::chrono::high_resolution_clock::now();
}

/**
 * \brief Возвращает время, прошедшее с момента создания таймера.
 * \return Время в миллисекундах (double).
 */
double Timer::elapsed() const {
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}

