#include<iostream>
using namespace std;

class node
{
private:
    int data;
    node* next;
    node* prev;
public:
    node(int d)
    {
        data = d;
        next = NULL;
        prev = NULL;
    }
    friend class linkedlist;
};

class linkedlist
{
private:
    node* head = NULL;
    node* tail = NULL;

public:
    void addathead(int d)
    {
        node* temp = new node(d);

        if (head == NULL)
        {
            head = tail = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }

    void addattail(int data)
    {
        node* temp = new node(data);

        if (tail == NULL)          // ✅ FIX: empty list
        {
            head = tail = temp;
        }
        else
        {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }

    void addatmid(int d, int location)
    {
        if (location <= 1)         // ✅ FIX
        {
            addathead(d);
            return;
        }

        node* current = head;
        int count = 1;

        while (current->next != NULL && count < location - 1)
        {
            current = current->next;
            count++;
        }

        if (current->next == NULL) // ✅ FIX
        {
            addattail(d);
            return;
        }

        node* temp = new node(d);
        temp->next = current->next;
        temp->prev = current;
        current->next->prev = temp;
        current->next = temp;
    }

    void remathead()
    {
        if (head == NULL) return;  // ✅ FIX

        node* temp = head;

        if (head == tail)          // ✅ FIX
        {
            head = tail = NULL;
        }
        else
        {
            head = head->next;
            head->prev = NULL;
        }
        delete temp;
    }

    void remattail()
    {
        if (tail == NULL) return;  // ✅ FIX

        node* temp = tail;

        if (head == tail)          // ✅ FIX
        {
            head = tail = NULL;
        }
        else
        {
            tail = tail->prev;
            tail->next = NULL;     // ✅ FIX
        }
        delete temp;
    }

    void rematmid(int location)
    {
        if (location <= 1)         // ✅ FIX
        {
            remathead();
            return;
        }

        node* current = head;
        int count = 1;

        while (current != NULL && count < location)
        {
            current = current->next;
            count++;
        }

        if (current == NULL) return;   // ✅ FIX

        if (current == tail)           // ✅ FIX
        {
            remattail();
            return;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }

    void print()
    {
        node* temp = head;
        while (temp != NULL)
        {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};

int main()
{
    linkedlist list;
    list.addathead(5);
    list.addathead(4);
    list.addattail(1);
    list.addatmid(10, 2);

    list.print();

    cout << "hello world" << endl;

    list.remathead();
    list.rematmid(2);
    list.remattail();

    list.print();
}
