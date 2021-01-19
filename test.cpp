#include <cassert>
#include <chrono>
#include "Shelf.hpp"
#include "Robot.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

void writeResultsToFile(std::string fileName, int index, int duration, int robotMoves){
    std::string s = fileName + std::to_string(index);
    fstream file;
    file.open(s,std::ios::out);
    file << robotMoves << ";" << duration;
    file.close();
}

void runTestFromStringNaive(std::string expected, std::string input, int index) {
    Shelf* shelf = Shelf::getShelfFromSring(input);
    Robot r;

    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.naiveSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    assert (Shelf::checkIfSorted(shelf->ShelfToString()));
    writeResultsToFile("../Results/Naive/out",index,duration.count(),r.getRobotMoves());
//    assert(expected==shelf->ShelfToString());
}

void runTestFromStringMaximalSubstring(std::string expected, std::string input, int index) {
    Shelf* shelf = Shelf::getShelfFromSring(input);
    Robot r;
    srand (time(NULL));
    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.maximalSubstringSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    std::cout<<"Expected: ";
    std::cout<<expected;
    std::cout<<std::endl;
    std::cout<<"Actual:   ";
    shelf->showShelf();
    std::cout<<std::endl;

    writeResultsToFile("out",index,duration.count(),r.getRobotMoves());
//    assert(expected==shelf->ShelfToString());
}



void runTestFromStringPosition(std::string expected, std::string input) {
    Shelf* shelf = Shelf::getShelfFromSring(input);
    Robot r;
    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.positionSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
//    std::cout<<"Expected: ";
//    std::cout<<expected;
//    std::cout<<std::endl;
//    std::cout<<"Actual:   ";
//    shelf->showShelf();
//    std::cout<<std::endl;
    int dcount = duration.count();
    std::cout<<duration.count()<<" " <<r.getRobotMoves()<<std::endl;

    assert(expected==shelf->ShelfToString());
}

int main(int argc, char *argv[]) {

//    runTestFromString("CMYK","CMYK");
//    runTestFromString("CYMYKYMK","KYMKCYMY");
//    runTestFromString("CKYKMYKK","MYKCKYKK");

//    std::cout<<"naive"<<std::endl;
//    runTestFromStringNaive("CMYK","CMYK",1);
//    runTestFromStringNaive("CMYKYMKY","KYMKCYMY",2);
//    runTestFromStringNaive("CMYKKYKK","MYKCKYKK",3);
//
//    std::cout<<"position"<<std::endl;
//    runTestFromStringPosition("CMYK","CMYK");

//    std::cout<<"Maximal Substring"<<std::endl;
////    runTestFromStringMaximalSubstring("CMYK","CMYK",1);
//    runTestFromStringMaximalSubstring("KMKKCMYMMM","KKKCMYMMMM",2);
//    runTestFromStringMaximalSubstring("KMKKCMYMMM","KKKCYMMMM",2);
//    runTestFromStringMaximalSubstring("CMYMMMKMKK","KKKCMYMMMM",3);

}