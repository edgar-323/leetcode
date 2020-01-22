/*
Given a non-empty string, encode the string such that its encoded length is the shortest.
The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.
Note:
k will be a positive integer and encoded string will not be empty or have extra space.
You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.

Example 1:
Input: "aaa"
Output: "aaa"
Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.

Example 2:
Input: "aaaaa"
Output: "5[a]"
Explanation: "5[a]" is shorter than "aaaaa" by 1 character.

Example 3:
Input: "aaaaaaaaaa"
Output: "10[a]"
Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".

Example 4:
Input: "aabcaabcd"
Output: "2[aabc]d"
Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".

Example 5:
Input: "abbbabbbcabbbabbbc"
Output: "2[2[abbb]c]"
Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".
*/
class Solution {
private:
    typedef std::unordered_map<std::string,std::string> Cache;

    int repetitions(const std::string& T, const std::string& S) {
        const int M = T.size();
        const int N = S.size();
        int reps = 0;
        int i = 0;
        while (i < N and S.substr(i, M) == T) {
            ++reps;
            i += M;
        }
        return reps;
    }

    std::string recurse1(const std::string& S, Cache& cache) {
        if (S.size() < 5) {
            return S;
        } else if (cache.count(S)) {
            return cache[S];
        }
        const int N = S.size();
        auto result = S;

        for (int i = 0; i < N; ++i) {
            const auto T = S.substr(0, i+1);
            const auto num_repetitions = repetitions(T, S);
            for (int k = 1; k <= num_repetitions; ++k) {
                const auto P =  k == 1 ?
                                T + recurse1(S.substr(T.size()), cache):
                                std::to_string(k) + "[" + recurse1(T, cache) + "]" + recurse1(S.substr(k * T.size()), cache);
                if (P.size() < result.size()) {
                    result = P;
                }
            }
        }
        cache[S] = result;
        return result;
    }

    std::string solution1(const std::string& S) {
        auto cache = Cache();
        return recurse1(S, cache);
    }
public:
    string encode(string s) {
        return solution1(s);        
    }
};
