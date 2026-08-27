#include <iostream>
using namespace std;

class AvlNode
{
public:
    int Element;
    AvlNode* Left;
    AvlNode* Right;
    int Height;

    AvlNode(int value)
    {
        Element = value;
        Left = Right = nullptr;
        Height = 0;
    }
};

class AVLTree
{
private:
    AvlNode* root;

    // Utility functions
    int Max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    int Height(AvlNode* P)
    {
        return (P == nullptr) ? -1 : P->Height;
    }

    // Rotations
    AvlNode* singleright(AvlNode* K2)
    {
        AvlNode* K1 = K2->Left;
        K2->Left = K1->Right;
        K1->Right = K2;

        K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
        K1->Height = Max(Height(K1->Left), K2->Height) + 1;

        return K1;
    }

    AvlNode* singleleft(AvlNode* K2)
    {
        AvlNode* K1 = K2->Right;
        K2->Right = K1->Left;
        K1->Left = K2;

        K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;
        K1->Height = Max(Height(K1->Right), K2->Height) + 1;

        return K1;
    }

    AvlNode* RL(AvlNode* K3)
    {
        K3->Left = singleleft(K3->Left);
        return singleright(K3);
    }

    AvlNode* LR(AvlNode* K3)
    {
        K3->Right = singleright(K3->Right);
        return singleleft(K3);
    }

    // Insert recursively
    AvlNode* Insert(int X, AvlNode* T)
    {
        if (T == nullptr)
        {
            T = new AvlNode(X);
        }
        else if (X < T->Element)
        {
            T->Left = Insert(X, T->Left);
            if (Height(T->Left) - Height(T->Right) == 2)
            {
                if (X < T->Left->Element)
                    T = singleright(T);
                else
                    T = RL(T);
            }
        }
        else if (X > T->Element)
        {
            T->Right = Insert(X, T->Right);
            if (Height(T->Right) - Height(T->Left) == 2)
            {
                if (X > T->Right->Element)
                    T = singleleft(T);
                else
                    T = LR(T);
            }
        }

        T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
        return T;
    }

    // Find minimum node
    AvlNode* FindMin(AvlNode* T)
    {
        if (T == nullptr)
            return nullptr;
        while (T->Left != nullptr)
            T = T->Left;
        return T;
    }

    // Delete recursively
    AvlNode* Delete(int X, AvlNode* T)
    {
        if (T == nullptr)
            return nullptr;

        if (X < T->Element)
            T->Left = Delete(X, T->Left);
        else if (X > T->Element)
            T->Right = Delete(X, T->Right);
        else
        {
            if (T->Left && T->Right)
            {
                AvlNode* temp = FindMin(T->Right);
                T->Element = temp->Element;
                T->Right = Delete(temp->Element, T->Right);
            }
            else
            {
                AvlNode* temp = T;
                T = (T->Left != nullptr) ? T->Left : T->Right;
                delete temp;
            }
        }

        if (T == nullptr)
            return T;

        T->Height = Max(Height(T->Left), Height(T->Right)) + 1;

        if (Height(T->Left) - Height(T->Right) == 2)
        {
            if (Height(T->Left->Left) >= Height(T->Left->Right))
                return singleright(T);
            else
                return RL(T);
        }
        else if (Height(T->Right) - Height(T->Left) == 2)
        {
            if (Height(T->Right->Right) >= Height(T->Right->Left))
                return singleleft(T);
            else
                return LR(T);
        }

        return T;
    }

    // Traversals
    void InOrder(AvlNode* T)
    {
        if (!T) return;
        InOrder(T->Left);
        cout << T->Element << " ";
        InOrder(T->Right);
    }

    void PreOrder(AvlNode* T)
    {
        if (!T) return;
        cout << T->Element << " ";
        PreOrder(T->Left);
        PreOrder(T->Right);
    }

    void PostOrder(AvlNode* T)
    {
        if (!T) return;
        PostOrder(T->Left);
        PostOrder(T->Right);
        cout << T->Element << " ";
    }

public:
    AVLTree()
    {
        root = nullptr;
    }

    void insert(int X)
    {
        root = Insert(X, root);
    }

    void deleteValue(int X)
    {
        root = Delete(X, root);
    }

    void inorder()
    {
        InOrder(root);
        cout << endl;
    }

    void preorder()
    {
        PreOrder(root);
        cout << endl;
    }

    void postorder()
    {
        PostOrder(root);
        cout << endl;
    }
};

int main()
{
    AVLTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "Inorder Traversal: ";
    tree.inorder();

    cout << "Preorder Traversal: ";
    tree.preorder();

    cout << "Postorder Traversal: ";
    tree.postorder();

    tree.deleteValue(40);

    cout << "After deleting 40, Inorder: ";
    tree.inorder();

    return 0;
}
