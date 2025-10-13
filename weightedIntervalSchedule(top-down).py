class Solution:
    def jobScheduling(self, startTime, endTime, profit) -> int:
        if not startTime or not endTime or not profit: # edge case
            return 0
        
        intervals = list(zip(startTime, endTime, profit))
        intervals.sort(key=lambda x : x[1]) # sort by the endTime of each interval

        n = len(intervals) # how many intervals are there
        memo = {}

        def findOPT(n):
            if n == 0: 
                return 0
            elif n == 1:
                return intervals[0][2] # only return the profit of the first interval
            if n in memo:
                return memo[n]
            
            value_n = intervals[n-1][2]
            previousCompatibleInterval_n = findPreviousCompatibleInterval(n)

            res = max(findOPT(n-1), value_n + findOPT(previousCompatibleInterval_n))
            memo[n] = res # store in the memo hashMap
            return res

        def findPreviousCompatibleInterval(n):
            currStart = intervals[n-1][0]

            for i in range(n-2, -1, -1):
                if intervals[i][1] <= currStart:
                    return i+1 # return the 1-based index
            return 0
        
        # or, the binary search is faster:
        def findPreviousCompatibleBinary(n):
            curr_start = intervals[n-1][0]
            left, right = 0, n-2  # Search in 0-based indices
            result = 0
            
            while left <= right:
                mid = (left+right)//2
                if intervals[mid][1] <= curr_start:
                    result = mid+1  # Convert to 1-based
                    left = mid+1
                else:
                    right = mid-1
            
            return result
        
        print(findOPT(n))
        return findOPT(n)
                 
def main():
    self = Solution
    startTime = [1, 2, 3, 3]
    endTime = [3, 4, 5, 6]
    profit = [50, 10, 40, 70]
    Solution.jobScheduling(self, startTime, endTime, profit)
main()