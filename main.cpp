#include "numcyp/numcyp.hpp"
#include "numcyp/numcypBase/numcypBase.hpp"

#define np numcyp

#include <vector>

int main () {
    std::vector<std::vector<int>> vec = {
        {1, 2, 3, 5},
        {4, 5, 6, 5},
        {7, 8, 9, 5}
    };
   
    np::print();
    np::array(vec, {3, 4});
    return 0;
}