/*
We have two integer sequences A and B of the same non-zero length.
We are allowed to swap elements A[i] and B[i].  
Note that both elements are in the same index position in their respective sequences.
At the end of some number of swaps, A and B are both strictly increasing.  
(A sequence is strictly increasing if and only if A[0] < A[1] < A[2] < ... < A[A.length - 1].)
Given A and B, return the minimum number of swaps to make both sequences strictly increasing.  
It is guaranteed that the given input always makes it possible.

Example:
Input: A = [1,3,5,4], B = [1,2,3,7]
Output: 1
Explanation: 
Swap A[3] and B[3].  Then the sequences are:
A = [1, 3, 5, 7] and B = [1, 2, 3, 4]
which are both strictly increasing.

Note:
A, B are arrays with the same length, and that length will be in the range [1, 1000].
A[i], B[i] are integer values in the range [0, 2000].
*/

class Solution {
private:
	int solution1(const std::vector<int>& A, const std::vector<int>& B) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         */
	    /* Explanation:	
         *
        */
		const int N = A.size();
        
        auto no_swap = std::vector<int>(N, N);
        auto swap = std::vector<int>(N, N);
        
        no_swap[0] = 0;
        swap[0] = 1;

        for (int i = 1; i < N; ++i) {
            if (A[i] > A[i-1] and B[i] > B[i-1] and A[i] > B[i-1] and B[i] > A[i-1]) {
                // for no_swap[i], we can choose whether or not we swapped at index i-1 (pick better of the two)
                no_swap[i] = std::min(no_swap[i-1], swap[i-1]);
                // if we are going to swap at index i, then we HAVE to add 1 to swap[i] but we pick best choice from no_swap[i-1] and swap[i]
                swap[i] = std::min(no_swap[i-1], swap[i-1]) + 1;
            } else if (A[i] > A[i-1] and B[i] > B[i-1]) {
                no_swap[i] = no_swap[i-1];
                swap[i] = swap[i-1] + 1;
            } else {
                no_swap[i] = swap[i-1];
                swap[i] = no_swap[i-1] + 1;
            }
        }

        return std::min(swap[N - 1], not_swap[N - 1]);
	}
public:
    int minSwap(vector<int>& A, vector<int>& B) {
  		return solution1(A, B);      
    }
};
