/*
Given an array arr of positive integers, consider all binary trees such that:
1) Each node has either 0 or 2 children;
2) The values of arr correspond to the values of each leaf in an in-order traversal of the tree.  
   (Recall that a node is a leaf if and only if it has 0 children.)
3) The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree respectively.   

Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node.  
It is guaranteed this sum fits into a 32-bit integer.

Example 1:
Input: arr = [6,2,4]
Output: 32
Explanation:
There are two possible trees.  The first has non-leaf node sum 36, and the second has non-leaf node sum 32.

    24            24
   /  \          /  \
  12   4        6    8
 /  \               / \
6    2             2   4
 
Constraints:
2 <= arr.length <= 40
1 <= arr[i] <= 15
It is guaranteed that the answer fits into a 32-bit signed integer (ie. it is less than 2^31).
*/

class Solution {
private:
    typedef std::vector<int> Leafs;

    int max_element(const Leafs& leafs, const int begin, const int end) {
        return *std::max_element( leafs.begin() + begin, leafs.begin() + end );
    }
    int recurse1(const Leafs& leafs,
                const int begin,
                const int end) {
        // ASSUMPTIONS:
        // 0 <= begin < end < N
        // end - begin >= 2
       
        if (end - begin < 2) {
            return 0;
        } else if (end - begin == 2) {
            return leafs[begin] * leafs[end-1]; 
        }
        // At least 3 elements to consider... 
        int min_val = INT_MAX;
        for (int i = begin + 1; i < end; ++i) {
            int left    = max_element( leafs, begin, i   );
            int right   = max_element( leafs, i    , end );
            min_val     = std::min(
                            min_val,
                            left*right + recurse1( leafs, begin, i ) + recurse1( leafs, i , end )
                          );
        }
        return min_val;
    }
	int solution1(const Leafs& leafs) {
        /* Time-Complexity:     O( EXPONENTIAL )
         * Space-Complexity:    O(     N       )
         * */
        return recurse1(leafs, 0, leafs.size());
    }

    int recurse2(const std::vector<int>& leafs,
                 const int begin,
                 const int end,
                 const std::vector<std::vector<int>>& max_elem,
                 std::vector<std::vector<int>>& cache) {
        if (cache[begin][end] >= 0) {
            return cache[begin][end];
        }
        if (end - begin < 2) {
            cache[begin][end] = 0;
        } else if (end - begin == 2) {
            cache[begin][end] = leafs[begin] * leafs[end-1];
        } else {
            int min_val = INT_MAX;
            for (int i = begin + 1; i < end; ++i) {
                int left = max_elem[begin][i-1];
                int right = max_elem[i][end-1];
                min_val = std::min(
                                min_val,
                                left*right + 
                                recurse2( leafs, begin, i, max_elem, cache ) +
                                recurse2( leafs, i, end, max_elem, cache )
                          );
            }
            cache[begin][end] = min_val;
        }
        return cache[begin][end];
    }
    int solution2(const Leafs& leafs) {
        /* Time-Complexity:     O( N^3 )
         * Space-Complexity:    O( N^2 )
         * */
        const int N = leafs.size();
        auto max_elem = std::vector<std::vector<int>>( N, std::vector<int>( N, 0 ) );
        for (int i = 0; i < N; ++i) {
            max_elem[i][i] = leafs[i]; 
            for (int j = i+1; j < N; ++j) {
                max_elem[i][j] = std::max( max_elem[i][j-1], leafs[j] );
            }
        }
        auto cache = std::vector<std::vector<int>>( N, std::vector<int>( N+1, -1 ) );

        return recurse2( leafs, 0, leafs.size(), max_elem, cache );
    }

    int solution3(const Leafs& leafs) {
        /* Time-Complexity:     O( N^3 )
         * Space-Complexity:    O( N^2 )
         * */
        const int N = leafs.size();
		auto max_elem = std::vector<std::vector<int>>( N, std::vector<int>( N, 0 ) );
        for (int i = 0; i < N; ++i) {
            max_elem[i][i] = leafs[i];
            for (int j = i+1; j < N; ++j) {
                max_elem[i][j] = std::max( max_elem[i][j-1], leafs[j] );
            }
        }
        auto DP = std::vector<std::vector<int>>( N, std::vector<int>( N+1, INT_MAX ) );
        // size 1 
        for (int i = 0; i < N; ++i) {
            DP[i][i+1] = 0;
        }
        // size 2
        for (int i = 0; i < N-1; ++i) {
            DP[i][i+2] = leafs[i] * leafs[i+1]; 
        }
        // size >= 3
        for (int sz = 3; sz <= N; ++sz) {
            for (int begin = 0, end = sz; end <= N; ++begin, ++end) {
                for (int i = begin+1; i < end; ++i) {
                    int inner_node_val = max_elem[begin][i-1] * max_elem[i][end-1];
                    DP[begin][end] = std::min(
                                        DP[begin][end],
                                        inner_node_val + DP[begin][i] + DP[i][end]
                                     );
                }
            }
        }

        return DP[0][N]; 
    }

    int solution4(Leafs& leafs) {
        /* Time-Complexity:     O( N^2 )
         * Space-Complexity:    O(  1  )
         * */
        // Explanation:
        // This method "joins the leaves from the bottom-up while keeping track of inner-node
        // sums along the way".
        // This solution notices that at any given time in the process, the next best pair of leaves
        // to join are the ones that produce a minimum product among all adjacent leaf products.
        // Why is this?
        // By working through a few examples by hand (and building possible trees along the way), you will
        // notice that this will maintain minimum values among all inner-nodes.
        // This strategy has a greedy property, but is in fact correct.
        int inner_node_sum = 0;
        
        // while inner nodes remain
        while (leafs.size() > 1) {
            const int N         = leafs.size();
            int min_adj_prod    = INT_MAX;
            int min_index       = -1;
            
            for (int i = 0; i < N-1; ++i) {
                int curr_adj_prod = leafs[i] * leafs[i+1];
                if (curr_adj_prod < min_adj_prod) {
                    min_adj_prod    = curr_adj_prod;
                    min_index       = leafs[i] < leafs[i+1] ? i : i+1;
                }
            }

            inner_node_sum += min_adj_prod;
            leafs.erase( leafs.begin() + min_index );
        }

        return inner_node_sum;
    }

    int solution5(const Leafs& leafs) {
        /* Time-Complexity:     O( N )
         * Space-Complexity:    O( N )
         * */
        /*
			Intuition
			When we build a node in the tree, we compared the two numbers a and b.
			In this process,
			the smaller one is removed and we won't use it anymore,
			and the bigger one actually stays.

			The problem can translated as following:
			Given an array A, choose two neighbors in the array a and b,
			we can remove the smaller one min(a,b) and the cost is a * b.
			What is the minimum cost to remove the whole array until only one left?

			To remove a number a, it needs a cost a * b, where b >= a.
			So a has to be removed by a bigger number.
			We want minimize this cost, so we need to minimize b.

			b has two candidates, the first bigger number on the left,
			the first bigger number on the right.

			The cost to remove a is a * min(left, right).
			With the intuition above in mind,
			we decompose a hard problem into reasonable easy one:
			Just find the next greater element in the array, on the left and one right.
		
            Refer to the problem (503. Next Greater Element II)
        */
        int results = 0;

        auto stack = std::stack<int>();

        for (const auto& leaf : leafs) {
            while (not stack.empty() and leaf >= stack.top()) {
                const auto top = stack.top(); stack.pop();
                results +=  stack.empty() ?
                            top * leaf :
                            top * std::min(stack.top(), leaf);
            }
            stack.push(leaf);
        }
        while (stack.size() > 1) {
            const auto top = stack.top(); stack.pop();
            results += top * stack.top();
        }    

        return results; 
    }
public:
    int mctFromLeafValues(std::vector<int>& arr) {
 		return solution5( arr );
    }
};
