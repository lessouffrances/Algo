class Solution:
    def lengthOfLIS(self, nums) :
        dp = [ 0 for _ in range(len(nums)+1)]
        dp[1] = 1
        print(dp)

        def findPrevCompatible(n):
            candidates = []
            for j in range(0, n-1):
                if nums[j] < nums[n-1]:
                    candidates.append(dp[j+1])
            return max(candidates) if len(candidates) >= 1 else 0
            
        for i in range(2, len(dp)):
            dp[i] = 1 + findPrevCompatible(i)
        return max(dp)

    
def main():
    solution = Solution()
    nums = [10,9,2,5,3,7,101,18] # 4
    # nums = [4,10,4,3,8,9]
    print(solution.lengthOfLIS(nums))
main()

        