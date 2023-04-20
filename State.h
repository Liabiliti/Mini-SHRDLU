#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <stack>
#include <queue>

using namespace std;

class State
{
private:
    int takenColumn, boardNumber;
    vector<vector<int>> board;
public:
    int value, size;
    vector<vector<int>> board;
    //vector<vector<int>> board;// needs to be private
    State() : board(3, vector<int>(3, 0))
    {
        size = 3;
        boardNumber = 6;
        random();
        pushdown();
    }
    State(int boardSize, int boardRange) : board(boardSize, vector<int>(boardSize, 0))
    {
        size = boardSize;
        if (isNumberInRange(boardRange, size))
        {
            boardNumber = boardRange;
            random();
            pushdown();
        }
        else
        {
            cout << "Not in the range of possible numbers" << endl;
        }
    }

    bool isNumberInRange(int value, int size)
    {
        if (value >= size && value <= (pow(size, 2) - size))
        {
            return true;
        }
        return false;
    }
    void random();
    void printBoard(vector<vector<int>> board);
    void pushdown();
    bool existingMove(State &newState, vector<State> &previousMoves);
    void possibleMoves(State currentState, queue<State> &possibleMoves, vector<State> &previousMoves);
    void possibleMoves(State currentState, vector<State> &possibleMoves, vector<State> &previousMoves);
    bool operator==(const State &object);

    bool isEmpty(int col)
    {
        if (board[size - 1][col] == 0)
        {
            return true;
        }
        return false;
    }

    bool isFull(int col)
    {
        if (board[0][col] != 0)
        {
            return true;
        }
        return false;
    }

    int removeBlock(int column)
    {
        if (!isEmpty(column))
        {
            takenColumn = column;
            for (int i = 0; i < size; i++)
            {
                if (board[i][column] != 0)
                {
                    int value = board[i][column];
                    board[i][column] = 0;
                    return value;
                }
            }
        }
        return -1;
    }

    bool insertBlock(int column, int value)
    {
        if (value == -1)
        {
            return false;
        }
        if (!isFull(column))
        {
            for (int i = size - 1; i >= 0; i--)
            {
                if (board[i][column] == 0)
                {
                    board[i][column] = value;
                    return true;
                }
            }
        }
        insertBlock(takenColumn, value);
        return false;
    }

    State moveBlock(int source, int destination)
    {
        State newState = *this;
        if (newState.insertBlock(destination, newState.removeBlock(source)))
        {
            return newState;
        }
        return *this;
    }
};
bool State::operator==(const State &state)
{
    for (int i = 0; i < state.board.size(); i++)
    {
        for (int j = 0; j < state.board[i].size(); j++)
        {
            if (board[i][j] != state.board[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
void State::possibleMoves(State currentState, queue<State> &possibleMoves, vector<State> &previousMoves)
{
    if (existingMove(currentState, previousMoves))
    {
        return;
    }
    previousMoves.push_back(State(currentState));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            State newState = moveBlock(i, j);
            if (!existingMove(newState, previousMoves))
            {
                possibleMoves.push(newState);
            }
        }
    }
}
void State::possibleMoves(State currentState, vector<State> &possibleMoves, vector<State> &previousMoves)
{
    if (existingMove(currentState, previousMoves))
    {
        return;//if current is an existing move, leave function
    }
    previousMoves.push_back(State(currentState));//if not add currentState to previous moves
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            State newState = moveBlock(i, j); 
            if (!existingMove(newState, previousMoves))
            {
                possibleMoves.push_back(newState); // if its not an existing move add it to possible moves
            }
        }
    }
}

bool State::existingMove(State &newState, vector<State> &previousMoves)
{
    for (int i = 0; i < previousMoves.size(); i++)
    {
        if (newState == previousMoves[i])
        {
            return true;
        }
    }
    return false;
}

void State::random()
{
    srand(time(0));
    for (int i = 1; i <= boardNumber; i++)
    {
        int row = rand() % size;
        int col = rand() % size;
        while (board[row][col] != 0)
        {
            row++;
            if (row % size == 0)
            {
                col++;
                row = 0;
                if (col % size == 0)
                {
                    col = 0;
                    row = 0;
                }
            }
        }
        board[row][col] = i;
    }
}

void State::printBoard(vector<vector<int>> board)
{
    for (int i = 0; i < size; i++)
    {
        cout << " ----";
    }
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            cout << "| " << setw(2) << board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    for (int i = 0; i < size; i++)
    {
        cout << " ----";
    }
    cout << endl;
}

void State::pushdown()
{
    stack<int> dropdown;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (board[j][i] != 0)
            {
                dropdown.push(board[j][i]);
            }
        }
        for (int j = size - 1; j >= 0; j--)
        {
            if (!dropdown.empty())
            {
                board[j][i] = dropdown.top();
                dropdown.pop();
            }
            else
            {
                board[j][i] = 0;
            }
        }
    }
}
