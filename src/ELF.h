#pragma once

#include <iostream>
#include <fstream>
#include <utility>
#include <unordered_map>

class ELF {

class SectionHeaderType {
public:
    static const int SHT_NULL = 0x0;
    static const int SHT_PROGBITS = 0x1;
    static const int SHT_SYMTAB = 0x2;
    static const int SHT_STRTAB = 0x3;
    static const int SHT_RELA = 0x4;
    static const int SHT_HASH = 0x5;
    static const int SHT_DYNAMIC = 0x6;
    static const int SHT_NOTE = 0x7;
    static const int SHT_NOBITS = 0x8;
    static const int SHT_REL = 0x9;
    static const int SHT_SHLIB = 0xA;
    static const int SHT_DYNSYM = 0xB;
    static const int SHT_INIT_ARRAY = 0xE;
    static const int SHT_FINI_ARRAY = 0xF;
    static const int SHT_PREINIT_ARRAY = 0x10;
    static const int SHT_GROUP = 0x11;
    static const int SHT_SYMTAB_SHNDX = 0x12;
    static const int SHT_NUM = 0x13;

    static const int SHT_UNKNOWN = -1;
};

public:

    explicit ELF(std::string path) : m_path(std::move(path)), m_contents(nullptr), m_size(0) {
        m_pheaders = new std::vector<ProgramHeader*>();
        m_sheaders = new std::unordered_map<std::string, SectionHeader*>();
    }

    ~ELF() {
        free(m_contents);
        delete m_pheaders;
        delete m_sheaders;
    }

    void load();

    std::vector<uint8_t> read(uint32_t offset, int numBytes) {
        std::vector<uint8_t> vals;
        vals.reserve(numBytes);
        for (int i = 0; i < numBytes; i++) {
            vals[i] = read8(offset + i);
        }
        return vals;
    }

    uint8_t read8(uint32_t offset) {
        return *(((uint8_t *) m_contents) + offset);
    }

    uint16_t read16(uint32_t offset) {
        return *(((uint16_t *) m_contents) + offset);
    }

    uint32_t read32(uint32_t offset) {
        return *(((uint32_t *) m_contents) + offset);;
    }

    struct FileHeader {
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

    FileHeader &fileHeader() {
        return *m_fileheader;
    }

    struct ProgramHeader {
        uint32_t p_type;
        uint32_t p_offset;
        uint32_t p_vaddr;
        uint32_t p_paddr;
        uint32_t p_filesz;
        uint32_t p_memsz;
        uint32_t p_flags;
        uint32_t p_align;
    };

    std::vector<ProgramHeader *> &programHeaders() {
        return *m_pheaders;
    }

    struct SectionHeader {
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

    std::unordered_map<std::string, SectionHeader*> &sectionHeaders() {
        return *m_sheaders;
    }

private:
    std::string m_path;
    uint8_t *m_contents;
    size_t m_size;

    FileHeader *m_fileheader;
    std::vector<ProgramHeader *> *m_pheaders;
    std::unordered_map<std::string, SectionHeader*> *m_sheaders;

    void loadSectionHeaders();

    void loadProgramHeaders();
};

