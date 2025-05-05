#ifndef NUMCYPBASE_HPP
#define NUMCYPBASE_HPP

#include "../numcyp.hpp"
#include "../numcypArray/numcypArray.hpp"
#include <iostream>
#include <vector>
#include <type_traits>
#include <iterator>
#include <cmath>
#include <algorithm>


namespace numcyp
{    
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    getShape(const T& value, std::vector<int>& shape) {
        return;
    }
    template <typename T>
    typename std::enable_if<!std::is_arithmetic<T>::value>::type
    getShape(const T& container, std::vector<int>& shape) {
        shape.push_back(container.size());
        getShape(container[0], shape);
    }
   
    template <typename T>
    NumcypArray array(std::vector<T> data) {
        //Must verify the shape manually
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
 
        std::vector<int> shape;
        getShape(data, shape);

        NumcypArray arr(shape);

        //Convert the data to an 1D vector
        arr.flatten(data, arr.data);

        return arr;
    };   



    /* ========== INITIAL PLACEHOLDERS ============= */
    NumcypArray full(std::vector<int> shape, float value);
    NumcypArray zeros(std::vector<int> shape);
    NumcypArray ones(std::vector<int> shape);
    NumcypArray eye(int dimension);
    
    NumcypArray arange(float start, float end, float step=1);
    NumcypArray linspace(float start, float end, int nbr_divisions);





    /* ========== INSPECTING ARRAY ============= */



    /* ========= ARRAY MATHEMATICS =========== */
        // Arithmetic operations
    int scalar_product(NumcypArray& a, NumcypArray& b);
    NumcypArray dot(NumcypArray& a, NumcypArray& b);



    /* ========= ARRAY MANIPULATION =========== */
        // Transposing Array
    NumcypArray transpose(NumcypArray& arr);
        // Adding / Removing elements
    NumcypArray append(NumcypArray& arr1, NumcypArray& arr2);
    NumcypArray insert(NumcypArray& arr, int index, float value);
    NumcypArray npdelete(NumcypArray& arr, int index);
        // Splitting Array
    std::vector<NumcypArray> hsplit(NumcypArray& arr, int nbr_splits);  
    std::vector<NumcypArray> vsplit(NumcypArray& arr, int nbr_splits);

}

#endif

