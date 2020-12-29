#include "Shelf.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>


Shelf::Shelf(std::string fileName)
{
    std::ifstream file(fileName);
    std::vector<char> v1;

    if(file.is_open())
    {
        char c;
        while(file>>c)
        {
            v1.push_back(c);
        }
    }
    else
        std::cout<<"Couldn't open a file: " << fileName << std::endl;

    shelf = v1;
}

Shelf::Shelf(int number)
{
    char colours[4] = {'C', 'M', 'Y', 'K'};
    std::vector<char> v1;

    for( int i = 0; i < number; i++ )
    {
        int colour = std::rand() % 4;
        v1.push_back(colours[colour]);
    }

    shelf = v1;
}

Shelf::Shelf(int amount, std::string sequences[], int probabilities[], int size)
{
    std::vector<char> v1;
    char colours[4] = {'C', 'M', 'Y', 'K'};

    for(int i = 0; i < amount; ++i)
    {
        int random = rand() % 101;
        int sum = 0;
        int index = -1;
        int iter = 0;
        bool changed = false;
        while(!changed)
        {
            if(iter == size)
            {
                changed = true;
            }
            else
            {
                sum += probabilities[iter];
                if(sum > random)
                {
                    changed = true;
                    index = iter;
                }
                else
                    iter++;
            }
        }

        if(index == -1)
            v1.push_back(colours[rand()%4]);
        else
        {
            std::string sequence = sequences[index];

            for(int i = 0; i < sequence.length(); i++)
                v1.push_back(sequence[i]);
        }
        
    }

    shelf = v1;
}
