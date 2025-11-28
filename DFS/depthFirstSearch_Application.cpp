#include <map>
#include <vector>
#include <set>
#include <cstdio>

using namespace std;

class DFSSolution
{
    public:
    set<char> visited;
    map<char, char> parent;
    vector<char> finishingOrder;
    int componentSize;

    // especially needed for DFS
    void init(const char& source) 
    {
        visited.clear();
        parent.clear();
        visited.insert(source);
        parent[source] = '\0'; // cannot have assignemnt statements outside of a function body in a class.
    }


    void depthFirstSearch(const char& u, map<char, vector<char>>& graph)
    {
        if (graph.find(u) != graph.end()) {
            for (const char& v : graph.at(u)) {
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] = u;
                    depthFirstSearch(v, graph);
                }
            }
        }
    }

    // With count of the vertices in one CC
    void depthFirstSearchWithComponentSizes(const char& u, map<char, vector<char>>& graph)
    {
        componentSize ++;

        if (graph.find(u) != graph.end()) {
            for (const char& v : graph.at(u)) {
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] = u;
                    depthFirstSearchWithComponentSizes(v, graph);
                }
            }
        }
    }


    void fullDepthFirstSearch(map<char, vector<char>>& graph) 
    {
        visited.clear();
        parent.clear();

        // collect all vertices
        set<char> allVertices = collectAllVertices(graph);

        // run FULL-DFS
        for (const auto& v : allVertices) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent[v] = '\0';
                depthFirstSearch(v, graph);
            }
        }
    }

    // FULL DFS return connected components
    set<map<char, char>> fullDepthFirstSearchReturnConnectedComponents(map<char, vector<char>>& graph) 
    {
        visited.clear();
        parent.clear();
        set<map<char, char>> connectedComponents;

        // collect all vertices
        set<char> allVertices = collectAllVertices(graph);

        // run FULL DFS
        for (const auto& v : allVertices) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent[v] = '\0';
                depthFirstSearch(v, graph);
                connectedComponents.insert(parent);
                parent.clear();
            }
        }
        return connectedComponents;
    }

    // FULL DFS count connected components
    int fullDepthFirstSearchCountConnectedComponents(map<char, vector<char>>& graph) 
    {
         visited.clear();
         parent.clear();
         int count = 0;

        set<char> allVertices = collectAllVertices(graph);

        for (const auto& v : allVertices) {
             if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent[v] = '\0';
                depthFirstSearch(v, graph);
                count ++;
                parent.clear();
             }
        }
        return count;
    }


    // FULL DFS count connected components with headcount in each connected component
    map<int, int> fullDepthFirstSearchCountConnectedComponentsWithSizes(map<char, vector<char>>& graph) 
    {
        visited.clear();
        parent.clear();
        map<int, int> componentSizes;
        int count = 0;

        set<char> allVertices = collectAllVertices(graph);

        for (const auto& v : allVertices) {
             if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent[v] = '\0';
                componentSize = 0;
                depthFirstSearchWithComponentSizes(v, graph);
                count ++;
                componentSizes.insert( { count, componentSize });
                parent.clear();
             }
        }
        return componentSizes;
    }


    // FULL DFS return finishing order
    vector<char> fullDepthFirstSearchReturnFinishingOrder(map<char, vector<char>>& graph)
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();

        set<char> allVertices = collectAllVertices(graph);
        
        for (const auto& v : allVertices) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent[v] = '\0';
                depthFirstSearch(v, graph);
                parent.clear();
            }
        }
        return finishingOrder;
    }

    private:
    set<char> collectAllVertices(map<char, vector<char>>& graph)
    {
        set<char> allVertices;
        for (const auto& pair : graph) {
            allVertices.insert(pair.first);
            for (const auto& neighbor : pair.second) {
                allVertices.insert(neighbor);
            }
        }
        return allVertices;
    }

    void printParentRelationships()
    {
        printf("Child -> Parent\n");
        for (const auto& pair : parent) {
            printf("%c -> %c\n", pair.first, pair.second);
        }
        printf("\n\n");
    }
};

int main()
{
    DFSSolution solution = DFSSolution();
    map<char, vector<char>> G = {
        // Component 1: A-B-C (triangle)
        {'A', {'B', 'C'}},
        {'B', {'A', 'C'}},
        {'C', {'A', 'B'}},
        
        // Component 2: D-E-F (triangle)
        {'D', {'E', 'F'}},
        {'E', {'D', 'F'}},
        {'F', {'D', 'E'}},
        
        // Component 3: G-H-I (linear chain)
        {'G', {'H'}},
        {'H', {'G', 'I'}},
        {'I', {'H'}}
    };
    
    solution.init('A');
    solution.depthFirstSearch('A', G);
    solution.printParentRelationships();

    solution.fullDepthFirstSearch(G);
    solution.printParentRelationships();

    set<map<char, char>> connectedComponents = solution.fullDepthFirstSearchReturnConnectedComponents(G);
    for (const auto& parent : connectedComponents) {
        printf("Child -> Parent\n");
        for (const auto& pair : parent) {
            printf("%c -> %c\n", pair.first, pair.second);
        }
        printf("\n\n");
    }
}