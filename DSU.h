#ifndef DSU_H
#define DSU_H
#include "bits.h"
#include "vector"
using namespace std;
const int error = -1e9;
class DSU
{
private:
    int countofGroups;
    vector<int> parents, ranks;

public:
    //Constructor
    DSU(int n)
    {
        int countOfGroups = n;
        vector<int> par(n), ran(n, 1);
        ranks = ran;
        parents = par;
        for (int i = 0; i < n; i++)
        {
            parents[i] = i;
        }
    }
    //Some functionalities
    void makeSet();
    void Union(int firstId, int secondId);
    int Find(int id);
    int sizeOfAGroup(int id);
    int totalGroups();
    bool isValid(int id);
};

bool DSU::isValid(int id)
{
    return (id < 0 || id >= parents.size());
}

void DSU::makeSet()
{
    countofGroups++;
    int prevSize = parents.size();
    parents.push_back(prevSize + 1);
    ranks.push_back(1);
}

int DSU::Find(int id)
{
    if (isValid(id) == false)
    {
        return error;
    }
    if (parents[id] == id)
    {
        return id;
    }
    int temp = parents[id];
    return parents[id] = Find(temp);
}

void DSU::Union(int firstId, int secondId)
{
    if (isValid(firstId) == false)
    {
        return;
    }
    if (isValid(secondId) == false)
    {
        return;
    }
    int firstGroup = Find(firstId);
    int secondGroup = Find(secondId);
    if (firstGroup == secondGroup)
    {
        return;
    }
    else if (ranks[firstGroup] > ranks[secondGroup])
    {
        parents[secondGroup] = firstGroup;
        ranks[firstGroup] += ranks[secondGroup];
    }
    else
    {
        parents[firstGroup] = secondGroup;
        ranks[secondGroup] += ranks[firstGroup];
    }
    countofGroups--;
}

int DSU::sizeOfAGroup(int id)
{
    if (isValid(id) == false)
    {
        return error;
    }
    else
    {
        return ranks[id];
    }
}

int DSU::totalGroups()
{
    return countofGroups;
}

#endif