#include "Robot.hpp"


std::vector<Ink> Robot::moveRight(std::vector<Ink> shelf, int start)
{
    Ink temp[4];
    int shelfSize = shelf.size();
    for(int i = 0; i < 4; ++i)
        temp[i] = shelf[start+i];
    
    for(int i = 0; i < shelfSize-4; ++i)
        shelf[start+i] = shelf[start+i+4];

    for(int i = 0; i < 4; ++i)
        shelf[shelfSize-4+i] = temp[i];

    return shelf;
}

std::vector<Ink> Robot::moveLeft(std::vector<Ink> shelf, int start, int stop)
{

    int toMove = (stop - start + 1)/4;
    for(int i = 0; i < toMove; i++)
    {
        Ink temporary[4];
        for(int j = 0; j < 4; ++j)
            temporary[j] = shelf[start+j];
    
        int left = shelf.size() - stop - 1;

        for(int j = 0; j < left; ++j)
            shelf[start+j] = shelf[start+j+4];
        
        for(int j = 0; j < 4; ++j)
            shelf[stop+1+j] = temporary[j];
    }
    return shelf;
}

std::vector<Ink> Robot::brutalForce(std::vector<Ink> shelf, int start, int nextColour)
{
    std::vector<Ink> temporaryShelf;
    if(shelf[start].getColour() == types[nextColour])
    {
        if(start+1 < shelf.size())
            temporaryShelf = brutalForce(shelf, start+1, (nextColour+1)%4);
        else
            return shelf;
    }
    else
    {
        if(shelf.size()-start > 3)
        {
            bool notFound = true;
            int index = start;
            while(notFound)                     //znajdujemy najblizszy pojemnik ktory powinien byc nastepny
            {
                index++;
                if(index < shelf.size())
                {
                    if(shelf[index].getColour() == types[nextColour])
                        notFound = false;
                }
                else
                    return shelf;
                
            }

            std::vector<Ink> temp;
            if((index)%4 == nextColour)
                temporaryShelf = brutalForce(moveLeft(shelf, start, index-1), start+1, (nextColour+1)%4);
            else
            {
                int position = 0;
                bool notFound = true;
                while(notFound)
                {
                    if((shelf.size()-4+position)%4 == nextColour)
                        notFound = false;
                    else
                        position++;
                }

                if(index > shelf.size()-4+position)
                {
                    temporaryShelf = brutalForce(moveRight(shelf, index-4), start, nextColour);
                }
                else
                {
                    if(index-position >= start)
                    {
                        std::vector<Ink> temp = moveLeft(moveRight(shelf, index-position), start, shelf.size()-5+position);
                        temporaryShelf = brutalForce(temp, start+1, (nextColour+1)%4);
                    }
                    else
                    {
                        int newPosition = shelf.size()-index+start;
                        std::vector<Ink> temp = moveRight(moveRight(shelf, start), newPosition-position); 
                        temporaryShelf = brutalForce(moveLeft(temp, start, shelf.size()-5+position), start+1, (nextColour+1)%4);
                    }   
                }
                
            }
            
        }
        else
            return shelf;
    }
    return temporaryShelf;
    
}


void Robot::brutalSolver(Shelf *shelf)
{
    shelf->setShelf(brutalForce(shelf->getShelf(), 0, 0));
}