#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Shelf.hpp"
#include "Ink.hpp"
#include "Robot.hpp"

using namespace std;

void saveShelf(Shelf shelf, string outfilename) 
{
    vector<Ink> s = shelf.getShelf();
    int size = s.size();
    char data[size];
    for(int i = 0; i < size; ++i)
        data[i] = s[i].getColour();
    
    ofstream outfile;
    outfile.open(outfilename);
    outfile << data << endl;                    
    outfile.close();
}

void solve(Shelf shelf, string outFileName, string solver)
{
    shelf.showShelf();
    Robot r;
    if(solver == "brutal")
        r.brutalSolver(&shelf);
    else if (solver == "naive")
    {
        r.naiveSolver(&shelf);
        return;
    }
    else if (solver == "substring")
    {
        r.maximalSubstringSolver(&shelf);
        return;
    }
    else if (solver == "position")
    {
        r.positionSolver(&shelf);
        shelf.showShelf();
        return;
    }
    else
    {
        cout << "Unknown mode" << endl;
        return; 
    }
    shelf.showShelf();
    saveShelf(shelf, outFileName);
}

int main(int argc, char *argv[])
{  
    string outFile = "out.txt";  

    if (argc > 1)
    {
        string mode = argv[1];

        if(mode == "-m1")
        {
            if(argc > 4)
            {
                string solver = argv[2];
                Shelf shelf = Shelf(string(argv[3]));
                solve(shelf, string(argv[4]), solver);
            }
            else 
            {
                cout << "Error: Some parameter(s) missing!" << endl;
                cout << "For help type 'h' or 'help'" << endl;
                return 1;
            }
        }
        else if (mode == "-m2")
        {

            if(argc > 3)
            {
                string solver = argv[2];
                if(argc==3)
                {
                    Shelf shelf = Shelf(stoi(argv[3]));
                    solve(shelf, outFile, solver);
                }
                else if (argc%2 == 0)
                {
                    int amount = stoi(argv[3]);
                    int number = (argc-4)/2;
                    int sum = 0;
                    string seq[number];
                    int possibilities[number];
                
                    for(int i = 0; i < number; i++)
                    {
                        seq[i] = argv[2*i+4];
                        possibilities[i] = stoi(argv[2*i+5]);
                        sum += possibilities[i];
                        if(sum > 100)
                        {
                            cout << "Error: Sum of possibilities of the sequences cannot be greater than 100!" << endl;
                            return 1;
                        }
                    }

                    Shelf shelf = Shelf(amount, seq, possibilities, number);
                    solve(shelf, outFile, solver);
                }
                else
                {
                    cout << "Error: There is some missing parameter!" << endl;
                    cout << "For help type 'h' or 'help'" << endl;
                    return 1;
                } 
            }
            else
            {
                cout << "Error: No parameters given!" << endl;
                cout << "For help type 'h' or 'help'" << endl;
                return 1;
            }
            
        }
        else if(mode == "-m3")
        {
            if(argc == 6)
            {
                string solver = argv[2];
                int amount = stoi(argv[3]);
                int step = stoi(argv[4]);
                int stepNum = stoi(argv[5]);
                int instancesNum = stoi(argv[6]);

                for(int i = 0; i < stepNum; i++)
                {
                    for(int j = 0; j < instancesNum; ++j)
                    {
                        Shelf shelf = Shelf(amount);
                        solve(shelf, outFile, solver);
                    }
                    amount += step;
                }
            }
            else
            {
                cout << "Error: Wrong number of parameters!" << endl;
                cout << "For help type 'h' or 'help'" << endl;
                return 1;
            }
            
        }
        else if(mode == "h" || mode == "help")
        {
            cout << endl;
            cout << "\tMode 1 - from file" << endl << endl;
            cout << "prog -m1 solverName inFileName outFileName" << endl << endl << endl;
            cout << "\tMode 2 - generator" << endl;
            cout << "For creating a random shelf containing 'number' elements, type:" << endl << endl;
            cout << "prog -m2 solverName number " << endl << endl << endl;
            cout << "If you want to give sequences with probabilities use syntax:" << endl << endl;
            cout << "prog -m2 solverName number seq1 prob1 seq2 prob2 ...." << endl << endl;
            cout << "number stands for amount of random drawing from these sequences and single containers" << endl;
            cout << "remember that sum of probabilities cannot be greater than 100" << endl << endl << endl;
            cout << "\tMode 3 - multiple problem" << endl << endl;
            cout << "prog -m3 solverName start step numberOfSteps numberOfInstances" << endl << endl;
            cout << "numberOfSteps - how many different sizes of problems will be solved" << endl;
            cout << "numberOfInstances - how many problems of one size will be solved" << endl << endl;
            cout << "Posiible solvers:" << endl;
            cout << "brutal" << "\t\tnaive" << "\t\tposition" << "\tsubstring" << endl;
        }
        else
        {
            cout << "Error: Unknown mode!" << endl;
            cout << "For help type 'h' or 'help'" << endl;
            return 1;
        }
        
    }
    else
    {
        cout << "No parameters given - cannot create shelf!" << endl;
        cout << "For help type 'h' or 'help'" << endl;
    }
    
    return 0;
}
