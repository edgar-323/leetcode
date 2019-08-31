class Solution {
private:
    void solution1(std::vector<char>& S) {
    	const int N = S.size();
        for (int i = 0; i < N/2; ++i) {
            char c = S[i];
            S[i] = S[N-1-i];
            S[N-1-i] = c;	
        }	    
    }
public:
    void reverseString(vector<char>& s) {
        solution1(s);
    }
};
