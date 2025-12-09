#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>

struct DijkstraResult
{
    map<char, int> delta;
    map<char, char> parent;
};

class DijkstraSolution
{
    public:
    DijkstraResult dijkstraShortestPath(map<char, vector<char, int>>& graph, char s)
    {
        // init
        map<char, int> delta;
        set<char> visited;
        map<char, char> parent;

        // set the delta for all vertices to INT_MAX
        for (const auto& adjList : graph) {
            delta[adjList.first] = INT_MAX;
            for (const auto& pair : adjList.second) { 
                delta[pair.first] INT_MAX;
            }
        }
        delta[s] = 0;
        parent = '\0';

        // init a pq;
        priority_queue<pair<int, char>, vector<pair<int, char>, greater<pair<int, char>>>> pq;
        pq.push( {0, s} );

        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();

            if (visited.find(u) != visited.end()) continue;
            visited.insert(u);

            if (graph.find(u) != graph.end()) {
                for (const auto& [v, weightUtoV] : graph[u]) {
                    if (delta[v] > delta[u] + weightUtoV) {
                        delta[v] = delta[u] + weightUtoV;
                        parent[v] = u;
                        pq.push({delta[v], v});
                    }
                }
            }
        }
        return { delta, parent };
    }
};