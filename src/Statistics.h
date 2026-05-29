/**
 * @file Statistics.h
 * @brief Вычисление основных статистик выборки.
 */

#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

/**
 * @struct SampleStats
 * @brief Набор описательных статистик.
 */
struct SampleStats {
    double mean;     ///< Среднее арифметическое
    double variance; ///< Несмещённая дисперсия (с делением на n-1)
    double stddev;   ///< Среднеквадратическое отклонение
    double cv;       ///< Коэффициент вариации (stddev/mean)
};

/**
 * @brief Вычисляет статистики для выборки.
 * @param data Входной вектор вещественных чисел.
 * @return SampleStats Структура с рассчитанными значениями.
 */
SampleStats computeStats(const std::vector<double>& data);

#endif