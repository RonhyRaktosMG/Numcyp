#ifndef NUMCYPARRAY_HPP
#define NUMCYPARRAY_HPP

#include "../numcyp.hpp"
#include <iostream>
#include <vector>
#include <type_traits>
#include <algorithm>


namespace numcyp
{

    class NumcypArray
    {
        public:
            std::vector<float> data {};
            
            std::vector<int> shape {};
            int ndim = 0;
            int size = 0;

            NumcypArray(std::vector<int> _shape);
            ~NumcypArray();

            void printShape();
            int getDataSize();
            friend std::ostream& operator<<(std::ostream& os, NumcypArray& arr);


            // Cas de base : si c'est un nombre (float, int, double...)
            template <typename T>
            typename std::enable_if<std::is_arithmetic<T>::value>::type
            flatten(const T& value, std::vector<float>& output) {
                output.push_back(static_cast<float>(value));
            }

            // Cas récursif : si c'est un std::vector ou un autre conteneur
            template <typename T>
            typename std::enable_if<!std::is_arithmetic<T>::value>::type
            flatten(const T& container, std::vector<float>& output) {
                using std::begin;
                using std::end;
                for (const auto& elem : container) {
                    flatten(elem, output);
                }
            }



        /* ========== INSPECTING ARRAY ============= */




        /* ========= ARRAY MATHEMATICS =========== */
            // Arithmetic operations
        friend NumcypArray operator+(NumcypArray& arr1, NumcypArray& arr2);
        friend NumcypArray operator-(NumcypArray& arr1, NumcypArray& arr2);
        friend NumcypArray operator*(NumcypArray& arr1, NumcypArray& arr2);
        friend NumcypArray operator/(NumcypArray& arr1, NumcypArray& arr2);
        int scalar_product(NumcypArray& b);
        NumcypArray dot(NumcypArray& b);

            // Comparison
        friend NumcypArray operator<(NumcypArray& arr, float a);
        
            // Aggregate functions
        float sum();
        NumcypArray sum(int axis);
        float min();
        NumcypArray min(int axis);
        float max();
        NumcypArray max(int axis);
        float mean();



        /* ========= SORTING =========== */
        void sort();



        /* ========= SUBSETTING, SLICING, INDEXING =========== */
        NumcypArray operator[](int index);
        NumcypArray slice(int start, int end);
            //Boolean Indexing
        NumcypArray operator[](NumcypArray& boolArr);


        /* ========= ARRAY MANIPULATION =========== */
            // Changing array shape
        NumcypArray reshape(std::vector<int> new_shape);
        NumcypArray ravel();

            // Adding / Removing elements
        NumcypArray resize(std::vector<int> new_shape);





            

    };
} // namespace numcyp

#endif