#include <vector>
#include "ELF.h"

void ELF::load() {
    std::ifstream in;
    // ate = open at end, so we can get size
    in.open(m_path, std::ios::binary | std::ios::ate);
    if(in.bad()) {
        std::cout << "Could not open file " << m_path << "\n";
        exit(1);
    }

    m_size = in.tellg();

    // Go back to the beginning
    in.seekg(0, std::ios::beg);

    m_contents = (uint8_t*) malloc(m_size);

    in.read((char *)m_contents, m_size);

    if(in.bad()) {
        std::cerr << "Could not read from file " << m_path << "\n";
        exit(1);
    }

}

uint32_t convert(uint32_t val) {
    return ((val & 0xFF000000) >> 24) |
                         ((val & 0x00FF0000) >> 8) |
                         ((val & 0x0000FF00) << 8) |
                         ((val & 0x000000FF) << 24);
}

ELF::ELFFileHeader & ELF::fileHeader()  {
    auto headerPtr = reinterpret_cast<ELFFileHeader*>(m_contents);
    ELFFileHeader &header = *headerPtr;
    if(header.EI_MAG != convert(0x7f454c46)) {
        std::cerr << m_path << " is not a valid ELF\n";
        exit(1);
    }

    if(header.EI_CLASS != 1) {
        std::cerr << "Only x86 ELFs are supported.\n";
        exit(1);
    }
    return header;
}

std::vector<ELF::ELFProgramHeader*> ELF::programHeaders() {
    auto fileHeader = this->fileHeader();
    std::vector<ELF::ELFProgramHeader*> headers;
    uint32_t offset = fileHeader.e_phoff;
    for(int i = 0; i < fileHeader.e_phnum; i++) {
        auto headerPtr = reinterpret_cast<ELFProgramHeader *>(m_contents + offset);
        headers.push_back(headerPtr);
        offset += fileHeader.e_phentsize;
    }
    return headers;
}

std::vector<ELF::ELFSectionHeader*> ELF::sectionHeaders() {
    auto fileHeader = this->fileHeader();
    std::vector<ELF::ELFSectionHeader*> headers;
    uint32_t offset = fileHeader.e_shoff;
    for(int i = 0; i < fileHeader.e_shnum; i++) {
        auto headerPtr = reinterpret_cast<ELFSectionHeader *>(m_contents + offset);
        headers.push_back(headerPtr);
        offset += fileHeader.e_shentsize;
    }
    return headers;
}

