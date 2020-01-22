/*
We are given N different types of stickers. 
Each sticker has a lowercase English word on it.
You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them.
You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
What is the minimum number of stickers that you need to spell out the target? 
If the task is impossible, return -1.

Example 1:
Input:
["with", "example", "science"], "thehat"
Output:
3
Explanation:
We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearrange the letters of those stickers, we can form the target "thehat".
Also, this is the minimum number of stickers necessary to form the target string.

Example 2:
Input:
["notice", "possible"], "basicbasic"
Output:
-1
Explanation:
We can't form the target "basicbasic" from cutting letters from the given stickers.
Note:

stickers has length in the range [1, 50].
stickers consists of lowercase English words (without apostrophes).
target has length in the range [1, 15], and consists of lowercase English letters.
In all test cases, all words were chosen randomly from the 1000 most common US English words, and the target was chosen as a concatenation of two random words.
The time limit may be more challenging than usual. It is expected that a 50 sticker test case can be solved within 35ms on average.
*/


class Solution {
private:
    static const int ALPH_SZ = 26;
    int N;

    int index(const char c) {
        return c - 'a';
    }

    char to_char(const int i) {
        return i + 'a';
    }

    int recurse1(const std::string& target, const std::vector<std::vector<int>>& count, std::unordered_map<std::string,int>& cache) {
        if (cache.count(target)) {
            return cache[target];
        }
        int min_stickers = INT_MAX;
        auto target_count = std::vector<int>(ALPH_SZ, 0);
        for (const auto& c : target) {
            ++target_count[index(c)];
        }

        for (int i = 0; i < N; ++i) {
            if (not count[i][index(target[0])]) {
                continue;
            }
            auto new_target = std::string("");
            for (int c = 0; c < ALPH_SZ; ++c) {
                const auto chars_still_needed = target_count[c] - count[i][c];
                if (chars_still_needed > 0) {
                    new_target += std::string(chars_still_needed, to_char(c));
                }
            }
			const auto stickers_needed = recurse1(new_target, count, cache);
            if (stickers_needed >= 0) {
                min_stickers = std::min( min_stickers, 1 + stickers_needed );
            }
        }

        return cache[target] = (min_stickers == INT_MAX ? -1 : min_stickers);
    }

	int solution1(const std::vector<std::string>& stickers, const std::string& target) {
        N = stickers.size();
        auto count = std::vector<std::vector<int>>(N, std::vector<int>(ALPH_SZ, 0));
        for (int i = 0; i < N; ++i) {
            for (const auto& c : stickers[i]) {
                ++count[i][index(c)];
            }
        }
        auto cache = std::unordered_map<std::string,int>();
        cache[""] = 0;
        return recurse1(target, count, cache);
	}
public:
    int minStickers(vector<string>& stickers, string target) {
  		return solution1(stickers, target);      
    }
};
