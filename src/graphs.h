#ifndef BFS_H
#define BFS_H value

#include <iostream>
#include <queue>
#include <list>
#include <stack>

class Graph {
    Graph& operator=(const Graph&);
    Graph(const Graph&);
    
protected:
    int numVertices;
    std::list<int> *adj;

public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        //TODO: fix the off by one; clients should start from 0 index
        adj = new std::list<int>[numVertices + 1];
    }

    virtual ~Graph() {
        delete[] adj;
    }

    void AddEdge(int vertex, int edge) {
        adj[vertex].push_back(edge);
    }

    virtual void Traverse(int vertex) = 0;
    virtual void TraverseRecurse(int vertex) = 0;
};

class BFS: public Graph {
public:
    BFS(int numVertices): Graph(numVertices) {};

    void Traverse(int vertex) {
        std::queue<int> q;
        std::map<int, bool> visited;

        visited[vertex] = true;

        q.push(vertex);

        while(!(q.empty())) {
            int current = q.front();
            std::cout << current << " " << std::endl;
            q.pop();

            for (auto it = adj[current].begin(); (adj[current].size() > 0) && it != adj[current].end(); it++) {
                if (visited.find(*it) == visited.end()) {
                    visited[*it] = true;
                    q.push(*it);
                }
            }
        }
    }

    //TODO: Implement this later
    void TraverseRecurse(int vertex) {}
};

class DFS: public Graph {
public:
    DFS(int numVertices): Graph(numVertices) {};

    //TODO: Implement this later
    void Traverse(int vertex) {}

    void DFSUtil(int vertex, std::map<int, bool> &visited) 
    {
        visited[vertex] = true;
        std::cout << vertex << " ";

        for (auto it = adj[vertex].begin(); it != adj[vertex].end(); it++) {
            if (visited.find(*it) == visited.end()) {
                visited[*it] = true;
                DFSUtil(*it, visited);
            }
        }
    }

    void TraverseRecurse(int vertex) {
        std::map<int, bool> visited;

        DFSUtil(vertex, visited);
    }

    void TopologicalSortUtil(int current, std::map<int, bool>& visited,
            std::stack<int>& nodeList ) {

        for (auto it = adj[current].begin(); it != adj[current].end(); it++) {
            if (!visited[*it]) {
                visited[*it] = true;
                TopologicalSortUtil(*it, visited, nodeList);
            }
        }

        nodeList.push(current);
    }

    /*
     *TopologicalSort: Print the nodes in a directed graph in 
     *topologically sorted order, i.e. if there is an edge from a->b, 
     *then a should always be before b in any given topologically
     *sorted list for the graph.
     */
    void TopologicalSort() {
        std::map<int, bool> visited;
        int current = 0;
        std::stack<int> nodeList;

        for(current = 1; current <= numVertices; current++) {
            if (adj[current].size() == 0)
                continue;

            if (visited[current])
                continue;

            visited[current] = true;
            TopologicalSortUtil(current, visited, nodeList);
        }

        while(!nodeList.empty()) {
            std::cout << nodeList.top() << " ";
            nodeList.pop();
        }
    }
};

#endif /* ifndef BFS_H */
