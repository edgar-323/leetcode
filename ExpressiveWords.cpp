/*
Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", "hi" -> "hiiii".  In these strings like "heeellooo", we have groups of adjacent letters that are all the same:  "h", "eee", "ll", "ooo".

For some given string S, a query word is stretchy if it can be made to be equal to S by any number of applications of the following extension operation: choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is 3 or more.

For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has size less than 3.  Also, we could do another extension like "ll" -> "lllll" to get "helllllooo".  If S = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: query = "hello" -> "hellooo" -> "helllllooo" = S.

Given a list of query words, return the number of words that are stretchy. 

Example:
Input: 
S = "heeellooo"
words = ["hello", "hi", "helo"]
Output: 1
Explanation: 
We can extend "e" and "o" in the word "hello" to get "heeellooo".
We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.

Notes:
0 <= len(S) <= 100.
0 <= len(words) <= 100.
0 <= len(words[i]) <= 100.
S and all words in words consist only of lowercase letters
*/
class Solution {
private:
    bool are_sketchy(const std::string& S, const std::string& T) {
        const int M = S.size();
        const int N = T.size();

        int l1 = 0;
        int r1 = 0;
        int l2 = 0;
        int r2 = 0;

        while (r1 < M or r2 < N) {
            if (r1 == M or r2 == N or S[l1] != T[l2]) {
                return false;
            }
            while (r1 < M and S[l1] == S[r1]) {
                ++r1;
            }
            while (r2 < N and T[l2] == T[r2]) {
                ++r2;
            }
            const auto m = r1 - l1;
            const auto n = r2 - l2;
            if (m < n or (m < 3 and n != m)) {
                return false;
            } 
            l1 = r1;
            l2 = r2;
        }

        return true;
    }

    int solution1(const std::string& S, const std::vector<std::string>& words) {
        /* Time-Complexity:     O(|S| * W)
         * Space-Complexity:    O(1)
         *      Where:
         *          W = len(words)
         */
        const int M = S.size();
        int sketchy_words = 0;
        for (const auto& word : words) {
            if (are_sketchy(S, word)) {
                ++sketchy_words;
            }
        }
        return sketchy_words;
    }
public:
    int expressiveWords(string S, vector<string>& words) {
        return solution1(S, words);        
    }
};
