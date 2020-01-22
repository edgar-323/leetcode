/*
We have a collection of rocks, each rock has a positive integer weight.
Each turn, we choose any two rocks and smash them together.  
Suppose the stones have weights x and y with x <= y.  
The result of this smash is:

If x == y, both stones are totally destroyed;
If x != y, the stone of weight x is totally destroyed, and the stone of weight y has new weight y-x.
At the end, there is at most 1 stone left.  Return the smallest possible weight of this stone (the weight is 0 if there are no stones left.)

Example 1:
Input: [2,7,4,1,8,1]
Output: 1
Explanation: 
We can combine 2 and 4 to get 2 so the array converts to [2,7,1,8,1] then,
we can combine 7 and 8 to get 1 so the array converts to [2,1,1,1] then,
we can combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we can combine 1 and 1 to get 0 so the array converts to [1] then that's the optimal value.

Note:
1 <= stones.length <= 30
1 <= stones[i] <= 100
*/

class Solution {
private:
    /***************************************************************************************************************/
    int N;
    int recurse1(std::vector<int>& stones) {
        // BRUTE-FORCE
        int min_stone = 0;
        bool one_stone = false;
        bool zero_stones = true;
        for (int i = 0; i < N; ++i) {
            if (not stones[i]) {
                continue;
            }
            if (one_stone) {
                one_stone = false;
                break;
            }
            zero_stones = false;
            one_stone = true;
            min_stone = stones[i];
        }
        if (zero_stones or one_stone) {
            return min_stone;
        }
        min_stone = INT_MAX;

        for (int i = 0; i < N; ++i) {
            if (not stones[i]) {
                continue;
            }
            for (int j = i+1; j < N; ++j) {
                if (not stones[j]) {
                    continue;
                }
                const int x = stones[i];
                const int y = stones[j];
                const int diff = std::max(x,y) - std::min(x,y);
                stones[i] = diff;
                stones[j] = 0;
                min_stone = std::min(min_stone, recurse1(stones));
                stones[i] = x;
                stones[j] = y;
            }
        }
        return min_stone;
    }

    int solution1(std::vector<int>& stones) {
        N = stones.size();
        return recurse1(stones);
    }
    /***************************************************************************************************************/
    static const int MAX_STONES = 30;
    static const int MAX_WEIGHT = 100;
    static const int MAX_SUM = MAX_STONES * MAX_WEIGHT;
    int solution2(const std::vector<int>& A) {
		/*
       	Intuition

		Same problem as:
		Divide all numbers into two groups,
		what is the minimum difference between the sum of two groups.
		Now it's a easy classic knapsack problem.


		Brief Prove

		All cases of "cancellation of rocks" can be expressed by two knapsacks.
		And the last stone value equals to the difference of these two knapsacks
		It needs to be noticed that the opposite proposition is wrong.


		Solution 1

		Explanation:

		Very classic knapsack problem solved by DP.
		In this solution, I use DP to record the achievable sum of the smaller group.
		DP[x] = 1 means the sum x is possible.


		Time Complexity:

		O(NS) time,
		O(S) space, where S = sum(A).
		*/
		bitset<MAX_SUM/2 + 1> DP;
        DP.set(0); 
        int sumA = 0;
        for (int a : A) {
            sumA += a;
            for (int i = std::min(1500, sumA); i >= a; --i) {
                DP[i] = DP[i] | DP[i - a]; // ==> DP[i] = DP[i] | DP[i-a] ==> (ith-bit | (i-a)th-bit)
            }
        }
        for (int i = sumA / 2; i > 0; --i) {
            if (DP[i]) {
                return sumA - i - i;
            }
        }

        return 0;
    }
    /***************************************************************************************************************/
public:
    int lastStoneWeightII(vector<int>& stones) {
        return solution2(stones); 
    }
};
