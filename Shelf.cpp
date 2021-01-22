#include <algorithm>
#include "Shelf.hpp"


Shelf *Shelf::getShelfFromSring(std::string s) {
    std::vector<Ink> newShelf;
    for(char c : s){
        Ink i = Ink(c);
        newShelf.push_back(i);
    }
    return new Shelf(newShelf);
}

Shelf* Shelf::getShelfFromFile(std::string fileName)
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

    return new Shelf(v1);
}

Shelf::Shelf(std::vector<Ink> shelf){
    this->shelf = shelf;
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

std::string Shelf::ShelfToString()
{
    std::string result;
    for(int i = 0; i < shelf.size(); i++)
        result += shelf[i].getColour();
    return result;
}

bool Shelf::checkIfSorted(std::string shelf) {
    int firstNotFour = -1, i = 3;
    while(i < shelf.size() && firstNotFour == -1){
        char c = shelf[i-3];
        char m = shelf[i-2];
        char y = shelf[i-1];
        char k = shelf[i-0];
        if( !(c=='C' && m=='M' && y=='Y' && k=='K') )
            firstNotFour = i - 3;
        i+=4;
    }

    int howManyLeft = shelf.size() - firstNotFour;
    if(howManyLeft <= 4)
        return true;
    else{
        int minFromLetters = countLetters(shelf,firstNotFour);
        if(minFromLetters == 0)
            return true;
        else{
            std::cout<<shelf;
            std::cout.flush();
            return false;
        }
    }

}

int Shelf::countLetters(std::string shelf, int start) {
    int c=0, m=0, y=0, k=0;
    for(int i = start; i < shelf.length(); i++){
        switch (shelf[i]) {
            case 'C':
                c++;
                break;
            case 'M':
                m++;
                break;
            case 'Y':
                y++;
                break;
            case 'K':
                k++;
                break;
            default:
                std::cout<<"shelf contains letter other than CMYK";
                exit(1);
        }
    }
    return std::min(c, std::min(m, std::min(y, k)));
}


