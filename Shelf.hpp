#ifndef SHELF_HPP
#define SHELF_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Ink.hpp"

class Shelf
{
    private:
        std::vector<Ink> shelf;
    
    public:
        Shelf() {};
        Shelf(std::string fileName);
        Shelf(int number);
        Shelf(int amount, std::string sequences[], int probabilities[], int size);
        ~Shelf() {};
        std::vector<Ink> getShelf() {return shelf;};
        void showShelf();
};

#endif
