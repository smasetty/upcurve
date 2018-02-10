#include <iostream>
#include <string>
#include "test_framework.h"
#include "tree_helper.h"

BST::~BST() {
    std::cout << "Now deleting the BST tree" << std::endl;
    DeleteTree(root);
}

void BST::InOrder(struct TreeNode *root)
{
    if (!root)
        return;

    InOrder(root->left);
    std::cout << root->key << " ";
    InOrder(root->right);
}

void BST::InOrder()
{
    InOrder(root);
    std::cout << std::endl;
}

int BST::LCA(struct TreeNode *root, int key1, int key2)
{
    if (!root)
        return -1;

    if (key1 < root->key && key2 < root->key)
        return LCA(root->left, key1, key2);
    else if (key1 > root->key && key2 > root->key)
        return LCA(root->right, key1, key2);

    return root->key;
}

int BST::LCA(int key1, int key2)
{
    return LCA(root, key1, key2);
}

struct TreeNode* BST::InsertKey(struct TreeNode *root, int key)
{
    if (root == nullptr)
        return new TreeNode(key);

    if (key < root->key)
        root->left = InsertKey(root->left, key);
    else if (key > root->key)
        root->right = InsertKey(root->right, key);

    return root;
}

bool BST::SearchKey(struct TreeNode *root, int key)
{
    if (root == nullptr)
        return false;

    if (root->key == key)
        return true;

    if (key < root->key)
        return SearchKey(root->left, key);
    if (key > root->key)
        return SearchKey(root->right, key);

    //not strictly needed, but need to shut off the compiler warning.
    return false;
}

static inline struct TreeNode* FindInorder(struct TreeNode *root) {
    struct TreeNode *current = root;

    while(current !=nullptr)
        current = current->left;

    return current;
}

struct TreeNode* BST::DeleteKey(struct TreeNode *root, int key)
{
    if (!root)
        return root;

    if (key < root->key)
        root->left = DeleteKey(root->left, key);
    else if (key > root->key)
        root->right = DeleteKey(root->right, key);
    else {
        if (root->left == nullptr) {
            struct TreeNode *temp = root->right;
            if (root)
                delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            struct TreeNode *temp = root->left;
            if (root)
                delete root;
            return temp;
        }

        struct TreeNode* inOrder = FindInorder(root->right);
        root->key = inOrder->key;

        root->right = DeleteKey(root->right, inOrder->key);
    }
    return root;
}

void BST::DeleteKey(int key) {
    DeleteKey(root, key);
}

bool BST::SearchKey(int key) {
    return SearchKey(root, key);
}

void BST::InsertKey(int key) {
    root = InsertKey(root, key);
}
