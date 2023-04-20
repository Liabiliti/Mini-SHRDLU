#include <queue>
#include "Goal.h"
#include "State.h"

using namespace std;
class CompareStates
{
public:
    bool operator()(const std::pair<int, State> &a, const std::pair<int, State> &b) const
    {
        return a.first < b.first;
    }
};

class Solver
{
    queue<State> moves;
    vector<State> heuristicMoves;
    priority_queue<pair<int, State>, vector<pair<int, State>>, CompareStates> pq;
    vector<State> previousMoves;

public:
    Goal goal;
    State startingState;

    Solver() // This solver creates a random goal state and a fixed board size of 3*3 and 6 numbers
    {        // Used for Pass to Credit
        goal = Goal();
        startingState = State();
    }
    Solver(bool input)
    {
        goal = Goal(input);
        startingState = State();
    }
    Solver(int boardSize, int boardRange) // This solver constructor allows for the person to write how big, many numbers and what the goal state is
    {                                     // This is used for Tasks Distinction to High Distinction
        goal = Goal(boardSize, boardRange);
        startingState = State(boardSize, boardRange);
    }
    Solver(int boardSize, int boardRange, bool input) // This solver constructor allows for the person to write how big, many numbers and what the goal state is
    {                                                 // This is used for Tasks Distinction to High Distinction
        goal = Goal(boardSize, input);
        startingState = State(boardSize, boardRange);
    }
    int heuristic(const State &currentState, vector<int> target) // Checks for how many moves away a goal state is, checks for disjunctive
    {
        int distance = 100;
        int row, col;
        for (row = 0; row < currentState.board.size(); row++)
        {
            for (col = 0; col < currentState.board[row].size(); col++)
            {
                if (currentState.board[row][col] == target[0])
                {
                    goto check;
                }
            }
        }
    check: //Change so that is adjusts with boardsize
        if (currentState.board[target[1]][target[2]] == target[0])
        {
            return distance;
        }
        if (currentState.board[target[1]][target[2]] != target[0])
        {
            distance -= 14;
        }
        if (currentState.board[target[1]][target[2]] != 0)
        {
            distance -= 14;
        }
        if ((row + 1) < currentState.size)
        {
            if (currentState.board[row + 1][col] == 1)
                distance -= 14;
        }
        if ((row - 1) > -1)
        {
            if (currentState.board[row - 1][col] != 0)
                distance -= 14;
        }
        if (target[1] - 1 > -1)
        {
            if (currentState.board[target[1] - 1][target[2]] != 0)
                distance -= 14;
        }
        if (row - 2 > -1)
        {
            if (currentState.board[row - 2][col] != 0)
                distance -= 14;
        }
        if (target[1] - 2 > -1)
        {
            if (currentState.board[target[1] - 2][target[2]] != 0)
                distance -= 14;
        }

        return distance;
    }
    bool heuristicSearch(int conjunctive)
    {
        cout << "\nGoal State:\n";
        goal.printBoard(goal.goalBoard);
        cout << "Starting State: \n";
        startingState.printBoard(startingState.board);
        // backToStart:
        int counter = 0;
        int distance = 0;
        for (int i = 0; i < goal.amountOfGoals.size(); i++)
        {
            distance += heuristic(startingState, goal.amountOfGoals[i]);
        }
        cout << distance << endl;
        pq.push(make_pair(distance, startingState));
        // pq.push(make_pair(heuristic(startingState, goal.amountOfGoals.front()), startingState)); // pushes initial state to priority queue

        while ((!pq.empty()) && (counter < 100))
        {
            State currentState = pq.top().second;
            pq.pop();                                                                // Pushes out board with the highest priority ^^3
            currentState.possibleMoves(currentState, heuristicMoves, previousMoves); // inserts the current state and outputs a list of moves

            if (isConjunctiveGoalState(currentState)) // also checks against previous moves
            {
                cout << "\nStep: " << counter << " found the goal state" << endl;
                currentState.printBoard(currentState.board);
                return true;
            }
            counter++;
            for (auto &move : heuristicMoves)
            {
                if (!startingState.existingMove(move, previousMoves))
                {
                    for (int i = 0; i < goal.amountOfGoals.size(); i++)
                    {
                        distance += heuristic(currentState, goal.amountOfGoals[i]);
                    }
                    pq.push(make_pair(distance, move));
                }
            }
            distance = 0;
        }
        return false;
    }
    bool heuristicSearch()
    {
        cout << "\nGoal State:\n";
        goal.printBoard(goal.goalBoard);
        cout << "Starting State: \n";
        startingState.printBoard(startingState.board);
    backToStart:
        int counter = 0;
        pq.push(make_pair(heuristic(startingState, goal.amountOfGoals.front()), startingState)); // pushes initial state to priority queue

        while ((!pq.empty()) && (!goal.amountOfGoals.empty()))
        {
            State currentState = pq.top().second;
            pq.pop();                                                                // Pushes out board with the highest priority ^^3
            currentState.possibleMoves(currentState, heuristicMoves, previousMoves); // inserts the current state and outputs a list of moves

            if (isDisjunctiveGoalState(currentState, goal.amountOfGoals.back())) // also checks against previous moves
            {
                cout << "\nStep: " << counter << " found the goal state for: " << goal.amountOfGoals.back()[0] << endl;
                currentState.printBoard(currentState.board);
                while (!pq.empty())
                {
                    pq.pop();
                }
                previousMoves.clear();
                counter = 0;
                goal.amountOfGoals.pop_back();
                if ((!goal.amountOfGoals.empty()))
                {
                    goto backToStart;
                }
                return true;
            }
            counter++;
            for (auto &move : heuristicMoves)
            {
                if (!startingState.existingMove(move, previousMoves))
                    pq.push(make_pair(heuristic(move, goal.amountOfGoals.back()), move));
            }
            if (counter > 100)
            {
                cout << "\nCould not find goal state for: " << goal.amountOfGoals.back()[0] << endl;
                while (!pq.empty())
                {
                    pq.pop();
                }
                previousMoves.clear();
                counter = 0;
                goal.amountOfGoals.pop_back();
                if ((!goal.amountOfGoals.empty()))
                {
                    goto backToStart;
                }
                return false;
            }
        }
        return false;
    }
    bool search()
    {
        cout << "\nGoal State:\n";
        goal.printBoard(goal.goalBoard);
        cout << "Starting State: \n";
        startingState.printBoard(startingState.board);
    backToStart:
        moves.push(startingState);
        int counter = 0;
        while ((!moves.empty()) && (!goal.amountOfGoals.empty()))
        {
            State currentState = moves.front();
            // currentState.printBoard(currentState.board);
            moves.pop();
            currentState.possibleMoves(currentState, moves, previousMoves);
            if (isDisjunctiveGoalState(currentState, goal.amountOfGoals.back())) // also checks against previous moves
            {
                cout << "\nStep: " << counter << " found the goal state for: " << goal.amountOfGoals.back()[0] << endl;
                currentState.printBoard(currentState.board);
                while (!moves.empty())
                {
                    moves.pop();
                }
                previousMoves.clear();
                counter = 0;
                goal.amountOfGoals.pop_back();
                if ((!goal.amountOfGoals.empty()))
                {
                    goto backToStart;
                }
                return true;
            }
            counter++;
            if (counter > 100)
            {
                cout << "\nCould not find goal state for: " << goal.amountOfGoals.back()[0] << endl;
                while (!moves.empty())
                {
                    moves.pop();
                }
                previousMoves.clear();
                counter = 0;
                goal.amountOfGoals.pop_back();
                if ((!goal.amountOfGoals.empty()))
                {
                    goto backToStart;
                }
                return false;
            }
        }
        return false;
    }
    bool isDisjunctiveGoalState(State currentState, vector<int> action)
    {
        if (currentState.board[action[1]][action[2]] == action[0])
        {
            return true;
        }
        return false;
    }
    bool isConjunctiveGoalState(State state)
    {
        int matches = 0;
        for (int i = 0; i < state.size; i++)
        {
            for (int j = 0; j < state.size; j++)
            {
                if (goal.goalBoard[i][j] == state.board[i][j] && (state.board[i][j] != 0))
                {
                    matches++;
                }
            }
        }
        if (matches == goal.amountOfGoals.size())
        {
            return true;
        }
        return false;
    }
};