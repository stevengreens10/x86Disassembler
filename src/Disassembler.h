#pragma once

#include <unordered_map>
#include <string>
#include "Register.h"
#include "Instruction.h"

namespace Disassembler {
    static std::unordered_map<int, Register> reg32Table = {
            {0, Register::EAX},
            {1, Register::ECX},
            {2, Register::EDX},
            {3, Register::EBX},
            {4, Register::ESP},
            {5, Register::EBP},
            {6, Register::ESI},
            {7, Register::EDI},
    };

    static std::unordered_map<int, Register> reg16Table = {
            {0, Register::AX},
            {1, Register::CX},
            {2, Register::DX},
            {3, Register::BX},
            {4, Register::SP},
            {5, Register::BP},
            {6, Register::SI},
            {7, Register::DI},
    };

    static std::unordered_map<int, Register> reg8Table = {
            {0, Register::AL},
            {1, Register::CL},
            {2, Register::DL},
            {3, Register::BL},
            {4, Register::AH},
            {5, Register::CH},
            {6, Register::DH},
            {7, Register::BH},
    };

    static std::unordered_map<int, Register> mmRegTable = {
            {0, Register::MM0},
            {1, Register::MM1},
            {2, Register::MM2},
            {3, Register::MM3},
            {4, Register::MM4},
            {5, Register::MM5},
            {6, Register::MM6},
            {7, Register::MM7},
    };

    static std::unordered_map<int, Register> xmmRegTable = {
            {0, Register::XMM0},
            {1, Register::XMM1},
            {2, Register::XMM2},
            {3, Register::XMM3},
            {4, Register::XMM4},
            {5, Register::XMM5},
            {6, Register::XMM6},
            {7, Register::XMM7},
    };

    static AddressingMode modeTable[] = {AddressingMode::REGNODISP_OR_DISPONLY, AddressingMode::DISPLACEMENT8,
                                         AddressingMode::DISPLACEMENT32,
                                         AddressingMode::REGISTER};

    bool isReg32(Register reg);
    bool isReg16(Register reg);
    bool isReg8(Register reg);
    bool isMMReg(Register reg);
    bool isXMMReg(Register reg);

    std::string mnemonicToString(InstructionMnemonic mnemonic);
    std::string registerToString(Register reg);
}