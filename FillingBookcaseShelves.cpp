/*
We have a sequence of books: the i-th book has thickness books[i][0] and height books[i][1].
We want to place these books in order onto bookcase shelves that have total width shelf_width.
We choose some of the books to place on this shelf (such that the sum of their thickness is <= shelf_width), then build another level of shelf of the bookcase so that the total height of the bookcase has increased by the maximum height of the books we just put down.  
We repeat this process until there are no more books to place.
Note again that at each step of the above process, the order of the books we place is the same order as the given sequence of books.  
For example, if we have an ordered list of 5 books, we might place the first and second book onto the first shelf, the third book on the second shelf, and the fourth and fifth book on the last shelf.
Return the minimum possible height that the total bookshelf can be after placing shelves in this manner.

Example 1:
Input: books = [[1,1],[2,3],[2,3],[1,1],[1,1],[1,1],[1,2]], shelf_width = 4
Output: 6
Explanation:
The sum of the heights of the 3 shelves are 1 + 3 + 2 = 6.
Notice that book number 2 does not have to be on the first shelf.
 
Constraints:
1 <= books.length <= 1000
1 <= books[i][0] <= shelf_width <= 1000
1 <= books[i][1] <= 1000
*/

class Solution {
private:
    static const int width  = 0;
    static const int height = 1;
    int N;
    int shelf_width;

    bool fits_in_shelf(const std::vector<int>& book, const int remaining_width) {
        return remaining_width >= book[width];
    }
    /******************************************************************************/
	int recurse1(const std::vector<std::vector<int>>& books, const int i) {
        if (i >= N) {
            return 0;
        }
        // We begin a new bookshelf with `book` as first book in the shelf.
        // Consequently, `book[1]` will be minimum height of this height.
        int shelf_height = books[i][height];
        int remaining_width = shelf_width - books[i][width];
        int j = i+1;
        // first we only include `book` in this shelf
        int min_height = shelf_height + recurse1( books, j );
        // now we try to include as many books as possible and see if its 
        // forces overall height to reduce
        for (; j < N and fits_in_shelf(books[j], remaining_width); ++j) {
            // shelf height will be the height of tallest book
            // in this shelf
            shelf_height        = std::max( shelf_height, books[j][height] );     
            // Can we do better by including books[i:j] in this shelf ?
            min_height          = std::min( min_height, shelf_height + recurse1( books, j+1 ) );
            // update remaining shelf space
            remaining_width    -= books[j][width];
        }
        
        return min_height; 
    }
    
    int solution1(const std::vector<std::vector<int>>& books, const int shelf_width) {
        N = books.size();
        if ( !N ) {
            return 0;
        }
        this->shelf_width = shelf_width;
        
        return recurse1( books, 0 );
	}
    /********************************************************************************/
    int* cache2;
    
    void cache2_init() {
        cache2 = new int[N];
        memset( cache2, -1, N );
    }
    
    void cache2_cleanup() {
        delete [] cache2;
        cache2 = NULL;
    }
    
    int recurse2(const std::vector<std::vector<int>>& books, const int i) {
        if (i >= N) {
            return 0;
        } else if (cache2[i] >= 0) {
            return cache2[i];
        }

        int shelf_height = books[i][height];
        int remaining_width = shelf_width - books[i][width];
        int j = i+1;
                
        int min_height = shelf_height + recurse2( books, j );
        for (; j < N and fits_in_shelf(books[j], remaining_width); ++j) {
            shelf_height        = std::max( shelf_height, books[j][height] );
            min_height          = std::min( min_height, shelf_height + recurse2( books, j+1 ) );
            remaining_width    -= books[j][width];
        }

        return (cache2[i] = min_height);
    }

    int solution2(const std::vector<std::vector<int>>& books, const int shelf_width) {
        N = books.size();
        if ( !N ) {
            return 0;
        }
        
        this->shelf_width = shelf_width;
        
        cache2_init();
        int min_height = recurse2( books, 0 );
        cache2_cleanup();

        return min_height;
    }
    /*******************************************************************************/
    int solution3(const std::vector<std::vector<int>>& books, const int shelf_width) {
        /* Time-Comlexity:  O( N^2 )
         * Space-Comlexity: O(  N  )
         * */
        N = books.size();
        if ( !N ) {
            return 0;
        }

        auto DP = std::vector<int>( N+1, INT_MAX );
        
        for (int i = N-1; i >= 0; --i) {
            int shelf_height = books[i][height];
            int remaining_width = shelf_width - books[i][width];
            DP[i] = shelf_height + DP[i+1];
            for (int j = i+1; j < N and fits_in_shelf(books[j], remaining_width); ++j) {
                shelf_height = std::max( shelf_height, books[j][height] );
                DP[i] = std::min( DP[i], shelf_height + DP[j+1] );
                remaining_width -= books[j][width];       
            }
        }

        return DP[0];
    }
    /******************************************************************************/ 
public:
    int minHeightShelves(vector<vector<int>>& books, int shelf_width) {
		return solution3( books, shelf_width);        
    }
};
