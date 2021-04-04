#include <iostream>
#include <vector>
#include "Logger.h"
#include "ELF.h"
#include "Instruction.h"
#include "InstructionStream.h"
#include "Disassembler.h"

int main(int argc, char *argv[]) {
    Logger logger{std::cout};
    if(argc != 2) {
        logger.print("Usage: disas <path-to-x86-elf>\n");
        return 1;
    }

    std::string elfPath = argv[1];

    ELF elf{elfPath};
    elf.load();

    auto programHeaders = elf.programHeaders();
    auto  sectionHeaders = elf.sectionHeaders();
    std::cout << "Program Headers:" << std::endl;
    for(auto & programHeader : programHeaders) {
        printf("ph_type=0x%08x, ph_ffset=0x%08x\n", programHeader->p_type, programHeader->p_offset);
    }
    std::cout << std::endl << "Section Headers:" << std::endl;
    for(auto & [name, sectionHeader] : sectionHeaders) {
        printf("[%18s] sh_type=0x%08x, sh_offset=0x%08x\n", name.c_str(), sectionHeader->sh_type, sectionHeader->sh_offset);
    }

    auto textSection = elf.sectionHeaders().find(".text")->second;

    InstructionStream instructionStream{elf.contents() + textSection->sh_offset, static_cast<int>(textSection->sh_size)};

    std::cout << "--Disassembly--" << std::endl;

    while(!instructionStream.finished()) {
        auto instruction = instructionStream.next();
        if(instruction.instructionType == InstructionType::REG_REG) {
            std::cout << Disassembler::mnemonicToString(instruction.mnemonic) << " "
                      << Disassembler::registerToString(instruction.regDst) << ", "
                      << Disassembler::registerToString(instruction.regSrc) << std::endl;
        }
    }

    return 0;
}
