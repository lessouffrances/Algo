class Solution:
    def jobScheduling(self, startTime, endTime, profits):
        if not startTime or not endTime:
            return 0
            
        # binary search approach:
        def findPreviousCompatibleIntervalBinary(n):
            if n == 1:
                return 0

            left, right = 0, n-2
            while left <= right:
                mid = (left+right) // 2
                if endTime[mid] <= startTime[n-1]:
                    left = mid+1
                else:
                    right = mid-1
            return left

        dp = [ 0 for _ in range(len(profits)+1) ]

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
        print(startTime)
        print(endTime)
        print(profits)
            
        for i in range(1, len(dp)):
            print(f"The prev compatible internval for {i} is: ", findPreviousCompatibleIntervalBinary(i))
            dp[i] = max( dp[findPreviousCompatibleIntervalBinary(i)] + profits[i-1], dp[i-1])
            print(dp, end="\n")
        return max(dp)             
            
def main():
    solution = Solution()
    # startTime = [1,2,3,3,7]
    # endTime = [3,4,5,6,8]
    # profit = [50,10,40,70,35]

    startTime = [6,15,7,11,1,3,16,2]
    endTime = [19,18,19,16,10,8,19,8]
    profits = [2,9,1,19,5,7,3,19] # 41
    print(solution.jobScheduling(startTime, endTime, profits))
main()