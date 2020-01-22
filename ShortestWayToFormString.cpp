/*
From any string, we can form a subsequence of that string by deleting some number of characters (possibly no deletions).
Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target.
If the task is impossible, return -1.

Example 1:
Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".

Example 2:
Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.

Example 3:
Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".

Constraints:
Both the source and target strings consist of only lowercase English letters from "a"-"z".
The lengths of source and target string are between 1 and 1000.
*/

class Solution {
private:
    static const int ALPH_SZ = 26;
    int index(const char c) {
        return int(c - 'a');
    }
    /************************************************************************************************************/
    int solution3(const std::string& src, const std::string& target) {
        /* Time-Complexity:     O( ALPH_SZ*M + N)
         * Space-Complexity:    O(   ALPH_SZ*M  )
         * */
        /* Motivation:
         * Notice that in solution2, the cost of finding a match in `src` for each character 
         * in `target` was O(lg(M)). In this solution we see how we can reduce that cost to O(1).
         * First, we see that in solution2 we do a binary search for `i` in `indices`.
         * What if instead, the size of `indices` is `M` (for all indices, so that `indices[0]` 
         * always exists) and what if we can have `indices[i]` tell us what the value of `i` should
         * now be?
         * We can indeed accomplish this by ...*/
        const int M = src.size();
        const int N = target.size();

        std::vector<std::vector<int>> map( ALPH_SZ, std::vector<int>( M, 0 ) );
        for (int i = 0; i < M; ++i) {
            map[index( src[i] )][i] = i+1;
        }
        for (int i = 0; i < ALPH_SZ; ++i) {
            for (int j = M-1, pre = 0; j >= 0; --j) {
                if ( !map[i][j] ) {
                    map[i][j] = pre;
                } else {
                    pre = map[i][j];
                }
            }
        }

        for (int c = 0; c < ALPH_SZ; ++c) {
            for (int i = M-1, pre = 0; i >= 0; --i) {
                if (not map[c][i]) {
                    map[c][i] = pre;
                } else {
                    pre = map[c][i];
                }
            }
        }

        int result = 0;
        int i = 0;
        for (int j = 0; j < N; ++j) {
            if (i == M) {
                i = 0;
                ++result;
            }
            if ( !map[index( target[j] )][0] ) {
                return -1;
            }
            i = map[index( target[j] )][i];
            if ( !i ) {
                // we didnt find target[j] but we know it exists in src at index < i.
                // we will search src again.
                ++result;
                --j;
            }
        }

        return result + 1;
    }
    /************************************************************************************************************/
    int binary_search2(const std::vector<int>& indices, int i) {
        // Assumes indices is sorted.
        // Returns first value (plus one) of indices that is greater than or equal to `i`.
        const int K = indices.size();
        int l = 0;
        int r = K;
        while (l <= r) {
            int mid = (l+r) / 2;
            if (mid == K) {
                break;
            }
            int index = indices[mid];
            if (index < i) {
                l = l == mid ? l+1 : mid;
            } else {
                // We know that index >= i but we have to make sure
                // that `index` is the earliest value in `indices`
                // s.t. `index >= i`. 
                if (mid == 0 or indices[mid-1] < i) {
                    // We found a match, so we at `index` so `i` should
                    // now be set to `index+1` because we found a match 
                    // for `target[j]` at `src[index]`. 
                    // Now we continue to match 'target[j+1:M)` from
                    // `src[index+1:N)`.
                    return index + 1;
                }
                r = r == mid ? r-1 : mid;    
            }
        }

        return -1;
    }
    int solution2(const std::string& src, const std::string& target) {
        /* Time-Complexity:     O( M + N*lg(M) ) 
         * Space-Complexity:    O(      1      )
         * */ 
        /* Motivation:
         *  Notice that in solution1, we (potentially) search all of
         *  `src` for every character of `target`.
         *  This makes gives us an runtime of O(M*N)
         *  But if we remember the positions of the characters of `src`
         *  and if we can have an efficent way of searching for certain
         *  inidices, then we can reduce runtime.
         *  We do this by mapping chars of `src` to list of indices
         *  where they occur and the doing binary search on those lists
         *  when we need to know by how much to increment `i`
         *  */
        const int M = src.size();
        const int N = target.size();
        
        // map from char c of `src` to indices of `src` where c appears.
        std::vector<std::vector<int>> map( ALPH_SZ, std::vector<int>() );
        
        // Populate map.
        // Notice that for each index list in `map`, the indices themselves
        // will be sorted due to how we are populating it.
        // This makes it perfect for binary search.
        for (size_t i = 0; i < M; ++i) {
            map[index( src[i] )].push_back( i );
        }
        
        int result = 0;
        int i = 0;
        for (size_t j = 0; j < N; ++j) {
            const char& t = target[j];

            // grab indices of `src` where `t` appears.
            const auto& indices = map[index( t )];
            if (indices.empty()) {
                // character `t` does not exist in `src`, so there is no
                // way to form `target` from subsequences of `src`.
                return -1;
            }
            // find next index of i 
            i = binary_search2( indices, i );
            if (i < 0) {
                // We know that `t` exists in 'src' but it occurs at an
                // earlier index than `i`, so in order to match `t`, we
                // need to research `src` from the beginning (i.e., we 
                // need to reset `i` to 0.)
                // Equivalently, this implies that we require an additional
                // subsquence of `src` to complete `target`, so we increment
                // `result`.
                // Also we decrement `j` (current index of `target`) because
                // we werent able to successfully match it in this iteration
                // so we need to match it in the next iteration.
                ++result;
                i = 0;
                --j;
            }
        }
        // We add 1 to `result` because although we completely matched
        // `target`, we never accounted for the last subsequence of `src`
        // (because we didn't enter the `if (i < 0)` clause within the
        // for-loop because we successfully matched the last character of
        // `target` and thus `binary_search2` returned a non-negative value.
        return result + 1;
    }
    /************************************************************************************************************/
    int recurse1(const std::string& src, const std::string& target, const size_t k) {
        // so far, we have found target[0:k), we need to complete the rest.
        const size_t N = target.size();
        size_t j = k;
        if (j >= N) {
            // target is complete. We did not need any additonal subsequences of src.
            return 0;
        }
        for (auto c : src) {
            if (c == target[j]) {
                ++j;
                if (j == N) {
                    // Success: We completed target[k:N) with one additional subsequence of src
                    return 1;
                }
            }
        }
        if (j == k) {
            // We did not make progress in finding target[k:N)
            // there is no point in making another recursive call
            // since it will also fail.
            return -1;
        }
        int next = recurse1(src, target, j);
        if (next < 0) {
            // the next recursive call(s) couldn't find target[j:N)
            return -1;
        }
        // success
        return 1 + next;
    }
	int solution1(const std::string& src, const std::string& target) {
	    /* Time-Complexity:     O( M*N )
         * Space-Complexity:    O(  M  )
         *  where M = size( src ) and N = size( target )
         * */
        return recurse1(src, target, 0);	
	}
    /************************************************************************************************************/
public:
    int shortestWay(string source, string target) {
   		return solution3( source, target );
    }
};
