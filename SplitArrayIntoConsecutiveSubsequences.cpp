/*
Given an array nums sorted in ascending order, 
return true if and only if you can split it into 1 or more subsequences such that each subsequence consists of consecutive integers and has length at least 3.

Example 1:
Input: [1,2,3,3,4,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 
1, 2, 3
3, 4, 5

Example 2:
Input: [1,2,3,3,4,4,5,5]
Output: True
Explanation:
You can split them into two consecutive subsequences : 
1, 2, 3, 4, 5
3, 4, 5

Example 3:
Input: [1,2,3,4,4,5]
Output: False
 
Constraints:
1 <= nums.length <= 10000
*/
class Solution {
private:
    bool solution1(const std::vector<int>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *      Where:
         *          N = len(A)
         */
        // EXPLANATION:
        // count[v] will count the number of occurerences of v in A[] (note that this number will decrease)
        // in the second loop, for all v € A[], we want to make v be part of SOME consecttive subsequence of
        // length at least 3.
        // If we find that count[v] == 0, it means that for we have made all occurerences of v part of different
        // valid subsequences.
        // Otherwise, lets define:
        //      tail[v] = # of consectuive subsequences of legth 3 where v is the final (biggest) value.
        // Thus, we check if tails[v-1] exists (i.e., do valid subsequences with final value v-1 exist?)
        // If so, then we make a new subsequence where v is the final value by doing:
        //      --tails[v-1] // one less subsequence where v-1 is final value
        //      ++tail[v] // one more subsequence where v is final value
        // If not, then we check if we have at least one unnassigned occurrence of v+1 and at least one
        // unnassigned occurrence of v+2. (If so, then we create new subsequence: {v, v+1, v+2}).
        // We do this as follows:
        //      --count[v+2] // one v+2 occurrence has been assigned to a subsequence
        //      --count[v+1] // one v+1 occurrence has been assigned to a subsequence
        //      ++tails[v+2] // v+2 now is final value of some valid subsequence.
        // if not then we cannot asssign v to some valid subsequence
        // so we return false
        //
        auto count = std::unordered_map<int,int>();
        auto tails = std::unordered_map<int,int>();
        
        for (const auto& v : A) {
            ++count[v];
        }
        for (const auto& v : A) {
            if (not count[v]) {
                continue;
            }
            if (tails[v-1]) {
                --tails[v-1];
                ++tails[v];
            } else if (count[v+1] and count[v+2]) {
                --count[v+1];
                --count[v+2];
                ++tails[v+2];
            } else {
                return false;
            }
            --count[v]; // assigned v.
        }
        return true;
    }
public:
    bool isPossible(vector<int>& nums) {
        return solution1(nums);        
    }
};
