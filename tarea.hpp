
#include <cmath>
#include <cstddef>
#include <functional>
#include <string>

// Clase que representa una familia universal de funciones de hash
class HashFunction {
private:
    size_t a;
    size_t b;
    size_t r;

    public:
    HashFunction(size_t a, size_t b, size_t r);

    size_t operator()(std::string s) const;
};

// funcion que genera un conjunto aleatorio de funciones de hashing 
// en base a una familia de hashes universal
std::vector<HashFunction> generateHashFunctions(size_t k, size_t range);

// funcion para leer las lineas de un archivo
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
    std::vector<HashFunction> funcs;
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


