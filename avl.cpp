// avl_tree.cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    explicit Node(const int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    static int getHeight(const Node* node) {
        if (node) return {node->height};
        return 0;
    }

    static int getBalance(const Node* node) {
        if (node){getHeight(node->left) - getHeight(node->right);}
        return 0;
    }

    static void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    static Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    static Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    static Node* balance(Node* node) {
        updateHeight(node);
        int balanceFactor = getBalance(node);
        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        } else if (balanceFactor < -1) {
            if (getBalance(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node* node, const int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;
        return balance(node);
    }

    static Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node* remove(Node* node, int key) {
        if (!node) return node;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }
        return balance(node);
    }

    void preorder(const Node* node) {
        if (node) {
            cout << node->key << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void inorder(const Node* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << " ";
            inorder(node->right);
        }
    }

    void postorder(const Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->key << " ";
        }
    }

    int getWidth(const Node* node, const int level) {
        if (!node) return 0;
        if (level == 1) return 1;
        return getWidth(node->left, level - 1) + getWidth(node->right, level - 1);
    }

    int getMaxWidth(const Node* node) {
        int maxWidth = 0;
        int h = getHeight(node);
        for (int i = 1; i <= h; ++i) {
            int width = getWidth(node, i);
            maxWidth = max(maxWidth, width);
        }
        return maxWidth;
    }

    static void levelOrder(Node* node) {
        if (!node) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            cout << curr->key << " ";
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
    }

    bool search(const Node* node, const int key) {
        if (!node) return false;
        if (key == node->key) return true;
        if(key < node->key){
            search(node->left, key);
        }else{
            search(node->right, key);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = remove(root, key); }
    bool search(int key) { return search(root, key); }
    int height() { return getHeight(root); }
    int width() { return getMaxWidth(root); }
    void printPreorder() { preorder(root); cout << endl; }
    void printInorder() { inorder(root); cout << endl; }
    void printPostorder() { postorder(root); cout << endl; }
    void printLevelOrder() { levelOrder(root); cout << endl; }
};

int main() {
}
