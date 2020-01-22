/*
You have a number of envelopes with widths and heights given as a pair of integers (w, h). 
One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Note:
Rotation is not allowed.

Example:
Input: [[5,4],[6,4],[6,7],[2,3]]
Output: 3 
Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
*/

class Solution {
private:
    int ceil_element(const std::vector<int>& DP, int left, int right, const int key) {
        while (right - left > 1) {
            const int mid = left + (right - left) / 2;
            if (DP[mid] >= key) {
                right = mid;
            } else {
                left = mid;
            }
        }

        return right;
    }

    void sort_envelopes(std::vector<std::vector<int>>& A) {
        std::sort(A.begin(), A.end(),
                    [] (const std::vector<int>& env1, const std::vector<int>& env2) -> bool
                    {
                        return  env1[0] == env2[0] ?
                                env1[1] > env2[1]:
                                env1[0] < env2[0];
                    });
    }

	int solution1(std::vector<std::vector<int>>& A) {
        /* Time-Complexity:     O(N * log(N))
         * Space-Complexity:    O(N)
         */
        /* Explanation:
         * Sort first by width, then within envelopes of same width,
         * sort in reverse by height.
         * This allows us to transform this problem into LIS based on
         * heights of the envelopes.
         */

        if (A.empty()) {
            return 0;
        }
        sort_envelopes(A);
        const int N = A.size(); 
        auto DP = std::vector<int>(N, 0); 
        int length = 1;

        DP[0] = A[0][1]; 
        for (int i = 1; i < N; ++i) {
            if (A[i][1] < DP[0]) {
                DP[0] = A[i][1];
            } else if (A[i][1] > DP[length-1]) {
                DP[length++] = A[i][1];
            } else {
                DP[ceil_element(DP, -1, length-1, A[i][1])] = A[i][1];
            }
        }

        return length;
	}

    int solution2(std::vector<std::vector<int>>& A) {
        if (A.empty()) {
            return 0;
        }
        const int N = A.size();
        sort_envelopes(A);
        auto DP = std::vector<int>();
        DP.reserve(N);
        DP.push_back(A.front()[1]);
        for (int i = 0; i < N; ++i) {
            const auto val = A[i][1];
            const auto it = std::lower_bound( DP.begin(), DP.end(), val ); 
            if (it == DP.end()) {
                DP.push_back( val );
            } else if (val < *it) {
                *it = val;
            }
        }

        return DP.size();
    }
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
  		return solution2(envelopes);      
    }
};
