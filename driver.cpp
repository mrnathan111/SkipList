#include "skiplist.h"

void test1() //tests the creation of the SkipList AND add function (which tests the addBefore function also). Also tests the Contains/Removes functions
{
    SkipList s(5);
    for (int i = 0; i < 10; i++)
    {
        s.Add(i);
    }
    for (int i = 0; i < 10; i++)
    {
        assert(s.Contains(i) == true);
    }
    assert(s.Remove(12) == false);
    assert(s.Contains(4) == true);
    s.Remove(4);
    assert(s.Contains(4) == false);
}

void test2() //testing print sL, only 1 level or else it'd be impossible to anticipate what the output will look like b/c of rand nums)
{
    SkipList s;
    s.Add(4);
    s.Add(2);
    s.Add(3);
    s.Add(1);
    stringstream ss, sss;
    ss << s;
    sss << "Level: 0 -- -2147483648, 1, 2, 3, 4, 2147483647";
    assert(ss.str() == sss.str());

}

void test3()
{
    SkipList s(5);
    for (int i = 0; i < 30; i++)
    {
        int number = rand() % 100;
        s.Add(number);
    }
    sNode* curNode = s.getTopHeadNode(); //curNode is frontGuards[maxLevel]
    assert(curNode->upLevel == nullptr); //nothing higher than max level
    assert(curNode->next->upLevel == nullptr); //nothing over next and up is valid b/c your at the highest level
    assert(curNode->next->next->next == nullptr); //theres 3 nodes (including guards) in top level in this list. Going over 3x's would be nullptr
    assert(curNode->prev == nullptr); //nothing to the left of the guard
    assert(curNode->data == -2147483648);
}

void test4()
{
    SkipList s;
    for (int i = 0; i < 30; i++)
    {
        int number = rand() % 100;
        s.Add(number);
    }
    sNode* curNode = s.getTopHeadNode(); //curNode is frontGuards[maxLevel]
    assert(curNode->prev == nullptr && curNode->upLevel == nullptr && curNode->downLevel == nullptr); //1 level, head has no ptrs but next
    assert(curNode->next->data == 1); //with the same list that is generated from rand(), there should be a 1 added (min val outside of guard) ==head->next
}

void test5()
{
    SkipList s(3);
    for (int i = 0; i < 9; i++)
    {
        int number = rand() % 100;
        s.Add(number);
    }
    sNode* curNode = s.getTopHeadNode(); //curNode is frontGuards[maxLevel]
    assert(curNode->next->prev == curNode);
    assert(curNode->downLevel->downLevel->next->data == 24);//going to first level and over 1, will get the 1st node (not guard) which is data 24
    assert(curNode->next->next->next->next == nullptr);
}

void testAll()
{
    test1();
    test2();
    test3();
    test4();
    test5();
}

int main()
{
    testAll();
    cout << "Done; Passed All Tests!" << endl;
    return 0;
}
