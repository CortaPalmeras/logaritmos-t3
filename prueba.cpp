
#include <cstddef>
#include <limits>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <random>

using HashFunction = std::function<size_t(const std::string&)>;
using HashFunctions = std::vector<HashFunction>;

const size_t RANDOM_SEED = 382;
const size_t MIN_NUM = std::numeric_limits<size_t>::min();
const size_t MAX_NUM = std::numeric_limits<size_t>::max();

std::default_random_engine rng(RANDOM_SEED);
std::uniform_int_distribution<size_t> dist(MIN_NUM, MAX_NUM);

size_t hashFunction(const std::string& str, size_t seed, size_t range) {
    std::hash<std::string> hashFn;
    return (hashFn(str) ^ seed) % range;
}

// Generate multiple hash functions
HashFunctions generateHashFunctions(size_t k, size_t range) {
    HashFunctions hashFunctions;
    hashFunctions.reserve(k);

    for (size_t i = 0; i < k; ++i) {
        size_t seed = dist(rng);

        hashFunctions.emplace_back([seed, range](const std::string& str) {
            return hashFunction(str, seed, range);
        });
    }

    return hashFunctions;
}

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
