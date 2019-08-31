/*
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
Find all the elements of [1, n] inclusive that do not appear in this array.
Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:
Input:
[4,3,2,7,8,2,3,1]
Output:
[5,6]
*/

class Solution {
private:
    std::vector<int> solution1(std::vector<int>& nums) {
        /*
        ************************************************
        Time-Complexity:    O(N)
        Space-Complexity:   O(N)
        ************************************************
        */
        const int N = nums.size();
        if (N == 0) {
            return std::vector<int>();
        }
        bool numMap[N]; 
        for (int i = 0; i < N; ++i) {
            numMap[i] = false;
        }
        for (auto& num : nums) {
            numMap[num-1] = true;
        }
        std::vector<int> missingNums;
        for (int i = 0; i < N; ++i) {
            if (!numMap[i]) {
                missingNums.push_back(i+1);
            }
        }
        return missingNums;
    }
    
    int abs(int x) {
        return (x < 0) ? -x : x;
    }
    
    std::vector<int> solution2(std::vector<int>& nums) {
        /*
        ************************************************
        Time-Complexity:    O(N)
        Space-Complexity:   O(1)
        ************************************************
        Idea: 
        The input numbers are all in the range [1,N].
        Before we would use a MAP<int, bool> to mark
        whether some number i in [1,N] is in the array
        with value true for being present and value
        false for being absent.
        We will recreate this by negating nums[i] if 
        i is in the array.
        So we iterate through the array and let
            num = nums[i]
        then we need to report that num is in the array
        by turning nums[num] negative (if not already 
        negative).
        So we use the input as our auxilary space.
        If our interviewer stated that we cannot alter our
        input array, we can easily undo our changes by
        going through the array again and negating negative
        entries (since the array only contained positive 
        entries).
        In conclusion, this uses O(1) space.
        ************************************************
        */
        const int N = nums.size();
        int val;
        for (int i = 0; i < N; ++i) {
            val = abs(nums[i]) - 1;
            nums[val] = (nums[val] > 0) ? -nums[val] : nums[val];
        }
        std::vector<int> missingNums;
        for (int i = 0; i < N; ++i) {
            if (nums[i] > 0) {
                missingNums.push_back(i+1);
            }
        }
        return missingNums;
    }
    
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        return solution2(nums);
    }
};
