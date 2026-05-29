/**
 * @file RandomTests.h
 * @brief Набор статистических тестов для случайных последовательностей.
 */

#ifndef RANDOM_TESTS_H
#define RANDOM_TESTS_H

#include <vector>

/**
 * @struct TestResult
 * @brief Результат выполнения одного теста.
 */
struct TestResult {
    double statistic; ///< Значение статистики теста (Z, χ² и т.д.)
    double pvalue;    ///< p-значение (не вычисляется в текущей версии)
    bool passed;      ///< Прошёл ли тест (true/false)
};

/// Тест хи-квадрат на равномерность распределения.
TestResult chiSquareTest(const std::vector<double>& data);

/// Тест серий (runs test) для проверки независимости битов.
TestResult runsTest(const std::vector<double>& data);

/// Тест перекрывающихся сумм (overlapping sums).
TestResult overlappingSumsTest(const std::vector<double>& data);

/// Тест минимального расстояния между точками на единичном квадрате.
TestResult minimumDistanceTest(const std::vector<double>& data);

/**
 * @brief Тест "обезьяны" – проверка покрытия 5-битовых слов.
 * @param data Входная последовательность чисел double.
 * @return Результат: passed, если пропущено менее 5 слов из 32.
 */
TestResult monkeyTest(const std::vector<double>& data);

/**
 * @brief Тест "сжатия" (squeeze) – моделирует многократное умножение.
 * @tparam RNG Тип генератора.
 * @param rng Генератор случайных чисел.
 * @param repetitions Количество повторений эксперимента.
 * @return Результат: passed, если среднее число шагов близко к 21.
 */
template<typename RNG>
TestResult squeezeTest(RNG& rng, int repetitions);

#include "RandomTests.tpp"

#endif // RANDOM_TESTS_H