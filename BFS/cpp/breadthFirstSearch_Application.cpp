#include <vector>
#include <map>
#include <set>
#include <climits>

using namespace std;

class BFSSolution 
{
    public:
    struct BFSResult
    {
        map<string, int> delta;
        map<string, string> parent;
        vector<set<string>> levelRanking;
    };

    // single pair shortest path
    struct ShortestPathResult
    {
        int dist;
        vector<string> shortestPath; // vector to preserve sequence
    };

    
    void printBFSResult(const BFSResult& result)
    {
        printf("===== BFS Result =====\n");
        
        // Print delta (distances)
        printf("\nDistances (delta):\n");
        for (const auto& pair : result.delta) {
            printf("  %s: ", pair.first.c_str());
            if (pair.second == INT_MAX) {
                printf("INF (unreachable)\n");
            } else {
                printf("%d\n", pair.second);
            }
        }
        
        // Print parent pointers
        printf("\nParent Pointers:\n");
        for (const auto& pair : result.parent) {
            printf("  %s -> ", pair.first.c_str());
            if (pair.second.empty()) {
                printf("NULL (root or unreachable)\n");
            } else {
                printf("%s\n", pair.second.c_str());
            }
        }
        
        // Print level ranking
        printf("\nLevel Ranking:\n");
        for (size_t i = 0; i < result.levelRanking.size(); i++) {
            printf("  Level %zu: { ", i);
            bool first = true;
            for (const auto& node : result.levelRanking[i]) {
                if (!first) printf(", ");
                printf("%s", node.c_str());
                first = false;
            }
            printf(" }\n");
        }
        printf("======================\n");
    }

    BFSResult breadthFirstSearch(map<string, vector<string>>& graph)
    {
        // choose a source
        string s = graph.begin()->first;

        // initialize
        map<string, int> delta;
        map<string, string> parent;
        vector<set<string>> levelRanking;
        set<string> visited;

        // put s into them
        delta[s] = 0;
        parent[s] = "";
        set<string> L_prev = {s};
        levelRanking.push_back( L_prev );
        visited.insert(s);

        int i = 1;
        while (!L_prev.empty()) {
            set<string> L_i;
            for (const string& u : L_prev) {
                if (graph.find(u) != graph.end()) {
                    for (const string& v : graph.at(u)) {
                        // if u is not visited yet
                        if (visited.find(v) == visited.end()) {
                            delta[v] = i;
                            parent[v] = u;
                            visited.insert(v);
                            L_i.insert(v);
                        }
                    }
                }
            }

            if (!L_i.empty()) {
                levelRanking.push_back(L_i);
            }
            L_prev = L_i;
            i ++;
        }

        // mark unreachable vertices
        // collect all vertices first
        set<string> allVertices;
        for (const auto& pair : graph) {
            allVertices.insert(pair.first);
            for (const auto& neighbor : pair.second) {
                allVertices.insert(neighbor);
            }
        }

        for (const auto& v : allVertices) {
            if (visited.find(v) == visited.end()) {
                delta[v] = INT_MAX;
                parent[v] = "";
            }
        }

        return { delta, parent, levelRanking };
    }


    ShortestPathResult singlePairShortestPath(map<string, vector<string>>& graph, string s, string t)
    {
        // initialize
        map<string, int> delta;
        map<string, string> parent;
        vector<set<string>> levelRanking;
        set<string> visited;

        // put s into them
        delta[s] = 0;
        parent[s] = "";
        set<string> L_prev = {s};
        levelRanking.push_back( L_prev );
        visited.insert(s);

        int i = 1;
        while (!L_prev.empty()) {
            set<string> L_i;
            for (const string& u : L_prev) {
                if (graph.find(u) != graph.end()) {
                    for (const string& v : graph.at(u)) {
                        // if u is not visited yet
                        if (visited.find(v) == visited.end()) {
                            delta[v] = i;
                            parent[v] = u;
                            visited.insert(v);
                            L_i.insert(v);
                        }
                    }
                }
            }

            if (!L_i.empty()) {
                levelRanking.push_back(L_i);
            }
            L_prev = L_i;
            i ++;
        }

        // mark unreachable vertices
        // collect all vertices first
        set<string> allVertices;
        for (const auto& pair : graph) {
            allVertices.insert(pair.first);
            for (const auto& neighbor : pair.second) {
                allVertices.insert(neighbor);
            }
        }

        for (const auto& v : allVertices) {
            if (visited.find(v) == visited.end()) {
                delta[v] = INT_MAX;
                parent[v] = "";
            }
        }

        // check if reachable
        bool reachable = false;
        for (const auto& v : visited) {
            if (visited.find(t) == visited.end()) {
                return { INT_MAX, {} };
            } else {
                reachable = true;
            }
        }

        // if reachable, reconstruct the shortest path
        vector<string> shortestPath; 
        if (reachable) {
            findParent(parent, t, shortestPath); // path starts from the t back to s
            reverse(shortestPath.begin(), shortestPath.end());
        }
        return { delta[t], shortestPath };
    }


    void findParent(map<string, string>& parentRelationships, string child, vector<string>& path)
    {
        path.push_back(child);
        for (const auto& pair  : parentRelationships) {
            if (pair.first == child) {
                return findParent(parentRelationships, pair.second, path);
            }
        }
        return;
    }


    // single pair reachability
    bool singlePairReachability(map<string, vector<string>>& graph, string s, string t)
    {
        // initialize
        map<string, int> delta;
        map<string, string> parent;
        vector<set<string>> levelRanking;
        set<string> visited;

        // layer 0
        delta[s] = 0;
        parent[s] = "";
        set<string> L_prev = { s };
        levelRanking.push_back(L_prev);
        visited.insert(s);

        int i = 1;
        while (!L_prev.empty()) {
            set<string> L_i;
            for (const string& u : L_prev) {
                if (graph.find(u) != graph.end()) {
                    for (const string& v : graph.at(u)) {
                        if (visited.find(v) == visited.end()) {
                            delta[v] = i;
                            parent[v] = u;
                            visited.insert(v);
                            L_i.insert(v);
                        }
                    }
                }
            }

            if (!L_i.empty()) {
                levelRanking.push_back(L_i);
            }
            L_prev = L_i;
            i++;
        }

        if (visited.find(t) == visited.end()) {
            return false;
        }
        return true;
    }

    void printShortestPathResult(ShortestPathResult result)
    {
        printf("The distance is %d\n", result.dist);
        printf("The shortest path is: \n");
        for (int i=0; i<result.shortestPath.size(); i++) {
            printf("%s ", result.shortestPath[i].c_str());
        }
        printf("\n");
    }
};


int main()
{
    map<string, vector<string>> G = {
        {"A", {"B", "C"}},
        {"B", {"A", "D", "E"}},
        {"C", {"A", "F", "G"}},
        {"D", {"B", "H", "I"}},
        {"E", {"B", "I", "J"}},
        {"F", {"C", "J", "K"}},
        {"G", {"C", "K"}},
        {"H", {"D", "L"}},
        {"I", {"D", "E", "L", "J"}},
        {"J", {"E", "F", "I"}},
        {"K", {"F", "G"}},
        {"L", {"H", "I"}}
    };

    BFSSolution solution = BFSSolution();
    BFSSolution::BFSResult result_1 = solution.breadthFirstSearch(G);
    solution.printBFSResult(result_1);

    
    bool result_2 = solution.singlePairReachability(G, "A", "H");
    printf("%u ", result_2);

    BFSSolution::ShortestPathResult result_3 = solution.singlePairShortestPath(G, "A", "H");
    solution.printShortestPathResult(result_3);

    return 0;
}

