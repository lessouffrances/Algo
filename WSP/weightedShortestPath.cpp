#include <vector>
#include <map>
#include <utility>
#include <climits>
#include <algorithm>
#include <optional>
#include <set>

using namespace std;

class Solution
{
    public:
    set<char> visited;
    map<char, char> parent;
    vector<char> finishingOrder;

    // need for recursive purposes for DFS
    void init(const char& s)
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();
        visited.insert(s);
        parent[s] = '\0';
    }

    // basic DFS
    void depthFirstSearch(const char& u, const map<char, vector<pair<char, int>>>& graph) 
    {
        if(graph.find(u) != graph.end()) {
            for (const auto& pair : graph.at(u)) {
                char v = pair.first;
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] = u;
                    depthFirstSearch(v, graph);
                }
            }
        }
        finishingOrder.push_back(u);
    }


    // FULL DFS to return topological order
    vector<char> fullDepthFirstSearchReturnTopologicalOrder(const map<char, vector<pair<char, int>>>& graph)
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();

        // collect all vertices
        set<char> allVertices = collectAllVertices(graph);

        for (const auto& v : allVertices) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent[v] = '\0';
                depthFirstSearch(v, graph);
                parent.clear(); // to have the separate parent tree for separate connected components
            }
        } 

        reverse(finishingOrder.begin(), finishingOrder.end());
        return finishingOrder;
    }

    
    // given a DAG, use this DAG Relaxation 
    map<char, int> WeightedShortestPathWithDAGRelaxation(const map<char, vector<pair<char, int>>>& graph, char s)
    {
        // initialize delta
        map<char, int> delta;
        // set delta to inf max for all the vertices
        for (const auto& adjList : graph) {
            delta[adjList.first] = INT_MAX;
            for (const auto& pair : adjList.second) {
                delta[pair.first] = INT_MAX;
            }
        }
        delta[s] = 0; // source to itself

        vector<char> topoOrder = fullDepthFirstSearchReturnTopologicalOrder(graph);

        // iterate vertices by topological order
        for (const auto& u : topoOrder) {
            if (delta[u] != INT_MAX && graph.find(u) != graph.end()) {
                for (const auto&  pair : graph.at(u)) {
                    char v = pair.first;
                    int weightUtoV = pair.second;
                    if (delta[v] > delta[u] + weightUtoV) {
                        delta[v] = delta[u] + weightUtoV;
                    }
                }
            }
        }
        return delta;
    }


    // given a DAG, do DAG relaxation and shortest path tree construction
    pair<map<char, int>, map<char, char>> WeightedShortestPathWithDAGRelaxationAndShortestPathTree(map<char, vector<pair<char, int>>>& graph, char s)
    {
        // initialize delta and parent
        map<char, int> delta;
        map<char, char> parent;

        // set delta to INF MAX for all vertices except source, and set parent to null for source
        for (const auto& adjList : graph) {
            delta[adjList.first] = INT_MAX;
            for (const auto& pair : adjList.second) {
                delta[pair.first] = INT_MAX;
            }
        }
        delta[s] = 0;
        parent[s] = '\0';

        // get topo Order
        vector<char> topoOrder = fullDepthFirstSearchReturnTopologicalOrder(graph);

        // iterate through topo Order
        for (const auto& u : topoOrder) {
            if (delta[u] != INT_MAX && graph.find(u) != graph.end()) {
                for (const auto& pair : graph.at(u)) {
                    char v = pair.first;
                    int weightUtoV = pair.second;
                    if (delta[v] > delta[u] + weightUtoV) {
                        delta[v] = delta[u] + weightUtoV;
                        parent[v] = u;
                    }
                }
            }
        }
        return { delta, parent };
    }


    private:
    set<char> collectAllVertices(const map<char, vector<pair<char, int>>>& graph)
    {
        set<char> allVertices;
        for (const auto& adjList : graph) {
            allVertices.insert(adjList.first);
            for (const auto& pair : adjList.second) {
                char v = pair.first;
                allVertices.insert(v);
            }
        }
        return allVertices;
    }
};

int main()
{
    map<char, vector<pair<char, int>>> DAG = {
        {'a' , { {'b', -5}, {'e', 7} }},
        {'b' , { {'c', -1}, {'e', 6}, {'f', -4} }},
        {'d' , { {'c', 5} }},
        {'e' , { {'f', 3} }},
        {'f' , { {'c', 8}, {'g', 2} }},
        {'g' , { {'c', 1}, {'h', -2} }},
        {'h' , { {'c', 9}, {'d', 4} }}
    };






};
