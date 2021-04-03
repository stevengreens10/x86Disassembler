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

    auto programHeaders = *elf.programHeaders();
    auto  sectionHeaders = *elf.sectionHeaders();
    std::cout << "Program Headers:" << std::endl;
    for(auto & programHeader : programHeaders) {
        printf("ph_type=0x%08x, ph_ffset=0x%08x\n", programHeader->p_type, programHeader->p_offset);
    }
    std::cout << std::endl << "Section Headers:" << std::endl;
    for(auto & [name, sectionHeader] : sectionHeaders) {
        printf("[%18s] sh_type=0x%08x, sh_offset=0x%08x\n", name.c_str(), sectionHeader->sh_type, sectionHeader->sh_offset);
    }

    auto textSection = (*elf.sectionHeaders()).find(".text")->second;
    auto bytes = elf.read(textSection->sh_offset, textSection->sh_size);

    std::cout << "\nBytes at .text: ";
    for(int i = 0; i < textSection->sh_size; i++) {
        std::cout << "0x" << std::hex << ((int)bytes[i]) << " ";
    }
    std::cout << std::endl;

    return 0;
}
