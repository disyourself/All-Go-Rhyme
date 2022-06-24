#include <iostream>
#include <set>
#include <string>

using namespace std;

class node
{
  public:
    int val = 0;
    node *next;
    node *prev;
    node (int num)
    {
        val = num;
        next = nullptr;
        prev = nullptr;
    }
};

class Solution
{
  public:
    bool
    hasCycle (string graph)
    {
        set<node *> map;

        for (int i = 0; i < graph.length ();)
            {
                int num1 = graph[i] - '0';
                int num2 = graph[i + 2] - '0';

                node *temp1 = nullptr;
                node *temp2 = nullptr;
                for (auto it = map.begin (); it != map.end (); it++)
                    {
                        if ((*it)->val == num1)
                            {
                                temp1 = *it;
                            }
                        if ((*it)->val == num2)
                            {
                                temp2 = *it;
                            }
                    }
                temp1 = temp1 == nullptr ? (new node (num1)) : temp1;
                temp2 = temp2 == nullptr ? (new node (num2)) : temp2;

                temp1->next = temp2;
                temp2->prev = temp1;

                i += 2;
            }

        for (auto it = map.begin (); it != map.end (); it++)
            {
                struct node *temp = *it;
                while (temp)
                    {
                        if (temp->next == *it)
                            {
                                return true;
                            }
                        else
                            temp = temp->next;
                    }
            }
        return false;
    }
};

int
main ()
{
    string graph = "1->2,2->3,3->1";

    Solution solu;
    bool ret = solu.hasCycle (graph);

    cout << ret;

    return 0;
}