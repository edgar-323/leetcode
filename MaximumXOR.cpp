/*
Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 2^31.

Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

Could you do this in O(n) runtime?

Example:

Input: [3, 10, 5, 25, 2, 8]

Output: 28

Explanation: The maximum result is 5 ^ 25 = 28.
*/

class BinaryTrie {
private:
    BinaryTrie* zero;
    BinaryTrie* one;
    // Description says we will only use first 31 bits.
    static const int N = sizeof( int ) * 8 - 1;
public:
    BinaryTrie(): zero(NULL), one(NULL) {}
    
    ~BinaryTrie() {
        if (zero) {
            delete zero;
            zero = NULL;
        }
        if (one) {
            delete one;
            one = NULL;
        }
    }

    void insert(unsigned int x) {
        BinaryTrie* trie = this;
        
        for (int i = N-1; i >= 0; --i) {
            unsigned int bit = (x & (1 << i));
            if (bit) {
                if (!trie->one) {
                    trie->one = new BinaryTrie();
                }
                trie = trie->one;
            } else {
                if (!trie->zero) {
                    trie->zero = new BinaryTrie();
                }
                trie = trie->zero;
            }
        }
    }
    int maxXor(unsigned int number) {
        // Assumes at least one element has been inserted.
        BinaryTrie* trie = this;
        for (int i = N-1; i >= 0; --i) {
            unsigned int bit = number & (1 << i);
            if (bit) {
                if (trie->zero) {
                    // Hit!
                    trie = trie->zero;
                } else {
                    // Miss!
                    // turn ith bit off
                    number = number & (~(1 << i));
                    // we don't worry about trie ever being NULL because at least one
                    // number has been inserted (reason about the rest...)
                    trie = trie->one;
                }
            } else {
                if (trie->one) {
                    // Hit!
                    // set the ith bit
                    number = number | (1 << i);
                    trie = trie->one;
                } else {
                    // Miss!
                    // Again, trie will never become NULL.
                    trie = trie->zero;
                }
            }
        }
        
        return int( number );       
    }
};

class Solution {
private:
    int solution2(std::vector<int>& nums) {
        /* Time-Complexity:     O( N * k)
         * Space-Complexity:    O(  2^k )
         *  where k = 31 
         * */
        const size_t N = nums.size();
        if (N <= 1) {
            return 0;
        }
        int maxXor = 0;
        
        BinaryTrie trie;
        trie.insert( nums[0] );
        for (size_t i = 1; i < N; ++i) {
            maxXor = std::max( maxXor, trie.maxXor( nums[i] ) );
            trie.insert( nums[i] );
        }

        return maxXor;
    }
    int solution1(std::vector<int>& nums) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  1  )
         * */
        const size_t N = nums.size();
        int maxXOR = INT_MIN;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = i+1; j < N; ++j) {
                maxXOR = std::max( maxXOR, nums[i] ^ nums[j] ); 
            }
        }
        return maxXOR;
    }
public:
    int findMaximumXOR(vector<int>& nums) {
        return solution2( nums );
    }
};
