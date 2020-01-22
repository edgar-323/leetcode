/*
Median is the middle value in an ordered integer list. 
If the size of the list is even, there is no middle value. 
So the median is the mean of the two middle value.

Examples:
[2,3,4] , the median is 3
[2,3], the median is (2 + 3) / 2 = 2.5

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. 
You can only see the k numbers in the window. Each time the sliding window moves right by one position. 
Your job is to output the median array for each window in the original array.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Median
---------------               -----
[1  3  -1] -3  5  3  6  7       1
 1 [3  -1  -3] 5  3  6  7       -1
 1  3 [-1  -3  5] 3  6  7       -1
 1  3  -1 [-3  5  3] 6  7       3
 1  3  -1  -3 [5  3  6] 7       5
 1  3  -1  -3  5 [3  6  7]      6
Therefore, return the median sliding window as [1,-1,-1,3,5,6].

Note:
You may assume k is always valid, ie: k is always smaller than input array's size for non-empty array.
*/

class Window {
private:
    std::multiset<int, greater<int>> max_set; 
    std::multiset<int> min_set;
public:
    Window() {}
    
    void add_num(const int num) {
        max_set.insert(num);
        min_set.insert(*max_set.begin());
        max_set.erase(max_set.begin());

        if (max_set.size() < min_set.size()) {
            max_set.insert(*min_set.begin());
            min_set.erase(min_set.begin());
        }
    }

    double get_median() {
        return  max_set.size() > min_set.size() ?
                double(*max_set.begin()):
                (double(*max_set.begin()) + double(*min_set.begin()))*0.5;
    }

    void remove_num(int num) {
        if (max_set.count(num)) {
            max_set.erase(max_set.find(num));
            if (max_set.size() < min_set.size()) {
                max_set.insert(*min_set.begin());
                min_set.erase(min_set.begin());
            }
        } else if (min_set.count(num)) {
            min_set.erase(min_set.find(num));
            if (min_set.size() + 1 < max_set.size()) {
                // max_set size can be at most one element greater than min_set
                min_set.insert(*max_set.begin());
                max_set.erase(max_set.begin());
            }
        }
    }
};

class Solution {
private:
    std::vector<double> solution1(const std::vector<int>& nums, const int K) {
        const int N = nums.size();

        auto window = Window();
        for (int i = 0; i < K-1; ++i) {
            window.add_num(nums[i]);
        }
        auto results = std::vector<double>();
        for (int i = K-1; i < N; ++i) {
            window.add_num(nums[i]);
            results.push_back(window.get_median());
            window.remove_num(nums[i - K + 1]);
        }

        return results;
    }
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        return solution1(nums, k);       
    }
};
