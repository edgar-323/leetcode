/*
The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

Example 1:
Input: 2
Output: [0,1,3,2]
Explanation:
00 - 0
01 - 1
11 - 3
10 - 2
For a given n, a gray code sequence may not be uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence.

00 - 0
10 - 2
11 - 3
01 - 1
Example 2:
Input: 0
Output: [0]
Explanation: We define the gray code sequence to begin with 0.
             A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
             Therefore, for n = 0 the gray code sequence is [0].
*/
class Solution {
private:
    int N;

    void recurse1(const int curr_num, const int i, std::vector<int>& results) {
        results.push_back(curr_num);
        // Can only flip bits in position {i,...,N}
        for (int j = i; j < N; ++j) {
            recurse1(curr_num | (1 << j), j+1, results);
        }
    }

    std::vector<int> solution1(const int N) {
        // INCORRECT: 
        // Produces Correct Sequence But Wrong Order
        this->N = N;
        auto results = std::vector<int>();
        recurse1(0, 0, results);

        return results;
    }

    std::vector<int> solution2(const int N) {
        const int K = 1 << N;
        auto results = std::vector<int>(); 
        results.reserve(K);
        for (int i = 0; i < K; ++i) {
            results.push_back( i ^ (i >> 1) );
        }

        return results;
    }
public:
    vector<int> grayCode(int n) {
 		return solution2(n);       
    }
};
