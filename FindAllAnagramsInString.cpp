/*
Given a std::string s and a non-empty std::string p, find all the start indices of p's anagrams in s.
Strings consists of lowercase English letters only and the length of both std::strings s and p will not be larger than 20,100.
The order of output does not matter.

Example 1:
Input:
s: "cbaebabacd" p: "abc"
Output:
[0, 6]
Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The sudstring with start index = 6 is "bac", which is an anagram of "abc".

Example 2:
Input:
s: "abab" p: "ab"
Output:
[0, 1, 2]
Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
*/

ass Solution {
private:
    /*********************************************************/
    std::vector<int> solution1(std::string& s, std::string& p) {
        std::vector<int> indices;
        const int M = p.size();
        const int N = s.size();
        const int lim = (N+1) - M;
        if (N == 0 || M == 0) {
            return indices;
        }
        std::string gram = p;
        std::sort(gram.begin(), gram.end());
        for (int i = 0; i < lim; ++i) {
            std::string str = s.substr(i, M);
            std::sort(str.begin(), str.end());
            if (gram.compare(str) == 0) {
                indices.push_back(i);
            }
        }
        return indices;
    }
    /*********************************************************/
    std::vector<int> solution2(std::string& s, std::string& p) {
        if (s.empty()) {
            return {};
        }
        const int S = s.size();
        const int P = p.size();
        std::vector<int> results;
        if (S == 0 || P == 0) {
            return results;
        }
        std::vector<int> sCountChar(128, 0), pCountChar(128, 0);
        // compute first window. 
        // pCountChar remains static after this.
        for (int i = 0; i < P; ++i) {
            ++sCountChar[s[i]]; 
            ++pCountChar[p[i]];
        }
        // check if first window is permutation of p.
        if (sCountChar == pCountChar) {
            results.push_back(0);
        }
        for (int i = P; i < S; ++i) {
            // Add New Char <--> increment right ptr
            ++sCountChar[s[i]];
            // Remove Oldest Char <--> increment left pointer
            --sCountChar[s[i-p.size()]];
            // check if current window is a permutation of std::string p
            if (sCountChar == pCountChar) {
                results.push_back(i-P+1);
            }
        }
        return results;
    }
    /*********************************************************/ 
public:
    std::vector<int> findAnagrams(std::string s, std::string p) {
        return solution2(s, p);
    }
};
