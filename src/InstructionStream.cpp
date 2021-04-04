#include <iostream>
#include "InstructionStream.h"
#include "Disassembler.h"

Instruction InstructionStream::next() {
    auto stream = m_stream + m_numBytesConsumed;
    uint8_t opcode = stream[0];
    uint8_t modrm = stream[1];

    int numBytesConsumed = 1;
    Instruction ins{};

    ins.opcode = opcode;
    ins.mod = mod(modrm);
    ins.reg = reg(modrm);
    ins.rm = rm(modrm);
    ins.mode = Disassembler::modeTable[ins.mod];

    if (opcode == 0x31) {
        ins.mnemonic = InstructionMnemonic::XOR;
        ins.instructionType = InstructionType::REG_REG;
        ins.regSrc = Disassembler::reg32Table.find(ins.reg)->second;
        ins.regDst = Disassembler::reg32Table.find(ins.rm)->second;
        numBytesConsumed = 2;
    } else {
        std::cerr << "Could not parse instruction with opcode 0x" << std::hex << (int) opcode << std::endl;
        exit(1);
    }

    m_numBytesConsumed += numBytesConsumed;

    return ins;
}

bool InstructionStream::finished() {
    return m_numBytesConsumed >= m_size;
}
