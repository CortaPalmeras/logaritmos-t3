
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <chrono>

// Este programa genera los valores vistos en la tabla 3 del informe

#define NOW() std::chrono::high_resolution_clock::now()

#include "tarea.hpp"

int main(int argc, char** argv) {

    if (argc != 3) {
        std::cerr << "Ingresa parametros de cantidad de bits y de hashes" << std::endl;
        exit(1);
    }

    size_t M = std::stoi(argv[1]);
    size_t k = std::stoi(argv[2]);

    std::vector<std::string> names = readFile("../data/Popular-Baby-Names-Final.csv");
    std::vector<std::string> films = readFile("../data/Film-Names.csv");

    std::ofstream resultados("resultados2.csv");

    resultados << "N,cantidad_nombres,t_bloom,t_grep,positive_bloom,positive_grep" << std::endl;

    BloomFilter bloom(M, k);
    GrepSearch grep;

    for (const auto& s : names) {
        bloom.insert(s);
        grep.insert(s);
    }

    for (size_t i = 10; i <= 16;  i += 2) {
        size_t N = std::pow(2, i);
        
        for (size_t j = 0; j <= 4; j++) {
            size_t cantidad_nombres = N * j / 4;

            std::vector<std::string> busquedas;
            busquedas.reserve(N);

            for (size_t l = 0; l < cantidad_nombres; l++) {
                busquedas.push_back(names[l]);
            }

            size_t f_size = films.size();
            for (size_t l = cantidad_nombres; l < N; l++) {
                busquedas.push_back(films[l%f_size]);
            }

            size_t positivos_bloom = 0;
            size_t positivos_grep = 0;

            double t_acumulado_bloom = 0;
            double t_acumulado_grep = 0;

            for (const std::string& s : busquedas) {
                auto t1 = NOW();
                positivos_bloom += bloom.search(s);
                auto t2 = NOW();
                positivos_grep += grep.search(s);
                auto t3 = NOW();

                std::chrono::duration<double_t, std::milli> t_bloom = t2 - t1;
                std::chrono::duration<double_t, std::milli> t_grep = t3 - t2;

                t_acumulado_bloom += t_bloom.count();
                t_acumulado_grep += t_grep.count();
            }


            resultados << N << ',' << cantidad_nombres << ','
                       << t_acumulado_bloom << ',' << t_acumulado_grep << ','
                       << positivos_bloom << ',' << positivos_grep << std::endl;

            std::cout << N << ' ' << cantidad_nombres << ' ' << positivos_bloom << ' ' << positivos_grep << std::endl;
        }
    }
    return 0;
}

