/**
 * @file ModifiedXorShift.h
 * @brief Генератор XorShift128 с добавлением нелинейности.
 */
#ifndef MODIFIED_XORSHIFT_H
#define MODIFIED_XORSHIFT_H

#include <cstdint>

/**
 * @class ModifiedXorShift
 * @brief Генератор на основе алгоритма XorShift128.
 * 
 * Состояние из четырёх 32-битных слов. В конце каждого цикла к выходному
 * значению прибавляется предыдущее состояние y для усиления нелинейности.
 */
class ModifiedXorShift {
private:
    uint32_t x, y, z, w; ///< Компоненты состояния

public:
    /**
     * @brief Конструктор.
     * @param seed Начальное зерно (используется для инициализации всех слов).
     */
    explicit ModifiedXorShift(uint32_t seed);

    /// Генерирует 32-битное число.
    uint32_t next();

    /// Генерирует число double в [0, 1).
    double nextDouble();
};

#endif // MODIFIED_XORSHIFT_H