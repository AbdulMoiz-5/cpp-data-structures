#include<iostream>
using namespace std;

class node
{
private:
    int data;
    node* next = NULL;
public:
    node(int d)
    {
        data = d;
    }
    friend class stacklist;
};

class stacklist
{
private:
    node* front = NULL;
    node* back = NULL;

public:
    // enqueue
    void enque(int d)
    {
        node* temp = new node(d);

        if (front == NULL)        // ✅ FIX
        {
            front = temp;
            back = temp;
        }
        else
        {
            back->next = temp;
            back = temp;
        }
    }

    // dequeue
    void deque()
    {
        if (front == NULL)
        {
            cout << "Queue is empty" << endl;
            return;
        }

        int data = front->data;
        node* temp = front;
        front = front->next;
        delete temp;

        if (front == NULL)        // ✅ important
            back = NULL;

        cout << "data which is removed is " << data << endl;
    }

    // 🔹 isEmpty
    bool isEmpty()
    {
        return (front == NULL);
    }

    // 🔹 front element
    int frontElement()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return front->data;
    }

    // 🔹 rear element
    int rearElement()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return back->data;
    }

    // 🔹 print queue
    void print()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        node* temp = front;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main()
{
    stacklist q;

    q.enque(10);
    q.enque(20);
    q.enque(30);

    q.print();

    cout << "Front: " << q.frontElement() << endl;
    cout << "Rear: " << q.rearElement() << endl;

    q.deque();
    q.print();
}
