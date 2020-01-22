/*
Write a program to find the nth super ugly number.
Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

Example:
Input: n = 12, primes = [2,7,13,19]
Output: 32 
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 
             super ugly numbers given primes = [2,7,13,19] of size 4.

Note:
1 is a super ugly number for any given primes.
The given numbers in primes are in ascending order.
0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
The nth super ugly number is guaranteed to fit in a 32-bit signed integer.
*/

class Solution {
private:
    typedef std::tuple<int,int,int> Node;

    int solution1(const int N, const std::vector<int>& primes) {
        const int K = primes.size();
        const auto cmp =    []
                            (const Node& v1, const Node& v2) -> bool {
                                return std::get<0>(v1) > std::get<0>(v2); 
                            };
        auto PQ = std::priority_queue<Node, std::vector<Node>, decltype(cmp)>(cmp);
        for (int k = 0; k < K; ++k) {
            PQ.push(std::make_tuple(primes[k], primes[k], 0));
        }
        
        auto ugly = std::vector<int>(N+1);
        ugly[0] = 1;

        int i = 1;
        
        while (i < N) {
            auto node = PQ.top(); PQ.pop();
            const auto num = std::get<0>(node);
            const auto prime = std::get<1>(node);
            const auto index = std::get<2>(node);
            
            if (num != ugly[i-1]) {
                ugly[i++] = num; 
            }

            PQ.push(std::make_tuple(num * primes[index+1], prime, index+1));
        }

        return ugly[N-1];
    }
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
 		return solution1(n, primes);       
    }
};
