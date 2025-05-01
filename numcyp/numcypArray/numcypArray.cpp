#include "numcypArray.hpp"


namespace numcyp
{
    NumcypArray::NumcypArray(std::vector<int> _shape)
    {
        shape = _shape;
        ndim = shape[0];
        size = getDataSize();
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


    /* ========== INSPECTING ARRAY ============= */


    /* ========== ARRAY MATHEMATICS ============= */
        // Arithmetic operations
    NumcypArray operator+(NumcypArray& arr1, NumcypArray& arr2){
        NumcypArray arr(arr1.shape);
        for (int i=0; i<arr1.getDataSize(); i++)
        {
            arr.data.push_back(arr1.data[i] + arr2.data[i]);
        }
        return arr;
    }
    NumcypArray operator-(NumcypArray& arr1, NumcypArray& arr2){
        NumcypArray arr(arr1.shape);
        for (int i=0; i<arr1.getDataSize(); i++)
        {
            arr.data.push_back(arr1.data[i] - arr2.data[i]);
        }
        return arr;
    }
    NumcypArray operator*(NumcypArray& arr1, NumcypArray& arr2){
        NumcypArray arr(arr1.shape);
        for (int i=0; i<arr1.getDataSize(); i++)
        {
            arr.data.push_back(arr1.data[i] * arr2.data[i]);
        }
        return arr;
    }
    NumcypArray operator/(NumcypArray& arr1, NumcypArray& arr2){
        NumcypArray arr(arr1.shape);
        for (int i=0; i<arr1.getDataSize(); i++)
        {
            arr.data.push_back(arr1.data[i] / arr2.data[i]);
        }
        return arr;
    }

        // Comparison
    NumcypArray operator<(NumcypArray& arr, float a)
    {
        NumcypArray res(arr.shape);
        
        for (int i=0; i<res.getDataSize(); i++)
        {
            res.data.push_back((arr.data[i] < a) ? 1 : 0);
        }

        return res;
    }
    
        // Aggregate functions
    int NumcypArray::sum()
    {
        int sum = 0;
        for (int i=0; i<getDataSize(); i++)
        {
            sum += data[i];
        }
        return sum;
    }
    NumcypArray NumcypArray::sum(int axis)
    {
        if (axis >= shape.size())
        {
            std::cout << "Axis out of range!\n";
            exit(EXIT_FAILURE);
        }

        //!!!!!! eto elah zao
        
        return res;
    }


    /* ========= SUBSETTING, SLICING, INDEXING =========== */
    NumcypArray NumcypArray::operator[](int index){
        if (index >= shape[0])
        {
            std::cout << "Index out of range!\n";
            exit(EXIT_FAILURE);
        }

        if (shape.size() == 1) {
            // If 1D array
            NumcypArray sub({1});
            sub.data.push_back(data[index]);
            return sub;
        }

        int dataToCopy = 1;
        for (size_t i = 1; i < shape.size(); i++) {
            dataToCopy *= shape[i];
        }

        // Create the new shape for the sub-array
        std::vector<int> newShape(shape.begin() + 1, shape.end());

        // Create the sub-array
        NumcypArray sub(newShape);
        for (int i = dataToCopy * index; i < dataToCopy * (index + 1); i++) {
            sub.data.push_back(data[i]);
        }

        return sub;
    }
    NumcypArray NumcypArray::slice(int start, int end){
        if (start < 0 || end > shape[0])
        {
            std::cout << "Index out of range!\n";
            exit(EXIT_FAILURE);
        }

        if (shape.size() == 1)
        {
            // If 1D array
            NumcypArray sub({end-start});
            for (int i = start; i < end; i++)
            {
                sub.data.push_back(data[i]);
            }
            return sub;
        }

        int dataToCopy = 1;
        for (size_t i = 1; i < shape.size(); i++) {
            dataToCopy *= shape[i];
        }
        // Create the new shape for the sub-array
        std::vector<int> newShape(shape.begin(), shape.end());
        newShape[0] = end - start;

        // Create the sub-array
        NumcypArray sub(newShape);
        for (int i = dataToCopy * start; i < dataToCopy * end; i++) {
            sub.data.push_back(data[i]);
        }
        return sub;
    }
        
    //Boolean indexing
    NumcypArray NumcypArray::operator[](NumcypArray& boolArr)
    {
        if (boolArr.getDataSize() != getDataSize())
        {
            std::cout << "Boolean array must have the same size as the original array!\n";
            exit(EXIT_FAILURE);
        }

        
        int dataToCopy = 0;
        for (int i=0; i<boolArr.getDataSize(); i++)
        {
            if (boolArr.data[i] == 1)
            {
                dataToCopy++;
            }
        }

        std::cout << "data to copy : " << dataToCopy << std::endl;

        // Create the new shape for the sub-array
        std::vector<int> newShape = {dataToCopy};
        NumcypArray res(newShape);
        for (size_t i = 1; i < shape.size(); i++) {
            if (boolArr.data[i] == 1)
            {
                res.data.push_back(data[i]);
            }
        }

        return res;
    }

    /* ========= ARRAY MANIPULATION =========== */
        // Changing array shape
    NumcypArray NumcypArray::reshape(std::vector<int> new_shape)
    {
        int new_size = 1;
        for (int i=0; i<new_shape.size(); i++)
            new_size *= new_shape[i];

        if (new_size != getDataSize())
        {
            std::cout << "Cannot reshape array of size " << getDataSize() << " into shape ";
            for (int i=0; i<new_shape.size(); i++)
                std::cout << new_shape[i] << " ";
            std::cout << "\n";
            exit(EXIT_FAILURE);
        }

        NumcypArray arr(new_shape);
        for (int i=0; i<data.size(); i++)
        {
            arr.data.push_back(data[i]);
        }
        return arr;
    }
    NumcypArray NumcypArray::ravel()
    {
        NumcypArray res({getDataSize()});
        for (int i=0; i<getDataSize(); i++)
        {
            res.data.push_back(data[i]);
        }
        return res;
    }

        // Adding / Removing elements
    NumcypArray NumcypArray::resize(std::vector<int> new_shape)
    {
        int new_size = 1;
        for (int i=0; i<new_shape.size(); i++)
            new_size *= new_shape[i];

        NumcypArray arr(new_shape);
        for (int i=0; i<new_size; i++)
        {
            arr.data.push_back(data[i%getDataSize()]);
        }
        return arr;
    }
}





