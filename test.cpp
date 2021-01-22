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

void AddHeadings(std::string fileName, int index){
    std::string s = fileName + std::to_string(index) + ".csv";
    fstream file;
    file.open(s,std::ios::out);
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



void runTestFromStringMaximalSubstring(string fileName, int index, int numLetters) {
    Shelf *shelf = new Shelf(numLetters);
    Robot r;
    string inshelf = shelf->ShelfToString();

    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.maximalSubstringSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    if(!Shelf::checkIfSorted(shelf->ShelfToString())){
        cout<<" polka nieposortowana"<<endl;
        cout<<inshelf<<endl;
        cout<<shelf->ShelfToString()<<endl;
        cout<<endl;
    }
    writeResultsToFile(fileName,index,duration.count(),r.getRobotMoves());
}

void runTestFromStringPosition( string fileName, int index, int numLetters) {
    Shelf *shelf = new Shelf(numLetters);
    Robot r;
    string inshelf = shelf->ShelfToString();

    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.positionSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    if(!Shelf::checkIfSorted(shelf->ShelfToString())){
        cout<<" polka nieposortowana"<<endl;
        cout<<inshelf<<endl;
        cout<<shelf->ShelfToString()<<endl;
        cout<<endl;
    }
    writeResultsToFile(fileName,index,duration.count(),r.getRobotMoves());
}

void runTestFromStringNaive( string fileName, int index, int numLetters) {
    Shelf *shelf = new Shelf(numLetters);
    string inshelf = shelf->ShelfToString();
    Robot r;

    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.naiveSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    if(!Shelf::checkIfSorted(shelf->ShelfToString())){
        cout<<inshelf<<endl;
        cout<<shelf->ShelfToString()<<endl;
        cout<<endl;
    }
    writeResultsToFile(fileName,index,duration.count(),r.getRobotMoves());
}

void runTestFromStringBrutal( string fileName, int index, int numLetters) {
    Shelf *shelf = new Shelf(numLetters);
    Robot r;
    string inshelf = shelf->ShelfToString();

    auto start = std::chrono::high_resolution_clock::now();//start measuring time
    r.brutalSolver(shelf);
    auto finish = std::chrono::high_resolution_clock::now();//finish measuring time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);

    if(!Shelf::checkIfSorted(shelf->ShelfToString())){
        cout<<" polka nieposortowana"<<endl;
        cout<<inshelf<<endl;
        cout<<shelf->ShelfToString()<<endl;
        cout<<endl;
    }
    writeResultsToFile(fileName,index,duration.count(),r.getRobotMoves());
}




void doTestsForSubstring() {
    string fileName = "../Results/Substring/substring";
    AddHeadings(fileName,5);
    for(int i = 0; i < 20; i++){
        runTestFromStringMaximalSubstring(fileName,5,5);
    }
    AddHeadings(fileName,10);
    for(int i = 0; i < 20; i++){
        runTestFromStringMaximalSubstring(fileName,10,10);
    }
    AddHeadings(fileName,100);
    for(int i = 0; i < 20; i++){
        runTestFromStringMaximalSubstring(fileName,100,100);
    }
    AddHeadings(fileName,40);
    for(int i = 0; i < 20; i++){
        runTestFromStringMaximalSubstring(fileName,40,40);
    }
    AddHeadings(fileName,1000);
    for(int i = 0; i < 20; i++){
        runTestFromStringMaximalSubstring(fileName,1000,1000);
    }
}

void doTestsForPosition() {
    string fileName = "../Results/Position/position";
    AddHeadings(fileName,5);
    for(int i = 0; i < 20; i++){
        runTestFromStringPosition(fileName,5,5);
    }
    AddHeadings(fileName,10);
    for(int i = 0; i < 20; i++){
        runTestFromStringPosition(fileName,10,10);
    }
    AddHeadings(fileName,100);
    for(int i = 0; i < 20; i++){
        runTestFromStringPosition(fileName,100,100);
    }
    AddHeadings(fileName,20);
    for(int i = 0; i < 20; i++){
        runTestFromStringPosition(fileName,20,20);
    }
    AddHeadings(fileName,40);
    for(int i = 0; i < 20; i++){
        runTestFromStringPosition(fileName,40,40);
    }
    AddHeadings(fileName,1000);
    for(int i = 0; i < 20; i++){
        runTestFromStringPosition(fileName,1000,1000);
    }
}

void doTestsForNaive() {
    string fileName = "../Results/Naive/naive";
    AddHeadings(fileName,5);
    for(int i = 0; i < 20; i++){
        runTestFromStringNaive(fileName,5,5);
    }
    AddHeadings(fileName,10);
    for(int i = 0; i < 20; i++){
        runTestFromStringNaive(fileName,10,10);
    }
    AddHeadings(fileName,100);
    for(int i = 0; i < 20; i++){
        runTestFromStringNaive(fileName,100,100);
    }
    AddHeadings(fileName,40);
    for(int i = 0; i < 20; i++){
        runTestFromStringNaive(fileName,40,40);
    }
    AddHeadings(fileName,1000);
    for(int i = 0; i < 20; i++){
        runTestFromStringNaive(fileName,1000,1000);
    }
}

void doTestsForBrutal() {
    string fileName = "../Results/Brutal/brutal";
    AddHeadings(fileName,5);
    for(int i = 0; i < 20; i++){
        runTestFromStringBrutal(fileName,5,5);
    }
    AddHeadings(fileName,10);
    for(int i = 0; i < 20; i++){
        runTestFromStringBrutal(fileName,10,10);
    }
    AddHeadings(fileName,100);
    for(int i = 0; i < 20; i++){
        runTestFromStringBrutal(fileName,100,100);
    }
    AddHeadings(fileName,40);
    for(int i = 0; i < 20; i++){
        runTestFromStringBrutal(fileName,40,40);
    }
    AddHeadings(fileName,1000);
    for(int i = 0; i < 20; i++){
        runTestFromStringBrutal(fileName,1000,1000);
    }
}

int main(int argc, char *argv[]) {

    srand((unsigned)time(NULL));

    doTestsForBrutal();
    doTestsForNaive();
    doTestsForPosition();
    doTestsForSubstring();
}


