#include "ModifiedXorShift.h"

ModifiedXorShift::ModifiedXorShift(uint32_t seed) {
    // Инициализация 
    x = seed;
    y = seed * 0x9e3779b9;
    z = y * 0x9e3779b9;
    w = z * 0x9e3779b9;
    // Избегаем нулевого состояния 
    if (w == 0) w = 1;
}

uint32_t ModifiedXorShift::next() {
    // Базовый XorShift128
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    w = w ^ (w >> 19) ^ (t ^ (t >> 8));
    // Добавленяем предыдущее состояние y (добавляем нелинейность)
    w = w + y;
    return w;
}

double ModifiedXorShift::nextDouble() {
    return static_cast<double>(next()) / 4294967296.0;
}