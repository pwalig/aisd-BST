#pragma once
#include <iostream>
using namespace std;
class BST {

    struct node {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t) {
        if (t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(int x, node* t)
    {
        if (t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if (x < t->data)
            t->left = insert(x, t->left);
        else if (x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    node* findMin(node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t) {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t) {
        node* temp;
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            t->left = remove(x, t->left);
        else if (x > t->data)
            t->right = remove(x, t->right);
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    void preorder(node* t)
    {
        if (t == NULL)
            return;
        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);
    }

    void postorder(node* t)
    {
        if (t == NULL)
            return;
        preorder(t->left);
        preorder(t->right);
        cout << t->data << " ";
    }

    node* find(node* t, int x) {
        if (t == NULL)
            return NULL;
        else if (x < t->data)
            return find(t->left, x);
        else if (x > t->data)
            return find(t->right, x);
        else
            return t;
    }

    int height(node* t, int i) {
        i++;
        int l = 0, r = 0;
        if (t->left != NULL)
            l = height(t->left, i);
        if (t->right != NULL)
            r = height(t->right, i);
        if (r > l)
            return r;
        if (l != 0)
            return l;
        return i;

    }

public:
    enum Disp_Mode {Preorder, Inorder, Postorder};

    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display(Disp_Mode d = Inorder) {
        switch (d)
        {
        case BST::Preorder:
            preorder(root);
            break;
        case BST::Inorder:
            inorder(root);
            break;
        case BST::Postorder:
            postorder(root);
            break;
        default:
            break;
        }
        cout << endl;
    }

    void search(int x) {
        root = find(root, x);
    }

    int get_height() {
        return height(root, 0);
    }
};

