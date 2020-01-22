/*
In an array A of 0s and 1s, how many non-empty subarrays have sum S?
 
Example 1:
Input: A = [1,0,1,0,1], S = 2
Output: 4
Explanation: 
The 4 subarrays are bolded below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]

Note:
A.length <= 30000
0 <= S <= A.length
A[i] is either 0 or 1.
*/
class Solution {
private:
    int helper1(const std::vector<int>& A) {
        const int N = A.size();
        int subarrays = 0;
        int left = 0;
        int right = 0;
        while (right < N) {
            while (right < N and not A[right]) {
                ++right; 
            }
            const int K = right - left;
            subarrays  += K * (K+1) / 2;
            left = ++right;
        }

        return subarrays; 
    }

    int solution1(const std::vector<int>& A, const int S) {
        if (not S) {
            return helper1(A);
        }
        const int N = A.size();
        int left = 0;
        int right = 0;
        auto deque = std::deque<int>();
        while (right < N and deque.size() < S) {
            if (A[right++]) {
                deque.push_back(right);
            }
        }
        int subarrays = 0;
        while (right < N) {
            if (A[right++]) {
                const int first = deque.front();
                const int last = deque.back();
                subarrays += (right - last) * (first - left);
                left = first;
                deque.pop_front();
                deque.push_back(right);
            }
        }
        if (deque.size() == S) {
            const int first = deque.front();
            const int last = deque.back();
            subarrays += (1 + right - last) * (first - left);
        }
        return subarrays;
    }
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
		return solution1(A, S);
    }
};
