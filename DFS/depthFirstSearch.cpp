#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <cstdio>

using namespace std;

class Solution {
    public:

    unordered_map<char, char> parent; // { child : parent }
    set<char> visited;

    void depthFirstSearch(const char& u, const map<char, vector<char>>& G) 
    {

        for (auto& v : G.at(u)) {
            // if v is not visited
            if (visited.find(v) == visited.end()) {
                parent[v] = u;
                visited.insert(v);
                depthFirstSearch(v, G);
            }
        }
    }

};

int main()
{
    Solution solution = Solution();

    map<char, vector<char>> graph = {
        {'A', {'B', 'C'}},
        {'B', {'A', 'D', 'E'}},
        {'C', {'A', 'F', 'G'}},
        {'D', {'B', 'H', 'I'}},
        {'E', {'B', 'I', 'J'}},
        {'F', {'C', 'J', 'K'}},
        {'G', {'C', 'K'}},
        {'H', {'D', 'L'}},
        {'I', {'D', 'E', 'L', 'J'}},
        {'J', {'E', 'F', 'I'}},    
        {'K', {'F', 'G'}},         
        {'L', {'H', 'I'}}          
    };

    solution.visited.insert('A');
    solution.parent['A'] = '\0';  // null char
    solution.depthFirstSearch('A', graph);

    // print the visited set
    printf("The following nodes are visited.\n");
    for (const auto& v : solution.visited) {
        printf("%c ", v);
    }
    printf("\n\n");

    // print the parent map
    printf("The following nodes are reachable from src.\n");
    for (const auto& pair : solution.parent) {
        printf("%c:%c  ", pair.first, pair.second);
    }
}