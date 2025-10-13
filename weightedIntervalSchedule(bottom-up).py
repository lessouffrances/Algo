class Solution:
    def jobScheduling(self, startTime, endTime, profit):
        if not startTime: # edge case
            return 0
        
        intervals = list(zip(startTime, endTime, profit))
        intervals.sort(key=lambda x : x[1])

        n = len(intervals)

        def findOPT(n):
            memo = [0] * (n+1)
            memo[0] = 0
            if n >= 1:
                memo[1] = intervals[0][2]
            
            for i in range(2, n+1):
                value_i = intervals[i-1][2]
                previousCompatibleInterval_i = findPreviousCompatibleInterval(i)
                memo[i] = max(memo[i-1], value_i + memo[previousCompatibleInterval_i])

            return memo[n]

        # Linear approach:
        def findPreviousCompatibleInterval(n):
            currStart = intervals[n-1][0]

            for j in range(n-2, -1, -1):
                if intervals[j][1] <= currStart:
                    return j+1
            return 0
        
        # or, the binary search is faster:
        def findPreviousCompatibleBinary(n):
            curr_start = intervals[n-1][0]
            left, right = 0, n-2  # Search in 0-based indices
            result = 0
            
            while left <= right:
                mid = (left + right) // 2
                if intervals[mid][1] <= curr_start:
                    result = mid + 1  # Convert to 1-based
                    left = mid + 1
                else:
                    right = mid - 1
            
            return result
        
        print(findOPT(n))
        return findOPT(n)
 
def main():
    self = Solution
    startTime = [1,2,3,3]
    endTime = [3,4,5,6]
    profit = [50,10,40,70]
    Solution.jobScheduling(self, startTime, endTime, profit)
main()