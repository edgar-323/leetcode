/*
Given a list of words, each word consists of English lowercase letters.

Let's say word1 is a predecessor of word2 if and only if we can add exactly one letter anywhere in word1 to make it equal to word2.  
For example, "abc" is a predecessor of "abac".

A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.

Return the longest possible length of a word chain with words chosen from the given list of words.

Example 1:

Input: ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: one of the longest word chain is "a","ba","bda","bdca".
 

Note:

1 <= words.length <= 1000
1 <= words[i].length <= 16
words[i] only consists of English lowercase letters.
*/

#include <iostream>
#include <string>
#include <vector>

class Solution {
private:
    static const int ALPH_SZ = 26;
    static const int MAX_WORD_SZ = 17;    
    int index(const char c) {
        return int(c - 'a');
    }
    
    typedef std::vector<int> Anagram; 
    typedef std::pair<Anagram, int> Pair;
    typedef std::vector<Pair> Bucket;
    
    bool is_predecessor(const Anagram& prev_anagram, Anagram& curr_anagram) {
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (not curr_anagram[i]) {
                continue;
            }
            --curr_anagram[i];
            bool are_equal = prev_anagram == curr_anagram;
            ++curr_anagram[i];
            if (are_equal) {
                return true;
            }
        }
        return false;
    }


	int solution1(const std::vector<std::string>& words) {
	    const int N = words.size();
        if (not N) {
            return 0;
        }
         
        auto buckets = std::vector<Bucket>(MAX_WORD_SZ);

        for (const auto& word : words) {
            auto anagram = std::vector<int>(ALPH_SZ, 0);
            for (const auto& c : word) {
                anagram[index(c)]++;
            }
            buckets[word.size()].push_back(Pair(anagram, 1));
        }
        
        int longest_chain = 0;

        for (int sz = 1; sz < MAX_WORD_SZ; ++sz) {
            Bucket& curr_bucket = buckets[sz];
            const Bucket& prev_bucket = buckets[sz-1];
            for (Pair& curr_pair : curr_bucket) {
                for (const Pair& prev_pair : prev_bucket) {
                    if (is_predecessor(prev_pair.first, curr_pair.first)) {
                        curr_pair.second = std::max(curr_pair.second, prev_pair.second + 1);
                    }
                } 
                longest_chain = std::max(longest_chain, curr_pair.second);
            }
        }
        
        return longest_chain; 
	}
public:
    int longestStrChain(std::vector<std::string>& words) {
  		return solution1(words);
    }
};

int main() {
    auto words = std::vector<std::string>{ "a","b","ba","bca","bda","bdca" };
    std::cout << Solution().longestStrChain(words) << std::endl;

    return EXIT_SUCCESS;
}
