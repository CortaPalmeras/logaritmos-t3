
#include <cstddef>
#include <string>
#include <random>
#include <iostream>
#include <fstream>
#include <functional>

#include "tarea.hpp"

size_t primo_grande = 2147483647;
std::hash<std::string> strHash;

// FAMILIA UNIVERSAL DE HASHES PARA STRINGS
HashFunction::HashFunction(size_t a, size_t b, size_t r) : a(a), b(b), r(r) {}

size_t HashFunction::operator()(const std::string& s) const {
    size_t suma = strHash(s) % r;
    return (((a * suma + b)) % primo_grande) % r;
}



// GENERACION DE FUNCIONES DE HASH
const size_t RANDOM_SEED = 382;
std::default_random_engine rng(RANDOM_SEED);

std::vector<HashFunction> generateHashFunctions(size_t k, size_t r) {
    std::vector<HashFunction> hashFunctions;
    std::uniform_int_distribution<size_t> dist(0, primo_grande - 1);

    for (size_t i = 0; i < k; ++i) {
        size_t a = dist(rng);
        size_t b = dist(rng);

        hashFunctions.emplace_back(a, b, r);
    }

    return hashFunctions;
}




// LEER UN ARCHIVO
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




// GREP SEARCH 
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



// BLOOM FILTER
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

