class Solution {
private: 
    double solution2(std::vector<int>& A, std::vector<int>& B) {
        /*
         * Time-Complexity:     O(lg(min(M, N))
         * Space-Complexity:    O(1)
         *
         * */

        int M = A.size();
        int N = B.size();
        
        if (M > N) {
            // ensure that: M <= N
            return solution2(B, A);
        }

        int i_min = 0;
        int i_max = M;
        int halflen = (M + N + 1) / 2;

        while (i_min <= i_max) {
            int i = (i_min + i_max) / 2;
            int j = halflen - i;
            
            if (i < i_max and B[j-1] > A[i]) {
                // i is too small.
                i_min = i+1;
            } else if (i > i_min and A[i-1] > B[j]) {
                // i is too big.
                i_max = i-1;
            } else {
                // i is perfect.
                // calculate max_left and 
                // (if necessary) min_right. 
                int max_left; 
                max_left = (i == 0) ? 
                            B[j-1] : 
                            ((j == 0) ? 
                                A[i-1] : 
                                std::max(A[i-1], B[j-1]));
                if ((M+N) % 2 == 1) {
                    // Combined array is of odd length.
                    // Median will be the middle element.
                    // max_left is middle element.
                    return max_left;
                }
                // Combined array is of even length.
                // Median will be the average of two 
                // middle elements.
                // The two middle elements are max_left
                // and min_right.
                int min_right;
                min_right = (i == M) ? 
                            B[j] : 
                            ((j == N) ? 
                                A[i] : 
                                std::min(A[i], B[j])); 
                return (max_left + min_right) / 2.0;
            }
        }

        return 0.0;
    }

    double solution1(std::vector<int>& nums1, std::vector<int>& nums2) {
        /*
         * Time-Complexity:     O(T*lg(T))
         * Space-Complexity:    O(T)
         *
         * Where T = N+M
         * N = size(nums1) 
         * M = size(nums2)
         * */
        
        auto all_nums = std::vector<int>();
        for (auto num : nums1) {
            all_nums.push_back(num);
        }   
        for (auto num : nums2) {
            all_nums.push_back(num);
        }
        std::sort(all_nums.begin(), all_nums.end());
        auto N = all_nums.size();
        return (N % 2 == 1) ? 
                all_nums[N/2] : 
                double(all_nums[N/2] + all_nums[N/2 - 1]) / 2.0;
    }
    
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
 	    return solution2(nums1, nums2);	       
    }
};

