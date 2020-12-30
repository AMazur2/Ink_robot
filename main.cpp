#include <iostream>
#include <fstream>
#include <vector>
#include "Shelf.hpp"
#include "Ink.hpp"

using namespace std;

void solve(Shelf shelf, string outFileName)
{
    shelf.showShelf();
}

int main(int argc, char *argv[])
{    
    if (argc > 1)
    {
        string mode = argv[1];

        if(mode == "-m1")
        {
            if(argc > 3)
            {
                Shelf shelf = Shelf(string(argv[2]));
                solve(shelf, string(argv[3]));
            }
            else 
            {
                cout << "Error: No filename given!" << endl;
                cout << "For help type 'h' or 'help'" << endl;
                return 1;
            }
        }
        else if (mode == "-m2")
        {
            if(argc > 2)
            {
                if(argc==3)
                {
                    Shelf shelf = Shelf(stoi(argv[2]));
                    solve(shelf, "out.txt");
                }
                else if (argc%2 == 1)
                {
                    int amount = stoi(argv[2]);
                    int number = (argc-3)/2;
                    int sum = 0;
                    string seq[number];
                    int possibilities[number];
                
                    for(int i = 0; i < number; i++)
                    {
                        seq[i] = argv[2*i+3];
                        possibilities[i] = stoi(argv[2*i+4]);
                        sum += possibilities[i];
                        if(sum > 100)
                        {
                            cout << "Error: Sum of possibilities of the sequences cannot be greater than 100!" << endl;
                            return 1;
                        }
                    }

                    Shelf shelf = Shelf(amount, seq, possibilities, number);
                    solve(shelf, "out.txt");
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
                int amount = stoi(argv[2]);
                int step = stoi(argv[3]);
                int stepNum = stoi(argv[4]);
                int instancesNum = stoi(argv[5]);

                for(int i = 0; i < stepNum; i++)
                {
                    for(int j = 0; j < instancesNum; ++j)
                    {
                        Shelf shelf = Shelf(amount);
                        solve(shelf, "out.txt");
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
            cout << "prog -m1 inFileName outFileName" << endl << endl << endl;
            cout << "\tMode 2 - generator" << endl;
            cout << "For creating a random shelf containing 'number' elements, type:" << endl << endl;
            cout << "prog -m2 number" << endl << endl << endl;
            cout << "If you want to give sequences with probabilities use syntax:" << endl << endl;
            cout << "prgramName -m2 number seq1 prob1 seq2 prob2 ...." << endl << endl;
            cout << "number stands for amount of random drawing from these sequences and single containers" << endl;
            cout << "remember that sum of probabilities cannot be greater than 100" << endl << endl << endl;
            cout << "\tMode 3 - multiple problem" << endl << endl;
            cout << "prog -m3 start step numberOfSteps numberOfInstances" << endl << endl;
            cout << "numberOfSteps - how many different sizes of problems will be solved" << endl;
            cout << "numberOfInstances - how many problems of one size will be solved" << endl;
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
