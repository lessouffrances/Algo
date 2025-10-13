class Solution:
    def unweightedIntervalScheduling(self, intervals):
        if not intervals:
            return 0
        
        intervals.sort(key=lambda x:x[1])
        print(intervals)
        res, lastIncludedInterval = 1, intervals[0]

        for i in range(1, len(intervals)):
            if intervals[i][0] >= lastIncludedInterval[1]:
                res += 1
                lastIncludedInterval = intervals[i]
            print(res)
        
        return (len(intervals)-res)
            
        
def main():
    solution = Solution()
    # intervals = [[1,2],[2,3],[3,4],[1,3]] #1
    # intervals = [[1,2],[1,2],[1,2]] #2
    # intervals = [[1,2],[2,3]] #0
    intervals = [[1,100],[11,22],[1,11],[2,12]] #2
    print(solution.unweightedIntervalScheduling(intervals))
main()