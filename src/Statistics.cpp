#include "Statistics.h"

#include <cmath>

SampleStats computeStats(
    const std::vector<double>& data) {

    size_t n = data.size();

    double mean = 0.0;

    for (double x : data) {
        mean += x;
    }

    mean /= n;

    double variance = 0.0;

    for (double x : data) {

        variance +=
            (x - mean) *
            (x - mean);
    }

    variance /= (n - 1);

    double stddev =
        std::sqrt(variance);

    double cv =
        stddev / mean;

    return {
        mean,
        variance,
        stddev,
        cv
    };
}

