#include "Robot.hpp"


int Robot::findNumber(std::vector<Ink> shelf)   //zwraca maksymalna ilosc czworek mozliwa do ulozenia
{
    int c = 0, m = 0, y = 0, k = 0;
    for (int i = 0; i < shelf.size(); ++i) {
        if (shelf[i].getColour() == 'C')
            c++;
        else if (shelf[i].getColour() == 'M')
            m++;
        else if (shelf[i].getColour() == 'Y')
            y++;
        else
            k++;
    }
    int min1 = std::min(c, m);
    int min2 = std::min(y, k);
    return std::min(min1, min2);
}

std::vector<int> Robot::findFours(std::vector<Ink> shelf)   //znajduje wysztkie ulozone juz czworki
{
    std::vector<int> places;
    int start = 0;

    while (start < shelf.size()) {
        int counter = 1;
        if (shelf[start].getColour() == 'C' && shelf.size() - start > 3) {
            bool continous = true;
            for (int i = 1; i < 4; ++i) {
                if (shelf[start + i].getColour() == types[i] && continous)
                    counter++;
                else if (shelf[start + i].getColour() != types[i] && continous)
                    continous = false;
            }
        }

        if (counter == 4)
            places.push_back(start);

        start += counter;
    }

    return places;
}

std::vector<Ink> Robot::moveRight(std::vector<Ink> shelf,
                                  int start)    //przesuwa w prawo 4 pojemniki zaczynajac od indeksu 'start' a reszte dosuwa zapelniajac puste pole
{
    std::vector<Ink> v;
    for (int i = 0; i < start; ++i)
        v.push_back(shelf[i]);

    Ink temp[4];
    int shelfSize = shelf.size();
    for (int i = 0; i < 4; ++i)
        temp[i] = shelf[start + i];

    for (int i = start + 4; i < shelfSize; ++i)
        v.push_back(shelf[i]);

    for (int i = 0; i < 4; ++i)
        v.push_back(temp[i]);

    return v;
}

std::vector<Ink> Robot::moveLeft(std::vector<Ink> shelf, int start,
                                 int stop)   //przesuwa pojemniki tak, aby pojemnik na miejscu 'stop+1' znalazl sie na miejscu 'start'
{                                                                       //potencjalne TODO: upewnic sie ze miedzy start a stop jest 4k pojemnikow, chociaz gleboko wierze
    //ze wzory ktore wyprowadzilem, zapewniaja juz optymalna ilosc pojemnikow do przesuwania
    int toMove = (stop - start + 1) / 4;

    std::vector<Ink> temp = shelf;
    std::vector<Ink> s;
    for (int i = 0; i < toMove; i++) {
        s = moveRight(temp, start);
        temp = s;
    }
    return temp;
}

std::vector<Ink> Robot::sortFours(std::vector<Ink> shelf, std::vector<int> fours,
                                  int start)    //przesuwa gotowe czworki na poczatek ciagu
{
    //ulatwia znajdywanie bledow
/*    std::cout << "fours.size(): " << fours.size();
    if(fours.size() > 0)
        std::cout << "\t\tfours[0]: " << fours[0];
    else
        std::cout << "\t\tfours[0]: -";    
    std::cout << "\tstart: " << start << "\tshelf: ";
    for(int i = 0; i < shelf.size(); ++i)
        std::cout<< shelf[i].getColour();
    std::cout <<std::endl;  */

    std::vector<Ink> temporary;
    if (fours.size() > 0) {
        if (start == fours[0] && start % 4 == 0)              //czwórka jest już na miejscu
        {
            fours.erase(fours.begin());
            temporary = sortFours(shelf, fours, start + 4);
        } else {
            if ((fours[0] - start) % 4 == 0)                     //pomiędzy kolejną czwórką a 'startem' jest 4k miejsc
            {
                int temp = fours[0];
                int amount = temp -
                             start;                  //o ile miejsc zostanie przesuniety ciag znajdujacy sie za czworka
                fours.erase(fours.begin());
                for (int i = 0; i < fours.size(); ++i)
                    fours[i] -= amount;                     //aktualizujemy pozycje czworek 
                temporary = sortFours(moveLeft(shelf, start, temp - 1), fours, start + 4);
            } else {
                int position = fours[0];
                int size = shelf.size();
                if (size % 4 ==
                    0)                         //rozmiar ciagu pozwala nam bezproblemowo dokonac przemieszczenia
                {
                    fours.erase(fours.begin());
                    temporary = sortFours(moveLeft(moveRight(shelf, position), start, size - 5), fours, start + 4);
                } else {

                    int shift = 0;
                    bool notFound = true;
                    int i = 1;
                    while (notFound)                     //obliczamy przemieszczenie jakie trzeba zastosować aby czworka byla na dobrej pozycji
                    {
                        shift++;
                        if (shelf.size() % 4 - i == 0)
                            notFound = false;
                        else
                            i++;
                    }

                    int pos = 4 - shift;                  //pozycja w przemiszczanej czworce poczatku ulozonej czworki
                    int tempStart = position - pos;     //poczatek przemiszczanej czworki
                    if (fours.size() > 1)                //mamy wiecej ulozonych czworek niz 1
                    {
                        if (tempStart >= start)          //nie jesteśmy ograniczeni z lewej strony
                        {
                            if (tempStart + 8 <
                                fours[1])      //mamy bezpieczną odleglość do przesuwania (aby nie uszkodzic nastepnej czworki)
                            {
                                std::vector<Ink> temp = moveLeft(moveRight(moveRight(shelf, tempStart), tempStart),
                                                                 start, shelf.size() - 5 - shift);
                                std::vector<int> foursPrim = findFours(temp);
                                bool deleted = true;
                                while (deleted)                          //usuwamy te, ktore juz sa ulozone
                                {
                                    if (foursPrim[0] < start + 4)
                                        foursPrim.erase(foursPrim.begin());
                                    else
                                        deleted = false;
                                }
                                temporary = sortFours(temp, foursPrim, start + 4);
                            } else                            //najedziemy na kolejna czworke
                            {

                                int amount = 2;             //ile czworek bedziemy przenosic
                                bool contains = true;       //czy kolejna czworka zawiera w sobie inna ulozona czworke
                                int index = 1;
                                while (contains)             //ile czworek musimy przeniesc
                                {
                                    if (tempStart + 4 * amount >= fours[index] && index < fours.size()) {
                                        amount++;
                                        index++;
                                    } else
                                        contains = false;
                                }

                                if (tempStart + 4 * amount >
                                    shelf.size())   //nie mozemy przeniesc wszystkich poniewaz wykracza to poza zakres polki
                                    amount--;                           //ostatnia musimy zniszczyc by reszte mozna bylo przeniesc

                                std::vector<Ink> temp = shelf;
                                for (int i = 0; i < amount; ++i)         //przenosimy wyliczona ilosc czworek
                                {
                                    temporary = moveRight(temp, tempStart);
                                    temp = temporary;
                                }

                                temporary = moveLeft(temp, start, shelf.size() - amount * 4 + pos -
                                                                  1); //doprowadzamy nasza czworke na poczatek (obecny 'start')
                                temp = temporary;
                                std::vector<int> foursPrim = findFours(
                                        temp);                //obliczamy nowe pozycje czworek

                                bool deleted = true;
                                while (deleted)                          //usuwamy te, ktore juz sa ulozone
                                {
                                    if (foursPrim[0] < start + 4)
                                        foursPrim.erase(foursPrim.begin());
                                    else
                                        deleted = false;
                                }

                                temporary = sortFours(temp, foursPrim, start + 4);
                            }
                        } else                            //jestesy ograniczeni z lewej strony
                        {
                            tempStart = start;
                            std::vector<Ink> temp;
                            if (tempStart + 8 < fours[1]) {
                                temp = moveRight(moveRight(shelf, tempStart), tempStart);
                                fours = findFours(temp);
                                bool deleted = true;
                                while (deleted) {
                                    if (fours[0] < start + 4)
                                        fours.erase(fours.begin());
                                    else
                                        deleted = false;
                                }
                                temporary = sortFours(temp, fours, start);
                            } else {
                                int amount = 2;
                                bool contains = true;
                                int index = 1;
                                while (contains) {
                                    if (index < fours.size() && tempStart + amount * 4 > fours[index]) {
                                        amount++;
                                        index++;
                                    } else
                                        contains = false;
                                }

                                if (tempStart + amount * 4 > shelf.size())
                                    amount--;

                                temp = shelf;
                                for (int i = 0; i < amount; ++i) {
                                    temporary = moveRight(temp, tempStart);
                                    temp = temporary;
                                }
                                fours = findFours(temp);
                                bool deleted = true;
                                while (deleted) {
                                    if (fours[0] < start)
                                        fours.erase(fours.begin());
                                    else
                                        deleted = false;
                                }

                                temporary = sortFours(temp, fours, start);

                            }
                        }
                    } else        //nie musimy sie przejmowac by nie zniszcyc innymch czworkek bo wiecej juz nie ma
                    {
                        if (tempStart > start && tempStart + 8 < shelf.size()) {
                            temporary = moveLeft(moveRight(moveRight(shelf, tempStart), tempStart), start,
                                                 shelf.size() - 5 - shift);
                        } else
                            temporary = shelf;

                    }
                }

            }

        }
    } else
        return shelf;
    return temporary;
}

std::pair<int, int> Robot::findMaximalSubstring(std::vector<Ink> shelf, int start, int colour) {
    int begining = 0;
    int length = 0;
    int tempBeg = 0;
    int tempLen = 0;
    int i = start;
    bool inSubstring = false;
    int nextColour = colour;
    while (i < shelf.size()) {
        if (shelf[i].getColour() == types[nextColour]) {
            if (!inSubstring) {
                tempBeg = i;
                inSubstring = true;
            }

            tempLen++;

            nextColour += 1;
            nextColour %= 4;
        } else {
            if (inSubstring) {
                inSubstring = false;
                if (tempLen > length) {
                    length = tempLen;
                    begining = tempBeg;
                    nextColour = colour;
                }
                tempLen = 0;
                tempBeg = 0;

            }
        }

        if (i + 1 == shelf.size()) {
            if (tempLen > length) {
                length = tempLen;
                begining = tempBeg;
            }
        }
        i++;
    }
    return std::make_pair(begining, length);
}

std::vector<Ink> Robot::brutalForce(std::vector<Ink> shelf, int start, int nextColour) {
    std::vector<Ink> temporaryShelf;
    if (shelf[start].getColour() ==
        types[nextColour])                       // od razu mamy odpowiedni pojemnik na miejscu
    {
        if (start + 1 <
            shelf.size())                                          //jezeli istnieje nastepny pojemnik to rekursywnie przechodzimy dalej
            temporaryShelf = brutalForce(shelf, start + 1, (nextColour + 1) % 4);
        else                                                                //jezeli nie to zwracamy obecną półkę
            return shelf;
    } else {
        if (shelf.size() - start >
            4)                                          //pozostala ilosc pojemnikow musi byc wieksza od 4
        {                                                                   //aby mozna bylo dokonac jakichkolwiek zmian w ciagu
            bool notFound = true;
            int index = start;                                              //miejsce najblizszego pojemnika ktory powinien byc nastepny
            while (notFound)                                                 //znajdujemy najblizszy pojemnik ktory powinien byc nastepny
            {
                if (index < shelf.size()) {
                    if (shelf[index].getColour() == types[nextColour])
                        notFound = false;
                    else
                        index++;
                } else                                                        //nie znalezlismy - zwracamy półkę i koniec algorytmu
                    return shelf;

            }

            std::vector<Ink> temp;                                          //pomocniczy wektor
            if ((index) % 4 ==
                nextColour)                                     //jezeli pojemnik jest na poprawnym miejscu, majac pod uwaga miejsca w czworkach
                temporaryShelf = brutalForce(moveLeft(shelf, start, index - 1), start + 1, (nextColour + 1) %
                                                                                           4);   //przesuwamy wszystkie czworki miedzy obecnym poczatkiem a pojemnikiem
            else {
                int position = 0;                                           //miejsce w przenoszonej czworce
                bool notFound = true;
                while (notFound)                                             //sprawdzamy na jakiej pozycji (majac na uwadze ostatnie 4 miejsca) powinien byc pojemnik
                {                                                           //aby mozna bylo poprawnie go przeniesc
                    if ((shelf.size() - 4 + position) % 4 == nextColour)
                        notFound = false;
                    else
                        position++;
                }

                if (index > shelf.size() - 4 +
                            position)                         //jezeli nie mozemy zrobic takiej czworki aby dany pojemnik byl na odpowiednim miejscu
                {                                                           //przenosimy poprzedzajaca czworke (przypadek ze pojemnik jest za daleko na prawo aby go przeniesc)
                    temporaryShelf = brutalForce(moveRight(shelf, index - 4), start, nextColour);
                } else {
                    if (index - position >=
                        start)                             //jezeli nasz pojemnik jest odpowiednio oddalony od punktu startu (mozemy stworzyc czworke
                    {                                                       //w ktorej pojemnik bedzie na odpowiednim miejscu)
                        std::vector<Ink> temp = moveLeft(moveRight(shelf, index - position), start, shelf.size() - 5 +
                                                                                                    position); //przenosimy ta czworke na prawo a potem przesuwamy
                        temporaryShelf = brutalForce(temp, start + 1, (nextColour + 1) %
                                                                      4);      //tak aby nasz pojemnik byl na miejscu 'start' i kontynuujemy algorytm
                    } else                                                    //pojemnik jest zbyt blisko startu wiec musimy go oddalic
                    {                                                       //przenosimy czworke zaczynajac od pojemnika znajdujacego sie na pozycji 'start'
                        int newPosition = shelf.size() - 4 + index -
                                          start;       //obliczamy nowa pozycje naszego pojemnika i wtedy gdy mamy juz na pewno wystarczajaca ilosc
                        std::vector<Ink> temp = moveRight(moveRight(shelf, start), newPosition -
                                                                                   position);   //pojemnikow przenoismy nasz pojemnik aby znajdowal sie na odpowiedniej pozycji
                        temporaryShelf = brutalForce(moveLeft(temp, start, shelf.size() - 5 + position), start + 1,
                                                     (nextColour + 1) % 4);    //na koniec doprowadzamy nasz pojemnik
                    }                                                       //na pozycje 'start' i kontynuujemy algorytm
                }

            }

        } else
            return shelf;
    }
    return temporaryShelf;

}

int Robot::findIndexOfWantedColourIfDivisibleByFour(int start, std::vector<Ink> shelf, char wantedColour) {
    for (int i = start; i < shelf.size(); i += 4) {
        if (shelf[i].getColour() == wantedColour)
            return i;
    }
    return -1;
}

void Robot::findOther(int startIndex, std::vector<Ink> shelf, char colour, int *whereToMoveRightIndex,
                      int *indexOfWantedColour) {
    int shelfSize = shelf.size();
    for (int currentIndex = startIndex; currentIndex < shelfSize; currentIndex++) {
        if (shelf[currentIndex].getColour() == colour) {
            //pelne pole z przodu i z tylu
            if ((currentIndex >= startIndex + 3) && (currentIndex + 3 < shelfSize)) {
                int m = currentIndex - startIndex, n = shelfSize - currentIndex - 1;
                int x = n + m - 3;
                int b = x % 4;

                if (currentIndex - b < startIndex) {
                    std::cout << "cofasz sie za start";
                    exit(1);
                }
                (*whereToMoveRightIndex) = currentIndex - b;
                (*indexOfWantedColour) = x + b + 1;

            }
        }
    }
}


std::vector<Ink>
Robot::moveWantedColorToCorrectPlace(std::vector<Ink> shelf, int start, char wantedColour, int fourInksPatternLeft) {

    int indexOfWantedColour = -1;
    indexOfWantedColour = findIndexOfWantedColourIfDivisibleByFour(start, shelf, wantedColour);

    if (indexOfWantedColour == -1) {
        int whereToMoveRightIndex = -1;
        findOther(start, shelf, wantedColour, &whereToMoveRightIndex, &indexOfWantedColour);
        shelf = moveRight(shelf, whereToMoveRightIndex);
    }

    if (indexOfWantedColour != start)
        shelf = moveLeft(shelf, start, indexOfWantedColour - 1);

    return shelf;
}

std::vector<Ink>
Robot::naive(std::vector<Ink> shelf, int start, char wantedColour, int fourInksPatternLeft)    //TODO: algorytm
{
    if (fourInksPatternLeft == 0)
        return shelf;
    else {

        shelf = moveWantedColorToCorrectPlace(shelf, start, wantedColour, fourInksPatternLeft);

//        showVariables(start, nextColour, fourInksPatternLeft, wantedColour);



        return shelf;
    }
}


void Robot::showVariables(int start, int nextColour, int toSort, char wantedColour) const {
    std::cout << "start: " << start << std::endl;
    std::cout << "toSort: " << toSort << std::endl;
    std::cout << "wantedColour: " << wantedColour << std::endl;
    std::cout << "nextColour: " << nextColour << std::endl;
}

std::vector<Ink> Robot::maximalSubstring(std::vector<Ink> shelf, int start, int nextColour, int toSort) //TODO: algorytm
{
    if (toSort == 0)
        return shelf;
    else {
        std::pair<int, int> p = findMaximalSubstring(shelf, start,
                                                     nextColour);     //p.first - zawiera w sobie informacje o poczatku najdluzszego podciagu
        std::cout << "TODO: maximal substring algorithm"
                  << std::endl;              //p.second - informuje jak dlugi jest ten podciag
        return shelf;                                                               //to co nalezy teraz zorbic to ulozyc ten podciag na odpowiednim miejscu
    }                                                                               //i podac odpowiednie parametry do rekursji
}

std::vector<Ink> Robot::positions(std::vector<Ink> shelf, int start, int nextColour, int toSort) //TODO: algorytm
{
    if (toSort == 0)
        return shelf;
    else {
        std::cout << "TODO: positions algorithm" << std::endl;
        return shelf;
    }

}

void Robot::brutalSolver(Shelf *shelf) {
    shelf->setShelf(brutalForce(shelf->getShelf(), 0, 0));
}

void Robot::naiveSolver(Shelf *shelf) {
    int num = findNumber(shelf->getShelf());
    if (num == 0)
        return;
    else {
        std::vector<Ink> temp;
        std::vector<int> fours = findFours(shelf->getShelf());
        if (fours.size() > 0) {
            temp = sortFours(shelf->getShelf(), fours, 0);
            std::vector<int> newFours = findFours(temp);
            bool consist = true;
            int start = 0;
            int index = 0;
            while (consist) {
                if (index < newFours.size() && start == newFours[index]) {
                    start += 4;
                    index++;
                    num--;
                } else
                    consist = false;
            }
            //temp - pulka, start - pierwsza pozycja nieułożona potencjalnie pozycja, num - liczba czworek do ulozenia jeszcze
            return shelf->setShelf(naive(temp, start, this->types[0], num));
        } else
            return shelf->setShelf(naive(shelf->getShelf(), 0, this->types[0], num));
    }
}

void Robot::maximalSubstringSolver(Shelf *shelf) {
    int num = findNumber(shelf->getShelf());
    if (num == 0)
        return;
    else
        return shelf->setShelf(maximalSubstring(shelf->getShelf(), 0, 0, num));
}

void Robot::positionSolver(Shelf *shelf) {
    int num = findNumber(shelf->getShelf());
    if (num == 0)
        return;
    else {
        std::vector<Ink> temp;
        std::vector<int> fours = findFours(shelf->getShelf());
        if (fours.size() > 0) {
            temp = sortFours(shelf->getShelf(), fours, 0);
            std::vector<int> newFours = findFours(temp);
            bool consist = true;
            int start = 0;
            int index = 0;
            while (consist) {
                if (index < newFours.size() && start == newFours[index]) {
                    start += 4;
                    index++;
                    num--;
                } else
                    consist = false;
            }
            std::cout << num << std::endl;
            return shelf->setShelf(positions(temp, start, 0, num));
        } else
            return shelf->setShelf(positions(shelf->getShelf(), 0, 0, num));
    }
}








