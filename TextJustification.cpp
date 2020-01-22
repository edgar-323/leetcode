/*
Given an array of words and a width maxWidth, 
format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.
You should pack your words in a greedy approach; 
that is, pack as many words as you can in each line. 
Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
Extra spaces between words should be distributed as evenly as possible. 
If the number of spaces on a line do not divide evenly between words, 
the empty slots on the left will be assigned more spaces than the slots on the right.
For the last line of text, it should be left justified and no extra space is inserted between words.
Note:
A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.

Example 1:
Input:
words = ["This", "is", "an", "example", "of", "text", "justification."]
maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]

Example 2:
Input:
words = ["What","must","be","acknowledgment","shall","be"]
maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be",
             because the last line must be left-justified instead of fully-justified.
             Note that the second line is also left-justified becase it contains only one word.

Example 3:
Input:
words = ["Science","is","what","we","understand","well","enough","to","explain",
         "to","a","computer.","Art","is","everything","else","we","do"]
maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
*/
class Solution {
private:
    std::vector<std::string> solution1(const std::vector<std::string>& words, const int L) {
        const int W = words.size();

        auto lines = std::vector<std::string>();

        for (int i = 0, k, l; i < W; i += k) {
            for (k = 0, l = 0; i + k < W and l + words[i+k].size() <= L - k; k++) {
                l += words[i+k].size();
            }
            auto line = words[i];
            for (int j = 0; j < k - 1; ++j) {
                if (i + k >= W) {
                    line += " ";
                } else {
                    line += std::string((L - l) / (k - 1) + (j < (L - l)%(k - 1)), ' ');
                }
                line += words[i+j+1];
            }
            line += std::string(L - line.size(), ' ');
            lines.push_back(line);
        }

        return lines;
    }
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        return solution1(words, maxWidth);        
    }
};
