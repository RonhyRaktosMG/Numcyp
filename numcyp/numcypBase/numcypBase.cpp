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
}
