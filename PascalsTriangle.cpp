/*
Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.
In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
*/

class Solution {
private:
    std::vector<std::vector<int>> solution1(const int N) {
        /*
         * Time-Complexity:    
         *      SUM(1 + 2 + ... + N) => O(N^2)
         * Space-Complexity:
         *      O(1)
         * 
         * NOTE:
         * Notice that the size of the return value will be O( N^2 )
         * so it is impossible for the runtime of any algorithm that
         * produces Pascal's Triangle to be of more efficient runtime
         * than O( N^2 ).
         * */
        if (N <= 0) {
            return std::vector<std::vector<int>>();
        }

        // Instantiate `results` to be vector of N empty vectors which we will iteratively update:
        std::vector<std::vector<int>> results( N, std::vector<int>() );
        // Add initial value `[[1]]`:
        results[0].push_back( 1 );

        for (int i = 1; i < N; ++i) {
            // We need previous collection of pascal values:
            const auto& prev = results[i-1];
            // We will update `results[i]`
            auto& curr = results[i];
            // Size of `results[i]` will be `i+1` so we reserve space for efficiency
            curr.reserve( i+1 );
           
            // All rows start with 1
            curr.push_back( 1 );
            for (int j = 1; j < i; ++j) {
                // `curr[j]` is a linear function of: (`prev[j-1]`, `prev[j]`)
                curr.push_back( prev[j-1] + prev[j] );
            }
            // All rows end with 1
            curr.push_back( 1 );
        }

        return results;
    }
public:
    vector<vector<int>> generate(int numRows) {
        return solution1(numRows);
    }
};
