class Solution:
    def minimalLatenessScheduling(self, jobLengths, deadlines):
        combos = []
        for i in range(len(jobLengths)):
            combos.append([jobLengths[i], deadlines[i]])

        combos.sort(key=lambda x:x[1])
        print("The sorted combos: ", combos)

        for i, combo in enumerate(combos):
            jobLengths[i] = combo[0]
            deadlines[i] = combo[1]
        print(jobLengths)
        print(deadlines)

        currEnd, maxLateness = 0, 0

        # Dont have to use the 2 lists that were put back from the sorted combo
        for jobLength, deadline in combos:
            currEnd += jobLength
            lateness = currEnd-deadline
            maxLateness = max(lateness, maxLateness)
        return maxLateness


def main():
    solution = Solution()
    jobLengths = [2, 5, 3, 4, 1, 7, 1]
    deadlines = [4, 7, 12, 3, 1, 7, 9]
    print(solution.minimalLatenessScheduling(jobLengths, deadlines))
main()