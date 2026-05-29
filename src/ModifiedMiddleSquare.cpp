#include "ModifiedMiddleSquare.h"

ModifiedMiddleSquare::ModifiedMiddleSquare(uint32_t seed) : state(seed) {
    // Если начальное состояние нулевое, заменяем на константу
    if (state == 0) state = 0x9e3779b9;
}

uint32_t ModifiedMiddleSquare::next() {
    // Квадрат состояния (64 бита)
    uint64_t square = static_cast<uint64_t>(state) * static_cast<uint64_t>(state);
    // Извлекаем средние 32 бита (биты 16..47)
    uint32_t middle = static_cast<uint32_t>((square >> 16) & 0xFFFFFFFF);
    // Циклический сдвиг влево на 13 бит
    uint32_t rotated = (middle << 13) | (middle >> 19);
    // XOR с предыдущим состоянием
    uint32_t new_state = rotated ^ state;
    // Защита от вырождения в ноль
    if (new_state == 0) new_state = 0x9e3779b9;
    state = new_state;
    return state;
}

double ModifiedMiddleSquare::nextDouble() {
    return static_cast<double>(next()) / 4294967296.0;
}
