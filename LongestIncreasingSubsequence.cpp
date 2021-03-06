/*
Given an unsorted array of integers, find the length of longest increasing subsequence.

Example:
Input: [10,9,2,5,3,7,101,18]
Output: 4 
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4. 

Note:
There may be more than one LIS combination, it is only necessary for you to return the length.
Your algorithm should run in O(N^2) complexity.
Follow up: Could you improve it to O(n log n) time complexity?
*/

class List {
public:
    int index;
    List* next;
    List(int index, List* next) {
        this->index = index;
        this->next = next;
    }
};

class Solution {
private:
    /******************************************************************/
    List** adjList;
    int* seen;
    int N;
    
    int visit(int node) {
        if (seen[node]) {
            return seen[node];
        }
        
        seen[node] = 1;
        int maxSeq = 0;
        for (List* list = adjList[node]; list != NULL; list = list->next) {
            int neighbor = list->index;
            maxSeq = std::max(maxSeq, visit(neighbor));
        }
        seen[node] += maxSeq;
        return seen[node];
    }
    
    int dfs() {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( N )
         * */
        int maxSeq = 0;
        for (int node = 0; node < N; ++node) {
            maxSeq = std::max(maxSeq, visit(node));
        }
        return maxSeq;
    }
    
    void generateGraph1(const std::vector<int>& nums) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O( N^2 )
         * */
        seen = new int[N];
        adjList = new List*[N];
        for (int i = 0; i < N; ++i) {
            seen[i] = 0;
            adjList[i] = NULL;
            for (int j = N-1; j > i; --j) {
                adjList[i] = (nums[j] <= nums[i]) ? adjList[i] :
                            (new List(j, adjList[i]));
            }
        }
    }
    
    void destroyGraph1(void) {
        for (int i = 0; i < N; ++i) {
            List* next = NULL;
            for (List* list = adjList[i]; list != NULL; list = next) {
                next = list->next;
                delete list;
            }
        }
        delete[] seen;
        delete[] adjList;
    }
    
    int solution1(const std::vector<int>& nums) {
        /*
        Time-Complexity:    O( N^2 ) 
        Space-Complexity:   O( N^2 )
        */
        N = nums.size();
        if (N == 0) {
            return 0;
        }
        generateGraph1(nums);
        int maxSeq = dfs();
        destroyGraph1();
        return maxSeq;
    }
    /******************************************************************/ 
    int solution2(const std::vector<int>& nums) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  N  )
         * */
        // Traditional Textbook Solution
        N = nums.size();
        if (N == 0) {
            return 0;
        }
         
        std::vector<int> DP( N, 1 );
        int max_subsq = 1;

        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    DP[i] = std::max( DP[i], 1 + DP[j] );
                }
            }
            max_subsq = std::max( max_subsq, DP[i] );
        } 

        return max_subsq; 
    }
    /******************************************************************/
    int solution3(const std::vector<int>& nums) {
        /* Time-Complexity:     O( N*log(N) )
         * Space-Complexity:    O(    N     )
         * */
        /* Explanation:
         * See https://www.algorithmist.com/index.php/Longest_Increasing_Subsequence
         * */
        N = nums.size();
       	if ( !N ) {
		  return 0;
	    }

		vector<int> tails;
		tails.reserve(nums.size());
		tails.push_back(nums.front());

		for (size_t i = 1; i < N; ++i) {
            const int& n = nums[i];
            auto iter = std::lower_bound(tails.begin(), tails.end(), n);
            if (iter == tails.end()) {
                tails.push_back(n);
            } else if (n < *iter) {
                *iter = n;
            }
		}

		return tails.size();
    }
    /******************************************************************/ 
    int ceil_element(const std::vector<int>& DP, int left, int right, const int key) {
        while (right - left > 1) {
            const int mid = left + (right - left) / 2;
            if (DP[mid] >= key) {
                right = mid;
            } else {
                left = mid;
            }
        }

        return right;
    }

    int solution4(const std::vector<int>& A) {
        /* Time-Complexity:     O(N * log(N))
         * Space-Complexity:    O(N)
         */
        /* Explanation:
         * See https://algorithmsandme.com/longest-increasing-subsequence-in-onlogn/
         * 
         * Note: "Top Candidate of an Active List" is the last element of that list.
         *
         * 1. If A[i] is the smallest among all top candidates of active lists, start new active list with A[i] of length 1.
         * 2. If A[i] is largest among all top candidates of active lists, clone the largest active list, and append A[i] to it.
         * 3. If A[i] is in between, find a list with largest top element that is smaller than A[i]. Clone and append A[i] to these lists.
         * 4. Discard all other lists of same length as that of this modified list.
         *
         */

        if (A.empty()) {
            return 0;
        }
        const int N = A.size();

        auto DP = std::vector<int>(N, 0);
        int length = 1;

        DP[0] = A[0];
        for (int i = 1; i < N; ++i) {
            if (A[i] < DP[0]) {
                DP[0] = A[i];
            } else if (A[i] > DP[length-1]) {
                DP[length++] = A[i];
            } else {
                DP[ceil_element(DP, -1, length-1, A[i])] = A[i];
            }
        }

        return length;
    }
    /******************************************************************/
public:
    int lengthOfLIS(vector<int>& nums) {
        return solution4(nums);
    }
};
