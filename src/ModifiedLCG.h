/**
 * @file ModifiedLCG.h
 * @brief Линейный конгруэнтный генератор с модификациями.
 */

#ifndef MODIFIED_LCG_H
#define MODIFIED_LCG_H

#include <cstdint>

/**
 * @class ModifiedLCG
 * @brief Генератор псевдослучайных чисел на основе LCG.
 * 
 * Использует 64-битное состояние, линейное преобразование и нелинейное
 * перемешивание старших 32 бит.
 */
class ModifiedLCG {
private:
    uint64_t state; ///< Текущее состояние генератора (64 бита)
    static constexpr uint64_t a = 6364136223846793005ull; ///< Множитель
    static constexpr uint64_t c = 1442695040888963407ull; ///< Приращение

public:
    /**
     * @brief Конструктор.
     * @param seed Начальное значение состояния.
     */
    explicit ModifiedLCG(uint64_t seed);

    /**
     * @brief Генерирует 32-битное псевдослучайное число.
     * @return uint32_t Случайное число в диапазоне [0, 2^32-1].
     */
    uint32_t next();

    /**
     * @brief Генерирует число с плавающей точкой в [0, 1).
     * @return double Случайное число.
     */
    double nextDouble();
};

#endif // MODIFIED_LCG_H