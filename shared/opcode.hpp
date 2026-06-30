#pragma once
#include <cstdint> // connect the library for understanding low-level hardware types 

// Instructions
namespace WIRE {
// We declare C++ to allocate exactly 8 bits for each operation 
enum class Opcode : uint8_t {
  // Basic system commands 
  OP_NONE = 0x00, // Empty operation
	OP_return = 0x01, // Finish and return value 

	// Working with stack memory 
	OP_PUSH = 0x02, // Push a constant onto the computation stack 
	OP_POP = 0x03, // Pop the top value from the stack

  // Classical mathematics
  OP_ADD = 0x04,
	OP_SUB = 0x05,
	OP_MUL = 0x06,
	OP_DIV = 0x07,
	OP_POW = 0x08, // Power
	OP_ROT = 0x09, // Root

	// Unique operations 
	OP_CLAMP = 0x0A, // Range clamp operator (><)

	// Dynamic prefix for extension .wvmm (Plugins)
	OP_VME = 0xFF
};
}

	
	
