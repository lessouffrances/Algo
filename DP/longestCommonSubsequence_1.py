class Solution:
    def longestCommonSubsequence(self, text1, text2):
        dp = [ [ 0 for _ in range(len(text1)+1) ]  for _ in range(len(text2)+1) ]
        for lst in dp:
            print(lst, end="\n")
        print("\n\n")
        
        for i in range(1, len(text2)+1):
            for j in range(1, len(text1)+1):
                if text1[j-1] == text2[i-1]:
                    dp[i][j] = dp[i-1][j-1]+1
                else:
                    dp[i][j] = max(dp[i][j-1], dp[i-1][j])
                
                for lst in dp:
                    print(lst, end="\n")
                print("\n\n")
        return dp[-1][-1]

    
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