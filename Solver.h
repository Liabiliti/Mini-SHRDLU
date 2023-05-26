#include "State.h"

class Solver
{
public:
    State startingState;
    queue<Action> actions;
    priority_queue<Action> pq;
    stack<Goal> disjunctiveGoals;
    vector<Goal> goals;
    vector<State> previousMoves;
    Goal goal;
    Solver(){};
    Solver(int boardSize, int amountOfNumbers)
    {
        startingState = State(boardSize, amountOfNumbers);
    }
    bool search()
    {
        Action move;
        cout << "Initial state: \n";
        startingState.printBoard();
        setGoal(goal);
        startingState.possibleMoves(actions);
        previousMoves.push_back(startingState);
        int counter = 0;
        do
        {
            if (actions.empty())
            {
                cout << "No possible moves left!\n";
                return false;
            }
            move = actions.front(); // Take first action from possible moves
            actions.pop();
            State temp = State(startingState); // Create a copy of current State
            temp.moveBlock(move);              // Copied state completes first move
            if (existingState(temp))           // If it is an existing move, get ne
            {
                continue;
            }
            startingState.moveBlock(move);
            cout << "\nStep: " << counter << " Move " << startingState.isValue(move.destination) << " from " << move.source << " to " << move.destination << ".\n";
            startingState.printBoard();
            if (startingState.isGoal(goal))
            {
                cout << "Found ";
                goal.print();
                cout << "!\n";
                return true;
            }
            previousMoves.push_back(startingState);
            while (!actions.empty())
            {
                actions.pop();
            }
            startingState.possibleMoves(actions);

            counter++;
            if (actions.empty())
            {
                cout << "No possible moves left!";
                return false;
            }
        } while (!(startingState.isGoal(goal)) && (counter < 100));
        cout << "Could not find Goal State";
        return false;
    }
    bool heuristicSearch()
    {
        Action move;
        cout << "Initial state: \n";
        startingState.printBoard();
        setGoal(goal);
        startingState.possibleMoves(pq, goal);
        previousMoves.push_back(startingState);
        int counter = 0;
        do
        {
            if (pq.empty())
            {
                cout << "No possible moves left!\n";
                return false;
            }
            move = pq.top(); 
            pq.pop();
            State temp = State(startingState);
            temp.moveBlock(move);              
            if (existingState(temp))           
            {
                continue;
            }
            startingState.moveBlock(move);
            cout << "\nStep: " << counter << " Move " << startingState.isValue(move.destination) << " from " << move.source << " to " << move.destination << ".\n";
            startingState.printBoard();
            if (startingState.isGoal(goal))
            {
                cout << "Found ";
                goal.print();
                cout << "!\n";
                return true;
            }
            previousMoves.push_back(startingState);
            while (!pq.empty())
            {
                pq.pop();
            }
            startingState.possibleMoves(pq, goal);
            counter++;
            if (pq.empty())
            {
                cout << "No possible moves left!";
                return false;
            }
        } while (!(startingState.isGoal(goal)) && (counter < 100));
        cout << "Could not find Goal State";
        return false;
    }
    bool heuristicDisjunctiveSearch() 
    {
        Action move;
        cout << "Initial state: \n";
        startingState.printBoard();
        int again = 0;
        while (again != -1 || disjunctiveGoals.size() >= startingState.getNumberOfBlocks())
        {
            setGoal(goal);
            disjunctiveGoals.push(goal);
            cout << "\nWould you like to add another goal?: ";
            cin >> again;
        }
        goal = disjunctiveGoals.top();
        disjunctiveGoals.pop();
        startingState.possibleMoves(pq, goal);
        previousMoves.push_back(startingState);
        int counter = 0;
        State base = State(startingState);
        do
        {

            if (pq.empty())
            {
                cout << "No possible moves left!\n";
                if (!disjunctiveGoals.empty())
                {
                    counter = 0;
                    startingState = base;
                    while (!pq.empty())
                    {
                        pq.pop();
                    }
                    startingState.possibleMoves(pq, goal);
                    previousMoves.push_back(startingState);
                    previousMoves.clear();
                    cout << "\nInitial state: \n";
                    startingState.printBoard();
                    goal = disjunctiveGoals.top();
                    disjunctiveGoals.pop();
                }
                else
                {
                    return false;
                }
            }
            move = pq.top(); // Take first action from possible moves
            pq.pop();
            State temp = State(startingState); // Create a copy of current State
            temp.moveBlock(move);              // Copied state completes first move
            if (existingState(temp))           // If it is an existing move, get new
            {
                continue;
            }
            startingState.moveBlock(move);
            cout << "\nStep: " << counter << " Move " << startingState.isValue(move.destination) << " from " << move.source << " to " << move.destination << ".\n"; // Did not make
            startingState.printBoard();
            if (startingState.isGoal(goal))
            {
                cout << "Found ";
                goal.print();
                cout << "!\n";
                counter = 0;
                startingState = base;
                while (!pq.empty())
                {
                    pq.pop();
                }
                startingState.possibleMoves(pq, goal);
                previousMoves.push_back(startingState);
                if (disjunctiveGoals.empty())
                {
                    return true;
                }
                previousMoves.clear();
                cout << "\nInitial state: \n";
                startingState.printBoard();
                goal = disjunctiveGoals.top();
                disjunctiveGoals.pop();
                continue;
            }
            previousMoves.push_back(startingState);
            while (!pq.empty())
            {
                pq.pop();
            }
            startingState.possibleMoves(pq, goal);
            counter++;
            if ((counter == 100) && (!disjunctiveGoals.empty()))
            {
                cout << "Could not find Goal State\n";
                counter = 0;
                startingState = base;
                while (!pq.empty())
                {
                    pq.pop();
                }
                startingState.possibleMoves(pq, goal);
                previousMoves.push_back(startingState);
                previousMoves.clear();
                cout << "Initial state: \n";
                startingState.printBoard();
                goal = disjunctiveGoals.top();
                disjunctiveGoals.pop();
            }
        } while (counter < 100);
        cout << "Could not find Goal State";
        return false;
    }
    bool heuristicConjunctiveSearch() 
    {
        Action move;
        cout << "Initial state: \n";
        startingState.printBoard();
        int again = 0;
        while (again != -1 || goals.size() >= startingState.getNumberOfBlocks()) // Add goal states
        {
            setConjunctiveGoal(goal);
            goals.push_back(goal);
            cout << "\nPress -1 to search; else type any other number for more goals: ";
            cin >> again;
        }
        startingState.possibleMoves(pq, goals);
        previousMoves.push_back(startingState);
        int counter = 0;
        do
        {
             if (pq.empty())
            {
                cout << "No possible moves left!\n";
                return false;
            }
            move = pq.top(); 
            pq.pop();
            State temp = State(startingState); 
            temp.moveBlock(move);             

            if (existingState(temp)) 
            {
                continue;
            }
            startingState.moveBlock(move);
            cout << "\nStep: " << counter << " Move " << startingState.isValue(move.destination) << " from " << move.source << " to " << move.destination << ".\n";
            startingState.printBoard();

            for (int i = 0; i < goals.size(); i++)
            {
                if (!startingState.isGoal(goals[i]))
                {
                    break;
                }
                else if (i == goals.size() - 1)
                {
                    cout << "Found goal states!\n";
                    return true;
                }
            }
            previousMoves.push_back(startingState);
            while (!pq.empty())
            {
                pq.pop();
            }
            startingState.possibleMoves(pq, goals);

            counter++;
            if (pq.empty())
            {
                cout << "No possible moves left!";
                return false;
            }

        } while (counter < 100);
        cout << "Could not find Goal State";
        return false;
    }
    bool existingState(State currentState)
    {
        for (int i = 0; i < previousMoves.size(); i++)
        {
            if (previousMoves[i] == currentState)
            {
                return true;
            }
        }
        return false;
    }
    bool existingState(SearchNode currentNode, vector<SearchNode> openSet)
    {
        for (int i = 0; i < openSet.size(); i++)
        {
            if (openSet[i] == currentNode)
            {
                return true;
            }
        }
        return false;
    }
    bool valueInGoals(int value)
    {
        for (int i = 0; i < goals.size(); i++)
        {
            if (goals[i].value == value)
            {
                return true;
            }
        }
        return false;
    }
    bool targetInGoals(int row, int col)
    {
        for (int i = 0; i < goals.size(); i++)
        {
            if ((goals[i].row == row) && (goals[i].col == col))
            {
                return true;
            }
        }
        return false;
    }
    void setConjunctiveGoal(Goal &goal)
    {
        int value = 0;
        int row = -1;
        int column = -1;
        cout << "Input a goal in the format (block, row, col):\n";
        while ((value < 1) || (value > startingState.getNumberOfBlocks()))
        {
            cout << "Block (1 - " << startingState.getNumberOfBlocks() << "): ";
            cin >> value;
            if (value < 1)
                cout << "Number not in range\n";
        }
        if (valueInGoals(value))
        {
            cout << "Value is already in a goal\n";
            return;
        }
        goal.value = value;
        while ((row < 0) || (row >= startingState.getBoardSize()))
        {
            cout << "Row (0 - " << startingState.getBoardSize() - 1 << " bottom - up): ";
            cin >> row;
            if ((row < 0) || (row >= startingState.getBoardSize()))
                cout << "Number not in range\n";
        }

        while ((column < 0) || (column >= startingState.getBoardSize()))
        {
            cout << "Column (0 - " << startingState.getBoardSize() - 1 << " left - right): ";
            cin >> column;
            if ((column < 0) || (column >= startingState.getBoardSize()))
                cout << "Number not in range\n";
        }
        if (targetInGoals(row, column))
        {
            cout << "Location is already occupied\n";
            return;
        }
        goal.row = row;
        goal.col = column;
        goal.print();
    }
    void setGoal(Goal &goal)
    {
        int value = 0;
        int row = -1;
        int column = -1;
        cout << "Input a goal in the format (block, row, col):\n";
        while ((value < 1) || (value > startingState.getNumberOfBlocks()))
        {
            cout << "Block (1 - " << startingState.getNumberOfBlocks() << "): ";
            cin >> value;
            if (value < 1)
                cout << "Number not in range\n";
        }
        goal.value = value;
        while ((row < 0) || (row >= startingState.getBoardSize()))
        {
            cout << "Row (0 - " << startingState.getBoardSize() - 1 << " bottom - up): ";
            cin >> row;
            if ((row < 0) || (row >= startingState.getBoardSize()))
                cout << "Number not in range\n";
        }

        while ((column < 0) || (column >= startingState.getBoardSize()))
        {
            cout << "Column (0 - " << startingState.getBoardSize() - 1 << " left - right): ";
            cin >> column;
            if ((column < 0) || (column >= startingState.getBoardSize()))
                cout << "Number not in range\n";
        }
        goal.row = row;
        goal.col = column;
        goal.print();
    }
    bool AStar()
    {
        priority_queue<SearchNode> openSet;                       // Creates pq of SearchNodes
        SearchNode startingNode(startingState, goal, 0, nullptr); // Initialised with it's own starting state and goal
        vector<SearchNode> previousMoves;
        cout << startingState.heuristic(startingNode.goal) << endl;
        startingNode.cost = 0;      // Set initial node to 0 + heuristic
        openSet.push(startingNode); // Push the starting Node into a priority Queue
        while (!openSet.empty())
        {
            SearchNode currentNode = openSet.top();
            // if (currentNode.state->isGoal(currentNode.goal))
            // {
            //     return reconstructPath(currentNode); // Coming later
            // }
            openSet.pop();
            previousMoves.push_back(currentNode);

            for (auto neighbourState : currentNode.possibleMoves(currentNode.state))
            {
                double tempScore = currentNode.cost + (100 / ((currentNode.state.getBoardSize() - 1) * 3) + 2); // Add one to cost, as a move is occurring
                SearchNode neighbourNode(neighbourState, goal, tempScore, &currentNode);                        // Create new Node with currentNode as parent
                neighbourNode.fScore = neighbourNode.state.heuristic(goal) + neighbourNode.cost;                // neighbourNode assigns cost as the heuristic plus the number of moves in parent
                cout << neighbourNode.fScore << endl;
                neighbourNode.state.printBoard();
                if (existingState(neighbourState)) // If it is an existing move, get a new Node
                {
                    continue;
                }
                // openSet.push(neighbourNode);
            }
        }
        return false;
    }
};