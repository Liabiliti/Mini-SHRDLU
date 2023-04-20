
class Action{
    public:
    int destination, source, heuristic;
    bool operator <(const Action a) const
    {
        return a.heuristic < this->heuristic;
    }
};