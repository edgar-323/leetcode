/*
In English, we have a concept called root, which can be followed by some other words to form another longer word - let's call this word successor. For example, the root an, followed by other, which can form another word another.
Now, given a dictionary consisting of many roots and a sentence. You need to replace all the successor in the sentence with the root forming it. If a successor has many roots can form it, replace it with the root with the shortest length.
You need to output the sentence after the replacement.

Example 1:
Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"

Note:
The input will only have lower-case letters.
1 <= dict words number <= 1000
1 <= sentence words number <= 1000
1 <= root length <= 100
1 <= sentence words length <= 1000
*/
class Trie {
private:
    static const int ALPH_SZ = 26;
    Trie* child[ALPH_SZ];
    int dict_index;

    int index(const char c) {
        return c - 'a';
    }

    void add_word(const std::string& word, const int pos, const int dict_index) {
        if (pos == word.size()) {
            this->dict_index = dict_index;
            return;
        }

        const auto i = index(word[pos]);
        if (not child[i]) {
            child[i] = new Trie();
        }
        child[i]->add_word(word, pos+1, dict_index);
    }

    int search(const std::string& word, const int pos) {
        if (pos == word.size() or dict_index >= 0) {
            return dict_index;
        }
        
        const auto i = index(word[pos]);
        return child[i] ? child[i]->search(word, pos+1) : -1;
    }

public:
    Trie() {
        dict_index = -1;
        for (int i = 0; i < ALPH_SZ; ++i) {
            child[i] = NULL;
        }
    }
    
    ~Trie() {
        for (int i = 0; i < ALPH_SZ; ++i) {
            if (child[i]) {
                delete child[i];
            }
        }
    }
    
    void add_word(const std::string& word, const int dict_index) {
        add_word(word, 0, dict_index);
    }

    int search(const std::string& word) {
        return search(word, 0);
    }
};

class Solution {
private:

    std::string get_next_word(const std::string& sentence, int& index) {
        const int N = sentence.size();
        std::string word = "";
        while (index < N and sentence[index] == ' ') {
            ++index;
        }
        while (index < N and sentence[index] != ' ') {
            word += std::string(1, sentence[index++]);
        }

        return word;
    }

    std::vector<std::string> get_words(const std::string& sentence) {
        auto words = std::vector<std::string>();
        int index = 0;
        std::string word;
        while (not (word = get_next_word(sentence, index)).empty()) {
            words.push_back(word);
        }

        return words;
    }

    std::string get_sentence(const std::vector<std::string>& words) {
        auto sentence = std::string("");
        const int W = words.size();
        for (int w = 0; w < W; ++w) {
            sentence += words[w] + (w < W-1 ? " " : "");
        }

        return sentence;
    }

    std::string solution1(const std::vector<std::string>& dict, const std::string& sentence) {
        auto trie = Trie();

        const int D = dict.size();
        for (int d = 0; d < D; ++d) {
            trie.add_word(dict[d], d);
        }

        auto words = get_words(sentence);
        const int W = words.size();
        for (int w = 0; w < W; ++w) {
            const auto dict_index = trie.search(words[w]);
            if (dict_index >= 0) {
                words[w] = dict[dict_index];
            }
        }

        return get_sentence(words);
    }

public:
    string replaceWords(vector<string>& dict, string sentence) {
        return solution1(dict, sentence);        
    }
};
