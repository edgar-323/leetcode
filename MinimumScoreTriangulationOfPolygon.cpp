/*
Given N, consider a convex N-sided polygon with vertices labelled A[0], A[i], ..., A[N-1] in clockwise order.
Suppose you triangulate the polygon into N-2 triangles.  
For each triangle, the value of that triangle is the product of the labels of the vertices, and the total score of the triangulation is the sum of these values over all N-2 triangles in the triangulation.
Return the smallest possible total score that you can achieve with some triangulation of the polygon.
 
Example 1:
Input: [1,2,3]
Output: 6
Explanation: The polygon is already triangulated, and the score of the only triangle is 6.

Example 2:
Input: [3,7,4,5]
Output: 144
Explanation: There are two triangulations, with possible scores: 3*7*5 + 4*5*7 = 245, or 3*4*5 + 3*4*7 = 144.  The minimum score is 144.

Example 3:
Input: [1,3,1,4,1,5]
Output: 13
Explanation: The minimum score triangulation has score 1*1*3 + 1*1*4 + 1*1*5 + 1*1*1 = 13.

Note:
3 <= A.length <= 50
1 <= A[i] <= 100
*/

class Solution {
private:
    int N;
    /************************************************************************************************/
    int** cache1;
    void init_cache1() {
        cache1 = new int*[N+1];
        for (int i = 0; i <= N; ++i) {
            cache1[i] = new int[N+1];
            for (int j = 0; j <= N; ++j) {
                cache1[i][j] = -1;
            }
        }
    }
    void destroy_cache1() {
        for (int i = 0; i <= N; ++i) {
            delete[] cache1[i];
        }
        delete[] cache1;
    }
    int in_cache1(const int i, const int j) {
        return cache1[i][j] >= 0;
    }
    int set_cache1(const int i, const int j, const int min_score) {
        return cache1[i][j] = min_score;
    }
    int recurse(const int i, const int j, const std::vector<int>& A) {
        if (in_cache1(i, j)) {
            return cache1[i][j];
        }
        int min_score;
        if (j - i < 2) {
            // Not a polygon
            min_score = 0;
        } else if (j - i == 2) {
            // Polygon is a triangle
            min_score = A[i] * A[i+1] * A[i+2]; 
        } else {
            min_score = INT_MAX;
            for (int k = i+1; k < j; ++k) {
                min_score = std::min(min_score, A[i]*A[k]*A[j] + recurse(i, k, A) + recurse(k, j, A));
            }
        }

        return set_cache1(i, j, min_score);
    }
	int solution1(const std::vector<int>& A) {
        N = A.size();
        init_cache1();
        const int min_score = recurse(0, N-1, A);
        destroy_cache1();

        return min_score;
	}
    /************************************************************************************************/
public:
    int minScoreTriangulation(vector<int>& A) {
  		return solution1(A);      
    }
};
