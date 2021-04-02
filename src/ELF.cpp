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

    auto fileHeader = this->fileHeader();

    if(fileHeader.EI_MAG != 0x464c457f) {
        std::cerr << m_path << " is not a valid ELF\n";
        exit(1);
    }

    if(fileHeader.EI_CLASS != 1) {
        std::cerr << "Only x86 ELFs are supported.\n";
        exit(1);
    }

    // Parse program headers
    std::vector<ELF::ELFProgramHeader*> pHeaders;
    uint32_t offset = fileHeader.e_phoff;
    for(int i = 0; i < fileHeader.e_phnum; i++) {
        auto headerPtr = reinterpret_cast<ELFProgramHeader *>(m_contents + offset);
        pHeaders.push_back(headerPtr);
        offset += fileHeader.e_phentsize;
    }

    // Parse section headers
    std::vector<ELF::ELFSectionHeader*> sHeaders;
    uint32_t sOffset = fileHeader.e_shoff;
    for(int i = 0; i < fileHeader.e_shnum; i++) {
        auto headerPtr = reinterpret_cast<ELFSectionHeader *>(m_contents + sOffset);
        sHeaders.push_back(headerPtr);
        sOffset += fileHeader.e_shentsize;
    }

    m_pheaders = pHeaders;
    m_sheaders = sHeaders;
}

ELF::ELFFileHeader & ELF::fileHeader()  {
    auto headerPtr = reinterpret_cast<ELFFileHeader*>(m_contents);
    ELFFileHeader &header = *headerPtr;
    return header;
}


