#ifndef TREE_HELPER_H
#define TREE_HELPER_H value

#include "tree.h"

/*
 * Some Helper routines for the tree problems
 */
// Function to create a simple binary tree
struct TreeNode* CreateBinaryTree1();

// Function to create a simple binary tree
struct TreeNodeX* CreateBinaryTreeX1();

// Function to create a simple binary tree
struct TreeNode* CreateBinaryTree2();

struct TreeNode* CreateBinarySearchTree();

//Calculate the number of nodes in a tree
int TreeSize(struct TreeNode *root);

//Traverse the tree Inorder
void InOrderPrint(struct TreeNode *root);

//Delete the whole tree
void DeleteTree(struct TreeNode *root);

//Find the LCA of a Binary Tree
struct TreeNode* LcaBt(struct TreeNode* root, int key1, int key2);

int LevelNode(struct TreeNode *root, int level, int& key);

void SerializeBinaryTree(struct TreeNode* root, FILE* fp);
void DeSerializeBinaryTree(struct TreeNode*& root, FILE* fp);

#endif
