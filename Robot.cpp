#include "Robot.hpp"


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


void Robot::brutalSolver(Shelf *shelf)
{
    shelf->setShelf(brutalForce(shelf->getShelf(), 0, 0));
}
