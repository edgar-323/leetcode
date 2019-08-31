/*
A string S represents a list of words.
Each letter in the word has 1 or more options.  If there is one option, the letter is represented as is.  If there is more than one option, then curly braces delimit the options.  For example, "{a,b,c}" represents options ["a", "b", "c"].

For example, "{a,b,c}d{e,f}" represents the list ["ade", "adf", "bde", "bdf", "cde", "cdf"].

Return all words that can be formed in this manner, in lexicographical order.

Example 1:
Input: "{a,b}c{d,e}f"
Output: ["acdf","acef","bcdf","bcef"]

Example 2:
Input: "abcd"
Output: ["abcd"]

Note:
1 <= S.length <= 50
There are no nested curly brackets.
All characters inside a pair of consecutive opening and ending curly brackets are different.
*/

class Solution {
private:
    size_t get_collections(const std::string& s, size_t i, std::vector<std::string>& results) {
        std::vector<std::vector<std::string>> collections;
        while (s[i] != '}') {
            if (s[i] != ',') {
                // must be letter
                std::vector<std::string> collection( results );
                for (auto& str : collection) {
                    str += std::string( 1, s[i] );
                }
                collections.push_back( collection );
            }
            ++i;
        }
        results.clear();
        for (const auto& collection : collections) {
            for (const auto& str : collection) {
                results.push_back( str );
            }
        }
        return i;
    }
	std::vector<std::string> solution1(const std::string& s) {
        std::vector<std::string> results;
        const size_t N = s.size();
        if ( !N ) {
            return results;
        }

        results.push_back( "" );

        for (size_t i = 0; i < N; ++i) {
            if (s[i] == '{') {
                i = get_collections( s, i+1, results );
            } else if (s[i] != ',') {
                for (auto& str : results) {
                    str += std::string(1, s[i]);
                }
            }
        }

        std::sort( results.begin(), results.end() );

        return results;
	}
public:
    vector<string> expand(string S) {
        return solution1( S );        
    }
};
