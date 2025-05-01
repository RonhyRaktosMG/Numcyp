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







    /* ========= ARRAY MANIPULATION =========== */
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
}
