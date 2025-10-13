class Solution:
    def mergeSort(self, arr) -> list[int]:
        if len(arr) <= 1:
            return arr
        
        mid = len(arr) // 2
        leftHalf = arr[:mid]
        rightHalf = arr[mid:]

        leftSorted = self.mergeSort(leftHalf)
        rightSorted = self.mergeSort(rightHalf)

        return self.merge(leftSorted, rightSorted)

    
    def merge(self, left, right):
        res = []
        i = j = 0

        # both halves have remaining elements 
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                res.append(left[i])
                i += 1
            else:
                res.append(right[j])
                j += 1
        
        while i < len(left):
            res.append(left[i])
            i += 1
        
        while j < len(right):
            res.append(right[j])
            j += 1
        
        return res

def main():
    self = Solution()
    nums = [11, 3, 42, 28, 17, 8, 2, 15]
    res = Solution.mergeSort(self, nums)
    print(res)
main()