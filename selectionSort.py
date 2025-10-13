class Solution:
    def selectionSort(self, arr) -> list[int]:
        n = len(arr)
        for i in range(n):
            min_idx = i

            for j in range(i, n):
                if arr[j] < arr[min_idx]:
                    min_idx = j
            arr[i], arr[min_idx] = arr[min_idx], arr[i]
            
        return arr

def main():
    self = Solution()
    nums = [2, 3, 8, 28, 42, 17, 11, 15]
    res = Solution.selectionSort(self, nums)
    print(res)
main()