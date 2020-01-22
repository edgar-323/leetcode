/*
For some fixed N, an array A is beautiful if it is a permutation of the integers 1, 2, ..., N, such that:

For every i < j, there is no k with i < k < j such that A[k] * 2 = A[i] + A[j].

Given N, return any beautiful array A.  (It is guaranteed that one exists.)
*/

/* ANSWER/EXPLANATION FROM LEET-CODER lee25

Intuition:

Try to divide and conquer,
so we have left part, right part.

One way is to divide into [1, N / 2] and [N / 2 + 1, N].
But it will cause problems when we merge them.

Another way is to divide into odds part and evens part.
So there is no k with A[k] * 2 = odd + even

I brute force all permutations when N = 5:
20 beautiful array found,
only 4 don't fit odd + even pattern:
[2, 1, 4, 5, 3]
[3, 1, 2, 5, 4]
[3, 5, 4, 1, 2]
[4, 5, 2, 1, 3]


Beautiful Array Properties

Saying that an array is beautiful,
there is no i < k < j,
such that A[k] * 2 = A[i] + A[j]

Apply these 3 following changes a beautiful array,
we can get a new beautiful array


1. Deletion
Easy to prove.

2. Addition
If we have A[k] * 2 != A[i] + A[j],
(A[k] + x) * 2 = A[k] * 2 + 2x != A[i] + A[j] + 2x = (A[i] + x) + (A[j] + x)

E.g: [1,3,2] + 1 = [2,4,3].

3. Multiplication
If we have A[k] * 2 != A[i] + A[j],
for any x != 0,
(A[k] * x) * 2 = A[k] * 2 * x != (A[i] + A[j]) * x = (A[i] * x) + (A[j] * x)

E.g: [1,3,2] * 2 = [2,6,4]


Explanation

With the observations above, we can easily construct any beautiful array.
Assume we have a beautiful array A with length N

A1 = A * 2 - 1 is beautiful with only odds from 1 to N * 2 -1
A2 = A * 2 is beautiful with only even from 2 to N * 2
B = A1 + A2 beautiful array with length N * 2

E.g:

A = [2, 1, 4, 5, 3]
A1 = [3, 1, 7, 9, 5]
A2 = [4, 2, 8, 10, 6]
B = A1 + A2 = [3, 1, 7, 9, 5, 4, 2, 8, 10, 6]
*/

class Solution {
private:
	std::vector<int> solution1(const int N) {
        /* Time-Complexity:     O( N ) 
         * Space-Complexity:    O( N )
         * */
  		std::vector<int> results { 1 };
        
        while (results.size() < N) {
            auto tmp = std::vector<int>();
            int k;
            for (auto i : results) {
                // ODDS
                k = i * 2 - 1;
                if (k <= N) {
                    tmp.push_back( k );
                }
            }
            for (auto i : results) {
                // EVENS
                k = i * 2;
                if (k <= N) {
                    tmp.push_back( k );
                }
            }
            results = tmp;
        }

        return results;
	}

    void recurse2(const int left, const int right, std::vector<int>& S) {
        if (right - left <= 1) {
            return;
        }
        auto odds = std::vector<int>();
        auto evens = std::vector<int>();
        for (int i = left; i <= right; ++i) {
            if (((i+1) - left) & 1) {
                odds.push_back(S[i]);
            } else {
                evens.push_back(S[i]);
            }
        }
        std::copy(odds.begin(),     odds.end(),     S.begin() + left);
        std::copy(evens.begin(),    evens.end(),    S.begin() + left + odds.size());
        
        const auto mid = left + (right - left)/2;
        recurse2(left, mid, S);
        recurse2(mid+1, right, S);
    }

    std::vector<int> solution2(const int N) {
        /* Time-Complexity:     O( N*log(N) )
         * Space-Complexity:    O(    N     )
         */
        // Explanation:
        // We want to produce an arrray 
        //      A[] = perm({1,...,N}) 
        // s.t. for all i < k < j, we have 
        //      2*A[k] != A[i] + A[j]
        // which is equivalent to
        //      A[k] - A[i] != A[j] - A[k]
        // So this tells us that, for all k (where i < k < j), 
        // the delta between A[k] and A[i] cannot be equal to the delta between A[j] and A[k].
        // Okay, let 
        //      di = A[k] - A[i]
        //      dj = A[j] - A[k]
        // It would be difficult to compute all possible delta and avoid an EXACT diff.
        // Instead lets concentrate on the parities of the deltas.
        // If di is odd and dj is even (or vice-versa) then there is no way for them to ever be equal.
        // How can we ensure that we build A[] in this manner?
        // Suppose we let A[] = {1,...,N} (in that exact order).
        auto S = std::vector<int>(N);
        for (int i = 0; i < N; ++i) {
            S[i] = i+1;
        }
        recurse2(0, N-1, S);

        return S;
    }
public:
    vector<int> beautifulArray(int N) {
        return solution2( N ); 
    }
};
