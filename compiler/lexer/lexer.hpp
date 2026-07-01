#pragma once
#include <string>
#include <cctype>
#include <vector>

namespace WIRE {

enum class TokenType {
  TOKEN_NONE,
  TOKEN_RETURN,

  
  TOKEN_PUSH,
  TOKEN_POP,
  TOKEN_ADD,
  TOKEN_SUB,
  TOKEN_MUL,
  TOKEN_DIV,
  TOKEN_POW,
  TOKEN_ROT,

  TOKEN_CLAMP,

  TOKEN_VME,
  TOKEN_EOF
};

struct Token {
  TokenType type; // Write here the type from the list above 
  std::string value; // Here we write the text itself, like "+" or "123" 
};

} // Closing the namespace
