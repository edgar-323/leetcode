/*
Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies:

Si % Sj = 0 or Sj % Si = 0.

If there are multiple solutions, return any subset is fine.

Example 1:

Input: [1,2,3]
Output: [1,2] (of course, [1,3] will also be ok)
Example 2:

Input: [1,2,4,8]
Output: [1,2,4,8]
*/


class Solution {
private:
    int N;
    /************************************************************************************************/
    std::vector<int> ans;
    bool is_divisible_subset(const std::vector<int>& subset) {
        const int M = subset.size();
        for (int i = 0; i < M; ++i) {
            for (int j = i+1; j < M; ++j) {
                if (subset[i] % subset[j] and subset[j] % subset[i]) {
                    return false;
                }
            }
        }
        return true;
    }
    void recurse1(const std::vector<int>& nums, const int i, std::vector<int> subset) {
        if (i >= N) {
            if (is_divisible_subset(subset) and ans.size() < subset.size()) {
                ans = subset;
            }
            return;
        }
        recurse1(nums, i+1, subset);
        subset.push_back(nums[i]);
        recurse1(nums, i+1, subset);
    }
    std::vector<int> solution1(const std::vector<int>& nums) {
        /* Time-Complexity:     O(T * 2^N)
         * Space-Complexity:    O( )
         *  where T = O(is_divisible_subset(*))
         * */
        N = nums.size();
        ans.clear();
        recurse1(nums, 0, std::vector<int>());
        return ans; 
    }
    /************************************************************************************************/
   	/*
	MATHEMATICS

	Before elaborating the solutions, 
	we give some corollaries that one can derive from the property of modulo operation, 
	which would prove useful later to solve the problem.

	Given a list of values [E, F, G] sorted in ascending order (i.e. E < F < G), 
	and [assuming] the list itself forms a divisible subset as described in the problem, 
	then we could extend the subset without enumerating all numbers in the subset, in the following two cases:
	
	Corollary I: 	For any value that can be divided by the largest element in the divisible subset, 
					by adding the new value into the subset, one can form another divisible subset, 
					i.e. for all h, if h % G == 0, then [E, F, G, h] forms a new divisible subset. 
	Corollary II: 	For all value that can divide the smallest element in the subset, 
					by adding the new value into the subset, one can form another divisible subset, 
					i.e. for all d, if E % d == 0, then [d, E, F, G] forms a new divisible subset.
	
	The above two corollaries could help us to structure an efficient solution, 
	since it suffices to have just one comparison in order to extend the subset. 
	
	*/
	/************************************************************************************************/
	/*
	DYNAMIC-PRPGRAMMING
	
	At the first glance, the problem might seem to be similar with those combination problems such as two sum and 3sum. 
	Indeed, like those combinations problems, it turned out to be rather helpful to sort the original list first, 
	which would help us to reduce the number of enumerations at the end.

	As another benefit of sorting the original list, we would be able to apply the mathematical corollaries explained at 
	the beginning of the article.

	So first of all, we sort the original list. 
	And as it turns out, this is another dynamic programming problem. 
	The key of solving a dynamic programming problem is to formulate the problem in a recursive and sound way.

	Here is our attempt, which you would see some theoretical supports later.

	For an ordered list [X1,X2,...,XN] we claim that the largest divisible subset from this list is the largest subset 
	among all possible divisible subsets that end with each of the number in the list.

	Let us define a function named EDS(Xi), which gives the largest divisible subset that ends with the number Xi.
	By "ends with", we mean that the number Xi should be the largest number in the subset. 
	For example, given the list [2,4,7,8] , let us calculate EDS(4) by enumeration.
	First, we list all divisible subsets that ends with 4, which should be {4} and {2, 4}.
	Then by definition, we have EDS(4) = {2,4}.
	Similarly, one can obtain that EDS(2) = {2} and EDS(7) = {7}.

	Note: a single number itself forms a divisible subset as well, though it might not be clearly stated in the problem statement.

	Finally let us define our target function that gives the largest divisible subset from an order list [X1,X2,...,XN],
	as LDS([X1,X2,...,XN]).
	Now, without further due, we claim that the following equation should hold:
		LDS([X1,X2,...,XN]) = EDS(Xi) s.t. len(EDS(Xi)) = max{ len(EDS(Xj)) | j € [0, N) }
	
	We could calculate the function EDS(Xi) recursively, with the corollaries we defined at the beginning of the article.
	
	*/
	/************************************************************************************************/
	/*	
	ALGORITHM

	Let us explain the algorithm on how to calculate EDS(Xi), following the above example with the list of [2,4,7,8].
	
	As a reminder, previously we have obtained the EDS(Xi) value for all elements less than 8, i.e.:
	EDS(2) = {2}, EDS(4) = {2,4}, EDS(7) = {7}.
	
	To obtain EDS(8), we simply enumerate all elements before 8 and their EDS(Xi) values respectively, with the following procedure:
	
	*	If the number 8 can be divided by the element Xi, then by appending the number 8 to EDS(Xi), 
		according to our Corollary I, we obtain another divisible subset that ends with 8.
		And this new subset stands as a potential value for EDS(8).
		For example, since 8 % 2 == 0, {2, 8} could be the final value for EDS(8), and similarly with the subset {2,4,8}
		obtained from EDS(4).
	*	If the number 8 can NOT be divided by the element Xi, then we could be sure that the value of EDS(Xi) would not contribute to 
		EDS(8), according to the definition of divisible subset.
		For example, the subset EDS(7) = {7} has no impact for EDS(8).
	*	We then pick the largest new subsets that we form with the help of EDS(Xi).
		Particularly, the subset {8} stands for a valid candidate for EDS(8).
		And in a hypothetical case where 8 cannot be divided by any of its previous elements, we would have EDS(8) = {8}. 			

	*/
	/************************************************************************************************/
 
    std::vector<int> solution2(std::vector<int>& nums) {
        /* Time-Complexity:     O(N^2)
         * Space-Complexity:    O(N^2)
         * */

        N = nums.size();
        if (not N) {
            return {};
        }
        std::sort(nums.begin(), nums.end());
        auto EDS = std::vector<std::vector<int>>(N);
        
        int m = 0;
        for (int i = 0; i < N; ++i) {
            int k = i;
            for (int j = 0; j < i; ++j) {
                if (nums[i] % nums[j] == 0 and EDS[k].size() < EDS[j].size()) {
                    k = j;
                }
            }
            if (k != i) {
                EDS[i] = EDS[k];
            }
            EDS[i].push_back(nums[i]);
            
            if (EDS[m].size() < EDS[i].size()) {
                m = i;
            }
        }
        
        return EDS[m];
    }
    /************************************************************************************************/
public:
    std::vector<int> largestDivisibleSubset(std::vector<int>& nums) {
  		return solution2(nums);      
    }
};
