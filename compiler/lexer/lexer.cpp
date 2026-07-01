#include "lexer.hpp"

namespace WIRE {

class lexer { 
private:
  std::string source;
  size_t cursor = 0;
public:
  lexer(std::string src) : source(src) {}

Token next_token() {
  while (cursor < source.length() && std::isspace(source[cursor])) {
    cursor++;
  }

  if ( cursor >= source.length()) {
    return{TokenType::TOKEN_EOF, ""};
  }
  // We announce the current
  char current = source[cursor];

  if (std::isdigit(current)) {
    std::string number = "";
    while (cursor < source.length() && std.isdigit(source[cursor])) {
      number += source[cursor];
      cursor++;
    }
  return {TokenType::TOKEN_PUSH, number};
  }

  if (current == '>') {
    if (cursor +1 < source.length() && source[cursor +1 ] == '<') {
      cursor +=2; // We take 2 characters at once
      return {TokenType::TOKEN_CLAMP, "><"};
    }
  }

  // Basic mathematics 
  if (current == '+') {cursor++; return {TokenType::TOKEN_ADD, "+"} };
  if (current == '-') {cursor++; return {TokenType::TOKEN_SUB, "-"} };
  if (current == '*') {
    if (cursor +1 < source.length() && source[cursor +1 ] == '*') {
      cursor +=2; // We take 2 characters at once
      return {TokenType::TOKEN_POW, "**"};
    }

    else {
      cursor++;
      return {TokenType::TOKEN_MUL, "*"};
    }

  };
  if (current == '/') {
    if (cursor +1 < source.length() && source[cursor +1 ] == '/') {
      cursor +=2; // We take 2 characters at once
      return {TokenType::TOKEN_ROT, "//"};
    }
    else {
      cursor++;
      return {TokenType::TOKEN_DIV, "/"};
    }
  };
  
  // If something is unknown 
  cursor++;
  return {TokenType::TOKEN_NONE, std::string(1, current)};
}
  
};

} // namespace WIRE 
