#pragma once
#include "sNode.h"

class SkipList
{
private:
    int depth;
    sNode **frontGuards;
    sNode **rearGuards;
    int maxLevel;
public:
    explicit SkipList(int depth = 1); //Default SkipList has depth = 1 
    virtual ~SkipList(); //Deconst
    sNode* getTopHeadNode() const; //returns top front guard node
    void deleteNodes(sNode* head); //deletes the given nodes memory
    bool Add(int newData); //returns TRUE if successfully added, no duplicates
    bool Remove(int targetVal); //Return TRUE if successfully removed
    bool Contains(int targetVal); //return TRUE if found in SkipList
    void addBefore(sNode *newNode, sNode *nextNode);
    bool alsoHigher(); //True if adding up, false if not
    friend ostream &operator<<(ostream &os, const SkipList &list);
};