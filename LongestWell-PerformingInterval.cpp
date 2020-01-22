/*
We are given hours, a list of the number of hours worked per day for a given employee.
A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.
A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.

Return the length of the longest well-performing interval.

 

Example 1:

Input: hours = [9,9,6,0,6,6,9]
Output: 3
Explanation: The longest well-performing interval is [9,9,6].
 

Constraints:

1 <= hours.length <= 10000
0 <= hours[i] <= 16
*/
class Solution {
private:
    int solution1(const std::vector<int>& hours) {
        const int N = hours.size();
        auto prefix_sum = std::vector<int>(N+1);
        prefix_sum[0] = 0;
        for (int i = 1; i <= N; ++i) {
            prefix_sum[i] = prefix_sum[i-1] + (hours[i-1] > 8 ? 1 : -1);
        }
        // monotone decreasing stack
        auto stack = std::stack<int>();
        for (int i = 0; i <= N; ++i) {
            if (stack.empty() or prefix_sum[stack.top()] > prefix_sum[i]) {
                stack.push(i);
            }
        }

        int result = 0;
        for (int j = N; j >= 0; --j) {
            while (not stack.empty() and prefix_sum[stack.top()] < prefix_sum[j]) {
                result = std::max( result, j - stack.top() );
                stack.pop();
            }
        }

        return result;
    }

    int solution2(const std::vector<int>& hours) {
        const int N = hours.size();

        int max_len = 0;
        auto seen = std::unordered_map<int,int>();
        int sum = 0;

        for (int i = 0; i < N; ++i) {
            sum += hours[i] > 8 ? 1 : -1;
            if (not seen.count(sum)) {
                seen[sum] = i;
            }
            if (sum > 0) {
                max_len = i + 1;
            } else if (seen.count(sum - 1)) {
                max_len = std::max(max_len, i - seen[sum-1]);
            } 
        }

        return max_len;
    }
public:
    int longestWPI(vector<int>& hours) {
        return solution1(hours);       
    }
};
