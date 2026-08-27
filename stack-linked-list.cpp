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
    int gethead()
    {
        return head->data;
    }

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
    void remathead()
    {
        if (head != NULL)
        {
            node *tmp = head;
            head = head->NEXT;
            delete tmp;
        }
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
    void del()
    {

        while (head != NULL)
        {
            node *temp = head;
            head = head->NEXT;
            delete temp;
        }
    }
};

class stacklist
{
private:
    linkedlist stack;
    int num = 0;

public:
    void push(int d)
    {
        stack.add_node(d);
        num++;
    }
    void pop()
    {
        cout << "poped value is "<<stack.gethead() << endl;
        stack.remathead();
        num--;
    }
    void top()
    {
        cout << stack.gethead() << endl;
    }
    bool isempty()
    {
        return (num == 0);
    }
    void print()
    {
        if (isempty())
        {
            cout << "Stack is empty" << endl;
            return;
        }

        stack.print(); // prints from top to bottom
    }
};

int main()
{
    stacklist list;
    list.push(12);
    list.push(23);
    list.print();
    cout<<"hello world"<<endl;
    list.pop();
    list.print();
}