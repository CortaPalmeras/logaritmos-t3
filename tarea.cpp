
#include <cstddef>
#include <limits>
#include <string>
#include <functional>
#include <random>
#include <iostream>
#include <fstream>

#include "tarea.hpp"

const size_t RANDOM_SEED = 382;
std::default_random_engine rng(RANDOM_SEED);

const size_t MIN_NUM = std::numeric_limits<size_t>::min();
const size_t MAX_NUM = std::numeric_limits<size_t>::max();
std::uniform_int_distribution<size_t> dist(MIN_NUM, MAX_NUM);

std::hash<std::string> stringHash;

HashFunctions generateHashFunctions(size_t k, size_t range) {
    HashFunctions hashFunctions;
    hashFunctions.reserve(k);

    for (size_t i = 0; i < k; ++i) {
        size_t seed = dist(rng);

        hashFunctions.emplace_back([seed, range](const std::string& str) {
            return (stringHash(str) ^ seed) % range;
        });
    }

    return hashFunctions;
}


std::vector<std::string> readFile(std::string name) {
    std::ifstream archivo(name);

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<std::string> lines;

    getline(archivo, line);

    while (getline(archivo, line)) {
        lines.push_back(line);
    }

    archivo.close();

    return lines;
}


GrepSearch::GrepSearch() : words() {}

void GrepSearch::insert(const std::string& s) {
    words.push_back(s);
}


bool GrepSearch::search(const std::string& s) {
    for (const std::string& word : words) {
        if (s == word) {
            return true;
        }
    }
    return false;
}



BloomFilter::BloomFilter(size_t m, size_t k) : bits(m, false) {
    funcs = generateHashFunctions(k, m);
}

void BloomFilter::insert(const std::string& s) {
    for (const HashFunction& hash : funcs) {
        bits[hash(s)] = true;
    }
}

bool BloomFilter::search(const std::string& s) {
    for (const HashFunction& hash : funcs) {
        if (bits[hash(s)] == false) {
            return false;
        }
    }
    return true;
}



