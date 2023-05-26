#include "Solver.h"

int main()
{
    int task = 0;
    int boardSize = 1;
    int amountOfNumbers = 0;
    cout << "1. Single goal solver without heuristics\n"
         << "2. Single goal solver with heuristics\n"
         << "3. Disjunctive goal solver\n"
         << "4. Conjunctive goal solver\n"
         << "5. Conjunctive goal solver on n*n board\n"
         << "6. A star solver on n*n board (doesn't work currently)\n";
    cin >> task;
    Solver s;
    switch (task)
    {
    case 1:
        s.search();
        break;
    case 2:
        s.heuristicSearch();
        break;
    case 3:
        s.heuristicDisjunctiveSearch();
        break;
    case 4:
        s.heuristicConjunctiveSearch();
        break;
    case 5:
        cout << "How large do you want the board?: ";
        cin >> boardSize;
        while ((boardSize < 3) || (boardSize > 9))
        {
            if ((boardSize < 3) || (boardSize > 9))
            {
                cout << "Board size must be greater than 2 and less than 10\nTry again: ";
            }
            cin >> boardSize;
        }
         cout << "How many numbers do you want on the board?: ";
         cin >> amountOfNumbers;
         while ((amountOfNumbers < boardSize) || (amountOfNumbers > (boardSize*boardSize)-boardSize))
        {
            if ((amountOfNumbers < boardSize) || (amountOfNumbers > (boardSize*boardSize)-boardSize))
            {
                cout << "Amount of numbers must be greater than " << boardSize-1 << " and less than " << ((boardSize*boardSize)-boardSize)+1 <<"\nTry again: ";
            }
            cin >> amountOfNumbers;
        }
        s = Solver(boardSize, amountOfNumbers);
        s.heuristicConjunctiveSearch();
        break;
    case 6:
        s.AStar();
        break;
    case 7:
        return 1;
        break;
    }
    return 0;
}