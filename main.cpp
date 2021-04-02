#include <iostream>
#include <vector>
#include "Logger.h"
#include "ELF.h"

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
        std::cout << "p_type: 0x" << programHeader->p_type << " | p_offset = 0x" << std::hex << programHeader->p_offset << std::endl;
    }
    std::cout << std::endl << "Section Headers:" << std::endl;
    for(auto & sectionHeader : sectionHeaders) {
        std::cout << "sh_type: 0x" << sectionHeader->sh_type << " | sh_offset = 0x" << std::hex << sectionHeader->sh_offset << std::endl;
    }

    return 0;
}
