
#include <cstddef>
#include <functional>
#include <string>

using HashFunction = std::function<size_t(const std::string&)>;
using HashFunctions = std::vector<HashFunction>;

HashFunctions generateHashFunctions(size_t k, size_t range);

std::vector<std::string> readFile(std::string name);

// Implementa la busqueda de string manera secuenciañ sin filtro
class GrepSearch {
    // Arreglo de palabras guardadas en el buscador.
    std::vector<std::string> words;

public:
    GrepSearch();

    // Inserta una palabra.
    void insert(const std::string& s);

    // Busca una palabra, retorna true si está y
    // false si no.
    bool search(const std::string& s);

};


// Implementa la busqueda de string con filtro de Bloom 
class BloomFilter {
    // Arreglo de funciones de hashing distintas.
    HashFunctions funcs;
    // Arreglo de bits.
    std::vector<bool> bits;

public:
    BloomFilter() = delete;
    BloomFilter(size_t m, size_t k);

    // Inserta una palabra.
    void insert(const std::string& s);

    // Busca una palabra, retorna true si está y 
    // false si no, puede tener falsos positivos.
    bool search(const std::string& s);
};


