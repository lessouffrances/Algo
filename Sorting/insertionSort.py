class Solution:
    def insertionSort(self, arr) -> list[int]:
        n = len(arr)

        for i in range(1, n):
            curr = arr[i]
            j = i - 1

            while j >= 0 and arr[j] > curr:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = curr
            
        return arr

def main():
    self = Solution()
    nums = [11, 3, 42, 28, 17, 8, 2, 15]
    res = Solution.insertionSort(self, nums)
    print(res)
main()