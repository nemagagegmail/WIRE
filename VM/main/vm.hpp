#pragma once
#include <vector>
#include <cstdint>
#include "shared/opcode.hpp" 

namespace WIRE {

class vm { 

private:
  std::vector<uint8_t> bytecode;
  std::vector<uint64_t> stack;
  size_t pc = 0;

  uint64_t pop();
  void push(uint64_t val);

public:
  vm(std::vector<uint8_t> code);
  void run();
} // namespace WIRE
  
