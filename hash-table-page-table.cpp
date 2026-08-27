#include <iostream>
using namespace std;

class HashedPageTable {
private:
    struct Entry {
        int logicalPage;
        int frameNumber;
        bool valid;
    };

    Entry table[37];            // created a hash table array in it 
    char physicalMemory[256];   // created 256 memory locations      

    unsigned int creatingHash(int pageNumber) 
    {     
        return pageNumber % 37; // we do hashing to create the index
    }

public:
    HashedPageTable() 
    {
        for (int i = 0; i < 37; i++) 
        {
            table[i].valid = false;
        }
        
        for (int i = 0; i < 256; i++) 
        {
            physicalMemory[i] = 'A' + (i % 26);
        }
    }

    void insert(int logicalPage, int frameNumber) 
    {
        unsigned int index = creatingHash(logicalPage); 
        
        table[index] = {logicalPage, frameNumber, true}; // we have added data in table
        cout << "Inserted Page: " << logicalPage << "  Frame: " << frameNumber << "\n";
    }

    void gettingdata(int logicalAddress)
    {
        int p = logicalAddress / 8; // created a logical adress parts
        int d = logicalAddress % 8; 

        unsigned int index = creatingHash(p); //converting logical address to pphysical address

        if (table[index].valid == true && table[index].logicalPage == p) // check the place is valid or not 
        {
            int f = table[index].frameNumber;
            int physicalAddress = (f * 8) + d; 
    
            char data = physicalMemory[physicalAddress];
            
            cout << "Logical Address: " << logicalAddress << "\n";
            cout << "It's Physical Address is " << physicalAddress << " Retrieved Data: " << data << "\n\n";
        } 
        else 
        {
            cout << "Data not Available for logical address: " << logicalAddress << "\n\n";
        }
    }
};

int main() {
    HashedPageTable h1;
    h1.insert(2, 5);
    h1.insert(9, 12);
    h1.insert(14, 1);

    cout << "\nNow accessing memory from the hash table through logical address\n";

    h1.gettingdata(19);
    h1.gettingdata(77);
    
    return 0;
}