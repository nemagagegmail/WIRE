#include <iostream>
#include <vector>
#include <cstdint>
#include "../shared/opcode.hpp"

void disassembler(const std::vector<uint_8>& code) {
  std::count << "---Decoding byte code--- \n";

  size_t offset = 0;
  while(offset < code.size()) {
  
    // We read the byte and convert it to our type in the Opcode
    
