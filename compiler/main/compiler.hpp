#pragma once 
#include <vector>
#include <cstdint>
#include "compiler/lexer/lexer.hpp"
#include "shared/opcode.hpp"

namespace WIRE {

class compiler {
private:
    lexer& src_lexer;
    std::vector<uint8_t> bytecode;

    void emit_byte(uint8_t byte);
    void emit_uint64(uint64_t value);

public:
    compiler(lexer& lex);
    std::vector<uint8_t> compile();
};
