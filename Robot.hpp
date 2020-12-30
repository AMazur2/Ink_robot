#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "Shelf.hpp"

class Robot
{
    private:
        char types[4] = {'C', 'M', 'Y', 'K'};
        std::vector<Ink> moveRight(std::vector<Ink> shelf, int start);
        std::vector<Ink> moveLeft(std::vector<Ink> shelf, int start, int stop);
        std::vector<Ink> brutalForce(std::vector<Ink> shelf, int start, int nextColour);
    public:
        Robot() {};
        ~Robot() {};
        void brutalSolver(Shelf *shelf);
};

#endif