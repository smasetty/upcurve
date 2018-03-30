#ifndef BACKTRACE_H
#define BACKTRACE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <map>

class Backtrack {
public:
    explicit Backtrack(int n): n{n} {};

    virtual bool IsASol(std::vector<int>& a, int k) = 0;
    virtual void ProcessSol(std::vector<int>& a, int k) = 0;
    virtual void FindCandidates(std::vector<int>& a, int k,
            std::vector<int>& candidates) = 0;

    void backtrack(std::vector<int>& a, int k) {
        std::vector<int> candidates;

        if (IsASol(a, k)) {
            ProcessSol(a, k);
        }
        else {
            k = k + 1;
            FindCandidates(a, k, candidates);
            for (auto it = candidates.begin(); it != candidates.end(); it++) {
                a.push_back(*it);
                backtrack(a, k);
                a.pop_back();
            }
        }
    };

protected:
    int n;
};

class BacktrackChar {
public:
    explicit BacktrackChar() {};

    virtual bool IsASol(std::vector<char>& a, int k) = 0;
    virtual void ProcessSol(std::vector<char>& a, int k) = 0;
    virtual void FindCandidates(std::vector<char>& a, int k,
            std::vector<char>& candidates) = 0;

    void backtrack(std::vector<char>& a, int k) {
        std::vector<char> candidates;

        if (IsASol(a, k)) {
            ProcessSol(a, k);
        }
        else {
            k = k + 1;
            FindCandidates(a, k, candidates);
            for (auto it = candidates.begin(); it != candidates.end(); it++) {
                a.push_back(*it);
                backtrack(a, k);
                a.pop_back();
            }
        }
    };
};

class Subset: public  Backtrack {

public:
    Subset(int n): Backtrack{n} {this->n = n;};

    bool IsASol(std::vector<int>& a, int k) override {
        return (k == this->n);
    }

    void ProcessSol(std::vector<int>& a, int k) override {
        int i = 0;
        for (auto it = a.begin(); it != a.end(); it++, i++) {
            if (*it)
                std::cout << i << " ";
        }

        std::cout << std::endl;
    }

    void FindCandidates(std::vector<int>& a, int k,
            std::vector<int>& candidates) override {

        candidates.push_back(1);
        candidates.push_back(0);
    }

    void GenerateSubsets() {
        int k = 0;
        backtrack(a, k);
    }

private:
    std::vector<int> a;
    int n;

};

class StringPerm: public BacktrackChar {
public:
    StringPerm(std::string& input) {
        mInput.assign(input);
        mInputSize = mInput.size();
    }

    bool IsASol(std::vector<char>& a, int k) override {
        return (k==mInput.size());
    }

    void ProcessSol(std::vector<char>& a, int k) override {
        for (auto it = a.begin(); it != a.end(); it++)
            std::cout << *it << " ";
        std::cout<< std::endl;
    }

    //This approach is going to fail miserably if the string
    //contains duplicate charaters
    void FindCandidates(std::vector<char>& a, int k,
            std::vector<char>& candidates) override {

        std::map<char, bool> inPerm;

        for (auto it = a.begin(); it!= a.end(); it++)
            inPerm[*it] = true;

        for (int i = 0; i < mInputSize; i++) {
            if (!inPerm[mInput[i]])
                candidates.push_back(mInput[i]);
        }
    }

    void GeneratePermutations() {
        int k = 0;
        backtrack(a, k);
    }

private:
    std::vector<char> a;
    std::string mInput;
    int mInputSize;
};
#endif
