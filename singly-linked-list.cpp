#include <iostream>
using namespace std;

class node
{
private:
    int data;
    node *NEXT = NULL;

public:
    node(int data1)
    {
        data = data1;
    }

    friend class linkedlist;
};

class linkedlist
{
private:
    node *head = NULL;

public:
    void add_node(int iData)
    {
        node *tmp = new node(iData);
        if (head == NULL)
        {
            head = tmp;
        }
        else
        {
            tmp->NEXT = head;
            head = tmp;
        }
    }

    void addinmid(int n, int location)
    {
        node *current = head;
        int count = 1;
        while (current->NEXT != NULL && count++ < location)
        {
            current = current->NEXT;
        }
        node *temp = new node(n);
        temp->NEXT = current->NEXT;
        current->NEXT = temp;
    }

    void addattail(int a)
    {
        node *temp1 = new node(a);
        temp1->NEXT = NULL;

        // Case 1: empty list
        if (head == NULL)
        {
            head = temp1;
            return;
        }

        // Case 2: list not empty
        node *temp = head;
        while (temp->NEXT != NULL)
        {
            temp = temp->NEXT;
        }

        temp->NEXT = temp1;
    }

    void remathead()
    {
        if (head != NULL)
        {
            node *tmp = head;
            head = head->NEXT;
            delete tmp;
        }
    }

    void rematmid(int location)
    {
        node *previous = head;
        node *current = head->NEXT;
        int count = 1;
        while (current->NEXT != NULL && count++ < location)
        {
            previous = current;
            current = current->NEXT;
        }
        previous->NEXT = current->NEXT;
        delete current;
        current = NULL;
    }

    void remattail()
    {
        if (head == NULL)
        {
            return;
        }
        else if (head->NEXT == NULL)
        {
            delete head;
            head = NULL;
        }
        else
        {
            node *previous = head;
            node *current = head->NEXT;
            while (current->NEXT != NULL)
            {
                previous = current;
                current = current->NEXT;
            }
            previous->NEXT = current->NEXT;
            delete current;
        }
    }

    void triversng()
    {
        node *temp = head;
        while (temp != NULL)
        {
            temp = temp->NEXT;
        }
    }

    void print()
    {
        node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << endl;
            temp = temp->NEXT;
        }
    }

    void del()
    {

        while (head != NULL)
        {
            node *temp = head;
            head = head->NEXT;
            delete temp;
        }
    }
    void reverseList()
    {
        node *prev = NULL;
        node *curr = head;
        node *next = NULL;

        while (curr != NULL)
        {
            next = curr->NEXT; // save next node
            curr->NEXT = prev; // reverse link
            prev = curr;       // move prev forward
            curr = next;       // move curr forward
        }

        head = prev; // new head
    }
};

int main()
{
    linkedlist list;

    list.add_node(10); // first node
    list.add_node(20); // adds at beginning
    list.add_node(30); // adds at beginning

    cout << "Linked list elements: ";
    list.print();
    list.addinmid(5, 2);
    cout << "After adding in mid" << endl;
    list.print();
    cout << "After adding in tail" << endl;
    list.addattail(45);
    list.print();
    // list.del();
    cout << "after removing" << endl;
    list.rematmid(2);
    list.print();

    return 0;
}
