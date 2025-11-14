class Solution:
    def binarySearch(self, arr, target):
        arr.sort()
        print(arr)

        left, right = 0, len(arr)-1

        while left <= right:
            mid = (left+right) // 2

            if arr[mid] > target:
                right = mid - 1
            elif arr[mid] < target:
                left = mid + 1
            else:
                return arr[mid]
        return -1

def main():
    solution = Solution()
    test_1 = [1, 1, 1, 1, 1]
    test_2 = []
    test_3 = [8, 7, 6, 5, 4, 3, 2, 1]
    target_3 = 6
    print(solution.binarySearch(test_3, target_3))

main()