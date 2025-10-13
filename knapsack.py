class Solution:
    def maximizeKnapsackValue(self, weights, prices, T):
        numOfItems = len(weights)
        dp = [ [0 for _ in range(T+1)] for _ in range(numOfItems+1) ]

        for i in range(1, numOfItems+1):
            for j in range(1, T+1):
                if weights[i-1] > j:
                    dp[i][j] = dp[i-1][j]
                else:
                    dp[i][j] = max(dp[i-1][j], prices[i-1]+dp[i-1][j-weights[i-1]])

        for lst in dp:
            print(lst, end="\n")

        return dp[numOfItems][T]

def main():
    solution = Solution()
    T = 8
    weights = [2, 3, 5]
    prices = [4, 5, 8]
    print(solution.maximizeKnapsackValue(weights, prices, T))
main()