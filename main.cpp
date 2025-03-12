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

    np::NumcypArray a = np::array(vec, {3, 2, 4});
    cout << a;
   
    np::NumcypArray a = np::eye(3);
    cout << a;

    cout << a.size << endl;
    cout << a.ndim << endl;

    np::NumcypArray b = a+a;
    b = b/b;
    cout << b ;
    return 0;
}