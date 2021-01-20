#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "Shelf.hpp"
#include <utility>

class Robot
{
    private:
        char types[4] = {'C', 'M', 'Y', 'K'};
        int robotMoves;
public:
    int getRobotMoves() const;

private:
    int findNumber(std::vector<Ink> shelf);
        std::vector<int> findFours(std::vector<Ink> shelf);
        std::vector<Ink> moveRight(std::vector<Ink> shelf, int start);
        std::vector<Ink> moveLeft(std::vector<Ink> shelf, int start, int stop);
        std::vector<Ink> sortFours(std::vector<Ink> shelf, std::vector<int> fours, int start);
        std::pair<int, int> findMaximalSubstring (std::vector<Ink> shelf, int start, int colour);
        std::vector<Ink> brutalForce(std::vector<Ink> shelf, int start, int nextColour);
//        std::vector<Ink> naive(std::vector<Ink> shelf, int start, int nextColour, int fourInksPatternLeft);
        std::vector<Ink> maximalSubstring(std::vector<Ink> shelf, int start, int nextColour, int fourInksPatternLeft);
        std::vector<Ink> positions(std::vector<Ink> shelf, int start, int nextColour, int toSort);


    public:
        Robot();
        ~Robot() {};
        void brutalSolver(Shelf *shelf);
        void naiveSolver(Shelf *shelf);
        void maximalSubstringSolver(Shelf *shelf);   //najwieksze podciagi
        void positionSolver(Shelf *shelf);  //optymalizacja czworkowa


    int findIndexOfWantedColourIfDivisibleByFour(int start, std::vector<Ink> shelf, char wantedColour);

    void showVariables(int start, int nextColour, int toSort, char wantedColour) const;

    void
    findOther(int startIndex, std::vector<Ink> shelf, char colour, int *whereToMoveRightIndex,
              int *indexOfWantedColour);

    std::vector<Ink> moveWantedColorToCorrectPlace(std::vector<Ink> shelf, int start, char wantedColour, int left);

    std::vector<Ink> naive(std::vector<Ink> shelf, int start, int nextColour, int fourInksPatternLeft);

    int findFirstWantedPositionInFour(std::vector<Ink> shelf, int start, int first);

    int findHowManyFoursSorted(std::vector<Ink> shelf, int start, int toSort, int substringLength);

    std::vector<Ink> moveSubstringAtTheEnd(std::vector<Ink> shelf, int start, std::pair<int, int> *substring);

    std::vector<Ink>
    moveSubstringToCorrectPlace(std::vector<Ink> shelf, int start, std::pair<int, int> *substring,
                                int firstPosition);

    bool ifSubstringCanBeMoved(int shelfSize, int start, std::pair<int, int> substring, int firstPosition);
};

#endif
