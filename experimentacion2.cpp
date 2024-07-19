
#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#define NOW() std::chrono::high_resolution_clock::now()

#include "tarea.hpp"

int main(void) {

    std::vector<std::string> names = readFile("../data/Popular-Baby-Names-Final.csv");
    std::vector<std::string> films = readFile("../data/Film-Names.csv");

    std::ofstream resultados("resultados2.csv");

    resultados << "N,m,k,p_bloom,p_grep" << std::endl;

    BloomFilter bloom(M, k);
    GrepSearch grep;

    for (const auto& s : names) {
        bloom.insert(s);
        grep.insert(s);
}

