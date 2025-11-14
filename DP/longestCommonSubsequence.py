class Solution:
    def longestCommonSubsequence(self, text1, text2) -> int:
        tableWidth, tableHeight = len(text1)+1, len(text2)+1
        dp = [ [0 for _ in range(tableHeight)] for _ in range(tableWidth) ]
        print(dp)

        for i in range(1, tableWidth):
            for j in range(1, tableHeight):
                if text1[i-1] == text2[j-1]:
                    dp[i][j] = dp[i-1][j-1] + 1
                else:
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1])
                
                print(dp)

        print(dp[tableWidth-1][tableHeight-1])            
        return dp[tableWidth-1][tableHeight-1]
        
        

def main():
    solution = Solution()
    text1 = "abcde"
    text2 = "ace" # 3

    # text1 = "abc" 
    # text2 = "abc" # 3

    # text1 = "abc"
    # text2 = "def" # 0

    solution.longestCommonSubsequence(text1, text2)
main()