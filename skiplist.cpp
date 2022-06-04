#include "skiplist.h"

SkipList::SkipList(int d) //if nothing, it'll do depth = 1. If you do pass an int, it'll do normal param
{
    if (d < 1) //if INVALID depth 
    {
        cout << "Depth value is NOT valid" << endl;
        return;   
    }
    else
    {
        depth = d;
        maxLevel = depth - 1;
        frontGuards = new sNode*[depth];
        rearGuards = new sNode*[depth];
        for (int i = 0; i < depth; i++) //creating guard sNodes with INT_MIN and INT_MAX data value
        {
            frontGuards[i] = new sNode(INT_MIN);
            rearGuards[i] = new sNode(INT_MAX);
        }
        rearGuards[0]->prev = frontGuards[0]; //linking rear and front guards on level 0
        frontGuards[0]->next = rearGuards[0];//^^
        if (depth != 1) //at least depth 2
        {
            for (int i = 1; i < depth; i++) //link the rest of the guards
            {
                frontGuards[i]->downLevel = frontGuards[i - 1];
                rearGuards[i]->downLevel = rearGuards[i - 1];
                frontGuards[i - 1]->upLevel = frontGuards[i];
                rearGuards[i - 1]->upLevel = rearGuards[i];
                frontGuards[i]->next = rearGuards[i];
                rearGuards[i]->prev = frontGuards[i];
            }
        }
    }
}

SkipList::~SkipList()
{
    for (int i = 0; i < depth; i++)
    {
        sNode* curNode = frontGuards[maxLevel - i]->next;
        sNode* deleteNode = curNode;
        while (curNode != rearGuards[maxLevel - i])
        {
            curNode = curNode->next;
            delete deleteNode;
            deleteNode = nullptr;
            deleteNode = curNode;
        }
    }
    for (int i = 0; i < depth; i++)
    {
        delete frontGuards[i];
        frontGuards[i] = nullptr;
        delete rearGuards[i];
        rearGuards[i] = nullptr;
    }
    delete[] frontGuards;
    delete[] rearGuards;
    frontGuards = nullptr;
    rearGuards = nullptr;
}

bool SkipList::Add(int newData)
{
    sNode* nextNode = frontGuards[0]->next;
    while (nextNode->next != nullptr && nextNode->data < newData)
    {
        nextNode = nextNode->next;
    }
    if (nextNode->data == newData) //if duplicate found
        {
            return false;
        } 
    sNode* newNode = new sNode(newData);
    addBefore(newNode, nextNode);
    int counter = 0;
    bool goUpOrNot = alsoHigher();
    while (goUpOrNot == true && counter != maxLevel)
    {
        sNode* newUpper = new sNode(newData);
        newUpper->downLevel = newNode;
        newNode->upLevel = newUpper;
        sNode* curNode = newNode;
        while (curNode->prev->upLevel == nullptr && curNode != nullptr)
        {
            curNode = curNode->prev;
        }
        curNode = curNode->prev->upLevel->next;
        addBefore(newUpper, curNode);
        newNode = newUpper;
        goUpOrNot = alsoHigher();
        counter++;
    }
    return true;
}
void SkipList::addBefore(sNode *newNode, sNode *nextNode)
{
    assert(newNode != nullptr && nextNode != nullptr && newNode->data < nextNode->data);
    newNode->next = nextNode;
    nextNode->prev->next = newNode;
    newNode->prev = nextNode->prev;
    nextNode->prev = newNode;
    assert(newNode->next == nextNode && nextNode->prev == newNode);
    assert(newNode->prev != nullptr && newNode->prev->data < newNode->data);
}

bool SkipList::Remove(int targetVal)
{
    if (Contains(targetVal) == false) //if targetVal is NOT in list, return false
        return false;
    else
    {
        sNode* curNode = frontGuards[maxLevel];
        while (curNode != nullptr)
        {
            while (curNode->next->data < targetVal)
            {
                curNode = curNode->next;
            }
            if (curNode->downLevel == nullptr && curNode->next->data == targetVal)
            {
                sNode* temp = curNode->next;
                temp->upLevel = curNode->next;
                temp->next = curNode->next->next;
                curNode->next = temp;
                temp->next->prev = curNode;
                curNode->next = temp->next;                
                return true;
            }
            if (curNode->next->data != targetVal)
                curNode = curNode->downLevel;
            else
            {
                curNode->next = curNode->next->next;
                curNode->next->prev = curNode;
            }
        }
    }
    if (Contains(targetVal) == false)
        return true;
    return false;
}

bool SkipList::Contains(int targetVal)
{
    sNode* curNode = frontGuards[maxLevel];
    while (curNode != nullptr)
    {
        while (curNode->next->data < targetVal)
        {
            curNode = curNode->next;
        }
        if (curNode->next->data == targetVal)
            return true;
        else
            curNode = curNode->downLevel;
    }
    return false;
}

ostream &operator<<(ostream &os, const SkipList &list)
{
    for (int i = 0; i < list.depth; i++)
    {
        os << "Level: " << list.depth - 1 - i << " -- ";
        sNode* curNode = list.frontGuards[list.depth - 1 - i];
        while (curNode != nullptr && curNode->next != nullptr)
        {
            os << curNode->data << ", ";
            curNode = curNode->next;
        }
        if (curNode != nullptr && curNode->next == nullptr) //Doesn't print the comma at the end of the level
        {
            os << curNode->data;
        }
        if (list.depth != 1)
            os << endl;
    }
    return os;
}

bool SkipList::alsoHigher()
{
    return ((rand() % 2) == 1);
}

sNode* SkipList::getTopHeadNode() const
{
    return frontGuards[maxLevel];
}