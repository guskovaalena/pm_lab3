/**
 * @mainpage Сравнение модифицированных генераторов случайных чисел
 * 
 * Проект реализует три генератора:
 * - ModifiedLCG – линейный конгруэнтный с 64-битным состоянием
 * - ModifiedXorShift – XorShift128 с добавлением нелинейности
 * - ModifiedMiddleSquare – модифицированный метод середины квадрата
 * 
 * Для каждого генератора:
 * - Генерируются выборки разного объёма (от 1000 до 1 000 000)
 * - Выполняется семь статистических тестов (хи-квадрат, серий, перекрывающихся
 *   сумм, минимального расстояния, "обезьяны", "сжатия", а также замеряется
 *   производительность).
 * - Результаты сохраняются в CSV-файл и выводятся в консоль.
 * 
 * @author Ваше Имя
 * @date Год
 */

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>

#include "ModifiedLCG.h"
#include "ModifiedXorShift.h"
#include "ModifiedMiddleSquare.h"

#include "Statistics.h"
#include "RandomTests.h"
#include "Benchmark.h"

template<typename RNG>
std::vector<double> generateSample(
    RNG& rng,
    size_t n
) {

    std::vector<double> data(n);

    for (size_t i = 0; i < n; ++i) {
        data[i] = rng.nextDouble();
    }

    return data;
}

void printHeader() {

    std::cout
        << std::setw(10) << "N"
        << std::setw(12) << "Mean"
        << std::setw(12) << "StdDev"
        << std::setw(12) << "CV"
        << std::setw(12) << "Chi2"
        << std::setw(12) << "Runs"
        << std::setw(12) << "Sums"
        << std::setw(12) << "MinDist"
        << std::setw(12) << "Monkey"
        << std::setw(12) << "Squeeze"
        << std::endl;
}

template<typename RNG>
void testGenerator(
    const std::string& name,
    RNG& rng,
    std::ofstream& timingCsv
) {

    std::cout << "\n========== "
              << name
              << " ==========\n";

    printHeader();

    std::vector<size_t> sizes = {

        1000,
        2000,
        5000,
        10000,
        20000,
        50000,
        100000,
        200000,
        500000,
        1000000
    };

    for (size_t n : sizes) {

        auto sample = generateSample(rng, n);

        auto stats = computeStats(sample);

        auto chi = chiSquareTest(sample);

        auto runs = runsTest(sample);

        auto sums = overlappingSumsTest(sample);

        auto minDist = minimumDistanceTest(sample);

        auto monkey = monkeyTest(sample);

        auto squeeze = squeezeTest(rng, 1000);

        std::cout
            << std::setw(10) << n
            << std::setw(12) << stats.mean
            << std::setw(12) << stats.stddev
            << std::setw(12) << stats.cv
            << std::setw(12) << chi.passed
            << std::setw(12) << runs.passed
            << std::setw(12) << sums.passed
            << std::setw(12) << minDist.passed
            << std::setw(12) << monkey.passed
            << std::setw(12) << squeeze.passed
            << std::endl;

        double timeMs =
            benchmark(rng, n);

        timingCsv
            << name
            << ","
            << n
            << ","
            << timeMs
            << "\n";
    }
}

double benchmarkMt19937(size_t n) {

    std::mt19937 rng(123456);

    Timer timer;

    for (size_t i = 0; i < n; ++i) {

        volatile uint32_t x = rng();

        (void)x;
    }

    return timer.elapsed();
}

int main() {

    std::ofstream timingCsv("../timing_results.csv");

    timingCsv << "generator,n,time_ms\n";

    ModifiedLCG lcg(123456789);

    ModifiedXorShift xorShift(987654321);

    ModifiedMiddleSquare middle(555555555);

    testGenerator(
        "LCG",
        lcg,
        timingCsv
    );

    testGenerator(
        "XorShift",
        xorShift,
        timingCsv
    );

    testGenerator(
        "MiddleSquare",
        middle,
        timingCsv
    );

    std::vector<size_t> sizes = {
        1000,
        2000,
        5000,
        10000,
        20000,
        50000,
        100000,
        200000,
        500000,
        1000000
    };


    for (size_t n : sizes) {

        double timeMs = benchmarkMt19937(n);

        timingCsv << "mt19937" << "," << n << "," << timeMs << "\n";

    }

    timingCsv.close();

    return 0;
}

