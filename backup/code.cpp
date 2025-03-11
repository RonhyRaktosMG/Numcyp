   /* // Cas de base : si c'est un nombre (float, int, double...), on l'ajoute
            template <typename T>
            typename std::enable_if<std::is_arithmetic<T>::value>::type
            displayData(const T& value) {
                std::cout << value << ", ";
            }

            // Cas récursif : si c'est un std::vector ou un autre conteneur, on le parcourt
            template <typename T>
            typename std::enable_if<!std::is_arithmetic<T>::value>::type
            displayData(const T& value) {
                
                for (auto& element: value){
                    std::cout << " [ ";
                    displayData(element);
                    std::cout << " ], \n";
                }
            } */