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
    set<char> ancestorStack;

    void init(char source)
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();
        visited.insert(source);
        parent[source] = '\0';
    }

    void depthFirstSearch(char u, map<char, vector<char>>& graph) 
    {
        if (graph.find(u) != graph.end()) {
            for (const char& v : graph[u]) {
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] =  u;
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
            for (const char& v : graph[u]) {
                if (ancestorStack.find(v) != ancestorStack.end()) return true;

                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] = u;

                    if depthFirstSearchDetectCycle(v, graph) return true;
                }
            }
        }
        ancestorStack.erase(u);
        finishingOrder.push_back(u);
        return false;
    }

    // for  undirected edges: don't double check one edge
    bool depthFirstSearchDetectCycleUndirectedEdge(char u, map<char, vector<char>>& graph)
    {
        ancestorStack.insert(u);

        if (graph.find(u) != graph.end()) {
            for (const auto& v : graph[u]) {
                if (v == parent[u]) continue; // bypass
                if (ancestorStack.find(v) != ancestorStack.end()) return true;
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] = u;
                    if (depthFirstSearchDetectCycleUndirectedEdge(v, graph)) return true;
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
                parent[v] = '\0';
                if (depthFirstSearchDetectCycle(v, graph)) return false;
            }
        }
        return true;
    }
};