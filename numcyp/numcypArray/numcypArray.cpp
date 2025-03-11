#include "numcypArray.hpp"


namespace numcyp
{
    NumcypArray::NumcypArray(std::vector<int> _shape)
    {
        shape = _shape;
        //std::cout << "NumcypArray constructor with ";
        //printShape();
    }

    NumcypArray::~NumcypArray()
    {
        //std::cout << "NumcypArray destructor" << std::endl;
    }

    void NumcypArray::printShape(){
        std::cout << "Shape: (";
        for (size_t i = 0; i < shape.size(); ++i) {
            std::cout << shape[i] << (i < shape.size() - 1 ? ", " : "");
        }
        std::cout << ")" << std::endl;
    }
    int NumcypArray::getDataSize(){
        int i=1;
        for (int& j: shape)
            i*=j;
        return i;
    }
    std::ostream& operator<<(std::ostream& os, NumcypArray& arr){
        std::cout << "\n";

        std::vector<int> temp_shape = {};
        int nbr_dim = arr.shape.size();
        int temp_dim = nbr_dim-1;
        int current_index = 0;
        for (int i=0; i<arr.shape.size(); i++)
            temp_shape.push_back(0);
        
        for (int i=0; i<nbr_dim; i++)
        {
            std::cout << "[";
        }

        while (1)
        {
            temp_dim = nbr_dim-1;
            std::cout << " " << arr.data[current_index] << " ";
            
            current_index++;

            temp_shape[temp_dim]++;
            while (temp_dim > 0) {
                if (temp_shape[temp_dim] == arr.shape[temp_dim])
                {
                    temp_shape[temp_dim] = 0;
                    temp_shape[temp_dim-1]++;
                    temp_dim--;
                    if (current_index != arr.data.size())
                    {
                        std::cout << " ]";
                        std::cout << "\n [";
                    }
                }
                else
                {
                    break;
                }
            }

            if (temp_shape[0] == arr.shape[0])
            {
                break;
            }
        }
        

        for (int i=0; i<nbr_dim; i++)
        {
            std::cout << "]";
        }

        std::cout << "\n\n";

        return os;
    }


    // display ((2, 3), (4, 5)) [
    // display (2, 3) -> (4, 5) [[
    // display (2 -> 3 -> 4 -> 5) [[2, 3], [4, 5]]
    
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