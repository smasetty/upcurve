#include <iostream>
#include <string>
#include "test_framework.h"
#include "graphs.h"
#include <vector>
#include <queue>

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

int TopologicalSort(void *data)
{
    int numVertices = 6;
    DFS dfs1(numVertices);
    dfs1.AddEdge(1, 2);
    dfs1.AddEdge(1, 3);
    dfs1.AddEdge(2, 3);
    dfs1.AddEdge(2, 4);
    dfs1.AddEdge(2, 5);
    dfs1.AddEdge(3, 4);
    dfs1.AddEdge(3, 5);
    dfs1.AddEdge(4, 6);
    dfs1.AddEdge(4, 5);
    dfs1.AddEdge(6, 5);

    dfs1.TopologicalSort();
    std::cout << std::endl;

    DFS dfs2(numVertices);
    dfs2.AddEdge(1, 2);
    dfs2.AddEdge(1, 3);
    dfs2.AddEdge(2, 3);
    dfs2.AddEdge(2, 4);
    dfs2.AddEdge(2, 5);
    dfs2.AddEdge(3, 4);
    dfs2.AddEdge(3, 5);
    dfs2.AddEdge(4, 6);
    dfs2.AddEdge(4, 5);
    dfs2.AddEdge(5, 6);

    dfs2.TopologicalSort();
    std::cout << std::endl;

    return TEST_SUCCESS;
}

#define BOARDSIZE 30

struct graphNode {
    int index;
    int distance;
public:
    graphNode(): index(0), distance(-1) {};
};

//Find out the least number of die throws to reach the end
int SnakesLaddersGame(void *data)
{
    std::vector<int> move(BOARDSIZE, -1);

    for (int i = 0; i < BOARDSIZE; i++)
        move[i] = -1;
    
    //Setup the Snakes and Ladders
    move[3]  = 22;
    move[5]  = 8;
    move[11] = 26;
    move[20] = 29;

    move[27] = 1;
    move[21] = 9;
    move[19] = 7;

    std::vector<bool> visited(BOARDSIZE, false);
    std::queue<graphNode> q;
    // Start from Zero always. Also assume no snakes and ladders at index 0,
    // if there was then the game is no fun.
    graphNode nodeFirst;
    nodeFirst.index = 0;
    nodeFirst.distance = 0;

    visited[nodeFirst.index] = true;
    q.push(nodeFirst);

    while (!q.empty()) {
        graphNode node = q.front();
        std::cout << "popped from the queue" << node.index << " " <<
            node.distance << std::endl;
        

        std::cout << node.index << " " << node.distance << std::endl;
        if(node.index == BOARDSIZE  - 1) {
            std::cout << "The shortest distance is " << node.distance << std::endl;
            break;
        }

        q.pop();

        for(int vertice = node.index + 1; vertice < (node.index + 1 + 6) &&
                vertice < BOARDSIZE; vertice++) {
            if (!visited[vertice]) {
                graphNode newNode;

                if (move[vertice] ==  -1)
                    newNode.index = vertice;
                else
                    newNode.index = move[vertice];

                std::cout << "This is the current distance " <<
                    node.distance << std::endl;

                newNode.distance = node.distance + 1;

                visited[vertice] = true;

                std::cout << "Pushing into the queue" << newNode.index << " "
                    << newNode.distance << std::endl;
                q.push(newNode);
            }
        }
    }

    return TEST_SUCCESS;
}

#define NR_ROWS     5
#define NR_COLS     5

static bool isSafe(int row, int col)
{
    if ((row >= 0 && row < NR_ROWS) && (col >= 0 && col < NR_COLS))
        return true;

    return false;
}

void DfsIslandHelper(int M[][NR_COLS], bool visited[][NR_COLS],
        int row, int col)
{
    static const int rIdx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int cIdx[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    visited[row][col] = true;

    for (int k = 0; k <  ARRAY_SIZE(rIdx); k++) {
        int nRow = row + rIdx[k];
        int nCol = col + cIdx[k];

        /*
         * Do a depth first search of all reachable 1's from this point on
         */
        if (M[nRow][nCol] && !visited[nRow][nCol] && isSafe(nRow, nCol))
            DfsIslandHelper(M, visited, nRow, nCol);
    }
}

int CountIslandsHelper(int M[][NR_COLS])
{
    int count = 0;
    bool visited[NR_ROWS][NR_COLS] = {{false}};

    for (int i = 0; i < NR_ROWS; i++) {
        for (int j = 0; j < NR_COLS; j++) {
            if (M[i][j] && !visited[i][j]) {
                DfsIslandHelper(M, visited, i, j);

                /*
                 * Count the number of distinct islands
                 */
                ++count;
            }
        }
    }

    return count;
}

int CountIslands(void* data)
{
    int M[NR_ROWS][NR_COLS] = {
        {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1},
    };

    std::cout << "The number of islands is: " << CountIslandsHelper(M) << std::endl;

    return TEST_SUCCESS;
}

const TestFamily* graphs_init()
{
    TestFamily *testFamily = new TestFamily("graphs", static_cast<int>(10));

    TEST_DEF(first_sample_test, simple_test);
    TEST_DEF(bfs_test, BFSTest);
    TEST_DEF(dfs_test, DFSTest);
    TEST_DEF(topological_Sort, TopologicalSort);
    TEST_DEF(snakes_and_ladders, SnakesLaddersGame);
    TEST_DEF(count_islands, CountIslands);

    return testFamily;
}
