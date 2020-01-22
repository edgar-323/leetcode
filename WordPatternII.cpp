/*
Given a pattern and a string str, find if str follows the same pattern.
Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Example 1:
Input: pattern = "abab", str = "redblueredblue"
Output: true

Example 2:
Input: pattern = pattern = "aaaa", str = "asdasdasdasd"
Output: true

Example 3:
Input: pattern = "aabb", str = "xyzabcxzyabc"
Output: false

Notes:
You may assume both pattern and str contains only lowercase letters.
*/

class Solution {
private:
    static const int ALPH_SZ = 26;
    int M,N;
    std::array<int, ALPH_SZ> pattern_count;
    std::array<std::string, ALPH_SZ> map;
    std::unordered_set<std::string> used;

    int index(const char c) {
        return c - 'a';
    }

    bool recurse1(
            const int i,
            const int j,
            const std::string& pattern,
            const std::string& str,
            const int lower_bound) {
        if (i == M or j == N) {
            return i == M and j == N;
        }
        
        const auto c = pattern[i];
        auto& mapped_str = map[index(c)];
        
        if (not mapped_str.empty()) {
            return  str.substr(j, mapped_str.size()) == mapped_str and
                    recurse1(i + 1, j + mapped_str.size(), pattern, str, lower_bound); 
        }

        for (int len = 1; i + len <= N; ++len) {
            mapped_str += str[j + len - 1];

            if (used.count(mapped_str)) {
                continue;
            }

			// 1. str's length should be at least lowerBound long
            // 2. use len-1 here because we set the initial length to be 1
            // 3. we do the lowerBound checking here because the len is increasing
            //    no need to continue the loop if lowerBound test fails
            const auto new_lower_bound = lower_bound + pattern_count[index(c)]*(len - 1);
            
            if (new_lower_bound > str.size()) {
                break;
            }

            used.insert(mapped_str);
            if (recurse1(i + 1, j + len, pattern, str, new_lower_bound)) {
                return true;
            }
            used.erase(mapped_str);
        }

        mapped_str.clear();

        return false;
    }

	bool solution1(const std::string& pattern, const std::string& str) {
        std::fill(pattern_count.begin(), pattern_count.end(), 0);
        for (const auto& c : pattern) {
            ++pattern_count[index(c)];
        }
        M = pattern.size();
        N = str.size();
        return recurse1(0, 0, pattern, str, pattern.size());
    }
public:
    bool wordPatternMatch(string pattern, string str) {
		return solution1(pattern, str);
    }
};
