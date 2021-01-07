#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "Shelf.hpp"
#include <utility>

class Robot
{
    private:
        char types[4] = {'C', 'M', 'Y', 'K'};
        int findNumber(std::vector<Ink> shelf);
        std::vector<int> findFours(std::vector<Ink> shelf);
        std::vector<Ink> moveRight(std::vector<Ink> shelf, int start);
        std::vector<Ink> moveLeft(std::vector<Ink> shelf, int start, int stop);
        std::vector<Ink> sortFours(std::vector<Ink> shelf, std::vector<int> fours, int start);
        std::pair<int, int> findMaximalSubstring (std::vector<Ink> shelf, int start, int colour);
        std::vector<Ink> brutalForce(std::vector<Ink> shelf, int start, int nextColour);
        std::vector<Ink> naive(std::vector<Ink> shelf, int start, int nextColour, int toSort);
        std::vector<Ink> maximalSubstring(std::vector<Ink> shelf, int start, int nextColour, int toSort);
        std::vector<Ink> positions(std::vector<Ink> shelf, int start, int nextColour, int toSort);
    public:
        Robot() {};
        ~Robot() {};
        void brutalSolver(Shelf *shelf);
        void naiveSolver(Shelf *shelf);
        void maximalSubstringSolver(Shelf *shelf);   //najwieksze podciagi
        void positionSolver(Shelf *shelf);  //optymalizacja czworkowa
};

#endif
