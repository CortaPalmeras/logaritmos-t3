
#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

#include "tarea.hpp"

int main(int argc, char** argv) {
    if (argc <= 3) {
        exit(1);
    }

    size_t hfunc_n = std::stoi(argv[1]);
    size_t range = std::stoi(argv[2]);

    std::vector<std::string> inputs;
    for (int i = 3; i < argc; i++) {
        inputs.emplace_back(argv[i]);
    }

    HashFunctions hashes = generateHashFunctions(hfunc_n, range);

    for (const std::string& input : inputs) {
        std::vector<bool> bits(range, false);

        for (const HashFunction& hash : hashes) {
            bits[hash(input)] = true;
        }

        size_t count= 0;

        for (size_t i = 0; i < bits.size(); i++) {
            count+= bits[i] == true;
        }

        std::cout << "input: \"" << input << "\" count: " << count<< std::endl;
    }

    return 0;
}
