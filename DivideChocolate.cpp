/*j
You have one chocolate bar that consists of some chunks. 
Each chunk has its own sweetness given by the array sweetness.
You want to share the chocolate with your K friends so you start cutting the chocolate bar into K+1 pieces using K cuts, each piece consists of some consecutive chunks.
Being generous, you will eat the piece with the minimum total sweetness and give the other pieces to your friends.
Find the maximum total sweetness of the piece you can get by cutting the chocolate bar optimally.

Example 1:
Input: sweetness = [1,2,3,4,5,6,7,8,9], K = 5
Output: 6
Explanation: You can divide the chocolate to [1,2,3], [4,5], [6], [7], [8], [9]

Example 2:
Input: sweetness = [5,6,7,8,9,1,2,3,4], K = 8
Output: 1
Explanation: There is only one way to cut the bar into 9 pieces.

Example 3:
Output: 5
Explanation: You can divide the chocolate to [1,2,2], [1,2,2], [1,2,2]

Constraints:
0 <= K < sweetness.length <= 10^4
1 <= sweetness[i] <= 10^5
*/
class Solution {
private:
    int get_cuts_needed(const std::vector<int>& bars, const int sweetness) {
        int total_sweetness = 0;
        int cuts_needed = 0;
        for (const auto bar : bars) {
            total_sweetness += bar;
            if (total_sweetness + bar >= sweetness) {
                total_sweetness = 0;
                ++cuts_needed;
            }
        }
        return cuts_needed;
    }

    int solution1(const std::vector<int>& bars, const int K) {
        int left = *std::min_element(std::begin(bars), std::end(bars));
        int right = std::accumulate(std::begin(bars), std::end(bars), 0);
        
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            const auto cuts_needed = get_cuts_needed(bars, mid);
            if (cuts_needed > K+1) {
                left = mid+1;
            } else {
                right = mid-1;
            }
        }

        return left;
    }
public:
    int maximizeSweetness(vector<int>& sweetness, int K) {
        return solution1(sweetness, K);       
    }
};
