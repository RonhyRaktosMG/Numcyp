#include "numcypArray.hpp"


namespace numcyp
{
    NumcypArray::NumcypArray(std::vector<int> _shape)
    {
        shape = _shape;
        std::cout << "NumcypArray constructor with ";
        printShape();
    }

    NumcypArray::~NumcypArray()
    {
        std::cout << "NumcypArray destructor" << std::endl;
    }

    void NumcypArray::printShape(){
        std::cout << "Shape: (";
        for (size_t i = 0; i < shape.size(); ++i) {
            std::cout << shape[i] << (i < shape.size() - 1 ? ", " : "");
        }
        std::cout << ")" << std::endl;
    }

    /* template <typename T>
    T empty(const std::vector<int>& shape) {
        if (shape.empty()) {
            throw std::invalid_argument("Shape cannot be empty");
        }

        if (shape.size() == 1) {
            return std::vector<typename T::value_type>(shape[0]);
        } else {
            std::vector<T> result;
            for (int i = 0; i < shape[0]; ++i) {
                result.push_back(allocateArray<typename T::value_type>(std::vector<int>(shape.begin() + 1, shape.end())));
            }
            return result;
        }
    } */
}