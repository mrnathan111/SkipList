#pragma once
#include <iostream>
#include <sstream>
#include <limits.h>
#include <cassert>
using namespace std;

class sNode
{
    friend class SkipList;
private:
    
public:
    explicit sNode(int data);
    int data;
    sNode *next;
    sNode *prev;
    sNode *upLevel;
    sNode *downLevel;
};