// #include "State.h"
// #include "Goal.h"
#include "Solver.h"

int main()
{
    int task, boardSize, numberRange, repeat = 0;
    bool input = false;
    Solver s;
    while (repeat != -1)
    {

        cout << "  1.Solver\n  2.Heuristic Solver\n  3.Heuristic Solver with Disjunctive Goals\n"
             << "  4.Heuristic Solver with Conjunctive Goals\n  5.Board Creation and another Task\nWhich Task would you like to run: \n";
        cin >> task;
        switch (task)
        {
        case 1:
            s = Solver();
            s.search();
            break;
        case 2:
            s = Solver();
            s.heuristicSearch();
            break;
        case 3:
            s = Solver();
            s.heuristicSearch();
            // Make sure heuristic search takes an argument to see whether it is for a conjunctive or disjunctive
            break;
        case 4:
            s = Solver();
            s.heuristicSearch(1);
            // Make sure heuristic search takes an argument to see whether it is for a conjunctive or disjunctive
            break;
        case 5:
            cout << "How big do you want the board: ";
            cin >> boardSize;
            cout << "\nHow many numbers do you want on the board: ";
            cin >> numberRange;
            s = Solver(boardSize, numberRange);
            s.heuristicSearch();
            break;
        default:
            cout << "Not an option";
            break;
        }
        cout << "Go again(-1 for no): ";
        cin >> repeat;
    }
    // Solver s;
    // s.heuristicSearch();

    return 1;
}