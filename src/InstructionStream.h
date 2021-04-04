#pragma once

#include <cstdint>
#include "Instruction.h"

class InstructionStream {

public:
    explicit InstructionStream(const uint8_t *stream, int size) : m_stream(stream), m_size(size) {}

    Instruction next();
    bool finished();

private:
    const uint8_t *m_stream;
    uint8_t m_numBytesConsumed = 0;
    const uint8_t m_size;

    static uint8_t mod(uint8_t modrm) {
        return (modrm & 0b11000000) >> 6;
    }

    static uint8_t reg(uint8_t modrm) {
        return (modrm & 0b00111000) >> 3;
    }

    static uint8_t rm(uint8_t modrm) {
        return (modrm & 0b00000111);
    }
};

