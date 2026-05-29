#include "ModifiedLCG.h"

ModifiedLCG::ModifiedLCG(uint64_t seed) : state(seed) {}

uint32_t ModifiedLCG::next() {
    // Линейное преобразование (автоматическое переполнение по модулю 2^64)
    state = a * state + c;
    // Берём старшие 32 бита как основной результат
    uint32_t output = static_cast<uint32_t>(state >> 32);
    // Нелинейное перемешивание XOR с константой
    output ^= 0x9e3779b9;
    return output;
}

double ModifiedLCG::nextDouble() {
    // Делим 32-битное целое на 2^32, получая диапазон [0, 1)
    return static_cast<double>(next()) / 4294967296.0;
}