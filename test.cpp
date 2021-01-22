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

void doTestsForNaive();

using namespace std;

//    std::cout<<"Expected: ";
//    std::cout<<expected;
//    std::cout<<std::endl;
//    std::cout<<"Actual:   ";
//    shelf->showShelf();
//    std::cout<<std::endl;

void AddHeadings(std::string fileName, int index){
    std::string s = fileName + std::to_string(index) + ".csv";
    fstream file;
    file.open(s,std::ios::app);
    file << "Robot Moves" << ";" << "Duration" << endl;
    file.close();
}

void writeResultsToFile(std::string fileName, int index, int duration, int robotMoves){
    std::string s = fileName + std::to_string(index) + ".csv";
    fstream file;
    file.open(s,std::ios::app);
    file << robotMoves << ";" << duration << endl;
    file.close();
}

void runTestFromStringBrutal( string fileName, int index, int numLetters) {
    Shelf *shelf = new Shelf(numLetters);
    Robot r;
    string inshelf = shelf->ShelfToString();

    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.brutalSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

//    assert (Shelf::checkIfSorted(shelf->ShelfToString()));
    if(!Shelf::checkIfSorted(shelf->ShelfToString())){
        cout<<" polka nieposortowana"<<endl;
        cout<<inshelf<<endl;
        cout<<shelf->ShelfToString()<<endl;
        cout<<endl;
    }
    writeResultsToFile(fileName,index,duration.count(),r.getRobotMoves());
}

void runTestFromStringMaximalSubstring(int index, int numLetters) {
    Shelf *shelf = new Shelf(numLetters);
    Robot r;
    shelf->showShelf();

    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.maximalSubstringSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    assert (Shelf::checkIfSorted(shelf->ShelfToString()));
    writeResultsToFile("../Results/Substring/out",index,duration.count(),r.getRobotMoves());
}

void runTestFromStringPosition( int index, int numLetters) {
    Shelf *shelf = new Shelf(numLetters);
    Robot r;
    shelf->showShelf();

    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.positionSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    assert (Shelf::checkIfSorted(shelf->ShelfToString()));
    writeResultsToFile("../Results/Position/out",index,duration.count(),r.getRobotMoves());
}

void runTestFromStringNaive( string fileName, int index, int numLetters) {
    Shelf *shelf = new Shelf(numLetters);
    string inshelf = shelf->ShelfToString();
    Robot r;
//    shelf->showShelf();

    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.naiveSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

//    assert (Shelf::checkIfSorted(shelf->ShelfToString()));
    if(!Shelf::checkIfSorted(shelf->ShelfToString())){
        cout<<inshelf<<endl;
        cout<<shelf->ShelfToString()<<endl;
        cout<<endl;
    }
    writeResultsToFile(fileName,index,duration.count(),r.getRobotMoves());
}




void doTestsForNaive() {
    AddHeadings("../Results/Naive/out",1);
    for(int i = 0; i < 20; i++){
        runTestFromStringNaive("../Results/Naive/out",1,5);
    }
    AddHeadings("../Results/Naive/out",2);
    for(int i = 0; i < 20; i++){
        runTestFromStringNaive("../Results/Naive/out",2,10);
    }
}

void doTestsForBrutal() {
    AddHeadings("../Results/Naive/out",1);
    for(int i = 0; i < 20; i++){
        runTestFromStringBrutal("../Results/Brutal/out",1,5);
    }
    AddHeadings("../Results/Naive/out",2);
    for(int i = 0; i < 20; i++){
        runTestFromStringBrutal("../Results/Brutal/out",2,10);
    }
}

int main(int argc, char *argv[]) {

    srand((unsigned)time(NULL));
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
//    runTestFromStringMaximalSubstring("","CMYK",1);
//    runTestFromStringMaximalSubstring("CMYKCMKKKKKK","KKKCMYKCMKKK",2);
//    runTestFromStringMaximalSubstring("CMYKCMYKKKYY","YYYCMYKCMKKK",3);
//    runTestFromStringMaximalSubstring("","KCMYKCM",2);
//    runTestFromStringMaximalSubstring("CMYMMMKMKK","KKKCMYMMMM",3);

    doTestsForBrutal();

}


