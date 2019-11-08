/*
Given an array A of integers, return the length of the longest arithmetic subsequence in A.
Recall that a subsequence of A is a list A[i_1], A[i_2], ..., A[i_k] with 0 <= i_1 < i_2 < ... < i_k <= A.length - 1, 
and that a sequence B is arithmetic if B[i+1] - B[i] are all the same value (for 0 <= i < B.length - 1).

Example 1:
Input: [3,6,9,12]
Output: 4
Explanation:
The whole array is an arithmetic sequence with steps of length = 3.

Example 2:
Input: [9,4,7,2,10]
Output: 3
Explanation:
The longest arithmetic subsequence is [4,7,10].

Example 3:
Input: [20,1,15,3,10,5,8]
Output: 4
Explanation: 
The longest arithmetic subsequence is [20,15,10,5].
 
Note:
2 <= A.length <= 2000
0 <= A[i] <= 10000
*/

class Solution {
private:
    int N;
    int longest_AS;
    
    /********************************************************************************/
    bool is_arithmetic_sqn1(const std::vector<int>& sqn) {
        const int K = sqn.size();
        if (K < 2) {
            return false;
        }

        for (int i = 1; i < K; ++i) {
            if (sqn[i] - sqn[i-1] != sqn[1] - sqn[0]) {
                return false;
            }
        }

        return true;
    }

    void recurse1(const std::vector<int>& A, const int index, std::vector<int> curr) {
        if (index >= N) {
            if (is_arithmetic_sqn1( curr ) and
                curr.size() > longest_AS) {
                longest_AS = curr.size();
            }
            return;
        }

        recurse1( A, index+1, curr );
        curr.push_back( A[index] );
        recurse1( A, index+1, curr ); 
    }

    int solution1(const std::vector<int>& A) {
        // IDEA:
        // Produce all possible subsequences
        // Take length of those that are Arithmetic Subsequences
        // Return longest length.
        N = A.size();
        longest_AS = 0;
        std::vector<int> curr;
        recurse1(A, 0, curr);

        return longest_AS;
    }
    /********************************************************************************/
    int solution2(const std::vector<int>& A) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  N  )
         * */
        // Can we solve this problem similary to how we solve "Longest Increasing SubSequences" ?
        // Basically for all indices `i € [0,N)`, we maintain a hashmap `map[i]` that maps
        // a common difference `diff` to the maximum length of all sequences that have common 
        // difference `diff` and end at `i`.
        //
        // When considering two elements `(A[i], A[j]), for i > j` with common difference `diff`:
        // We first check that maximum length of sequence with common difference `diff` whcih ends
        // at index `j`
        // Let's call this maximum lenght `len`.
        // If `len` is zero (i.e., `diff` does not exist in `map[j]`) then we set `len` to one
        
        N = A.size();
        longest_AS = 0;

        std::vector<std::unordered_map<int, int>> map( N );

        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                const int diff  = A[i] - A[j];
                const int len   = map[j].count(diff) ? map[j][diff] : 1;
                auto iter       = map[i].find(diff);
                if (it == map[i].end()) {
                    map[i].insert( std::make_pair( diff, 0 ) );
                    iter = map[i].find( diff );
                }
                iter->second    = std::max( iter->second, len + 1 );
                longest_AS      = std::max( longest_AS, it->second ); 
            }
        }

        return longest_AS;
    }
    /********************************************************************************/
public:
    int longestArithSeqLength(vector<int>& A) {
  		return solution2( A );      
    }
};
