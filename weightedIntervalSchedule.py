class Solution:
    def jobScheduling(self, startTime, endTime, profits):
        if not startTime or not endTime:
            return 0

        # Linear approach:
        def findPreviousCompatibleInterval(n):
            if n == 1:
                return 0

            for i in range(n-2, -1, -1):
                if endTime[i] <= startTime[n-1]:
                    return i+1

            return 0

        # binary search approach:
        def findPreviousCompatibleIntervalBinary(n):
            if n == 1:
                return 0

            left, right = 0, n-2
            result = 0
            
            while left <= right:
                mid = (left+right) // 2

                if endTime[mid] <= startTime[n-1]:
                    left = mid+1
                    result = mid+1
                else:
                    right = mid-1
        
            return result
            

        intervals = []
        for start, end, profit in zip(startTime, endTime, profits):
            intervals.append((start, end, profit))
        print(intervals)

        intervals.sort(key=lambda x:x[1])
        print(intervals)

        for i, interval in enumerate(intervals):
            startTime[i] = interval[0]
            endTime[i] = interval[1]
            profits[i] = interval[2]
        
        print("Sorted start time: ", startTime)
        print("Sorted end time: ", endTime)
        print("Sorted profits: ", profits)
        
        numOfIntervals = len(profits)
        dp = [ 0 for _ in range(numOfIntervals+1)]
        print("Allocated DP Array: ", dp, end="\n\n")

        for i in range(1, numOfIntervals+1):
            print(f"The previous compatible interval for interval {i} is: ", findPreviousCompatibleIntervalBinary(i))
            dp[i] = max(dp[i-1], profits[i-1]+dp[findPreviousCompatibleIntervalBinary(i)])
            print(dp)

        return max(dp)
 
def main():
    solution = Solution()
    # startTime = [1,2,3,3,7]
    # endTime = [3,4,5,6,8]
    # profit = [50,10,40,70,35]

    startTime = [6,15,7,11,1,3,16,2]
    endTime = [19,18,19,16,10,8,19,8]
    profits = [2,9,1,19,5,7,3,19]
    print(solution.jobScheduling(startTime, endTime, profits))
main()