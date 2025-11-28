

class DFSSolution
{
    public:
    set<char> visited;
    map<char, char> parent;
    vector<char> finishingOrder; // for topo
    set<char> ancestorStack; // for cycle

    void init(char s)
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();
        visited.insert(s);
        parent[s] = '\0';
    }


    // base DFS
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


    bool depthFirstSearchDetectCycle(char u, map<char, vector<char>>& graph)
    {
        ancestorStack.insert(u);

        if (graph.find(u) != graph.end()) {
            for (const char& v : graph.at(u)) {
                if (ancestorStack.find(v) != ancestorStack.end()) return true;

                // normal DFS logic
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    parent[v] = u;

                    // recurse on v
                    if (depthFirstSearchDetectCycle(v, graph)) return true;
                }
            }
        }
        ancestorStack.erase(u);
        finishingOrder.push_back(u);
        return false;
    }


    // FULL DFS
    void fullDepthFirstSearch(map<char, vector<char>>& graph)
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
            }
        }
    }


    // FULL DFS, is DAG
    bool fullDepthFirstSearchIsDAG(map<char, vector<char>>& graph)
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();
        ancestorStack.clear();

        set<char> allVertices = collectAllVertices(graph);

        for (const auto& v : allVertices) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent = '\0';
                if (depthFirstSearchDetectCycle(v, graph)) return false;
            }
        }
        return true;
    }


    // FULL DFS has cycle
    bool fullDepthFirstSearchHasCycle(map<char, vector<char>>& graph)
    {
        visited.clear();
        parent.clear();
        finishingOrder.clear();
        ancestorStack.clear();

        set<char> allVertices = collectAllVertices(graph);

        for (const auto& v : allVertices) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                parent = '\0';
                if (depthFirstSearchDetectCycle(v, graph)) return false;
            }
        }
        return true;
    }


    // FULL DFS returining finishing order
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