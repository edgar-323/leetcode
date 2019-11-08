/*
We have an array A of non-negative integers.

For every (contiguous) subarray B = [A[i], A[i+1], ..., A[j]] (with i <= j), we take the bitwise OR of all the elements in B, obtaining a result A[i] | A[i+1] | ... | A[j].

Return the number of possible results.  
(Results that occur more than once are only counted once in the final answer.)

Example 1:
Input: [0]
Output: 1
Explanation: 
There is only one possible result: 0.

Example 2:
Input: [1,1,2]
Output: 3
Explanation: 
The possible subarrays are [1], [1], [2], [1, 1], [1, 2], [1, 1, 2].
These yield the results 1, 1, 2, 1, 3, 3.
There are 3 unique values, so the answer is 3.

Example 3:
Input: [1,2,4]
Output: 6
Explanation: 
The possible results are 1, 2, 3, 4, 6, and 7.
 
Note:
1 <= A.length <= 50000
0 <= A[i] <= 10^9
*/

class Solution {
private:
    /***********************************************************************************************************/
    int get_bit_wise_OR(const std::vector<int>& A, const int begin, const int end) {
        int bitwise_OR = 0;
        for (int i = begin; i < end; ++i) {
            bitwise_OR |= A[i];
        }
        return bitwise_OR;
    }
	int solution1(const std::vector<int>& A) {
        /* Time-Complexity:     O(N^3)
         * Space-Complexity:    O( N )
         */
        const int N = A.size();
        auto unique_bitwise_ORs = std::unordered_set<int>();
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j <= N; ++j) {
                const int bitwise_OR = get_bit_wise_OR(A, i, j);
                if (not unique_bitwise_ORs.count(bitwise_OR)) {
                    unique_bitwise_ORs.insert(bitwise_OR);
                }
            }
        }
        return unique_bitwise_ORs.size();
	}
    /***********************************************************************************************************/
    int solution2(const std::vector<int>& A) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O( N )
         */

        const int N = A.size();
        auto unique_bitwise_ORs = std::unordered_set<int>();
        for (int i = 0; i < N; ++i) {
            int bitwise_xor = 0;
            for (int j = i; j < N; ++j) {
                bitwise_xor ^= A[j];
                if (not unique_bitwise_ORs.count(bitwise_xor)) {
                    unique_bitwise_ORs.insert(bitwise_xor);
                }
            }
        }
        
        return unique_bitwise_ORs.size();
    }
    /***********************************************************************************************************/
    int solution3(const std::vector<int>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         * 
         * 
         */
        auto ans = std::unordered_set<int>();
        auto curr = std::unordered_set<int>{0};
        for (const int x : A) {
            auto temp = std::unordered_set<int>();
            for (const int y : curr) {
                if (not temp.count(x|y)) {
                    temp.insert(x|y);
                }
            }
            curr = temp;
            if (not curr.count(x)) {
                curr.insert(x);
            }
            for (const int y : curr) {
                if (not ans.count(y)) {
                    ans.insert(y);
                }
            }
        }
        
        return ans.size();
    }
    /***********************************************************************************************************/
    int solution4(const std::vector<int>& A) {
        const int N = A.size();
        auto c = std::vector<int>();
        
        for (auto i = 0, st = 0, en = 0; i < N; ++i, st = en, en = c.size()) {
            c.push_back(A[i]);
            for (auto j = st; j < en; ++j) {
               if (c.back() != (c[j] | A[i])) {
                  c.push_back(c[j] | A[i]);
               }
            }
        }

        return std::unordered_set<int>(c.begin(), c.end());
    }
    /***********************************************************************************************************/
public:
    int subarrayBitwiseORs(vector<int>& A) {
        return solution3(A);     
    }
};
