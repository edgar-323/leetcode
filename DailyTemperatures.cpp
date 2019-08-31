/*
Given a list of daily temperatures T, return a list such that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. 
If there is no future day for which this is possible, put 0 instead.

For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].
*/

class Solution {
private:
    const int MAX_TEMP = 100;
    const int MIN_TEMP = 30;
  
    std::vector<int> solution4(const std::vector<int>& T) {
        /* Time-Complexity:     O( ? ) 
         * Space-Complexity:    O( 1 )
         * */
        const int N = T.size();
        auto results = std::vector<int>(N, 0);

        for (int i = N-2; i >= 0; --i) {
            int j = i+1;
            while ( j < N and T[i] >= T[j] ) {
                j = !results[j] ? N : j + results[j];
            }
            results[i] = j < N ? j - i : 0;
        }

        return results;
    }

    std::vector<int> solution3(const std::vector<int>& T) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( N )
         * */ 
        const int N = T.size();
        auto results = std::vector<int>( N, 0 );
        std::stack<int> stack;

        for (int i = N - 1; i >= 0; --i) {
            // While the stack is not empty and while the temperature at top of stack doesnt not satisfy requiements.
            while (!stack.empty() and T[i] >= T[stack.top()]) {
                stack.pop();
            }
            results[i] = stack.empty() ? 0 : stack.top() - i;
            stack.push( i );
        }
        
        return results; 
    }

    int offset2(int t) {
        return t - MIN_TEMP;
    }
    std::vector<int> solution2(const std::vector<int>& T) {
        /* Time-Complexity:     O( N * W )
         * Space-Complexity:    O(   W   )
         * */
        const int N = T.size();
        const int W = MAX_TEMP - MIN_TEMP + 1;
        auto results = std::vector<int>(N, 0);
        // Maps a temperature T[i] to an index i
        auto temperature_indices = std::vector<int>( W, -1);
        
        // We process in reverse order in order to efficently compute/update temperature_indices
        for (int i = N-1; i >= 0; --i) {
            // Current temperature is T[i]
            // We have to check if temperatures {T[i]+1, T[i]+2, ..., MAX_TEMP} have occurred in days {i+1, i+2, ...}
            // We will check temperature_indices, since, if it does contain a temperature in the above set, then that temperature will have occurred in the above date set due to the fact
            // that we are updating temperature_indices in reverse order and this also means that we overwrite existing temperature indices (if they did exist) and so each date in temperature_indices 
            // will be the earliest date that a higher temperature occurred.
            for (int j = offset2(T[i]) + 1; j < W; ++j) {
                const auto index = temperature_indices[j];
                if (index < 0) {
                    continue;
                }
                results[i] = !results[i] ? index - i : std::min( results[i], index - i);
            }
            temperature_indices[offset2(T[i])] = i;
        }

        return results;
    }
    std::vector<int> solution1(const std::vector<int>& T) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  1  )
         * */
        const size_t N = T.size();
        std::vector<int> results(N, 0);
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = i+1; j < N; ++j) {
                if (T[j] > T[i]) {
                    results[i] = j-i;
                    break;
                }
            }
        }
        return results;
    }	
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        return solution2( T );    
    }
};
