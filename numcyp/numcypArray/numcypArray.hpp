#ifndef NUMCYPARRAY_HPP
#define NUMCYPARRAY_HPP

#include "../numcyp.hpp"
#include <iostream>
#include <vector>

namespace numcyp
{

    class NumcypArray
    {
        public:
            std::vector<int> shape {};

            NumcypArray(std::vector<int> _shape);
            ~NumcypArray();

            void printShape();

    };
} // namespace numcyp

#endif