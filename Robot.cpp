#include "Robot.hpp"


int Robot::findNumber(std::vector<Ink> shelf)   //zwraca maksymalna ilosc czworek mozliwa do ulozenia
{
    int c, m, y, k = 0;
    for(int i = 0; i < shelf.size(); ++i)
    {
        if(shelf[i].getColour() == 'C')
            c++;
        else if(shelf[i].getColour() == 'M')
            m++;
        else if(shelf[i].getColour() == 'Y')
            y++;
        else
            k++;  
    }
    int min1 = std::min(c,m);
    int min2 = std::min(y,k);
    return std::min(min1,min2);
}

std::vector<int> Robot::findFours(std::vector<Ink> shelf)   //znajduje wysztkie ulozone juz czworki
{
    std::vector<int> places;
    int start = 0;

    while(start < shelf.size())
    {
        int counter = 0;
        if(shelf[start].getColour() == 'C' && shelf.size()-start > 3)
        {
            counter++;
            bool continous = true;
            for(int i = 1; i < 4; ++i)
            {
                if(shelf[start+i].getColour() == types[i] && continous)
                    counter++;
                else if( shelf[start+i].getColour() != types[i] && continous)
                    continous = false;
            }
        }
        if(counter == 4)
        {
            places.push_back(start);
            start += 4;
        }
        else
            start +=counter;
    }

    return places;
}

std::vector<Ink> Robot::moveRight(std::vector<Ink> shelf, int start)    //przesuwa w prawo 4 pojemniki zaczynajac od indeksu 'start' a reszte dosuwa zapelniajac puste pole
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

std::vector<Ink> Robot::moveLeft(std::vector<Ink> shelf, int start, int stop)   //przesuwa pojemniki tak, aby pojemnik na miejscu 'stop+1' znalazl sie na miejscu 'start'
{                                                                       //potencjalne TODO: upewnic sie ze miedzy start a stop jest 4k pojemnikow, chociaz gleboko wierze
                                                                        //ze wzory ktore wyprowadzilem, zapewniaja juz optymalna ilosc pojemnikow do przesuwania
    int toMove = (stop - start + 1)/4;

    for(int i = 0; i < toMove; i++)
    {
        Ink temporary[4];
        for(int j = 0; j < 4; ++j)
            temporary[j] = shelf[start+j];
    
        int left = shelf.size() - start - 4;

        for(int j = 0; j < left; ++j)
            shelf[start+j] = shelf[start+j+4];
        
        for(int j = 0; j < 4; ++j)
            shelf[shelf.size()-4+j] = temporary[j];
    }
    return shelf;
}

std::vector<Ink> Robot::sortFours(std::vector<Ink> shelf, std::vector<int> fours, int start)    //przesuwa gotowe czworki na poczatek ciagu     TODO: Dokonczyc
{
    std::vector<Ink> temporary;
    if(fours.size() > 0)
    {
        if( start == fours[0] && start%4 == 0)              //czwórka jest już na miejscu
        {
            fours.erase(fours.begin());
            temporary = sortFours(shelf, fours, start+4);
        }
        else
        {
            int position = fours[0];
            int size = shelf.size();
            if(size%4 == 0)                                 //rozmiar ciagu pozwala nam bezproblemowo dokonac przemieszczenia
            {
                fours.erase(fours.begin());
                temporary = sortFours(moveLeft(moveRight(shelf, position), start, size-5), fours, start+4);
            }
            else
            {
                int shift = 0;
                bool notFound = true;
                int i = 1;
                while(notFound)                         //obliczamy przemieszczenie jakie trzeba zastosować aby czworka byla na dobrej pozycji
                {
                    shift++;
                    if(shelf.size() - i == 0)
                        notFound = false;
                    else
                        i++;
                    
                }

                if(fours.size() > 1)
                {

                }
                else
                {
                    
                }
            }
            
        }
    }
    return temporary;
}

std::vector<Ink> Robot::brutalForce(std::vector<Ink> shelf, int start, int nextColour)
{
    std::vector<Ink> temporaryShelf;
    if(shelf[start].getColour() == types[nextColour])                       // od razu mamy odpowiedni pojemnik na miejscu
    {
        if(start+1 < shelf.size())                                          //jezeli istnieje nastepny pojemnik to rekursywnie przechodzimy dalej
            temporaryShelf = brutalForce(shelf, start+1, (nextColour+1)%4);
        else                                                                //jezeli nie to zwracamy obecną półkę
            return shelf;
    }
    else
    {
        if(shelf.size()-start > 4)                                          //pozostala ilosc pojemnikow musi byc wieksza od 4
        {                                                                   //aby mozna bylo dokonac jakichkolwiek zmian w ciagu
            bool notFound = true;
            int index = start;                                              //miejsce najblizszego pojemnika ktory powinien byc nastepny
            while(notFound)                                                 //znajdujemy najblizszy pojemnik ktory powinien byc nastepny
            {
                if(index < shelf.size())
                {
                    if(shelf[index].getColour() == types[nextColour])
                        notFound = false;
                    else
                        index++;
                }
                else                                                        //nie znalezlismy - zwracamy półkę i koniec algorytmu
                    return shelf;
                
            }

            std::vector<Ink> temp;                                          //pomocniczy wektor
            if((index)%4 == nextColour)                                     //jezeli pojemnik jest na poprawnym miejscu, majac pod uwaga miejsca w czworkach
                temporaryShelf = brutalForce(moveLeft(shelf, start, index-1), start+1, (nextColour+1)%4);   //przesuwamy wszystkie czworki miedzy obecnym poczatkiem a pojemnikiem
            else
            {
                int position = 0;                                           //miejsce w przenoszonej czworce
                bool notFound = true;
                while(notFound)                                             //sprawdzamy na jakiej pozycji (majac na uwadze ostatnie 4 miejsca) powinien byc pojemnik
                {                                                           //aby mozna bylo poprawnie go przeniesc
                    if((shelf.size()-4+position)%4 == nextColour)
                        notFound = false;
                    else
                        position++;
                }

                if(index > shelf.size()-4+position)                         //jezeli nie mozemy zrobic takiej czworki aby dany pojemnik byl na odpowiednim miejscu
                {                                                           //przenosimy poprzedzajaca czworke (przypadek ze pojemnik jest za daleko na prawo aby go przeniesc)
                    temporaryShelf = brutalForce(moveRight(shelf, index-4), start, nextColour);
                }
                else
                {
                    if(index-position >= start)                             //jezeli nasz pojemnik jest odpowiednio oddalony od punktu startu (mozemy stworzyc czworke
                    {                                                       //w ktorej pojemnik bedzie na odpowiednim miejscu)
                        std::vector<Ink> temp = moveLeft(moveRight(shelf, index-position), start, shelf.size()-5+position); //przenosimy ta czworke na prawo a potem przesuwamy
                        temporaryShelf = brutalForce(temp, start+1, (nextColour+1)%4);      //tak aby nasz pojemnik byl na miejscu 'start' i kontynuujemy algorytm
                    }
                    else                                                    //pojemnik jest zbyt blisko startu wiec musimy go oddalic
                    {                                                       //przenosimy czworke zaczynajac od pojemnika znajdujacego sie na pozycji 'start'
                        int newPosition = shelf.size()-4+index-start;       //obliczamy nowa pozycje naszego pojemnika i wtedy gdy mamy juz na pewno wystarczajaca ilosc
                        std::vector<Ink> temp = moveRight(moveRight(shelf, start), newPosition-position);   //pojemnikow przenoismy nasz pojemnik aby znajdowal sie na odpowiedniej pozycji
                        temporaryShelf = brutalForce(moveLeft(temp, start, shelf.size()-5+position), start+1, (nextColour+1)%4);    //na koniec doprowadzamy nasz pojemnik
                    }                                                       //na pozycje 'start' i kontynuujemy algorytm
                }
                
            }
            
        }
        else
            return shelf;
    }
    return temporaryShelf;
    
}

std::vector<Ink> Robot::naive(std::vector<Ink> shelf, int start, int nextColour)    //TODO: algorytm
{
    return shelf;
}

std::vector<Ink> Robot::maximalSubstring(std::vector<Ink> shelf, int start, int nextColour) //TODO: algorytm
{
    return shelf;
}

std::vector<Ink> Robot::positions(std::vector<Ink> shelf, int start, int nextColour, int toSort) //TODO: algorytm
{
    return shelf;
}

void Robot::brutalSolver(Shelf *shelf)
{
    shelf->setShelf(brutalForce(shelf->getShelf(), 0, 0));
}

void Robot::naiveSolver(Shelf *shelf)       //TODO: uzupelnic
{
    int num = findNumber(shelf->getShelf());
    if( num == 0)
        return;
    else
        std::cout << "TODO: naive solver" << std::endl;

    return;
}

void Robot::maximalSubstringSolver(Shelf *shelf)    //TODO: uzupelnic
{
    int num = findNumber(shelf->getShelf());
    if( num == 0)
        return;
    else
        std::cout << "TODO: maximal substring solver" << std::endl;

    return;
}

void Robot::positionSolver(Shelf *shelf)    //TODO: uzupelnic
{
    int num = findNumber(shelf->getShelf());
    if( num == 0 )
        return;
    else
    {
        std::vector<int> fours = findFours(shelf->getShelf());
        std::cout << fours.size() <<std::endl;
        if(fours.size() > 0)
        {
            std::vector<Ink> temp = sortFours(shelf->getShelf(), fours, 0);
        }

    }  
}

