#pragma once

#include <cstdint>
#include <unordered_map>
#include "InstructionType.h"
#include "Register.h"
#include "InstructionMnemonic.h"

enum class AddressingMode {
    REGNODISP_OR_DISPONLY, DISPLACEMENT8, DISPLACEMENT32, REGISTER
};

class Instruction {
public:
    uint16_t opcode;

    uint8_t mod;
    uint8_t reg;
    uint8_t rm;

    uint32_t sib;

    AddressingMode mode;
    InstructionMnemonic mnemonic;
    InstructionType instructionType;

    union {
        uint8_t imm8;
        uint16_t imm16;
        uint32_t imm32;
    };

    union {
        uint8_t disp8;
        uint32_t disp32;
    };

    Register regSrc;

    Register regDst;

    uint32_t mem;

};