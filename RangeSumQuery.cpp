/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]
sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3

Note:
You may assume that the array does not change.
There are many calls to sumRange function.
*/

class NumArray {
private:
    /* EXPLANATION:
     * We let:
     *      DP[i] = sum(nums[0:i])
     *          for i € {0,...,N-1}
     * So that:
     *      sumRange(i,j) = DP[j] - DP[i-1]
     * 
     * This means that calls to sumRange(*) execute in O(1) time.
     *  */
    int N;
    int* DP;
public:
    NumArray(vector<int>& nums) {
        N = nums.size();
        if (!N) {
            return;
        }
        DP = new int[N];
        DP[0] = nums[0];
        for (int i = 1; i < N; ++i) {
            DP[i] = DP[i-1] + nums[i];
        }
    }

    ~NumArray() {
        if (N) {
            delete [] DP;
        }
    }
    
    int sumRange(int i, int j) {
        /* ASSUMES:
         * 0 <= i <= j < N
         * */
        return DP[j] - (i > 0 ? DP[i-1] : 0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
