#include "numcypBase.hpp"

namespace numcyp
{

    NumcypArray full(std::vector<int> shape, float value)
    {
        NumcypArray arr(shape);

        for (int i=0; i<arr.getDataSize(); i++)
            arr.data.push_back(value);

        return arr;
    }
    NumcypArray zeros(std::vector<int> shape)
    {
        return full(shape, 0);
    }
    NumcypArray ones(std::vector<int> shape)
    {
        return full(shape, 1);
    }
    NumcypArray eye(int dimension)
    {
        NumcypArray arr({dimension, dimension});
        int l = 0;
        for (int i=0; i<arr.getDataSize(); i++)
        {
            // 1, 0 ,0
            // 0, 1, 0
            // 0, 0, 1
            if (i%dimension == l){
                arr.data.push_back(1);
            }
            else {
                arr.data.push_back(0);
            }
            if (i%dimension == dimension-1)
            {
                l++;
            }
        }
        return arr;
    }


    NumcypArray arange(float start, float end, float step)
    {
        int array_size = ceil((end - start) / step);  // !!! Doit être Math.ceil()
        float temp_value = start;
        std::cout << "array size : " << array_size << std::endl;
        
        NumcypArray arr({array_size});
        for (int i=0; i<array_size; i++)
        {
            arr.data.push_back(temp_value);
            temp_value += step;
        }
        return arr;
    }
    NumcypArray linspace(float start, float end, int nbr_divisions)
    {
        float temp_value = start;
        NumcypArray arr({nbr_divisions});
        for (int i=0; i<nbr_divisions; i++)
        {
            arr.data.push_back(temp_value);
            temp_value += (end-start)/ (nbr_divisions-1);
        }
        
        return arr;
    }



    /* ============== */
    /* TEMPLATE ARRAY */
    /* ============== */




    /* ========= ARRAY MATHEMATICS =========== */
        // Arithmetic operations
    int scalar_product(NumcypArray& a, NumcypArray& b)
    {
        return a.scalar_product(b);
    }
    NumcypArray dot(NumcypArray& a, NumcypArray& b)
    {
        return a.dot(b);
    }

    


    /* ========= ARRAY MANIPULATION =========== */
        // Transposing Array
    NumcypArray transpose(NumcypArray& arr)
    {
        if (arr.shape.size() != 2)
        {
            std::cout << "Transpose only works for 2D arrays!\n";
            exit(EXIT_FAILURE);
        }

        std::vector<int> new_shape;
        for (int i=arr.shape.size()-1; i>=0; i--)
        {
            new_shape.push_back(arr.shape[i]);
        }

        NumcypArray newArr(new_shape);
        for (int i=0; i<arr.getDataSize(); i++)
        {
            newArr.data.push_back(0);
        }
        
        int rows = arr.shape[0];
        int columns = arr.shape[1];

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < columns; j++) {
                newArr.data[j * rows + i] = arr.data[i * columns + j];
            }
        }

        return newArr;
    }
        // Adding / Removing elements
    NumcypArray append(NumcypArray& arr1, NumcypArray& arr2)
    {
        NumcypArray arr({arr1.getDataSize() + arr2.getDataSize()});
        for (int i=0; i<arr1.getDataSize(); i++)
        {
            arr.data.push_back(arr1.data[i]);
        }
        for (int i=0; i<arr2.getDataSize(); i++)
        {
            arr.data.push_back(arr2.data[i]);
        }
        return arr;
    }
    NumcypArray insert(NumcypArray& arr, int index, float value)        // !!!!!! afaka atao tableau ny index sy ny value
    {
        NumcypArray newArr({arr.getDataSize() + 1});
        for (int i=0; i<index; i++)
        {
            newArr.data.push_back(arr.data[i]);
        }
        newArr.data.push_back(value);
        for (int i=index; i<arr.getDataSize(); i++)
        {
            newArr.data.push_back(arr.data[i]);
        }
        return newArr;
    }
    NumcypArray npdelete(NumcypArray& arr, int index)
    {
        NumcypArray newArr({arr.getDataSize() - 1});
        for (int i=0; i<index; i++)
        {
            newArr.data.push_back(arr.data[i]);
        }
        for (int i=index+1; i<arr.getDataSize(); i++)
        {
            newArr.data.push_back(arr.data[i]);
        }
        return newArr;
    }
        // Splitting Array
    std::vector<NumcypArray> hsplit(NumcypArray& arr, int nbr_splits)
    {
        if (arr.shape.size() != 2)
        {
            std::cout << "Split only works for 2D arrays!\n";
            exit(EXIT_FAILURE);
        }

        if (arr.shape[1] % nbr_splits != 0)
        {
            std::cout << "Cannot split array of shape " << arr.shape[1] << " into " << nbr_splits << "\n";
            exit(EXIT_FAILURE);
        }

        std::vector<NumcypArray> res;
        int new_shape_col = arr.shape[1] / nbr_splits;
        std::vector<int> new_shape;
        new_shape.push_back(arr.shape[0]);
        if (new_shape_col != 1)
            new_shape.push_back(new_shape_col);
        for (int i=0; i<nbr_splits; i++)
        {
            NumcypArray newArr(new_shape);
            for (int j=0; j<arr.shape[0]; j++)
            {
                for (int k=0; k<new_shape_col; k++)
                {
                    newArr.data.push_back(arr.data[j*arr.shape[1] + i*new_shape_col + k]);
                }
            }
            res.push_back(newArr);
        }
        
        return res;
    }
    std::vector<NumcypArray> vsplit(NumcypArray& arr, int nbr_splits)
    {
        if (arr.shape.size() != 2)
        {
            std::cout << "Split only works for 2D arrays!\n";
            exit(EXIT_FAILURE);
        }

        if (arr.shape[0] % nbr_splits != 0)
        {
            std::cout << "Cannot split array of shape " << arr.shape[0] << " into " << nbr_splits << "\n";
            exit(EXIT_FAILURE);
        }

        std::vector<NumcypArray> res;
        int new_shape_row = arr.shape[0] / nbr_splits;
        std::vector<int> new_shape;
        if (new_shape_row != 1)
            new_shape.push_back(new_shape_row);
        new_shape.push_back(arr.shape[1]);
        for (int i=0; i<nbr_splits; i++)
        {
            NumcypArray newArr(new_shape);
            for (int j=0; j<new_shape_row; j++)
            {
                for (int k=0; k<arr.shape[1]; k++)
                {
                    newArr.data.push_back(arr.data[(i*new_shape_row + j)*arr.shape[1] + k]);
                }
            }
            res.push_back(newArr);
        }
        
        return res;
    }

}




