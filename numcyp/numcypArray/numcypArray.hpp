#ifndef NUMCYPARRAY_HPP
#define NUMCYPARRAY_HPP

#include "../numcyp.hpp"
#include <iostream>
#include <vector>
#include <type_traits>


namespace numcyp
{

    class NumcypArray
    {
        public:
            std::vector<int> shape {};
            std::vector<float> data {};

            NumcypArray(std::vector<int> _shape);
            ~NumcypArray();

            void printShape();
            int getDataSize();
            friend std::ostream& operator<<(std::ostream& os, NumcypArray& arr);


            // Cas de base : si c'est un nombre (float, int, double...), on l'ajoute
            template <typename T>
            typename std::enable_if<std::is_arithmetic<T>::value>::type
            flatten(const T& value, std::vector<float>& output) {
                output.push_back(static_cast<float>(value));
            }

            // Cas récursif : si c'est un std::vector ou un autre conteneur, on le parcourt
            template <typename T>
            typename std::enable_if<!std::is_arithmetic<T>::value>::type
            flatten(const T& container, std::vector<float>& output) {
                using std::begin;
                using std::end;
                for (const auto& elem : container) {
                    flatten(elem, output);
                }
            }


            
    };
} // namespace numcyp

#endif