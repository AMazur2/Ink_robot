#include "Shelf.hpp"


Shelf::Shelf(std::string fileName)
{
    std::ifstream file(fileName);
    std::vector<Ink> v1;

    if(file.is_open())
    {
        char c;
        while(file>>c)
        {
            Ink ink = Ink(c);
            v1.push_back(ink);
        }
    }
    else
        std::cout<<"Couldn't open a file: " << fileName << std::endl;

    shelf = v1;
}

Shelf::Shelf(int number)
{
    char colours[4] = {'C', 'M', 'Y', 'K'};
    std::vector<Ink> v1;
    srand((unsigned)time(NULL));

    for( int i = 0; i < number; i++ )
    {
        int colour = std::rand() % 4;
        Ink ink = Ink(colours[colour]);
        v1.push_back(ink);
    }

    shelf = v1;
}

Shelf::Shelf(int amount, std::string sequences[], int probabilities[], int size)
{
    std::vector<Ink> v1;
    char colours[4] = {'C', 'M', 'Y', 'K'};
    srand((unsigned)time(NULL));

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
        {
            Ink ink = Ink(colours[rand()%4]);
            v1.push_back(ink);
        
        }
        else
        {
            std::string sequence = sequences[index];

            for(int i = 0; i < sequence.length(); i++)
            {
                Ink ink = Ink(sequence[i]);
                v1.push_back(ink);
            }
        }
        
    }

    shelf = v1;
}

void Shelf::showShelf()
{
    for(int i = 0; i < shelf.size(); i++)
        std::cout << shelf[i].getColour();
    std::cout << std::endl;
}
