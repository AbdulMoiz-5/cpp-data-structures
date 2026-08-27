#include <iostream>
using namespace std;

class queue
{
private:
    int arr[10];
    int num = 0;
    int front = 0;
    int back = 0;
    int size = 10;
    int total_element = 0;

public:
    void enque(int d)
    {
        arr[num] = d;
        num++;
    }

    void enque1(int d)
    {
        if (total_element < size) // it tell the user to only enter 10 element so(front != back) back front ke peche na ajae
        {
            arr[back] = d;
            back = (++back) % size; // it would make the array circular it works from 0--9
            total_element++;
        }
    }
    void deque()
    {
        int first = arr[0];
        for (int i = 0; i < (num - 1); i++)
        {
            arr[i] = arr[i + 1];
        }
        num--;
        cout << "Number which you delete is" << first << endl;
    }
    void deque1()
    {
        if (total_element > 0) // hm ne ye use kea take front back ke peche na ajae
        {
            int temp = arr[front];
            ++front;
            cout << "value which is removed is " << temp << endl;
            total_element--;
        }
    }
    // 🔹 isEmpty
    bool isEmpty()
    {
        return (total_element == 0);
    }
    // 🔹 Front element
    int frontElement()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        return arr[front];
    }

    // 🔹 Rear element
    int rearElement()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return -1;
        }
        int index = (back - 1 + size) % size;
        return arr[index];
    }

    // 🔹 Print queue
    void print()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        int i = front;
        for (int count = 0; count < total_element; count++)
        {
            cout << arr[i] << " ";
            i = (i + 1) % size;
        }
        cout << endl;
    }
};

int main()
{
    queue q;
    q.enque1(12);
    q.enque1(2);
    q.enque1(1);

    q.print();

    cout << "Front: " << q.frontElement() << endl;
    cout << "Rear: " << q.rearElement() << endl;

    q.deque1();
    q.print();
}