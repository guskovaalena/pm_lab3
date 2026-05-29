/**
 * @file RandomTests.cpp
 * @brief Реализация набора статистических тестов для проверки качества случайных чисел.
 */

#include "RandomTests.h"

#include <cmath>
#include <map>
#include <bitset>

/**
 * @brief Тест хи-квадрат (χ²) на равномерность распределения.
 * 
 * Диапазон [0,1) разбивается на 20 равных интервалов. Подсчитывается количество
 * чисел, попавших в каждый интервал, и вычисляется статистика χ².
 * 
 * @param data Вектор вещественных чисел из диапазона [0,1).
 * @return TestResult Структура с полем passed = true, если χ² < 30.144
 *         (критическое значение для α=0.05 и числа степеней свободы 19).
 */
TestResult chiSquareTest(const std::vector<double>& data) {

    int bins = 20;

    std::vector<int> observed(bins, 0);

    for (double x : data) {

        int index =
            static_cast<int>(x * bins);

        if (index >= bins) {
            index = bins - 1;
        }

        observed[index]++;
    }

    double expected =
        static_cast<double>(data.size()) / bins;

    double chi2 = 0.0;

    for (int count : observed) {

        double diff =
            count - expected;

        chi2 +=
            diff * diff / expected;
    }

    // df = bins - 1, alpha = 0 -> 30.144 теоретическое критическое значение для хи-квадрат
    bool passed =
        chi2 < 30.144;

    return {
        chi2,
        0.0,
        passed
    };
}

/**
 * @brief Тест серий (runs test) для проверки независимости битов.
 * 
 * Последовательность преобразуется в битовую: значение >= 0.5 → 1, иначе 0.
 * Подсчитывается количество серий (непрерывных блоков одинаковых битов).
 * Сравнивается с ожидаемым количеством серий для независимой последовательности.
 * 
 * @param data Вектор чисел double из [0,1).
 * @return TestResult Поле passed = true, если |Z| < 1.96 (уровень значимости 0.05).
 */
TestResult runsTest(const std::vector<double>& data) {

    int runs = 1;

    for (size_t i = 1; i < data.size(); ++i) {

        if ((data[i] >= 0.5) != (data[i - 1] >= 0.5)) {
            runs++;
        }
    }

    double n1 = 0.0;
    double n2 = 0.0;

    for (double x : data) {

        if (x >= 0.5) {
            n1++;
        }
        else {
            n2++;
        }
    }

    double expected =
        (2.0 * n1 * n2) /
        (n1 + n2) + 1.0;

    double variance =
        (
            2.0 * n1 * n2 *
            (2.0 * n1 * n2 - n1 - n2)
        ) /
        (
            std::pow(n1 + n2, 2.0) *
            (n1 + n2 - 1.0)
        );

    double z =
        (runs - expected) /
        std::sqrt(variance);

    // для alpha = 0.05, критическое значение для нормального распределения ~ 1.96
    bool passed = std::abs(z) < 1.96;

    return {
        z,
        0.0,
        passed
    };
}

/**
 * @brief Тест перекрывающихся сумм (overlapping sums).
 * 
 * Берутся перекрывающиеся блоки длиной 100. Для каждого блока вычисляется сумма
 * входящих в него чисел. Для идеально равномерной последовательности сумма
 * элементов блока распределена нормально с математическим ожиданием 50.
 * 
 * @param data Вектор чисел double из [0,1).
 * @return TestResult Поле passed = true, если среднее значение сумм отличается от 50
 *         менее чем на 1 (эмпирический критерий).
 */
TestResult overlappingSumsTest(const std::vector<double>& data) {

    const int block = 100;

    std::vector<double> sums;

    for (
        size_t i = 0;
        i + block < data.size();
        ++i
    ) {

        double s = 0.0;

        for (int j = 0; j < block; ++j) {
            s += data[i + j];
        }

        sums.push_back(s);
    }

    double mean = 0.0;

    for (double x : sums) {
        mean += x;
    }

    mean /= sums.size();

    double variance = 0.0;

    for (double x : sums) {

        variance +=
            (x - mean) *
            (x - mean);
    }

    variance /= sums.size();

    double expectedMean = 50.0;

    bool passed = std::abs(mean - expectedMean) < 1.0;

    return {
        mean,
        variance,
        passed
    };
}

/**
 * @brief Тест минимального расстояния между точками на единичном квадрате.
 * 
 * Первые 2000 чисел интерпретируются как 1000 точек (x, y) на единичном квадрате.
 * Вычисляется минимальное евклидово расстояние между любыми двумя различными точками.
 * Качественный ГСЧ не должен давать слишком маленьких расстояний.
 * 
 * @param data Вектор чисел double из [0,1). Должен содержать не менее 2000 элементов.
 * @return TestResult Поле passed = true, если минимальное расстояние больше 1e-6.
 */
TestResult minimumDistanceTest(
    const std::vector<double>& data
) {

    int points = 1000;

    double minDist = 1e9;

    for (int i = 0; i < points; ++i) {

        double x1 = data[2 * i];
        double y1 = data[2 * i + 1];

        for (int j = i + 1; j < points; ++j) {

            double x2 = data[2 * j];
            double y2 = data[2 * j + 1];

            double dx = x1 - x2;
            double dy = y1 - y2;

            double dist =
                dx * dx + dy * dy;

            if (dist < minDist) {
                minDist = dist;
            }
        }
    }

    bool passed = minDist > 1e-6;

    return {
        minDist,
        0.0,
        passed
    };
}

/**
 * @brief Тест "обезьяны" (monkey test) – проверка покрытия 5-битовых слов.
 * 
 * Каждое входное число преобразуется в 32-битовое целое (масштабированием),
 * из которого выделяются младшие 5 бит (значение от 0 до 31). Подсчитывается,
 * сколько различных слов из 32 возможных не встретились ни разу.
 * 
 * @param data Вектор чисел double из [0,1).
 * @return TestResult Поле passed = true, если пропущено менее 5 слов.
 */
TestResult monkeyTest(
    const std::vector<double>& data
) {

    std::map<int, int> words;

    for (double x : data) {

        uint32_t value = static_cast<uint32_t>(x * 4294967295u); // 2^32 - 1
        
        //31 = 11111 -> берем 5 младших битов
        int word = value & 31;

        words[word]++;
    }

    int missing = 0;

    for (int i = 0; i < 32; ++i) {

        if (words[i] == 0) {
            missing++;
        }
    }

    bool passed =
        missing < 5;

    return {
        static_cast<double>(missing),
        0.0,
        passed
    };
}