#include "Goal.h"
#include "State.h"
#include "Solver.h"

using namespace std;
class MonteCarlo
{
    priority_queue<pair<int, State>, vector<pair<int, State>>, CompareStates> pq;
    queue<State> moves;
    State startingState;
    Goal goal;
    vector<State> previousMoves;
    void MonteCarloTreeSearchAlgorithm()
    {
        startingState.possibleMoves(startingState, moves, previousMoves);
        while(!moves.empty())
        {
            State temp = moves.top();
            moves.pop();
    
        }
        

    }
    int simulation(State board)
    {
        double found = 0.0;
        int times = 10000;
        for(int i = 0; i < 10000; i++)
        {
            found += expansion(board);
        }

    }
    double expansion(State board)
    {
        if(isDisjunctiveGoalState(board, goal.amountOfGoals.top()))
        {
            return 1;
        }
        int i, j;
        for(i = 0; i < board.size(); i++)
        {
            for(j = 0; j < )
        }
        board = Move()
    }
}
