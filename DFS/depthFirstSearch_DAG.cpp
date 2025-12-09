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
    vector<char> finishingOrder; // for Topological Order
    set<char> ancestorStack; // for cycle detection

    // especially needed for DFS
    void init(char source) 
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();
        visited.insert(source);
        parent[source] = '\0'; // cannot have assignemnt statements outside of a function body in a class.
    }

    // basic DFS
    void depthFirstSearch(char u, map<char, vector<char>>& graph)
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
        finishingOrder.push_back(u);
    }


    // DFS detect cycle
    bool depthFirstSearchDetectCycle(char u, map<char, vector<char>>& graph)
    {
        ancestorStack.insert(u);

        if (graph.find(u) != graph.end()) {
            for (const char& v : graph.at(u)) {
                // v is in the ancestor path
                if (ancestorStack.find(v) != ancestorStack.end()) {
                    return true;
                }
                
                // normal DFS logic
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] = u;

                    // recurse on v
                    if (depthFirstSearchDetectCycle(v, graph)) {
                        return true;
                    }
                }
            }
        }
        ancestorStack.erase(u);
        finishingOrder.push_back(u);
        return false;
    }

    // for undirected edges: bypass parent, don't double check one edge
    bool depthFirstSearchDetectCycleUndirectedEdge(char u, map<char, vector<char>>& graph) 
    {
      ancestorStack.insert(u);
      
      if (graph.find(u) != graph.end()) {
         for (const auto& v : graph[u]) {
            if (v == parent[u]) continue; // bypass
            if (ancestorStack.find(v) != ancestorStack.end()) {
               return true;
            }
            if (visited.find(v) == visited.end()) {
               visited.insert(v);
               parent[v] = u;
               if (depthFirstSearchDetectCycleUndirectedEdge(v)) return true;
            }
         }
      }
      ancestorStack.erase(u);
      finishingOrder.push_back(u);
      return false;
   }


    // FULL DFS: isDAG
    bool fullDepthFirstSearchGraphIsDAG(map<char, vector<char>>& graph) 
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();
        ancestorStack.clear();

        set<char> allVertices = collectAllVertices(graph);

        // FULL depthFirstSearchDetectCycle 
        for (const auto& v : allVertices) {
            if (visited.find(v) == visited) {
                visited.insert(v);
                parent = '\0';
                if (depthFirstSearchDetectCycle(v, graph)) {
                    return false;
                } 
            }
        }
        return true;
    }


    // FULL DFS: has cycle
    bool fullDepthFirstSearchHasCycle(map<char, vector<char>>& graph) 
    {
        // return !fullDepthFirstSearchIsDAG(graph)

        visited.clear();
        parent.clear();
        finishingOrder.clear();
        ancestorStack.clear();

        set<char> allVertices = collectAllVertices(graph);

        for (const auto& v : allVertices) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent[v] = '\0';
                if (depthFirstSearchDetectCycle(v, graph)) {
                    return true;
                }
            }
        }
        return false;
    }


    void printParentRelationships()
    {
        printf("Child -> Parent\n");
        for (const auto& pair : parent) {
            printf("%c -> %c\n", pair.first, pair.second);
        }
        printf("\n\n");
    }

    // FULL basic DFS
    void fullDepthFirstSearch(map<char, vector<char>>& graph) 
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();

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
};

int main()
{
    DFSSolution solution = DFSSolution();
    
}