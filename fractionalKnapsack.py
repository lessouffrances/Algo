class Solution:
    def maximizeFractionalKnapsackValue(self, weights, prices, T):
        if (not weights) or (not prices) or (not T):
            return 0

        densities = []
        for weight, price in zip(weights, prices):
            densities.append([price/weight, price, weight])
        print(densities)

        densities.sort(key=lambda x:x[0], reverse=True)
        print(densities)
        res, totalValue = [], 0

        for info in densities:
            if T <= 0:
                return res, totalValue

            if weight <= T:
                fraction = 1
            else:
                fraction = T / info[2]
            
            currValue, currWeight = fraction * info[1], fraction * info[2]
            res.append((currWeight, info[2]))
            totalValue += currValue
            T = T - currWeight

def main():
    solution = Solution()
    T = 35
    weights = [1, 5, 7, 2, 5, 3, 4, 9, 12]
    prices = [102, 501, 71, 0, 10, 12, 13, 17, 18]
    print(solution.maximizeFractionalKnapsackValue(weights, prices, T))
main()