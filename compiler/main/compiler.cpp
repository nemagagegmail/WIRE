#include <iostream>
#include <cstdlib>
#include "compiler.hpp"

namespace WIRE {

compiler::compiler(lexer& lex) : src_lexer(lex) {}

void compiler::emit_byte(uint8_t byte) {
    bytecode.push_back(byte);
}

void compiler::emit_uint64(uint64_t value) {
    for (int i = 0; i < 8; ++i) {
        emit_byte(static_cast<uint8_t>((value >> (i * 8)) & 0xFF));
    }
}

std::vector<uint8_t> compiler::compile() {
    Token token;
    
    while (true) {
        token = src_lexer.next_token();

        if (token.type == TokenType::TOKEN_EOF) {
            emit_byte(0x00); // Записуємо HALT / EOF в кінець байт-коду
            break;
        }

        switch (token.type) {
            case TokenType::TOKEN_PUSH: {
                uint64_t value = std::stoull(token.value);
                emit_byte(0x01); // OP_PUSH
                emit_uint64(value);
                break;
            }

            case TokenType::TOKEN_ADD:
                emit_byte(0x02); // OP_ADD
                break;

            case TokenType::TOKEN_SUB:
                emit_byte(0x03); // OP_SUB
                break;

            case TokenType::TOKEN_MUL:
                emit_byte(0x04); // OP_MUL
                break;

            case TokenType::TOKEN_DIV:
                emit_byte(0x05); // OP_DIV
                break;

            case TokenType::TOKEN_POW:
                emit_byte(0x06); // OP_POW (**)
                break;

            case TokenType::TOKEN_POP:
                emit_byte(0x07); // OP_POP (Викидаємо верхнє значення)
                break;

            case TokenType::TOKEN_RETURN:
                emit_byte(0x08); // OP_RETURN
                break;

            case TokenType::TOKEN_ROT:
                emit_byte(0x09); // OP_ROT (//)
                break;

            case TokenType::TOKEN_CLAMP:
                emit_byte(0x0A); // OP_CLAMP (><)
                break;

            case TokenType::TOKEN_VME:
                emit_byte(0x0C); // Твій системний токен VME
                break;

            case TokenType::TOKEN_NONE:
                std::cerr << "[COMPILER ERROR] Unknown token encountered: " << token.value << std::endl;
                exit(1);

            default:
                break;
        }
    }

    return bytecode;
}

} // namespace WIRE
