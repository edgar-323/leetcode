/*
Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
The number of elements initialized in nums1 and nums2 are m and n respectively.
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2.

Example:
Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3
Output: [1,2,2,3,5,6]
*/

class Solution {
private:
    /*************************************************************************************************/
    void solution2(std::vector<int>& nums1, const size_t M, std::vector<int>& nums2, const size_t N) {
        /* 
         * Time-Complexity:     O( M+N )
         * Space-Complexity:    O(  1  )
         * */
        size_t i = M-1, j = N-1, k = M+N-1;
        while (i >= 0 and j >= 0) {
            nums1[k--] = (nums1[i] > nums2[j]) ? nums1[i--] : nums2[j--];
        }
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }
    /*************************************************************************************************/
    void solution1(std::vector<int>& nums1, const size_t M, std::vector<int>& nums2, const size_t N) {
        /* 
         * Time-Complexity:     O( M+N )
         * Space-Complexity:    O( M+N )
         * */
        std::vector<int> aux(M+N, -1);
        size_t i = 0, j = 0, k = 0;
        while (i < M and j < N) {    
            aux[k++] = (nums1[i] <= nums2[j]) ? nums1[i++] : nums2[j++];
        }
        while (i < M) {
            aux[k++] = nums1[i++];
        }
        while (j < N) { 
            aux[k++] = nums2[j++];
        }
        for (i = 0; i < k; ++i) {
            nums1[i] = aux[i];
        }
   }
   /*************************************************************************************************/
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        solution2( nums1, m, nums2, n );
    }
};
