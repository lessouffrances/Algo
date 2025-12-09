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
    map<char, int> delta; // shortest path from s
    map<char, char> parent; // shortest path tree
};

class DijkstraSolution 
{
    public:
    DijkstraResult dijkstraShortestPath(map<char, vector<pair<char, int>>> graph, char s) 
    {
        // initialize 
        map<char, int> delta;
        set<char> visited;
        map<char, char> parent;

        // set the delta for all vertices to INT_MAX;
        for (const auto& adjList : graph) {
            delta[adjList.first] = INT_MAX;
            for (const auto& pair : adjList.second) {
                delta[pair.first] = INT_MAX;
            }
        }
        delta[s] = 0;
        parent[s] = "\0";

        // initialize a priority queue       
        priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;
        pq.push({0, s});

        while (!pq.empty()) {
            auto [dist, u] = pq.top(); // return the top to the min heap
            pq.pop(); // remove the top of the min heap

            if (visited.find(u) != visited.end()) continue;
            visited.insert(u);
            if(graph.find(u) != graph.end()) {
                for (const auto& [v, weightUtoV] : graph.at(u)) {
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

int main()
{
    // graph with non-negative weights
    map<char, vector<pair<char, int>>> G = {
        {'a', {{'b', 4}, {'c', 2}}},
        {'b', {{'c', 1}, {'d', 5}}},
        {'c', {{'d', 8}, {'e', 10}}},
        {'d', {{'e', 2}, {'f', 6}}},
        {'e', {{'f', 3}}},
        {'f', {{'g', 1}}},
        {'g', {{'h', 4}}},
        {'h', {}}
    };
}