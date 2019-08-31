/*
Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?

Example:

Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

class Solution {
private:
    int solution1(const int N) {
        /*
        ******************************************************************************
        This is my soluton, which I derived by noticing symmetrical 
        patterns that occur when drawing/producing all BSTs of size N.
        In particular, I derived the recurrence:
            U[N] = 2*SUM{U[k]*U[N-1-k] for k in range(0,N/2)} + U[N/2]^2 [if N is odd]
        But I was unable to derive an analytical expression for this recurrence.
        Thus, I was forced to employ a Dynamic-Programming method to solve this.
        ******************************************************************************
        UPDATE:
        It can be shown that the equation I derived is that of the "Catalan Numbers".
        More importantly, the equation can be simplifed to:
            U[N] = 2*(2*n+1)*C[N-1] / (N+2)
        Which can be easily computed in O(N) time using O(1) Space since C[N] depends
		only on C[N-1].
        ******************************************************************************
        Time-Complexity:
            ==> SUM{i/2 for i in range(0, N)}
            ==> (1/2)*SUM{i for i in range(0, N)}
            ==> (1/2)*N*(N+1)/2
            ==> N*(N+1)/4
            ==> O(N^2)
        Space-Complexity:
            ==> N+1
            ==> O(N)
        ******************************************************************************
        */
        if (N <= 0) {
            return 0;
        }
        vector<int> unique(N+1, 0);
        int mid;
        unique[0] = unique[1] = 1;
        for (int i = 2; i < N+1; ++i) {
            mid = i / 2;
            for (int k = 0; k < mid; ++k) {
                unique[i] += (unique[k]*unique[i-1-k]);
            }
            unique[i] = 2*unique[i] + ((i%2 == 1) ? unique[mid]*unique[mid] : 0);
        }
        return unique[N];
    }
    
public:
    int numTrees(int n) {
        return solution1(n);
    }
};
