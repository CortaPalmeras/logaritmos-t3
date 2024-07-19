
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "tarea.hpp"

// Este programa genera los valores vistos en la tabla 2 del informe

#define NOW() std::chrono::high_resolution_clock::now()

int main(void) {

    std::vector<std::string> baby = readFile("../data/Popular-Baby-Names-Final.csv");
    std::vector<std::string> film = readFile("../data/Film-Names.csv");

    size_t n = baby.size();
    double ln2 = std::log(2);

    std::cout << "Palabras en baby names: " << baby.size() << std::endl;
    std::cout << "Palabras en film names: " << film.size() << std::endl;

    std::ofstream resultados("resultados1.csv");

    resultados << "m,k,k_opt,false_positives" << std::endl;

    GrepSearch grep;
    for (const auto& s : baby) {
        grep.insert(s);
    }

    size_t positivos_grep = 0;
    for (const auto& s : film) {
        positivos_grep += grep.search(s);
    }
    std::cout << "Falsos positivos del metodo grep: " << positivos_grep << std::endl;

    for (int m = 100000; m <= 3000000; m += 100000){
        size_t k_opt = std::round( ln2 * ((double) m / n));

        std::vector<size_t> ks;
        size_t intervalo = k_opt / 5;
        if (intervalo != 0) {
            for (size_t i = 0; i < k_opt; i += intervalo) {
                ks.push_back(i);
            }
        }
        ks.push_back(k_opt);
        
        for (size_t i = 5; i <= 25; i += 5) {
            ks.push_back(k_opt + i);
        }

        for (const size_t& k : ks) {

            BloomFilter bloom(m, k);

            for (const auto& s : baby) {
                bloom.insert(s);
            }

            size_t positivos_bloom = 0;
            for (const auto& s : film) {
                positivos_bloom += bloom.search(s);
            }

            resultados << m << ',' << k << ',' << k_opt << ',' << positivos_bloom - positivos_grep << std::endl;
        }
    }
}

