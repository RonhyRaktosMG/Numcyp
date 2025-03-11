#include <iostream>
#include <vector>
#include <type_traits>

// Cas de base : si c'est un float, on l'ajoute au vecteur de sortie
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value>::type
flatten(const T& value, std::vector<float>& output) {
    output.push_back(value);
}

// Cas récursif : si c'est un std::vector, on l'explore récursivement
template <typename T>
typename std::enable_if<!std::is_floating_point<T>::value>::type
flatten(const T& container, std::vector<float>& output) {
    for (const auto& elem : container) {
        flatten(elem, output);
    }
}

int main() {
    std::vector<std::vector<std::vector<float>>> nestedVector = {
        {{1.0f, 2.0f}, {3.0f}, {3}}, 
        {{4.0f}, {5.0f, 6.0f}}, 
        {{4.0f}, {5.0f, 6.0f}}, 
    };

    std::vector<float> flatVector;
    flatten(nestedVector, flatVector);

    for (float val : flatVector) {
        std::cout << val << " ";
    }

    return 0;
}