#include <iostream>
#include <string>
#include "test_framework.h"
#include "graphs.h"

int simple_test(void *data)
{
    std::cout << "This is very simple test case." << std::endl;
    return TEST_SUCCESS;
}

int BFSTest(void *data)
{
    int numVertices = 6;
    BFS bfs(numVertices);
    bfs.AddEdge(1, 2);
    bfs.AddEdge(1, 3);
    bfs.AddEdge(2, 1);
    bfs.AddEdge(2, 4);
    bfs.AddEdge(2, 5);
    bfs.AddEdge(3, 1);
    bfs.AddEdge(3, 5);
    bfs.AddEdge(4, 2);
    bfs.AddEdge(4, 6);
    bfs.AddEdge(4, 5);
    bfs.AddEdge(5, 2);
    bfs.AddEdge(5, 4);
    bfs.AddEdge(5, 6);
    bfs.AddEdge(6, 5);

    bfs.Traverse(1);
    std::cout << std::endl;

    return TEST_SUCCESS;
}

int DFSTest(void *data)
{
    int numVertices = 6;
    DFS dfs(numVertices);
    dfs.AddEdge(1, 2);
    dfs.AddEdge(1, 3);
    dfs.AddEdge(2, 1);
    dfs.AddEdge(2, 4);
    dfs.AddEdge(2, 5);
    dfs.AddEdge(3, 1);
    dfs.AddEdge(3, 5);
    dfs.AddEdge(4, 2);
    dfs.AddEdge(4, 6);
    dfs.AddEdge(4, 5);
    dfs.AddEdge(5, 2);
    dfs.AddEdge(5, 4);
    dfs.AddEdge(5, 6);
    dfs.AddEdge(6, 5);

    dfs.TraverseRecurse(1);
    std::cout << std::endl;

    return TEST_SUCCESS;
}

const TestFamily* graphs_init()
{
    TestFamily *testFamily = new TestFamily("graphs", static_cast<int>(10));

    TEST_DEF(first_sample_test, simple_test);
    TEST_DEF(bfs_test, BFSTest);
    TEST_DEF(dfs_test, DFSTest);

    return testFamily;
}
