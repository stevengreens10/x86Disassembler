#include <vector>
#include "ELF.h"

void ELF::load() {
    std::ifstream in;
    // ate = open at end, so we can get size
    in.open(m_path, std::ios::binary | std::ios::ate);
    if (in.bad()) {
        std::cout << "Could not open file " << m_path << "\n";
        exit(1);
    }

    m_size = in.tellg();

    // Go back to the beginning
    in.seekg(0, std::ios::beg);

    m_contents = (uint8_t *) malloc(m_size);

    in.read((char *) m_contents, m_size);

    if (in.bad()) {
        std::cerr << "Could not read from file " << m_path << "\n";
        exit(1);
    }

    m_fileheader = reinterpret_cast<FileHeader *>(m_contents);

    if (m_fileheader->EI_MAG != 0x464c457f) {
        std::cerr << m_path << " is not a valid ELF\n";
        exit(1);
    }

    if (m_fileheader->EI_CLASS != 1) {
        std::cerr << "Only x86 ELFs are supported.\n";
        exit(1);
    }

    loadProgramHeaders();
    loadSectionHeaders();
}

void ELF::loadSectionHeaders() {
    // Find string table section
    auto *strTable = reinterpret_cast<SectionHeader *>(m_contents + (m_fileheader->e_shoff + (m_fileheader->e_shstrndx * m_fileheader->e_shentsize)));

    uint32_t sOffset = m_fileheader->e_shoff;
    for (int i = 0; i < m_fileheader->e_shnum; i++) {
        auto sHeaderPtr = reinterpret_cast<SectionHeader *>(m_contents + sOffset);
        if (sHeaderPtr->sh_type != SectionHeaderType::SHT_NULL) {
            char *name = ((char *)m_contents + strTable->sh_offset + sHeaderPtr->sh_name);
            (*m_sheaders)[name] = sHeaderPtr;
        }
        sOffset += m_fileheader->e_shentsize;
    }
}

void ELF::loadProgramHeaders() {
    // Parse program headers
    uint32_t offset = m_fileheader->e_phoff;
    for (int i = 0; i < m_fileheader->e_phnum; i++) {
        auto headerPtr = reinterpret_cast<ProgramHeader *>(m_contents + offset);
        m_pheaders->push_back(headerPtr);
        offset += m_fileheader->e_phentsize;
    }
}