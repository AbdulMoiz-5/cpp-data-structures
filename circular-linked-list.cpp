#include <iostream>
using namespace std;

class node
{
public:
    int data;
    node *next;
    node(int d)
    {
        data = d;
        next = NULL;
    }
};

class circularList
{
private:
    node *head = NULL;
    node *tail = NULL;

public:
    // Add at head
    void addAtHead(int data)
    {
        node *temp = new node(data);
        if (head == NULL)
        {
            head = tail = temp;
            tail->next = head;
        }
        else
        {
            temp->next = head;
            head = temp;
            tail->next = head;
        }
    }

    // Add at tail
    void addAtTail(int data)
    {
        node *temp = new node(data);
        if (tail == NULL) // empty list
        {
            head = tail = temp;
            tail->next = head;
        }
        else
        {
            tail->next = temp;
            tail = temp;
            tail->next = head;
        }
    }

    // Add at middle (position starts at 1)
    void addAtMid(int data, int position)
    {
        if (position <= 1 || head == NULL)
        {
            addAtHead(data);
            return;
        }

        node *current = head;
        int count = 1;

        // move to (position-1) or last node
        while (current->next != head && count < position - 1)
        {
            current = current->next;
            count++;
        }

        if (current->next == head) // insert at tail
        {
            addAtTail(data);
            return;
        }

        node *temp = new node(data);
        temp->next = current->next;
        current->next = temp;
    }

    // Remove at head
    void removeAtHead()
    {
        if (head == NULL)
            return; // empty

        if (head == tail) // only one node
        {
            delete head;
            head = tail = NULL;
        }
        else
        {
            node *temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
        }
    }

    // Remove at tail
    void removeAtTail()
    {
        if (tail == NULL)
            return; // empty

        if (head == tail) // one node
        {
            delete head;
            head = tail = NULL;
            return;
        }

        node *current = head;
        while (current->next != tail)
        {
            current = current->next;
        }

        delete tail;
        tail = current;
        tail->next = head;
    }

    // Remove at middle (position starts at 1)
    void removeAtMid(int position)
    {
        if (head == NULL)
            return; // empty
        if (position <= 1)
        {
            removeAtHead();
            return;
        }

        node *current = head;
        int count = 1;

        while (current->next != head && count < position - 1)
        {
            current = current->next;
            count++;
        }

        node *toDelete = current->next;

        if (toDelete == head)
            return; // position out of bounds
        if (toDelete == tail)
        {
            removeAtTail();
            return;
        }

        current->next = toDelete->next;
        delete toDelete;
    }

    // Traverse and print
    void traverse()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }

        node *temp = head;
        do
        {
            cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }
    void reverse()
    {
        if (head == NULL || head->next == head)
            return; // empty or single node

        node *prev = tail; // Important: tail initially points to old head
        node *curr = head;
        node *next;

        do
        {
            next = curr->next;
            curr->next = prev; // reverse pointer
            prev = curr;
            curr = next;
        } while (curr != head);

        // Update head and tail
        tail = head;
        head = prev;
    }
};

int main()
{
    circularList list;

    // Adding
    list.addAtHead(2);
    list.addAtHead(5);
    list.addAtTail(10);
    list.addAtMid(7, 2); // position 2
    list.traverse();     // 5 7 2 10

    // Removing
    list.removeAtHead();
    list.traverse(); // 7 2 10

    list.removeAtMid(2);
    list.traverse(); // 7 10

    list.removeAtTail();
    list.traverse(); // 7

    return 0;
}
