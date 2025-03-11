#include "numcyp/numcyp.hpp"
#include "numcyp/numcypBase/numcypBase.hpp"
#include "numcyp/numcypArray/numcypArray.hpp"

#define np numcyp

#include <vector>
#include <iostream>

using namespace std;

int main () {
    vector<vector<int>> vec = {
        {1, 2, 3, 5},
        {4, 5, 6, 5},
        {7, 8, 9, 5}
    };

    /* vector<vector<vector<int>>> vec = {
        {
            {1, 1, 2, 3},
            {1, 1, 2, 3},
        },
        {
            {2, 3, 3, 3},
            {6, 1, 2, 7},
        },
        {
            {1, 5, 2, 9},
            {1, 6, 2, 9},
        }
    }; */
   
    np::NumcypArray r = np::arange(10, 25, 2);
    cout << r;

    np::NumcypArray l = np::linspace(0, 2, 4);
    cout << l;

    return 0;
}