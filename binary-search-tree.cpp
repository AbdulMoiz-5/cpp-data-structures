#include <iostream>
using namespace std;

class node
{
private:
    int data;
    node* leftchild;
    node* rightchild;
    friend class bst;

public:
    node(int d)
    {
        data = d;
        leftchild = NULL;
        rightchild = NULL;
    }
};

class bst
{
private:
    node* root;

    // insert (already correct)
    node* insert(int d, node* t)
    {
        if (t == NULL)
        {
            t = new node(d);
        }
        else if (d < t->data)
        {
            t->leftchild = insert(d, t->leftchild);
        }
        else if (d > t->data)
        {
            t->rightchild = insert(d, t->rightchild);
        }
        return t;
    }

    // inorder traversal (already correct)
    void inorder(node* t)
    {
        if (t == NULL)
            return;

        inorder(t->leftchild);
        cout << t->data << " ";
        inorder(t->rightchild);
    }

    // 🔹 preorder traversal
    void preorder(node* t)
    {
        if (t == NULL)
            return;

        cout << t->data << " ";
        preorder(t->leftchild);
        preorder(t->rightchild);
    }

    // 🔹 postorder traversal
    void postorder(node* t)
    {
        if (t == NULL)
            return;

        postorder(t->leftchild);
        postorder(t->rightchild);
        cout << t->data << " ";
    }

    // 🔹 find minimum (used in delete)
    node* findMin(node* t)
    {
        while (t->leftchild != NULL)
            t = t->leftchild;
        return t;
    }

    // 🔹 delete function
    node* deleteNode(int d, node* t)
    {
        if (t == NULL)
            return t; 

        if (d < t->data)
        {
            t->leftchild = deleteNode(d, t->leftchild);
        }
        else if (d > t->data)
        {
            t->rightchild = deleteNode(d, t->rightchild);
        }
        else
        {
            // node with one or no child
            if (t->leftchild == NULL)
            {
                node* temp = t->rightchild;
                delete t;
                return temp;
            }
            else if (t->rightchild == NULL)
            {
                node* temp = t->leftchild;
                delete t;
                return temp;
            }

            // node with two children
            node* temp = findMin(t->rightchild);
            t->data = temp->data;
            t->rightchild = deleteNode(temp->data, t->rightchild);
        }
        return t;
    }

public:
    bst()
    {
        root = NULL;
    }

    void insert(int d)
    {
        root = insert(d, root);
    }

    void inorder()
    {
        inorder(root);
        cout << endl;
    }

    // 🔹 public preorder
    void preorder()
    {
        preorder(root);
        cout << endl;
    }

    // 🔹 public postorder
    void postorder()
    {
        postorder(root);
        cout << endl;
    }

    // 🔹 public delete
    void deleteValue(int d)
    {
        root = deleteNode(d, root);
    }
};

int main()
{
    bst h;
    h.insert(12);
    h.insert(56);
    h.insert(1);
    h.insert(20);

    cout << "Inorder Traversal: ";
    h.inorder();

    cout << "Preorder Traversal: ";
    h.preorder();

    cout << "Postorder Traversal: ";
    h.postorder();

    h.deleteValue(12);

    cout << "Inorder after delete: ";
    h.inorder();

    return 0;
}
