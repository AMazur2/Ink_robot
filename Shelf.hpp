#ifndef SHELF_HPP
#define SHELF_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Ink.hpp"

class Shelf
{
    private:
    Shelf(std::vector<Ink> shelf);

    std::vector<Ink> shelf;
    
    public:
        Shelf() {};
        Shelf(int number);
        Shelf(int amount, std::string sequences[], int probabilities[], int size);
        ~Shelf() {};
        std::vector<Ink> getShelf() {return shelf;};
        void setShelf(std::vector<Ink> s) {shelf = s;};
        void showShelf();

        static Shelf*  getShelfFromSring(std::string s);
        static Shelf*  getShelfFromFile(std::string fileName);

    std::string ShelfToString();

    static bool checkIfSorted(std::string shelf);

    static int countLetters(std::string shelf, int start);
};

#endif
