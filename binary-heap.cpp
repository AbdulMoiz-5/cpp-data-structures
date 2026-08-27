#include<iostream>
using namespace std;



//to find min of two integers
int min(int& a, int& b){
    if(a < b){
        return a;
    }   
    else 
        return b;
}

class BinaryHeap {
	private:
		int* arr;	// dynamic
		int count = 1;		// current number of elements
        int capacity = 5; // initial capacity of heap to 5
	public:
        //default constructor
		BinaryHeap(){
            arr = new int[capacity];
        }	
        //parameterized constructor
        BinaryHeap(int _capacity){
            capacity = _capacity;
            arr = new int[capacity];
        }
        //resize array if it is full
        void resize(){
            capacity = capacity * 2;
            int* new_arr = new int[capacity];

            //copy old array to new array
            for(int i = 1; i < count; i++){
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;

        }
		void enqueue(int value){
            //if array is already full resize it
            if(count == capacity){
                resize();
            }      
            //then add element to the array in structure property
            arr[count] = value;
            count++;

            int index = count - 1; //for helping in the heap property

            //heap property matlab k heapifying the array now
            while(index > 1 && arr[index] < arr[index/2]){
                // if condition is true then swap
                int temp = arr[index];                
                arr[index] = arr[index / 2];
                arr[index/2] = temp;
                // changing the index to its parent   
                index = index / 2;
            }
        }
        //function to remove the root element the lowest 
        //and replace it with the last element and then heapfy everything
        int removeMin() {
            if(count == 1) {  // heap is empty
                cout << "Heap is empty!" << endl;
                return -1;    // or any error value
            }

            int minVal = arr[1];          // root value to return
            arr[1] = arr[count - 1];      // move last element to root
            count--;                       // decrease heap size

            int i = 1;                     // start heapifying down from root

            while(2 * i < count) {         // while node has at least a left child
                int left = 2 * i;
                int right = 2 * i + 1;
                int smallest = left;

                if(right < count) {
                    // pick the smaller child using min function
                    smallest = (arr[left] == min(arr[left], arr[right])) ? left : right;
                }

                if(arr[i] > arr[smallest]) {  // swap if heap property violated
                    int temp = arr[i];
                    arr[i] = arr[smallest];
                    arr[smallest] = temp;
                    i = smallest;             // move down to child
                } else {
                    break;                    // heap property satisfied
                }
            }

            return minVal;  // return removed root
        }

        //function to display the nodes of binary heap
		void display(){
            // if heap is empty then
            if(count == 1){
                cout<<"Heap is empty"<<endl;
                return;
            }
            //if not then print all the elements
            for(int i = 1; i < count; ++i){
                cout<<arr[i]<<"  ";
            }
            cout<<endl;
        }

};

int main(){
    BinaryHeap minHeap;
    minHeap.enqueue(11);
    minHeap.display();
    minHeap.enqueue(21);
    minHeap.display();
    minHeap.enqueue(2);
    minHeap.display();
    minHeap.enqueue(67);
    minHeap.display();
    minHeap.enqueue(3);
    minHeap.display();
    minHeap.enqueue(6);
    minHeap.display();

    minHeap.removeMin();
    minHeap.display();
    minHeap.removeMin();
    minHeap.display();
    minHeap.removeMin();
    minHeap.display();
    minHeap.removeMin();
    minHeap.display();
    minHeap.removeMin();
    minHeap.display();
    minHeap.removeMin();
    minHeap.display();
    minHeap.removeMin();
    minHeap.display();

    return 0;
}