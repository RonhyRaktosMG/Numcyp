#include <iostream>
#include <vector>
#include <stdexcept>
#include <type_traits>

class NumcypArray {
public:
    std::vector<int> shape;

    NumcypArray(std::vector<int> s) : shape(std::move(s)) {}

    void printShape() const {
        std::cout << "Shape: (";
        for (size_t i = 0; i < shape.size(); ++i) {
            std::cout << shape[i] << (i < shape.size() - 1 ? ", " : "");
        }
        std::cout << ")" << std::endl;
    }
};

// Fonction pour récupérer la shape d'un tableau de n'importe quelle profondeur
template <typename T>
std::vector<int> inferShape(const T& data) {
    std::vector<int> shape;
    auto* current = &data; // Utilisation d'un pointeur pour éviter les problèmes de références

    while constexpr (std::is_same_v<std::decay_t<decltype(*current)>, std::vector<typename std::decay_t<decltype(*current)>::value_type>>) {
        shape.push_back(current->size());
        if (!current->empty()) {
            current = &(*current)[0]; // On descend dans la structure
        } else {
            break;
        }
    }

    return shape;
}

// Fonction principale
template <typename T>
NumcypArray array(const T& data) {
    auto shape = inferShape(data);
    if (shape.empty()) {
        throw std::invalid_argument("Array must have at least one row");
    }
    return NumcypArray(shape);
}

// Exemple d'utilisation
int main() {
    std::vector<std::vector<std::vector<int>>> data = {
        {
            {1, 2}, {3, 4}
        },
        {
            {5, 6}, {7, 8}
        }
    };

    NumcypArray arr = array(data);
    arr.printShape(); // Affiche : Shape: (2, 2, 2)

    std::vector<int> oneD = {1, 2, 3};
    NumcypArray arr1D = array(oneD);
    arr1D.printShape(); // Affiche : Shape: (3)

    return 0;
}
