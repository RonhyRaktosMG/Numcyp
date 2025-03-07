#ifndef NUMCYPBASE_HPP
#define NUMCYPBASE_HPP

#include "../numcyp.hpp"
#include "../numcypArray/numcypArray.hpp"
#include <iostream>
#include <vector>

namespace numcyp
{
    void print();
    
    template <typename T>
    NumcypArray array(T& data, std::vector<int> shape) {

        //Must verify the shape manually
        /* std::vector<int> shape;

        int s = data.size();
        if (s == 0) {
            throw std::invalid_argument("Array must have at least one row");
        }
        shape.push_back(s);

        auto* row = &data;
        
        while (row->size() != 1){
            s = row->size();
            std::cout << s << std::endl;
            shape.push_back(s);
            row = &(*row)[0];
        } */

        
        //Display of the shape
        std::cout << "Shape : (";
        for (int i:shape){
            std::cout << i << ", ";
        }
        std::cout << ")" << std::endl;

        NumcypArray a(shape);
        return a;
    };   
}

#endif

