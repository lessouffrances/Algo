class Solution:
    def breadthFirstSearch(self, graph):
        # Choose a source
        s = list(graph.keys())[0]
        delta = {}
        parent = {}
        level_ranking = []
        visited = {}

        # Base case: L0 = {s} (as a set)
        delta[s] = 0
        parent[s] = None
        L_0 = {s}
        visited = {s}
        level_ranking.append(L_0)
        
        i = 1
        L_prev = level_ranking[i-1]
        
        while L_prev:
            L_i = set()  
            for u in L_prev:
                for v in graph.get(u, []):
                    if v not in visited:
                        L_i.add(v)
                        delta[v] = i
                        parent[v] = u
            if L_i:
                level_ranking.append(L_i)
            
            L_prev = L_i
            i += 1
        
        for v in graph.keys():
            if v not in delta:
                delta[v] = float('inf')
        
        return delta, parent, level_ranking


def main():
    solution = Solution()
    g = { "A": ["B", "C"],
          "B": ["A", "D", "E"],
          "C": ["A", "F", "G"],
          "D": ["B", "H", "I"],
          "E": ["B", "I", "J"],
          "F": ["C", "J", "K"],
          "G": ["C", "K"],
          "H": ["D", "L"],
          "I": ["D", "E", "L", "J"],
          "J": ["E", "F", "I"],
          "K": ["F", "G"],
          "L": ["H", "I"]
        }

    delta, parent, level_ranking = solution.breadthFirstSearch(g)
    print(delta)
    print(parent)
    print(level_ranking)
main()