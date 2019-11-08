/*
You are given n pairs of numbers. 
In every pair, the first number is always smaller than the second number.
Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. 
Chain of pairs can be formed in this fashion.
Given a set of pairs, find the length longest chain which can be formed. 
You needn't use up all the given pairs. 
You can select pairs in any order.

Example 1:
Input: [[1,2], [2,3], [3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4]

Note:
The number of given pairs will be in the range [1, 1000].
*/

class Solution {
private:
    int solution1(std::vector<std::vector<int>>& pairs) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O( N )
         */
        const int N = pairs.size();
        if (not N) {
            return 0;
        }
        // O(N * log(N))
        std::sort(pairs.begin(), pairs.end(), 
				[]
				(const std::vector<int>& p1, const std::vector<int>& p2) -> bool {
					const int a = p1[0];
					const int c = p2[0];
					return a <= c;
				}
		);
        // O(N^2)
        auto DP = std::vector<int>(N, 1);
        for (int i = 1; i < N; ++i) {
           for (int j = 0; j < i; ++j) {
                const int b = pairs[j][1];
                const int c = pairs[i][0];
                if (b < c) {
                    DP[i] = std::max(DP[i], DP[j] + 1);
                }
           }
        }
        // O(N)
        return *std::max_element(DP.begin(), DP.end());
    }
    

    int solution2(std::vector<std::vector<int>>& pairs) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         */ 

        /* NOTE FOR SELF:
         * I initially had the signature of this function as:
         * 
         * int solution2(const std::vector<std::vector<int>>& pairs);
         *
         * Since pairs was declared 'const', and since we are attempting to
         * sort pairs, the compiler was giving some absolutely disgusting
         * compilation errros that did not point me to const qualifier.
         *
         * Also, within the compare function that we are feeding into
         * std::sort(), ensure that you only return true when absolutely
         * certain.
         * I was returning a[1] <= b[1] and i was getting "dangling references"
         * runtime error on leetcode.
         * When i changed it to a[1] < b[1], they runtime errors ceased.
         */
        // O(N * log(N))
        std::sort(pairs.begin(), pairs.end(),
                    []
                    (const vector<int>& p1, const vector<int>& p2) -> bool {
                        return p1[1] < p2[1];
                    }
        );
        // O(N)
        int curr = INT_MIN;
        int ans = 0;
        for (const auto& pair : pairs) {
            const int a = pair[0];
            const int b = pair[1];
            if (curr < a) {
                curr = b;
                ++ans;
            }
        }

        return ans;
    }

public:
    int findLongestChain(std::vector<std::vector<int>>& pairs) {
        return solution2(pairs);
    }
};
