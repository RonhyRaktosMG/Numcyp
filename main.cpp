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
    */


    // 2D array
    vector<vector<int>> vec = {
        {3, 4, 2},
        {4, 2, 3},
        {7, 8, 2}
    };
   

/*     vector<vector<vector<int>>> vec = {
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
*/
   
    np::NumcypArray a = np::array(vec);
    np::NumcypArray b = np::array(vector<int>{4, 5, 6});
    cout << "Le  tableau : \n" << a << endl;
    cout << "b : " << b << endl;

    np::NumcypArray c = np::dot(a, b);

    cout << "c : " << c << endl;
    return 0;
}