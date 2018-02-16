#ifndef BACKTRACE_H
#define BACKTRACE_H value

#include <vector>

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
                //std::cout << "Loop" << candidates.size() << std::endl;
                a.push_back(*it);
                backtrack(a, k);
                a.pop_back();
            }
        }
    };

protected:
    int n;
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

#endif
