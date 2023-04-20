#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
// #include "State.h"

using namespace std;

class Goal
{
    int boardSize = 3;

public:
    int value, row, col;
    vector<vector<int>> amountOfGoals;
    vector<vector<int>> goalBoard;
    Goal() : goalBoard(3, vector<int>(3, 0))
    {
        srand(time(NULL));
        int row, col;
        for (int i = 0; i < 6; i++)
        {
            row = rand() % 3;
            col = rand() % 3;
            if (addGoal(i, row, col))
            {
                vector<int> action = {i, row, col};
                amountOfGoals.push_back(action);
            }
        }
    }
    Goal(bool input) : goalBoard(3, vector<int>(3, 0))
    {
        userInput();
    }
    Goal(int size, int numbers) : goalBoard(size, vector<int>(size, 0))
    {
        boardSize = size;
        srand(time(NULL));
        int row, col;
        for (int i = 0; i < numbers; i++)
        {
            row = rand() % size;
            col = rand() % size;
            if (addGoal(i, row, col))
            {
                vector<int> action = {i, row, col};
                amountOfGoals.push_back(action);
            }
        }
    }
    Goal(int size, bool input) : goalBoard(size, vector<int>(size, 0))
    {
        boardSize = size;
        userInput();
    }
    bool addGoal(int value, int row, int column)
    {
        if (row > boardSize-1 || column > boardSize-1)
        {
            cout << "Out of board range\n";
            return false;
        }
        else if (isNumberInRange(value))
        {
            if (!isNumberInBoard(value))
            {
                if (goalBoard[row][column] == 0)
                {
                    goalBoard[row][column] = value;
                    return true;
                }
                cout << "Place already taken\n";
                return false;
            }
            cout << "Number already in list!\n";
            return false;
        }
        cout << "Number out of range!\n";
        return false;
    }
    bool isNumberInBoard(int value)
    {
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if (goalBoard[i][j] == value)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool isNumberInRange(int value)
    {
        if (value > 0 && value <= ((boardSize * boardSize) - boardSize))
        {
            return true;
        }
        return false;
    }
    void userInput()
    {
        int exit = 0, value, row, column;
        while (exit != -1)
        {
            cout << "Write -1 if you don't want to add goals" << endl;
            cin >> exit;
            if (exit != -1)
            {
                cout << "Value: ";
                cin >> value;
                cout << "\nRow: ";
                cin >> row;
                cout << "\nColumn: ";
                cin >> column;
                if (addGoal(value, row, column))
                {
                    vector<int> action = {value, row, column};
                    amountOfGoals.push_back(action);
                }
            }
        }
    }
    void printBoard(vector<vector<int>> board)
    {
        for (int i = 0; i < boardSize; i++)
        {
            cout << " ----";
        }
        cout << endl;
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {

                cout << "| " << setw(2) << board[i][j] << " ";
            }
            cout << "|" << endl;
        }
        for (int i = 0; i < boardSize; i++)
        {
            cout << " ----";
        }
        cout << endl;
    }
};
