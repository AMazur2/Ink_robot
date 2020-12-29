#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Shelf
{
    private:
        std::vector<char> shelf;
    
    public:
        Shelf(std::string fileName);
        Shelf(int number);
        Shelf(int amount, std::string sequences[], int probabilities[], int size);
        Shelf(std::vector<char> s) {shelf = s;};
        ~Shelf();
        std::vector<char> getShelf() {return shelf;};

};