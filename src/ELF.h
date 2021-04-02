#pragma once

#include <iostream>
#include <fstream>
#include <utility>

class ELF {

public:

    explicit ELF(std::string path) : m_path(std::move(path)), m_contents(nullptr), m_size(0) {}

    ~ELF() {
        free(m_contents);
    }

    void load();


    uint8_t read8(uint32_t offset) {
        return *(((uint8_t *) m_contents) + offset);
    }

    uint16_t read16(uint32_t offset) {
        uint16_t val = *(((uint16_t *) m_contents) + offset);
        return ((val & 0xFF00) >> 8) + ((val & 0xFF) << 8);
    }

    uint32_t read32(uint32_t offset) {
        uint32_t val = *(((uint32_t *) m_contents) + offset);
        uint32_t endianVal = ((val & 0xFF000000) >> 24) |
                             ((val & 0x00FF0000) >> 8) |
                             ((val & 0x0000FF00) << 8) |
                             ((val & 0x000000FF) << 24);
        return endianVal;
    }

    struct ELFFileHeader {
        uint32_t EI_MAG;

        uint8_t EI_CLASS;
        uint8_t EI_DATA;
        uint8_t EI_VERSION;
        uint8_t EI_OSABI;
        uint8_t EI_ABIVERSION;

        uint8_t padding[7];

        uint16_t e_type;
        uint16_t e_machine;
        uint32_t e_version;
        uint32_t e_entry;
        uint32_t e_phoff;
        uint32_t e_shoff;
        uint32_t e_flags;

        uint16_t e_ehsize;
        uint16_t e_phentsize;
        uint16_t e_phnum;
        uint16_t e_shentsize;
        uint16_t e_shnum;
        uint16_t e_shstrndx;
    };

    ELFFileHeader &fileHeader();

    struct ELFProgramHeader {
        uint32_t p_type;
        uint32_t p_offset;
        uint32_t p_vaddr;
        uint32_t p_paddr;
        uint32_t p_filesz;
        uint32_t p_memsz;
        uint32_t p_flags;
        uint32_t p_align;
    };

    std::vector<ELFProgramHeader *> programHeaders() {
        return m_pheaders;
    }

    struct ELFSectionHeader {
        uint32_t sh_name;
        uint32_t sh_type;
        uint32_t sh_flags;
        uint32_t sh_addr;
        uint32_t sh_offset;
        uint32_t sh_size;
        uint32_t sh_link;
        uint32_t sh_info;
        uint32_t sh_addralign;
        uint32_t sh_entsize;
    };

    std::vector<ELFSectionHeader *> sectionHeaders() {
        return m_sheaders;
    }

private:
    std::string m_path;
    uint8_t *m_contents;
    size_t m_size;

    std::vector<ELFProgramHeader *> m_pheaders;
    std::vector<ELFSectionHeader *> m_sheaders;
};

