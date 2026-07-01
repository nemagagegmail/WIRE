#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Fixed paths according to project structure
#include "compiler/lexer/lexer.hpp"
#include "compiler/main/compiler.hpp"
#include "vm/main/vm.hpp"

int main(int argc, char* argv[]) {
    // Check argument count: expect input file path
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename.w>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    // Verify file extension is '.w'
    if (filename.length() < 3 || filename.substr(filename.length() - 2) != ".w") {
        std::cerr << "[ERROR] Invalid file extension. WIRE source files must end with '.w'" << std::endl;
        return 1;
    }

    // Open target source file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Could not open file: " << filename << std::endl;
        return 1;
    }

    // Read source code into string buffer
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source_code = buffer.str();
    file.close();

    // Stage 1: Initialize Lexer with source token stream
    WIRE::lexer lex(source_code);

    // Stage 2: Compile tokens into executable bytecode array
    WIRE::compiler comp(lex);
    std::vector<uint8_t> bytecode = comp.compile();

    // Stage 3: Load bytecode into Virtual Machine and execute
    WIRE::vm virtual_machine(bytecode);
    virtual_machine.run();

    return 0;
}
