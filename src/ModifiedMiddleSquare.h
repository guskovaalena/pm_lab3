/**
 * @file ModifiedMiddleSquare.h
 * @brief Модифицированный метод середины квадрата.
 */

#ifndef MODIFIED_MIDDLE_SQUARE_H
#define MODIFIED_MIDDLE_SQUARE_H

#include <cstdint>

/**
 * @class ModifiedMiddleSquare
 * @brief Генератор, улучшающий классический метод середины квадрата.
 * 
 * На каждом шаге: state = state^2, берутся средние 32 бита, циклический сдвиг,
 * XOR с предыдущим состоянием. Предотвращается вырождение в ноль.
 */
class ModifiedMiddleSquare {
private:
    uint32_t state; ///< Текущее состояние (32 бита)

public:
    /**
     * @brief Конструктор.
     * @param seed Начальное состояние (если 0, заменяется на константу).
     */
    explicit ModifiedMiddleSquare(uint32_t seed);

    /// Генерирует 32-битное число.
    uint32_t next();

    /// Генерирует double в [0, 1).
    double nextDouble();
};

#endif // MODIFIED_MIDDLE_SQUARE_H