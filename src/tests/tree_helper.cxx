#include <iostream>
#include "tree.h"

/*
 * Some Helper routines for the tree problems
 */
// Function to create a simple binary tree
struct TreeNode* CreateBinaryTree1()
{
    struct TreeNode *root = new TreeNode(10);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(8);
    root->left->right = new TreeNode(4);

    return root;
}

// Function to create a simple binary tree
struct TreeNode* CreateBinaryTree2()
{
    struct TreeNode *root = new TreeNode(20);
    root->left = new TreeNode(8);
    root->right = new TreeNode(22);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(12);
    root->left->right->left = new TreeNode(10);
    root->left->right->right = new TreeNode(14);
    root->right->right = new TreeNode(25);

    return root;
}

// Function to create a simple binary tree
struct TreeNode* CreateBinarySearchTree()
{
    struct TreeNode *root = new TreeNode(15);
    root->left = new TreeNode(10);
    root->right = new TreeNode(20);
    root->left->left = new TreeNode(8);
    root->left->right = new TreeNode(12);
    root->right->left = new TreeNode(16);
    root->right->right = new TreeNode(25);

    return root;
}

int TreeSize(struct TreeNode *root)
{
    if (!root)
        return 0;

    int leftSize = TreeSize(root->left);
    int righSize = TreeSize(root->right);

    return leftSize + righSize + 1;
}

void InOrderPrint(struct TreeNode *root)
{
    if(!root)
        return ;

    InOrderPrint(root->left);
    std::cout << root->key << " ";
    InOrderPrint(root->right);
}

void DeleteTree(struct TreeNode *root)
{
    if(!root)
        return;

    DeleteTree(root->left);
    DeleteTree(root->right);

    delete root;
}

//Find the LCA of a Binary Tree
struct TreeNode* LcaBt(struct TreeNode* root, int key1, int key2)
{
    if(!root)
        return nullptr;

    if (root->key == key1 || root->key == key2)
        return root;

    struct TreeNode *left = LcaBt(root->left, key1, key2);
    struct TreeNode *right = LcaBt(root->right, key1, key2);

    if(left && right)
        return root;

    return left? left : right;
}

int LevelNode(struct TreeNode *root, int level, int& key)
{
    if (!root)
        return -1;

    if(root->key == key)
        return level;

    //Try left of the tree
    int left = LevelNode(root->left, level + 1, key);
    if (left == -1)
        return LevelNode(root->right, level + 1, key);

    return left;
}

#define MARKER -1
void SerializeBinaryTree(struct TreeNode* root, FILE* fp)
{
    if(!root) {
        fprintf(fp, "%d ", MARKER);
        return;
    }

    fprintf(fp, "%d ", root->key);

    SerializeBinaryTree(root->left, fp);
    SerializeBinaryTree(root->right, fp);
}

void DeSerializeBinaryTree(struct TreeNode* &root, FILE* fp)
{
    int val = -1;

    int ret = fscanf(fp, "%d ", &val);
    std::cout << ret << " " << val << " " << std::endl;

    if (val == EOF || val == MARKER)
        return;

    root = new TreeNode(val);
    DeSerializeBinaryTree(root->left, fp);
    DeSerializeBinaryTree(root->right, fp);
}
