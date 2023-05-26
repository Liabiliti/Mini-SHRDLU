#include <iostream>
using namespace std;
class Action{
    public:
    int destination, source;
    double heuristic;
    bool operator <(const Action a) const
    {
        return this->heuristic > a.heuristic;
    }
};