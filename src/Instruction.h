#pragma once

#include <cstdint>
#include "InstructionType.h"
#include "Register.h"

enum class AddressingMode {
    REGNODISP_OR_DISPONLY, DISPLACEMENT8, DISPLACEMENT32, REGISTER
};

class X86Instruction {
public:
    uint16_t opcode;

    uint8_t mod;
    uint8_t reg;
    uint8_t rm;

    uint32_t sib;

    AddressingMode mode;
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

    union {
        Register regSrc8;
        Register regSrc16;
        Register regSrc32;
    };

    union {
        Register regDst8;
        Register regDst16;
        Register regDst32;
    };

    uint32_t mem;

};

namespace Instruction {
    std::unordered_map<int, Register> reg32Table = {
            {0, Register::EAX},
            {1, Register::ECX},
            {2, Register::EDX},
            {3, Register::EBX},
            {4, Register::ESP},
            {5, Register::EBP},
            {6, Register::ESI},
            {7, Register::EDI},
    };

    std::unordered_map<int, Register> reg16Table = {
            {0, Register::AX},
            {1, Register::CX},
            {2, Register::DX},
            {3, Register::BX},
            {4, Register::SP},
            {5, Register::BP},
            {6, Register::SI},
            {7, Register::DI},
    };

    std::unordered_map<int, Register> reg8Table = {
            {0, Register::AL},
            {1, Register::CL},
            {2, Register::DL},
            {3, Register::BL},
            {4, Register::AH},
            {5, Register::CH},
            {6, Register::DH},
            {7, Register::BH},
    };

    std::unordered_map<int, Register> mmRegTable = {
            {0, Register::MM0},
            {1, Register::MM1},
            {2, Register::MM2},
            {3, Register::MM3},
            {4, Register::MM4},
            {5, Register::MM5},
            {6, Register::MM6},
            {7, Register::MM7},
    };

    std::unordered_map<int, Register> xmmRegTable = {
            {0, Register::XMM0},
            {1, Register::XMM1},
            {2, Register::XMM2},
            {3, Register::XMM3},
            {4, Register::XMM4},
            {5, Register::XMM5},
            {6, Register::XMM6},
            {7, Register::XMM7},
    };

    int idxFromRegister(Register reg) {
        std::unordered_map<int, Register> *map;
        if(isReg32(reg)) {
            map = &reg32Table;
        } else if(isReg16(reg)) {
            map = &reg16Table;
        } else if(isReg8(reg)) {
            map = &reg8Table;
        } else if(isMMReg(reg)) {
            map = &mmRegTable;
        } else {
            map = &xmmRegTable;
        }

        for(const auto [idx, reg2] : *map) {
            if(reg == reg2) {
                return idx;
            }
        }

        return -1;
    }
}