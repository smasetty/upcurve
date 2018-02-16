#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "test_framework.h"
#include "graphs.h"
#include "tree.h"
#include "tree_helper.h"
#include "backtrace.h"

int BSTTest(void *data) {
    //TODO create an Interface object and use dynamic casting if needed.
    BST bstTester;
    bstTester.InsertKey(50);
    bstTester.InsertKey(30);
    bstTester.InsertKey(20);
    bstTester.InsertKey(40);
    bstTester.InsertKey(70);
    bstTester.InsertKey(60);
    bstTester.InsertKey(80);

    bstTester.InOrder();

    bstTester.DeleteKey(80);
    bstTester.InOrder();
    bstTester.DeleteKey(20);
    bstTester.InOrder();
    bstTester.DeleteKey(30);
    bstTester.InOrder();

    return TEST_SUCCESS;
}

int BSTTestLCA(void *data) {

    BST bstTester;
    bstTester.InsertKey(50);
    bstTester.InsertKey(30);
    bstTester.InsertKey(20);
    bstTester.InsertKey(40);
    bstTester.InsertKey(70);
    bstTester.InsertKey(60);
    bstTester.InsertKey(80);

    std::cout << "The LCA is " << bstTester.LCA(20, 40) << std::endl;
    return TEST_SUCCESS;
}

static void InOrderSave(struct TreeNode *root, std::vector<int>& keys)
{
    if(!root)
        return;

    InOrderSave(root->left, keys);
    keys.push_back(root->key);
    InOrderSave(root->right, keys);
}

static void InOrderRestore(struct TreeNode *root, std::vector<int>& keys,
        int& index)
{
    if(!root)
        return ;

    InOrderRestore(root->left, keys, index);
    root->key = keys[index++];
    InOrderRestore(root->right, keys, index);
}

//A program to convert a binary tree to a binary search tree while retaining
//the tree structure.
int BTToBST(void *data)
{
    struct TreeNode *bt = CreateBinaryTree1();
    std::vector<int> keys;

    InOrderSave(bt, keys);

    std::cout << "The keys in original order" << std::endl;
    for (auto it = keys.begin(); it != keys.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::sort(keys.begin(), keys.end());

    std::cout << "The keys in sorted order" << std::endl;
    for (auto it = keys.begin(); it != keys.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    int index = 0;
    InOrderRestore(bt, keys, index);

    std::cout << "BST" << std::endl;
    InOrderPrint(bt);
    std::cout << std::endl;

    return TEST_SUCCESS;
}

void BoundaryTraversalLeft(struct TreeNode *root)
{
    if (!root)
        return;

    if (root->left) {
        std::cout << root->key << " ";
        BoundaryTraversalLeft(root->left);
    } 
    else if (root->right) {
        std::cout << root->key << " ";
        BoundaryTraversalLeft(root->right);
    }
    else
        return;// Do not print leaf nodes
}

void BoundaryTraversalBottom(struct TreeNode *root)
{
    if(!root)
        return;

    BoundaryTraversalBottom(root->left);
    if(!root->left && !root->right)
        std::cout << root->key << " ";
    BoundaryTraversalBottom(root->right);
}

void BoundaryTraversalRight(struct TreeNode *root)
{
    if (!root)
        return;

    if (root->right) {
        BoundaryTraversalRight(root->right);
        std::cout << root->key << " ";
    } 
    else if (root->left) {
        BoundaryTraversalRight(root->left);
        std::cout << root->key << " ";
    }
    else
        return;// Do not print leaf nodes
}

int BoundaryTraversal(void *data)
{
    struct TreeNode *root = CreateBinaryTree2();
    if(!root)
        return TEST_SKIPPED;

    std::cout << root->key << " ";

    BoundaryTraversalLeft(root->left);
    BoundaryTraversalBottom(root);
    BoundaryTraversalRight(root->right);

    std::cout << std::endl;
    DeleteTree(root);
    return TEST_SUCCESS;
}

int LCAOfBT(void* data)
{
    struct TreeNode *root = CreateBinaryTree2();
    if(!root)
        return TEST_SKIPPED;
   
    struct TreeNode *lca = LcaBt(root, 4, 25);
    if(lca)
        std::cout << lca->key << " ";
    std::cout << std::endl;

    return TEST_SUCCESS;
}

//function to find the distance between two nodes in a binary tree
int DistanceNodes(void *data)
{
    struct TreeNode *root = CreateBinaryTree2();
    if(!root)
        return TEST_SKIPPED;

    struct TreeNode *lca = LcaBt(root, 4, 25);

    if (!lca)
        return TEST_SKIPPED;

    int level = 0;
    int key = 4;

    int dist1 = LevelNode(lca, level, key);

    level = 0;
    key = 25;
    int dist2 = LevelNode(lca, level, key);

    std::cout << "The distance between the nodes is " << dist1 + dist2 << std::endl;
    
    return TEST_SUCCESS;
}

const TestFamily* trees_init()
{
    TestFamily *testFamily = new TestFamily("trees", static_cast<int>(10));

    TEST_DEF(binary_search_tree, BSTTest);
    TEST_DEF(bst_lca, BSTTestLCA);
    TEST_DEF(bt_to_bst, BTToBST);
    TEST_DEF(boundary_traversal, BoundaryTraversal);
    TEST_DEF(lca_bt, LCAOfBT);
    TEST_DEF(distance_nodes, DistanceNodes);

    return testFamily;
}
