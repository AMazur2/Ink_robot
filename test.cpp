#include <cassert>
#include "Shelf.hpp"
#include "Robot.hpp"


void runTestFromStringNaive(std::string expected, std::string input) {
    Shelf* shelf = Shelf::getShelfFromSring(input);
    Robot r;
    r.naiveSolver(shelf);
//    std::cout<<"Expected: ";
//    std::cout<<expected;
//    std::cout<<std::endl;
//    std::cout<<"Actual:   ";
//    shelf->showShelf();
//    std::cout<<std::endl;

    assert(expected==shelf->ShelfToString());
}

void runTestFromStringPosition(std::string expected, std::string input) {
    Shelf* shelf = Shelf::getShelfFromSring(input);
    Robot r;
    r.positionSolver(shelf);
//    std::cout<<"Expected: ";
//    std::cout<<expected;
//    std::cout<<std::endl;
//    std::cout<<"Actual:   ";
//    shelf->showShelf();
//    std::cout<<std::endl;

    assert(expected==shelf->ShelfToString());
}

int main(int argc, char *argv[]) {

//    runTestFromString("CMYK","CMYK");
//    runTestFromString("CYMYKYMK","KYMKCYMY");
//    runTestFromString("CKYKMYKK","MYKCKYKK");

    runTestFromStringNaive("CMYK","CMYK");
    runTestFromStringNaive("CMYKYMKY","KYMKCYMY");
    runTestFromStringNaive("CMYKKYKK","MYKCKYKK");

    runTestFromStringPosition("CMYK","CMYK");

}