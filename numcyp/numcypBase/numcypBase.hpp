#ifndef NUMCYPBASE_HPP
#define NUMCYPBASE_HPP

#include "../numcyp.hpp"
#include "../numcypArray/numcypArray.hpp"
#include <iostream>
#include <vector>
#include <type_traits>
#include <iterator>
#include <cmath>


namespace numcyp
{    
   
    template <typename T>
    NumcypArray array(T& data, std::vector<int> shape) {
        //Must verify the shape manually
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        NumcypArray arr(shape);

        //Convert the data to an 1D vector
        arr.flatten(data, arr.data);

        return arr;
    };   

    NumcypArray full(std::vector<int> shape, float value);
    NumcypArray zeros(std::vector<int> shape);
    NumcypArray ones(std::vector<int> shape);
    

    NumcypArray arange(float start, float end, float step=1);
    NumcypArray linspace(float start, float end, int nbr_divisions);
}

#endif

