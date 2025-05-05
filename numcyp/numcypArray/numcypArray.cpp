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
    int NumcypArray::scalar_product(NumcypArray& b)
    {
        if (shape.size() != 1 || b.shape.size() != 1)
        {
            std::cout << "Scalar product only works for 1D arrays!\n";
            exit(EXIT_FAILURE);
        }

        if (shape[0] != b.shape[0])
        {
            std::cout << "Arrays must have the same size!\n";
            exit(EXIT_FAILURE);
        }

        int res = 0;
        for (int i=0; i<getDataSize(); i++)
        {
            res += data[i] * b.data[i];
        }
        
        return res;
    }
    NumcypArray NumcypArray::dot(NumcypArray& b)
    {
        if (shape.size() > 2 || b.shape.size() > 2)
        {
            std::cout << "Dot product only works for 2D/1D arrays!\n";
            exit(EXIT_FAILURE);
        }
        if (shape.size() == 1)
        {
            std::cout << "Dot product doesn't work with 1D*Array (try reversing them or use scalar_product)" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (shape.size() == 2 && b.shape.size() == 1)
        {
            NumcypArray res(b.shape);
            for (int i=0; i<shape[0]; i++)
            {
                res.data.push_back(0);
                for (int j=0; j<shape[1]; j++)
                {
                    res.data[i] += data[i*shape[1] + j] * b.data[j];
                }
            }
            return res;
        }

        else  // 2D * 2D
        {
            if (shape[1] != b.shape[0])
            {
                std::cout << "Arrays must have the same size!\n";
                exit(EXIT_FAILURE);
            }
            int rows = shape[0];
            int columns = b.shape[1];
            NumcypArray res({rows, columns});
            
            for (int i=0; i<rows; i++)
            {
                for (int j=0; j<columns; j++)
                {
                    res.data.push_back(0);
                    for (int k=0; k<shape[1]; k++)
                    {
                        res.data[i*columns + j] += data[i*shape[1] + k] * b.data[k*columns + j];
                    }
                }
            }

            return res;
        }
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
    float NumcypArray::sum()
    {
        float sum = 0;
        for (int i=0; i<getDataSize(); i++)
        {
            sum += data[i];
        }
        return sum;
    }
    NumcypArray NumcypArray::sum(int axis)
    {
        // !!!!!!!! Tsy mande raha tsy axis=0 

        if (axis >= shape.size())
        {
            std::cout << "Axis out of range!\n";
            exit(EXIT_FAILURE);
        }

        std::vector<int> newShape(shape.begin()+1+axis, shape.end());
        NumcypArray res(newShape);

        // Calculate the sum 
        int dataToCopy = 1;
        for (size_t i = 0; i < axis; i++) {
            dataToCopy *= shape[i];
        }
        int dataToSum = 1;
        for (size_t i = axis + 1; i < shape.size(); i++) {
            dataToSum *= shape[i];
        }
        for (int i = 0; i < dataToCopy; i++) {
            for (int j = 0; j < dataToSum; j++) {
                int sum = 0;
                for (int k = 0; k < shape[axis]; k++) {
                    sum += data[i * shape[axis] * dataToSum + k * dataToSum + j];
                }
                res.data.push_back(sum);
            }
        }

        return res;
    }
    float NumcypArray::min()
    {
        float min = data[0];
        for (int i=1; i<getDataSize(); i++)
        {
            if (data[i] < min)
            {
                min = data[i];
            }
        }
        return min;
    }
    NumcypArray NumcypArray::min(int axis)
    {
        // !!!!!!!! Tsy mande raha tsy axis=0 

        if (axis >= shape.size())
        {
            std::cout << "Axis out of range!\n";
            exit(EXIT_FAILURE);
        }

        std::vector<int> newShape(shape.begin()+1+axis, shape.end());
        NumcypArray res(newShape);

        // Calculate the min 
        int dataToCopy = 1;
        for (size_t i = 0; i < axis; i++) {
            dataToCopy *= shape[i];
        }
        int dataToMin = 1;
        for (size_t i = axis + 1; i < shape.size(); i++) {
            dataToMin *= shape[i];
        }
        for (int i = 0; i < dataToCopy; i++) {
            for (int j = 0; j < dataToMin; j++) {
                int min = data[i * shape[axis] * dataToMin + j];
                for (int k = 1; k < shape[axis]; k++) {
                    if (data[i * shape[axis] * dataToMin + k * dataToMin + j] < min)
                    {
                        min = data[i * shape[axis] * dataToMin + k * dataToMin + j];
                    }
                }
                res.data.push_back(min);
            }
        }

        return res;
    }
    float NumcypArray::max()
    {
        float max = data[0];
        for (int i=1; i<getDataSize(); i++)
        {
            if (data[i] > max)
            {
                max = data[i];
            }
        }
        return max;
    }
    NumcypArray NumcypArray::max(int axis)
    {
        // !!!!!!!! Tsy mande raha tsy axis=0 

        if (axis >= shape.size())
        {
            std::cout << "Axis out of range!\n";
            exit(EXIT_FAILURE);
        }

        std::vector<int> newShape(shape.begin()+1+axis, shape.end());
        NumcypArray res(newShape);

        // Calculate the max 
        int dataToCopy = 1;
        for (size_t i = 0; i < axis; i++) {
            dataToCopy *= shape[i];
        }
        int dataToMax = 1;
        for (size_t i = axis + 1; i < shape.size(); i++) {
            dataToMax *= shape[i];
        }
        for (int i = 0; i < dataToCopy; i++) {
            for (int j = 0; j < dataToMax; j++) {
                int max = data[i * shape[axis] * dataToMax + j];
                for (int k = 1; k < shape[axis]; k++) {
                    if (data[i * shape[axis] * dataToMax + k * dataToMax + j] > max)
                    {
                        max = data[i * shape[axis] * dataToMax + k * dataToMax + j];
                    }
                }
                res.data.push_back(max);
            }
        }

        return res;
    }
    float NumcypArray::mean()
    {
        return sum() / getDataSize();
    }


    /* ========= SORTING ARRAY =========== */
    void NumcypArray::sort()
    {
        int numberInEachDim = shape[shape.size()-1];
        int index = 0;

        while (index < getDataSize())
        {
            std::sort(data.begin() + index, data.begin() + index + numberInEachDim);
            index += numberInEachDim;
        }

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





