/*
Design an Iterator class, which has:

A constructor that takes a string characters of sorted distinct lowercase English letters and a number combinationLength as arguments.
A function next() that returns the next combination of length combinationLength in lexicographical order.
A function hasNext() that returns True if and only if there exists a next combination.

Example:
CombinationIterator iterator = new CombinationIterator("abc", 2); // creates the iterator.
iterator.next(); // returns "ab"
iterator.hasNext(); // returns true
iterator.next(); // returns "ac"
iterator.hasNext(); // returns true
iterator.next(); // returns "bc"
iterator.hasNext(); // returns false
 
Constraints:
1 <= combinationLength <= characters.length <= 15
There will be at most 10^4 function calls per test.
It's guaranteed that all calls of the function next are valid.
*/

class CombinationIterator {
private:
    std::vector<int> index;
    std::string S;
    int N,K;
    
    void set_next(const int i) {
        if (i < 0) {
            return;
        }
        ++index[i];
        if (N - index[i] >= K - i) {
            for (int j = i+1; j < K; ++j) {
                index[j] = 1 + index[j-1];
            }
        } else {
            set_next(i-1);
        }
    }
public:
    CombinationIterator(string characters, int combinationLength) {
        S = characters;
        N = characters.size();
        K = combinationLength;
        index = std::vector<int>(K);
        for (int i = 0; i < K; ++i) {
            index[i] = i;
        }
    }
    
    string next() {
        auto str = std::string(K, 0);
        for (int i = 0; i < K; ++i) {
            str[i] = S[index[i]];
        }
        set_next(K-1);

        return str;
    }
    
    bool hasNext() {
        return index[K-1] < N;
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
