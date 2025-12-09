#include <vector>
#include <set>
#include <map>
#include <climits>

using namespace std;

struct BFSResult
{
    set<char> visited;
    vector<vector<char>> levelRanking;
    map<char, int> delta;
    map<char, char> parent;
};

class BFSSolution
{
    public:
    BFSResult breadthFirstSearch(const map<char, vector<char>>& graph, char s)
    {
        // init
        set<char> visited;
        map<char, int> delta;
        map<char, char> parent;
        vector<vector<char>> levelRanking;

        // set delta to INT_MAX
        set<char> allVertices = collectAllVertices(graph);
        for (const auto& vertex : allVertices) {
            delta[v] = INT_MAX;
        }
        delta[s] = 0;

        parent[s] = '\0';
        visited.insert(s);
        vector<char> L_prev = { s };
        levelRanking.push_back( L_prev );

        int i = 1;
        while (!L_prev.empty()) {
            vector<char> L_i;

            for (const autp& u : L_prev) {
                if (graph.find(u) != graph.end()) {
                    set<char> L_i;
                    for (char v : graph[u]) {
                        if (visited.find(v) == visited.end()) {
                            visited.insert(v);
                            parent[v] = u;
                            delta[v] = i;
                            L_i.insert(v);
                        }
                    }
                }
                if (!L_i.empty()) {
                    levelRanking.push_back(L_i);
                }
                L_prev = L_i;
                i++; 
            }
        }
        // check reachability
        for (const auto& vertex : allVertices) {
            if (visited.find(vertex) == visited.end()) {
                parent[vertex] = '\0';
            }
        }

        return { visited, levelRanking, delta, parent }
    }

    private:
    set<char> collectAllVertices(const map<char, vector<char>>& graph)
    {
        set<char> allVertices;

        for (const auto& adjList : graph) {
            allVertices.insert(adjList.first) {
                for (const auto& vertex : adjList) {
                    allVertices.insert(vertex);
                }
            }
        }
        return allVertices;
    }
};