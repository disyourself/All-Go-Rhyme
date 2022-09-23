
#include <limits.h>

class Node
{
  public:
    int   val;
    Node *next;
    Node *prev;

    Node (int val_) : val (val_), next (nullptr), prev (nullptr) {}
};

class MyLinkedList
{
  private:
    Node *head;
    Node *tail;

  public:
    MyLinkedList () : head (new Node (INT_MAX)), tail (new Node (INT_MIN))
    {
        head->next = tail;
        tail->prev = head;
    }

    int
    get (int index)
    {
        Node *ptr = head->next;
        int   i   = 0;

        while (i < index) {
            ++i;
            if (!ptr->next)
                return -1;
            ptr = ptr->next;
        }
        if (!ptr->next)
            return -1;
        return ptr->val;
    }

    void
    addAtHead (int val)
    {
        Node *old_head   = head->next;
        head->next       = new Node (val);
        head->next->prev = head;
        head->next->next = old_head;
        old_head->prev   = head->next;
    }

    void
    addAtTail (int val)
    {
        Node *old_tail       = tail->prev;
        old_tail->next       = new Node (val);
        old_tail->next->prev = old_tail;
        old_tail->next->next = tail;
        tail->prev           = old_tail->next;
    }

    void
    addAtIndex (int index, int val)
    {
        if (index < 0)
            addAtHead (val);

        Node *ptr = head->next;
        int   i   = 0;
        while (i < index && ptr->next)
        {
            ++i;
            ptr = ptr->next;
        }

        if (!ptr->next && i == index) {
            addAtTail (val);
        }
        else if (ptr->next) {
            Node *prevp       = ptr->prev;
            prevp->next       = new Node (val);
            prevp->next->prev = prevp;
            prevp->next->next = ptr;
            ptr->prev         = prevp->next;
        }
        else
            return;
    }

    void
    deleteAtIndex (int index)
    {
        Node *ptr = head->next;
        int   i   = 0;
        while (i < index)
        {
            ++i;
            if (!ptr->next)
                return;
            ptr = ptr->next;
        }
        if (ptr->next)
        {
            Node *p = ptr->prev;
            Node *n = ptr->next;

            p->next = n;
            n->prev = p;
        }
    }
};
/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
