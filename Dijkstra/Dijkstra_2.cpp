// cannot address negative weights
#include <vector>
#include <algorithm>
#include <cstdio>
#include <climits>
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
    DijkstraResult dijkstraShortestPath(map<char, vector<pair<char, int>>> graph, char s)
    {
        map<char, int> delta;
        set<char> visited;
        map<char, char> parent;

        // set all delta to MAX
        for (const auto& adjList : graph) {
            delta[adjList.first] = INT_MAX;
            for (const auto& pair: adjList.second) {
                delta[pair.first] = INT_MAX;
            }
        }
        delta[s] = 0;
        parent[s] = -1;

        priority_queue<pair<int, char>, vector<pair<int, char>>, great<pair<char, int>>> pq;
        pq.push({0, s});

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
            return {delta, parent};
        }
    }
};