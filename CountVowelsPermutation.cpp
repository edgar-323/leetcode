/*
Given an integer n, your task is to count how many strings of length n can be formed under the following rules:

Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
Each vowel 'a' may only be followed by an 'e'.
Each vowel 'e' may only be followed by an 'a' or an 'i'.
Each vowel 'i' may not be followed by another 'i'.
Each vowel 'o' may only be followed by an 'i' or a 'u'.
Each vowel 'u' may only be followed by an 'a'.
Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: n = 1
Output: 5
Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
Example 2:

Input: n = 2
Output: 10
Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
Example 3: 

Input: n = 5
Output: 68
 

Constraints:

1 <= n <= 2 * 10^4
*/

class Solution {
private:
    static const int MOD_VAL = 1e9 + 7;
    static const int ALPH_SZ = 5; // ALPHABET = {'a', 'e', 'i', 'o', 'u'} => Size 5
    
    int index(const char c) {
        switch (c) {
            case 'a':   return 0;
            case 'e':   return 1;
            case 'i':   return 2;
            case 'o':   return 3;
            case 'u':   return 4;
            default:    return -1;
        }
    }

    const std::vector<std::vector<char>> adj_list 
                                {
                                    { index('e') },
                                    { index('a'), index('i') },
                                    { index('a'), index('e'), index('o'), index('u') },
                                    { index('i'), index('u') },
                                    { index('a') }
                                };

	int solution1(const int N) {
        /* Time-Complexity:     O((V+E) * N)
         * Space-Complexity:    O((V+E) * N)
         *      Where V = ALPH_SZ and E = # edges in adj_list
         *
         * Since ALPH_SZ is constant, we have an O(N) time and space complexity.
         */
		/*  EXPLANATION:	

            Alphabet:
            [“a”, “e”, “i”, “o”, “u”]

            Possible Transitions:
            * “a” -> [“e”]
            * “e” -> [“a”, “i”]
            * “i” ->  [“a”, “e”, “o”, “u”]
            * “o” -> [“i”, “u”]
            * “u” -> [“a”]


            Possible Solution1:
            Do a graph traversal in order to produce all possible permutations.
            Nodes will be represented by two parameters:
            * Vowel
            * Length of Permutation
            Our first nodes will be:
            * (“a”, 1)
            * (“e”, 1)
            * (“i”, 1)
            * (“o”, 1)
            * (“u”, 1)
            We can either initiate a Depth First Search or a Breadth First Search.
            In either case we initiate a counter variable “count” at zero.
            Whenever our traversal algorithm reaches a node with length equal to N, it increments “count” and ceases to transition to other neighbor nodes.
            Otherwise it transitions to other neighbor nodes.

            RunTime
            Let T be equal to the total number of possible permutations (I.e., T is the number we are looking for).
            Notice that our graph traversal increments “count” T times.
            So we have a lower bound of T for our runtime.
            Producing each permutation takes at most N operations (N edge transitions) so we have an upper bound of O(T*N)
            This is indeed unacceptable since the problem description states that the answer (T) may be so big that they want us to return it modulo (10^9  + 7).


            Possible Solution2:
            What if we tried to take a more recursive approach based on the current index, which will range from 0 to N-1.
            We will pair this index with a current letter.
            For example, say we are currently looking at (“i”, 0) and N == 2.
            Then conceptually this will map to “i*”.
            How many transitions does “i” have? 
            Four.
            So we will have:
            [“ia”, “ie”, “io”, “iu”]
            So, our recursive formula can look something like:
            DP[“i”, 0] = DP[“a”, 1] + DP[“e”, 1] + DP[“o”, 1] + DP[“u”, 1]

            With base case:
            DP[*, j] = 0 for j >= N

            So how can we expand the above idea and what will be the resultant runtimes?

            It appears that in general:
            DP[u, i] = SUM{ DP[v, i+1] }
             For all edges (transitions) u->v that exist.

            The answer we are interested in is:
            SUM{ DP[c, 0] }, for all c in the alphabet.

            Let’s analyze the runtime complexity.
            Notice that at most, there can be ALPH_SZ (in our case 5) transitions.
            And “i” can range between 0 and N.
            Therefore a bottom-up (or memorized) solution should yield a runtime complexity of O(ALPH_SZ * N).

            Since, in our case, ALPH_SZ is a constant, our runtime would be O(N).

		*/

        auto DP = std::vector<std::vector<int>>(ALPH_SZ, std::vector<int>(N+1, 0));
        for (int c = 0; c < ALPH_SZ; ++c) {
            DP[c][N] = 1;
        }
        for (int i = N-1; i; --i) {
            for (int node = 0; node < ALPH_SZ; ++node) {
                for (int neighbor : adj_list[node]) {
                    DP[node][i] = (DP[node][i] + DP[neighbor][i+1]) % MOD_VAL;
                }
            }
        }
        int permutations = 0;
        for (int node = 0; node < ALPH_SZ; ++node) {
            permutations = (permutations + DP[node][1]) % MOD_VAL;
        }

        return permutations;
	}
public:
    int countVowelPermutation(int n) {
  		return solution1(n);      
    }
};
