#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "test_framework.h"
#include "graphs.h"
#include "tree.h"
#include "tree_helper.h"
#include "ll_helper.h"

int BSTTest(void *data)
{
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

int BSTTestLCA(void *data)
{
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

/*
 * Generate a balanced BST from a sorted array using a recursive approach.
 * The idea is to create a node for the middle element of the array and then
 * recurse of left and right sides with the left part and the right part of
 * the array respectively.
 */
struct TreeNode* GenerateBlancedBST(std::vector<int>& arr, int start, int end)
{
    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;

    struct TreeNode* root = new TreeNode(arr[mid]);

    root->left = GenerateBlancedBST(arr, start, mid - 1);
    root->right = GenerateBlancedBST(arr, mid + 1, end);

    return root;
}

int SortedArrToBST(void *data)
{
    std::vector<int> arr;
    int start = 0;
    int end = 10;
    for (int i = start; i < end; i++)
        arr.push_back(i);

    struct TreeNode* root = GenerateBlancedBST(arr, start, end - 1);
    if(!root)
        return TEST_FAILURE;

    InOrderPrint(root);

    DeleteTree(root);

    return TEST_SUCCESS;
}

struct TreeNode* GenerateBalancedBST(struct Node** headref, int n)
{
    if (n <= 0)
        return nullptr;

    struct TreeNode* left = GenerateBalancedBST(headref, n/2);
    struct TreeNode* root = new TreeNode((*headref)->key);
    
    root->left = left;
    
    *headref = (*headref)->next;

    root->right = GenerateBalancedBST(headref, n - n/2 - 1);

    return root;
}


int SortedLLToBST(void *data)
{
    /* Genereate a linke list with even elements and in sorted order keys */
    struct Node* head = GenerateListEven();
    int n = LLLength(head);

    struct TreeNode* root = GenerateBalancedBST(&head, n);

    InOrderPrint(root);

    DeleteTree(root);

    return TEST_SUCCESS;
}

struct TreeNode* CreateBadBST()
{
    struct TreeNode *root = new TreeNode(6);
    root->left = new TreeNode(10);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(12);
    root->right->left = new TreeNode(7);

    return root;
}

static void FixBstHelper(struct TreeNode* root, struct TreeNode** first,
        struct TreeNode** middle, struct TreeNode** last,
        struct TreeNode** prev)
{
    if (!root)
        return;

    /* remember that this is an inorder traversal, recurse on the left tree */
    FixBstHelper(root->left, first, middle, last, prev);
    
    /*
     * compare the prev node and the current node, the current node is always
     * supposed to be greater than the previous node, if not mark it as an
     * exception. There are two cases
     * a) When the exception is for the adjacent nodes in the tree
     * b) When the exception is not the adjacent nodes in the tree
     */
    if(*prev && root->key < (*prev)->key) {
        if(!(*first)) {
            *first = *prev;
            *middle = root;
        }
        else
            *last = root;
    }

    /* Mark the current node as prev for parent recursions */
    *prev = root;

    /* recurse on the right tree */
    FixBstHelper(root->right, first, middle, last, prev);
}

/*
 * The InOrderSave and InOrderRestore methods can also be used to solve this
 * problem, but you know this is a cute way and efficient too.
 */
int FixBst(void* data)
{
    struct TreeNode* root = CreateBadBST();
    struct TreeNode *first, *middle, *last, *prev;
    first = middle = last = prev = nullptr;

    std::cout << "This is the tree before the fixing the bad pointers " << std::endl;
    InOrderPrint(root);
    std::cout<< std::endl;

    FixBstHelper(root, &first, &middle, &last, &prev);
    std::cout << "Here are the bad keys" << std::endl;
    if (first && last)
        std::cout << first->key << " " << last->key << std::endl;
    else if(first && middle)
        std::cout << first->key << " " << middle->key << std::endl;
    else
        std::cout << "The BST tree is just fine" << std::endl;

    DeleteTree(root);
    return TEST_SUCCESS;
}

struct TreeNode* PreorderToBSTHelper(std::vector<int>& arr, int& index, int key,
        int min, int max, int size)
{
    /* Base Case */
    if (index >= size)
        return nullptr;

    if (key > min && key < max) {
        struct TreeNode* root = new TreeNode(arr[index]);
        index += 1;

        if (index < size) {
           root->left = PreorderToBSTHelper(arr, index, arr[index], min, key,
                   size); 

           root->right = PreorderToBSTHelper(arr, index, arr[index], key, max,
                   size); 
        }

        return root;
    }

    return nullptr;
}

/*
 * In a post order traversal of a tree, the last Node is always the root.
 * So make it the root and use the BST principles for the childs and recur.
 */
struct TreeNode* PostOrderToBSTHelper(std::vector<int>& arr, int& index,
        int key, int min, int max, int size)
{
    /* Base case for recursion */
    if (index < 0)
        return nullptr;

    if (key > min && key < max) {
        struct TreeNode* root = new TreeNode(arr[index]);
        index -= 1;

        if (index >= 0) {
            root->left = PostOrderToBSTHelper(arr, index, arr[index], min, key, size);
            root->right = PostOrderToBSTHelper(arr, index, arr[index], key, max, size);
        }
        
        return root;
    }

    return nullptr;
}

int PreorderToBST(void *data)
{
    std::vector<int> arr;

    /* Create a preorder traversal for a BST */
    arr.push_back(1);
    arr.push_back(7);
    arr.push_back(5);
    arr.push_back(50);
    arr.push_back(40);
    arr.push_back(10);

    int size = arr.size();
    int min = INT_MIN;
    int max = INT_MAX;
    int index = size - 1;
    int key = arr[index];
 
    struct TreeNode* root = PostOrderToBSTHelper(arr, index, key, min, max, size);

    InOrderPrint(root);
    std::cout << std::endl;
    DeleteTree(root);
    return TEST_SUCCESS;
}

int PostOrderToBST(void *data)
{
    std::vector<int> arr;

    /* Create a preorder traversal for a BST */
    arr.push_back(10);
    arr.push_back(5);
    arr.push_back(1);
    arr.push_back(7);
    arr.push_back(40);
    arr.push_back(50);

    int size = arr.size();
    int min = INT_MIN;
    int max = INT_MAX;
    int key = arr[0];
    int index = 0;
 
    struct TreeNode* root = PreorderToBSTHelper(arr, index, key, min, max, size);
    InOrderPrint(root);
    std::cout << std::endl;
    DeleteTree(root);
    return TEST_SUCCESS;
    return TEST_SUCCESS;
}

int SerializeBT(void* data)
{
    struct TreeNode* root = CreateBinaryTree1();
    FILE *fp = fopen("./tree.txt", "abrw+");
    if (!fp) {
        std::cout << "could not open a file for writing - " <<
            strerror(errno) << std::endl;
        return TEST_SKIPPED;
    }
    
    SerializeBinaryTree(root, fp);
    
    InOrderPrint(root);
    std::cout << std::endl;

    struct TreeNode* tempRoot = nullptr;

    DeSerializeBinaryTree(tempRoot, fp);

    InOrderPrint(tempRoot);
    std::cout << std::endl;

    DeleteTree(root);
    DeleteTree(tempRoot);
    fclose(fp);
    return TEST_SUCCESS;
}

/*
 * Use a stack to implement inorder traversal without recursion
 */
void InOrderWoRecursionHelper(struct TreeNode* root)
{
    struct TreeNode* current = root;
    std::stack<struct TreeNode*> s;

    while (current != nullptr) {
        s.push(current);
        current = current->left;

        /*TODO: re-arrange the conditional to just use the while loop */
        if(current == nullptr && !s.empty()) {
            while(!s.empty()) {
                struct TreeNode* temp = s.top();
                s.pop();
                std::cout << temp->key << " ";

                if (temp->right) {
                    current = temp->right;
                    break;
                }
            }
        }
    }
}

int InOrderWoRecursion(void* data)
{
    struct TreeNode* root = CreateBinaryTree1();

    InOrderWoRecursionHelper(root);

    DeleteTree(root);

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
    TEST_DEF(sorted_arr_to_bst, SortedArrToBST);
    TEST_DEF(sorted_ll_to_bst, SortedLLToBST);
    TEST_DEF(fix_bst, FixBst);
    TEST_DEF(preorder_to_bst, PreorderToBST);
    TEST_DEF(postorder_to_bst, PostOrderToBST);
    TEST_DEF(serialize_bt, SerializeBT);
    TEST_DEF(inorder_wo_recursion, InOrderWoRecursion);

    return testFamily;
}
