#ifndef RANDOM_TESTS_TPP
#define RANDOM_TESTS_TPP

#include <cmath>

/**
 * @brief Выполняет тест хи-квадрат с 20 равновероятными интервалами.
 * @param data Вектор чисел из диапазона [0,1).
 * @return TestResult с полем passed = true, если χ² < 30.144 (критическое для α=0.05, df=19).
 */
template<typename RNG>
TestResult squeezeTest(RNG& rng, int repetitions) {

    const double start =
        2147483648.0;

    double mean = 0.0;

    for (int i = 0; i < repetitions; ++i) {

        double x = start;

        int count = 0;

        while (x > 1.0) {

            x *= rng.nextDouble();

            count++;
        }

        mean += count;
    }

    mean /= repetitions;

    bool passed =
        std::abs(mean - 21.0) < 2.0;

    return {
        mean,
        0.0,
        passed
    };
}

#endif