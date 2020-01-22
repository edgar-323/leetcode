/*
Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].
You need to return the number of important reverse pairs in the given array.

Example1:
Input: [1,3,2,3,1]
Output: 2

Example2:
Input: [2,4,3,5,1]
Output: 3

Note:
The length of the given array will not exceed 50,000.
All the numbers in the input array are in the range of 32-bit integer.
*/
class Solution {
private:
    typedef long long LL;

    int recurse1(const int left, const int right, std::vector<int>& A) {
        if (left >= right) {
            return 0;
        }
        const int mid = left + ((right - left) >> 1);
        int result = recurse1(left, mid, A) + recurse1(mid+1, right, A);
        
        int i = left;
        int j = mid+1;
        int k = 0;
        int p = mid+1;
        
        auto merge = std::vector<int>(right - left + 1); 

        while (i <= mid) {
            while (p <= right and A[i] > 2*LL(A[p])) {
                ++p;
            }
            result += (p - (mid+1));
            while (j <= right and A[i] >= A[j]) {
                merge[k++] = A[j++];
            }
            merge[k++] = A[i++];
        }
        
        while (j <= right) {
            merge[k++] = A[j++];
        }

        for (int q = left; q <= right; ++q) {
            A[q] = merge[q - left];
        }

        return result;
    }
    int solution1(std::vector<int>& A) {
        /* Time-Complexity:     O(N*log(N))
         * Space-Complexity:    O(N)
         */
        /* Explanation:
         * Use Merge-Sort as the underlying algorithm.
         * We will solve this probem using Divide And Conquer As Follows:
         * Let:
         *      T[i,j] = # of reverse pairs in A[i:j] (inclusive)
         * 
         * Then, we divide in the middle (mid = (i+j)/2):
         *      T[left,right] = T[left:mid] + T[mid+1:right] + F[left,mid,right]
         * Here is where must notice certain properties:
         *      1)  We want to find left indices `i` in A[left:mid] and indices `j` in A[mid+1:right]
         *          such that A[i] > 2*A[j]
         *      2)  All i € {left,...,mid} will be less than all j € {mid+1,...,right} 
         *          Thus, the order in which indices in A[left:mid] appear does not matter.
         *          Hence, we can sort A[left:mid] and A[mid+1:right] along the recursion
         *          exactly as Merge Sort does.
         */
        return recurse1(0, A.size() - 1, A);
    }
public:
    int reversePairs(vector<int>& nums) {
        return solution1(nums);    
    }
};
