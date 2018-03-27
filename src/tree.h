#ifndef TREE_H
#define TREE_H value

struct TreeNode {
    int key;
    struct TreeNode *left, *right;
public:
    TreeNode(int key): key(key) {left = nullptr; right = nullptr;};
    TreeNode() {key = 0; left = nullptr; right = nullptr;};
    ~TreeNode() {};
};

struct TreeNodeX {
    int key;
    struct TreeNodeX *left, *right, *parent;
public:
    /*
     * A few constructors
     */
    TreeNodeX(int key): key(key) {left = nullptr; right = nullptr;
        parent = nullptr;};

    TreeNodeX() {key = 0; left = nullptr; right = nullptr;
        parent = nullptr;};

    ~TreeNodeX() {};
};

class Tree {
public:
    virtual void InsertKey(int key) = 0;
    virtual void DeleteKey(int key) = 0;
    virtual bool SearchKey(int key) = 0;

    virtual ~Tree() {};
};

class BST: public Tree {
public:
    BST(): root{nullptr} {};

    void InsertKey(int key) override;
    void DeleteKey(int key) override;
    bool SearchKey(int key) override;
    void InOrder(void);
    int LCA(int key1, int key2);
    ~BST();

private:
    struct TreeNode* InsertKey(struct TreeNode *root, int key);
    bool SearchKey(struct TreeNode *root, int key);
    struct TreeNode* DeleteKey(struct TreeNode *root, int key);
    void InOrder(struct TreeNode *root);
    int LCA(struct TreeNode *root, int key1, int key2);
    struct TreeNode *root;
};
#endif
