#include <map>
#include <string>
#include <climits>
#include <set>
#include <vector>

using namespace std;

class Solution 
{
    public: 
    struct BFSResult
    {
        map<string, int> delta;
        map<string, string> parent;
        vector<set<string>> levelRanking;
    };

    BFSResult breadthFirstSearch(map<string, vector<string>>& graph)
    {
        // choose a source
        string s = graph.begin()->first;

        // initialize
        map<string, int> delta;
        map<string, string> parent;
        vector<set<string>> levelRanking;
        set<string> visited;

        delta[s] = 0;
        parent[s] = "";
        levelRanking.push_back( {s} );
        visited.insert(s);

        int i = 1;
        set<string> L_prev = levelRanking[0];
        while (!L_prev.empty()) {
            set<string> L_i;
            for (const string& u : L_prev) {
                for (const string& v : graph.at(u)) {
                    if (visited.find(v) == visited.end()) {
                        L_i.insert(v);
                        delta[v] = i;
                        parent[v] = u;
                        visited.insert(v);
                    }
                }
            }

            if (!L_i.empty()) {
                levelRanking.push_back(L_i);
            }
            L_prev = L_i;
            i++;
        }

        // unreachable vertices
        for (const auto& pair : graph) {
            const string& it = pair.first;
            if (visited.find(it) == visited.end()) {
                delta[it] = INT_MAX;
            }
        }

        return {delta, parent, levelRanking};
    }
};

