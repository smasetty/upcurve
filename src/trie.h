#ifndef TRIE_H
#define TRIE_H value

#include <iostream>
#include <iterator>
#include <map>

struct TrieNode {
    std::map<char, struct TrieNode*> arr;
    bool endOfWord;
};

class Trie {
public:
    Trie() {
        rootNode = new TrieNode();
        rootNode->endOfWord = false;
    };

    ~Trie() {
        std::cout << "Deleting the Trie tree \n";
        DeleteTree(rootNode);
    }

    void InsertWord(const std::string &word) {
        auto wordLen = word.length();

        if (wordLen == 0)
            return;

        // We should always start with the root node
        struct TrieNode *current = rootNode;

        for (int i = 0; i < wordLen; i++) {

            auto it = current->arr.find(word[i]);

            if (it == current->arr.end())
                current->arr[word[i]] = new TrieNode();

            current = current->arr[word[i]];

            if ((i + 1) == wordLen)
                current->endOfWord= true;
        }
    }

    bool SearchWord(const std::string& word) {
        auto wordLen = word.length();

        if (wordLen == 0)
            return false;

        struct TrieNode *current = rootNode;

        for (int i = 0; i < wordLen; i++) {
            auto it = current->arr.find(word[i]);

            if (it == current->arr.end())
                return false;

            current = current->arr[word[i]];

            if ((i + 1) == wordLen)
                return current->endOfWord;
        }
        return false;
    }

    bool DeleteWord(const std::string& word) {
        auto wordLen = word.length();

        if (wordLen == 0)
            return false;

        return DeleteWord(rootNode, word, 0);
    }

private:

    bool DeleteTree(struct TrieNode *node) {

        for (auto it = node->arr.begin(); it != node->arr.end(); it++)
            DeleteTree(it->second);

        if (node->arr.size() == 0) {
            delete node;
        }

        return true;
    }

    bool DeleteWord(struct TrieNode *node, const std::string& word, int index) {
        if ((index) == word.length()) {

            if (!node->endOfWord)
                return false;

            if (node->arr.size() == 0) {
                delete node;
                return true;
            }
            else
                return false;
        }

        struct TrieNode *nextNode = node->arr[word[index]];
        if (!nextNode)
            return false;

        bool toDelete = DeleteWord(nextNode, word, index + 1);

        if (toDelete) {
            node->arr.erase(word[index]);

            if (node->arr.size() == 0) {
                delete node;
                return true;
            }
        }

        return false;
    }

    struct TrieNode *rootNode;
};

#endif /* ifndef TRIE_H */
