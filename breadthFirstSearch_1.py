class Solution:
    def breadthFirstSearch(self, graph):
        # choose a source
        s = list(graph.keys())[0]

        # initialize
        delta = {s: 0} #the distance from source to source is 0
        parent = {s: None} #the source does not have any parent
        L_prev = {s} #the first level only has the source itself 
        level_ranking = [L_prev] #the level_ranking will only have the first level
        visited = set(s)

        i = 1
        while L_prev:
            L_i = set()
            for u in L_prev:
                for v in graph.get(u, []):
                    if v not in visited:
                        L_i.add(v)
                        delta[v] = i
                        parent[v] = u
                        visited.add(v)
            if L_i:
                level_ranking.append(L_i)
            L_prev = L_i
            i += 1
        
        for v in graph.keys():
            if v not in visited:
                delta[v] = float('inf')

        return delta, parent, level_ranking, visited
                 

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

    delta, parent, level_ranking, visited = solution.breadthFirstSearch(g)
    print(delta)
    print(parent)
    print(level_ranking)
main()