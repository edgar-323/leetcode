/*
Given an unsorted integer array, find the smallest missing positive integer.

Example 1:
Input: [1,2,0]
Output: 3

Example 2:
Input: [3,4,-1,1]
Output: 2

Example 3:
Input: [7,8,9,11,12]
Output: 1

Note:
Your algorithm should run in O(n) time and uses constant extra space.
*/

class Solution {
private:
    /*************************************************************/ 
    int solution1(std::vector<int>& nums) {
        /* CORRECT BUT VIOLATES BOTH THE 
         * TIME AND SPACE COMPLEXITIES OF 
         * THE ALGORITHMIC REQUIREMENTS.
         * 
         * Time-Complexity:     O(N * lg(N))
         * Space-Complexity:    O(N)
         *  
         * */
        std::set<int> _set(nums.begin(), nums.end());
        nums = std::vector(_set.begin(), _set.end());
        std::sort(nums.begin(), nums.end());
        size_t start = 0;
        const size_t N = nums.size();
        while (start < N and nums[start] <= 0) {
            ++start;
        }
        int firstPositive = 1;
        while (start < N and nums[start] == firstPositive) {
            ++start;
            ++firstPositive;
        }
        return firstPositive;
    }
    /*************************************************************/ 
    int solution2(std::vector<int>& nums) {
        /* CORRECT BUT VIOLATES SPACE 
         * COMPLEXITY OF THE ALGORITHMIC
         * REQUIREMENTS.
         *
         * Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *
         * */
        std::unordered_set<int> allPositives;
        for (int& num : nums) {
            if (num > 0 and allPositives.count(num) == 0) {
                allPositives.insert(num);
            }
        }
        const int N = allPositives.size();
        int firstPositive = 1;
        for (int _ = 0; _ < N; ++_) {
            if (allPositives.count(firstPositive) > 0) {
                ++firstPositive;
            } else {
                break;
            }
        }
        return firstPositive;
    }
    /*************************************************************/
    int solution3(std::vector<int>& nums) {
        /* SAME COMPLEXITIES AS SOLUTION2 
         * BUT WE HAVE FIGURED OUT A WAY OF
         * USING A VECTOR AS A "SET"
         * */
        std::vector<int> allPositives;
        for (int num : nums) {
            if (num > 0) {
                allPositives.push_back(num);
            }
        }
        const size_t N = allPositives.size();
        for (int i = 0; i < N; ++i) {
            int num = std::abs(allPositives[i]);
            if (num <= N and allPositives[num-1] > 0) {
                allPositives[num-1] *= -1;
            }
        }
        for (int i = 0; i < N; ++i) {
            if (allPositives[i] > 0) {
                return i+1;
            }
        }
        
        return N+1;
    }
    /*************************************************************/ 
    const int movePositivesToFront(std::vector<int>& nums) {
        const int N = nums.size();
        int nextPos = N-1;
        while (nextPos >= 0 and nums[nextPos] <= 0) {
            --nextPos;
        }
        for (int i = nextPos-1; i >= 0; --i) {
            if (nums[i] <= 0) {
                int temp = nums[nextPos];
                nums[nextPos] = nums[i];
                nums[i] = temp;
                --nextPos;
            }
        }
        return nextPos+1;
    }
    int solution4(std::vector<int>& nums) {
        /* FINAL ALGORITHM. 
         *
         * Time-Complexity:     O(N)
         * Space-Complexity:    O(1)
         *
         * */
        const int N = movePositivesToFront(nums);
        std::vector<int>& allPositives = nums;
        for (int i = 0; i < N; ++i) {
            int positive = std::abs(allPositives[i]);
            if (positive <= N and allPositives[positive-1] > 0) {
                allPositives[positive-1] *= -1;
            }
        }
        for (int i = 0; i < N; ++i) {
            if (allPositives[i] > 0) {
                return i+1;
            }
        }
        return N+1;
    }
    /*************************************************************/
public:
    int firstMissingPositive(vector<int>& nums) {
        return solution4(nums);        
    }
};



