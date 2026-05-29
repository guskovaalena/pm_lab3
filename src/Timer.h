#ifndef TIMER_H
#define TIMER_H

#include <chrono>

/**
 * \brief Класс для измерения времени выполнения участка кода.
 * 
 * \details Использует std::chrono::high_resolution_clock для высокоточных замеров.
 * Время измеряется в миллисекундах (double).
 */
class Timer {

private:
    std::chrono::time_point<std::chrono::steady_clock> start; ///< Момент старта таймера.

public:
    /**
     * \brief Конструктор – запускает таймер.
     * 
     * Фиксирует текущее время в момент создания объекта.
     */
    Timer();
    /**
     * \brief Деструктор по умолчанию (не делает ничего, так как ресурсов нет).
     */
    ~Timer() = default;
    /**
     * \brief Возвращает время, прошедшее с момента создания таймера.
     * \return Прошедшее время в миллисекундах (тип double).
     */
    double elapsed() const;
};

#endif