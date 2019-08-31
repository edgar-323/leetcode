/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

For example,
[2,3,4], the median is 3
[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:
void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
 

Example:
addNum(1)
addNum(2)
findMedian() -> 1.5
addNum(3) 
findMedian() -> 2
 

Follow up:
If all integer numbers from the stream are between 0 and 100, how would you optimize it?
If 99% of all integer numbers from the stream are between 0 and 100, how would you optimize it?
*/

#include "bostree.h"
#include <vector>

static const auto cmp = [] (const void* _a, const void* _b) -> int {
    int a = *((int*) _a); 
    int b = *((int*) _b);
    return (a == b) ? 0 : ((a < b) ? -1 : 1);
};

class MedianFinder {
private:
    BOSTree* tree;
    std::vector<int> elems;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        tree = bostree_new( cmp, NULL );
    }
    
    void addNum(int a) {
        elems.push_back( a );
        bostree_insert( tree, &elems[elems.size()-1], NULL ); 
        assert( elems.size() == bostree_node_count( tree ) );
    }
    
    double findMedian() {
        const size_t N = elems.size();
        assert( N > 0 );
        if (N % 2 == 0) {
           int a = *((int*) (bostree_select( tree, N/2-1 )->key));
           int b = *((int*) (bostree_select( tree, N/2 )->key));
           return double(a + b) / 2.0;
        } else {
            int mid = *((int*) (bostree_select( tree, N/2 )->key));
            return double( mid );
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
