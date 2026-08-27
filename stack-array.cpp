#include <iostream>
using namespace std;

class stack
{
private:
    int array[10];
    int num=0;
public:
    void push(int d)
    {
        array[num]=d;
        num++;
    }
    void top()
    {
        cout<<"last character is"<<array[num-1]<<endl;
    }
    void pop()
    {
        cout<<"last character is"<<array[num-1]<<endl;
        num--;
    }
    void print()
    {
        for(int i=0 ;i< num ; i++)
        {
            cout<<array[i]<<endl;
        }
    }

};


int main()
{
    stack st;
    st.push(12);
    st.push(23);
    st.print();
    st.pop();
    st.print();

}