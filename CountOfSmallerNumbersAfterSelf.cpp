/*
You are given an integer array nums and you have to return a new counts array. 
The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:
Input: [5,2,6,1]
Output: [2,1,1,0] 
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
*/

class Solution {
private:
    typedef std::array<int, 3> Triplet;
    static const int VALUE = 0;
    static const int INDEX = 1;
    static const int LESS_THAN = 2;

    void sort_by_value1(const int left, const int right, std::vector<Triplet>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *      Where:
         *          N = (right - left + 1)
         */
        /* Sort A[left:right] (inclusive) By VALUE 
         * Assumes A[left:mid] and A[mid+1:right] are already sorted by VALUE
         */
        auto merged = std::vector<Triplet>(right - left + 1);
        int k = 0;
        const int mid = left + (right - left) / 2;
        int i = left;
        int j = mid+1; 
        while (i <= mid and j <= right) {
            if (A[i][VALUE] < A[j][VALUE]) {
                merged[k++] = A[i++];
            } else {
                merged[k++] = A[j++];
            }
        }
        while (i <= mid) {
            merged[k++] = A[i++];
        }
        while (j <= right) {
            merged[k++] = A[j++];
        }
        for (i = left; i <= right; ++i) {
            A[i] = merged[i-left];
        }
    }

    void augment_left_half(const int left, const int right, std::vector<Triplet>& A) {
        /* Time-Complexity:     O(N)
         * Space-Complexity:    O(N)
         *      Where:
         *          N = (right - left + 1)
         */
        /* Assumes A[left:mid] and A[mid+1:right] is sorted by VALUE.
         * Now, all we have to do is:
         *  For i € {left,...,mid}:
         *      A[i][LESS_THAN] += total #s in A[mid+1:right] that are LESS_THAN A[i][VALUE]
         * Since A[left:mid] is sorted we take advantage as follows:
         * Suppose, for i € {left,...,mid-1}, A[i] has x total numbers in A[mid+1:right] that are
         * less than A[i][VALUE].
         * Then, A[i+1] also has these x values that are less that A[i+1][VALUE] (plus, possibly
         * some addittional values).
         * Why is this? Because A[i][VALUE] <= A[i+1][VALUE].
         * This allows us to augment every value in A[left:mid] in linear time.
         */
        const int mid = left + (right - left) / 2;
      	auto left_augmentation = std::vector<int>(mid-left+1, 0);

        for (int i = left, j = mid+1; i <= mid; ++i) {
            if (i > left) {
                left_augmentation[i-left] += left_augmentation[i-left-1];
            }
            while (j <= right and A[i][VALUE] > A[j][VALUE]) {
                ++j;
                ++left_augmentation[i-left];
            }
            A[i][LESS_THAN] += left_augmentation[i-left];
        }
    }

    void recurse1(const int left, const int right, std::vector<Triplet>& A) {
        if (left >= right) {
            return;
        }
        const auto mid = left + (right - left) / 2;
        recurse1(left, mid, A);
        recurse1(mid+1, right, A);
        augment_left_half(left, right, A);
        sort_by_value1(left, right, A);
    }

    std::vector<int> solution1(const std::vector<int>& nums) {
        /* Time-Complexity:     O(N*log(N))
         * Space-Complexity:    O(N)
         */
        if (nums.empty()) {
            return {};
        }
        const int N = nums.size();
        // O(N)
        auto A = std::vector<Triplet>(N);
        for (int i = 0; i < N; ++i) {
            A[i] = {nums[i], i, 0};
        }
        // O(N*log(N))
        recurse1(0, N-1, A);
        // O(N*log(N))
        std::sort(A.begin(), A.end(),
                []
                (const Triplet& p1, const Triplet& p2) -> bool 
                {
                    return p1[INDEX] < p2[INDEX];
                });
        // O(N)
        auto results = std::vector<int>(N);
        for (int i = 0; i < N; ++i) {
            results[i] = A[i][LESS_THAN];
        }

        return results;
    }
public:
    vector<int> countSmaller(vector<int>& nums) {
        return solution1(nums);    
    }
};
