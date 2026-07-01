#include <iostream>
#include <cmath>
#include <cstdlib>
#include "vm.hpp"

namespace WIRE {

vm::vm(std::vector<uint8_t> code) : bytecode(code) {}

uint64_t vm::pop() {
  if (stack.empty()) {
    std::cerr << "[CRITICAL ERROR] Stack Underflow! PC: "<< pc << std::endl;
    exit(1);
  }
  uint64_t val = stack.back();
  stack.pop_back();
  return val;
}
void vm::push(uint64_t val) {
  if (stack.size() >= 1024) {
    std::cerr << "[CRITICAL ERROR] Stack Overflow! "<< std::endl;
      exit(1);
  }
  stack.push_back(val);
}
void vm::run() {
    while (pc < bytecode.size()) {
        uint8_t instruction = bytecode[pc++];

        switch (instruction) {
            case 0x00: // EOF / HALT
                return;

            case 0x01: { // OP_PUSH (Reading uint64_t from bytecode)
                uint64_t value = 0;
                for (int i = 0; i < 8; ++i) {
                    value |= (static_cast<uint64_t>(bytecode[pc++]) << (i * 8));
                }
                push(value);
                break;
            }

            case 0x02: { // OP_ADD
                uint64_t b = pop();
                uint64_t a = pop();
                push(a + b);
                break;
            }

            case 0x03: { // OP_SUB
                uint64_t b = pop();
                uint64_t a = pop();
                push(a - b);
                break;
            }

            case 0x04: { // OP_MUL
                uint64_t b = pop();
                uint64_t a = pop();
                push(a * b);
                break;
            }

            case 0x05: { // OP_DIV
                uint64_t b = pop();
                uint64_t a = pop();
                if (b == 0) {
                    std::cerr << "[CRITICAL ERROR] Division by zero!" << std::endl;
                    exit(1);
                }
                push(a / b);
                break;
            }

            case 0x06: { // OP_POW (Power "**")
                uint64_t b = pop();
                uint64_t a = pop();
                push(static_cast<uint64_t>(std::pow(a, b)));
                break;
            }

            case 0x09: { // OP_ROT (Root "//")
                uint64_t a = pop();
                push(static_cast<uint64_t>(std::sqrt(a)));
                break;
            }

            case 0x0A: { // OP_CLAMP (Затискач ><)
                uint64_t max_val = pop();
                uint64_t min_val = pop();
                uint64_t val     = pop();
                
                if (val < min_val) val = min_val;
                if (val > max_val) val = max_val;
                
                push(val);
                break;
            }

            default:
                std::cerr << "[ERROR] Unknown OpCode: " << static_cast<int>(instruction) << std::endl;
                return;
        }
    }
}

} // namespace WIRE

