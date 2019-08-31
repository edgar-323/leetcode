/*
You're given strings J representing the types of stones that are jewels, and S representing the stones you have.  Each character in S is a type of stone you have.  You want to know how many of the stones you have are also jewels.
The letters in J are guaranteed distinct, and all characters in J and S are letters. Letters are case sensitive, so "a" is considered a different type of stone from "A".

Example 1:
Input: J = "aA", S = "aAAbbbb"
Output: 3

Example 2:
Input: J = "z", S = "ZZ"
Output: 0

Note:
S and J will consist of letters and have length at most 50.
The characters in J are distinct.
*/

class Solution {
private:
    static const int ALPH_SZ = 26;
    int index(const char& c) {
        if ('a' <= c and c <= 'z') {
            return int(c - 'a');
        }
        return ALPH_SZ + int(c - 'A');
    }

 	int solution1(const std::string& J, const std::string& S) {
        /* Time-Complexity:     O( M + N + ALPH_SZ )
         * Space-Complexity:    O(    ALPH_SZ      )
         * */
        std::vector<bool> set( 2*ALPH_SZ, false );
        const int M = J.size();
        const int N = S.size();
        for (int i = 0; i < M; ++i) {
            set[index( J[i] )] = true;
        }
        int JAS = 0;
        for (int i = 0; i < N; ++i) {
            if (set[index( S[i] )]) {
                ++JAS;
            }
        }
        return JAS;
    } 
public:
    int numJewelsInStones(string J, string S) {
        return solution1( J, S ); 
    }
};
