#ifndef INK_HPP
#define INK_HPP
#include <string>
#include <iostream>

class Ink
{
    private:
        char colour;
    
    public:
        Ink() {};
        Ink(char col) {colour = col;};
        ~Ink() {};
        char getColour() {return colour;};

};

#endif
