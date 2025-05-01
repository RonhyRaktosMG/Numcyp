#include "numcyp/numcyp.hpp"
#include "numcyp/numcypBase/numcypBase.hpp"
#include "numcyp/numcypArray/numcypArray.hpp"

#define np numcyp

#include <vector>
#include <iostream>

using namespace std;

int main () {
    // 1D array
    /* vector<int> vec = {
        1, 2, 3, 5,
    };
    np::NumcypArray a = np::array(vec, {4}); */


    // 2D array
    vector<vector<int>> vec = {
        {1, 2, 3, 5},
        {4, 5, 6, 5},
        {7, 8, 9, 5}
    };
    np::NumcypArray a = np::array(vec, {3, 4});


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
    };  
    np::NumcypArray a = np::array(vec, {3,2,4}); */
   

    cout << "Le  tableau : \n" << a << endl;
    np::NumcypArray c = a.sum(0);
    cout << "Le tableau c : \n" << c << endl;
    return 0;
}