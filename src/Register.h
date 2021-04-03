#pragma once

enum class Register {
    EAX, AX, AL, AH,
    EBX, BX, BL, BH,
    ECX, CX, CL, CH,
    EDX, DX, DL, DH,
    ESI, SI, EBP, BP,
    EDI, DI, ESP, SP,
    XMM0,XMM1,XMM2,XMM3,XMM4,XMM5,XMM6,XMM7,
    MM0,MM1,MM2,MM3,MM4,MM5,MM6,MM7

};

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