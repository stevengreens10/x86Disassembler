cmake_minimum_required(VERSION 3.17)
project(x86Disassembler)

set(CMAKE_CXX_STANDARD 20)

add_executable(x86Disassembler main.cpp ELF.cpp ELF.h Instruction.h InstructionType.h Register.h InstructionMnemonic.h InstructionStream.cpp InstructionStream.h Disassembler.cpp Disassembler.h)
