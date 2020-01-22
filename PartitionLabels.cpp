/*
A string S of lowercase letters is given. 
We want to partition this string into as many parts as possible so that each letter appears in at most one part, 
and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.

Note:
    S will have length in range [1, 500].
    S will consist of lowercase letters ('a' to 'z') only.
*/
class Solution {
private:
    static const int ALPH_SZ = 26;

    int index(const char c) {
        return c - 'a';
    }

    std::vector<int> solution1(const std::string& S) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(ALPH_SZ)
         */

        // Thoughts: 
        // How to define a partition?
        // Well, a partition is a window (i.e., a substr of S).
        // Thus, it has (left, right) pointers.
        // Suppose left = i and right = j?
        // How do we know if (left, right) defines a partition ?
        // This occurrs if all characters in S[left:right] do not
        // appear in S[right+1:N].
        // This means that everytime we increment `right`,
        // we have to scan S[left:right] and check that no character 
        // appears in S[right+1:N]. 
        // This solution can run in O(N^2) in the worst case.
        // Is there a better solution?
        // Consider c = S[i], for some i € {0,...,N-1}.
        // Let's define:
        //      last_pos[c] = index of last_occurrence of c in S. 
        //
        // Now we initialize left = right = 0.
        // Let P = last_occurrence[S[0]].
        // We do:
        //      i = 0; 
        //          

        const int N = S.size();
        auto last_pos = std::vector<int>(ALPH_SZ, -1);
        for (int i = 0; i < N; ++i) {
            last_pos[index(S[i])] = i;
        }
        auto partition_labels = std::vector<int>();

        int left = 0;
        int right = 0;
        int P = -1; 
        
        while (right < N) {
            P = std::max(P, last_pos[index(S[right++])]);

            if (right > P) {
                partition_labels.push_back(right - left); 
                left = right;
            }
        } 
        return partition_labels;
    }

public:
    vector<int> partitionLabels(string S) {
        return solution1(S);
    }
};
