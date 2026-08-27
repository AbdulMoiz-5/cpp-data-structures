#include<iostream>
using namespace std;


// this is basically a node in adjancy list the data here is the neighbour and 
//the next is use for the other neighbor
struct Node{
    int data; // neighbor
    Node* next;  
};

//this is graph which has vertices and the relation of vertices is represented by the adj_list
struct graph{
    int vertices;
    Node** adj_list;
};

// V here is number of vertices
graph* create_graph(int V){
    graph* graph1 = new graph; // a new graph
    graph1->vertices = V;
    graph1->adj_list = new Node*[V]; //adj list
    //nulling the adj_list
    for(int i = 0; i < V; i++){
        graph1->adj_list[i] = nullptr;
    }
    return graph1;
}


//for adding edges
void add_edge(graph* graph1, int src, int dest){
    Node* new_node = new Node;
    new_node->data = dest;
    new_node->next = graph1->adj_list[src];
    graph1->adj_list[src] = new_node;


    // in case the graph is undirected
    new_node = new Node;
    new_node->data = src;
    new_node->next = graph1->adj_list[dest];
    graph1->adj_list[dest] = new_node;
    return;
}

void printGraph(graph* graph1){
    for(int i = 0; i < graph1->vertices; i++){
        cout<<i<<" -> ";
        Node* temp = graph1->adj_list[i];
        while(temp != nullptr){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
}

void deleteGraph(graph* graph1){
    for(int i = 0; i < graph1->vertices; i++){
        Node* temp = graph1->adj_list[i];
        while(temp != nullptr){
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }

    delete[] graph1->adj_list;
    delete graph1;
}




int main(){
    graph* Graph = create_graph(3);
    add_edge(Graph, 0, 1);
    add_edge(Graph, 0, 2);
    printGraph(Graph);
    deleteGraph(Graph);
    return 0;
}