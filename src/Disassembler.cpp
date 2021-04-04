#include "Disassembler.h"

namespace Disassembler {

    bool isReg32(Register reg) {
        switch (reg) {
            case Register::EAX:
            case Register::EBX:
            case Register::ECX:
            case Register::EDX:
            case Register::ESI:
            case Register::EDI:
            case Register::EBP:
            case Register::ESP:
                return true;
            default:
                return false;
        }
    }

    bool isReg16(Register reg) {
        switch (reg) {
            case Register::AX:
            case Register::BX:
            case Register::CX:
            case Register::DX:
            case Register::SI:
            case Register::DI:
            case Register::BP:
            case Register::SP:
                return true;
            default:
                return false;
        }
    }

    bool isReg8(Register reg) {
        switch (reg) {
            case Register::AL:
            case Register::BL:
            case Register::CL:
            case Register::DL:
            case Register::AH:
            case Register::BH:
            case Register::CH:
            case Register::DH:
                return true;
            default:
                return false;
        }
    }

    bool isMMReg(Register reg) {
        switch (reg) {
            case Register::MM0:
            case Register::MM1:
            case Register::MM2:
            case Register::MM3:
            case Register::MM4:
            case Register::MM5:
            case Register::MM6:
            case Register::MM7:
                return true;
            default:
                return false;
        }
    }

    bool isXMMReg(Register reg) {
        switch (reg) {
            case Register::XMM0:
            case Register::XMM1:
            case Register::XMM2:
            case Register::XMM3:
            case Register::XMM4:
            case Register::XMM5:
            case Register::XMM6:
            case Register::XMM7:
                return true;
            default:
                return false;
        }
    }

    int idxFromRegister(Register reg) {
        std::unordered_map<int, Register> *map;
        if (isReg32(reg)) {
            map = &reg32Table;
        } else if (isReg16(reg)) {
            map = &reg16Table;
        } else if (isReg8(reg)) {
            map = &reg8Table;
        } else if (isMMReg(reg)) {
            map = &mmRegTable;
        } else {
            map = &xmmRegTable;
        }

        for (const auto[idx, reg2] : *map) {
            if (reg == reg2) {
                return idx;
            }
        }

        return -1;
    }

    std::string mnemonicToString(InstructionMnemonic mnemonic) {
        switch (mnemonic) {
            case InstructionMnemonic::MOV:
                return "mov";
            case InstructionMnemonic::XOR:
                return "xor";
        }
    }

    std::string registerToString(Register reg) {
        switch(reg) {
            case Register::EAX:
                return "eax";
            case Register::AX:
                return "ax";
            case Register::AL:
                return "al";
            case Register::AH:
                return "ah";
            case Register::EBX:
                return "ebx";
            case Register::BX:
                return "bx";
            case Register::BL:
                return "bl";
            case Register::BH:
                return "bh";
            case Register::ECX:
                return "ecx";
            case Register::CX:
                return "cx";
            case Register::CL:
                return "cl";
            case Register::CH:
                return "ch";
            case Register::EDX:
                return "edx";
            case Register::DX:
                return "dx";
            case Register::DL:
                return "dl";
            case Register::DH:
                return "dh";
            case Register::ESI:
                return "esi";
            case Register::SI:
                return "si";
            case Register::EBP:
                return "ebp";
            case Register::BP:
                return "bp";
            case Register::EDI:
                return "edi";
            case Register::DI:
                return "di";
            case Register::ESP:
                return "esp";
            case Register::SP:
                return "sp";
            case Register::XMM0:
                return "xmm0";
            case Register::XMM1:
                return "xmm1";
            case Register::XMM2:
                return "xmm2";
            case Register::XMM3:
                return "xmm3";
            case Register::XMM4:
                return "xmm4";
            case Register::XMM5:
                return "xmm5";
            case Register::XMM6:
                return "xmm6";
            case Register::XMM7:
                return "xmm7";
            case Register::MM0:
                return "mm0";
            case Register::MM1:
                return "mm1";
            case Register::MM2:
                return "mm2";
            case Register::MM3:
                return "mm3";
            case Register::MM4:
                return "mm4";
            case Register::MM5:
                return "mm5";
            case Register::MM6:
                return "mm6";
            case Register::MM7:
                return "mm7";
        }
    }
}