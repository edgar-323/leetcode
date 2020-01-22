/*
Design a hit counter which counts the number of hits received in the past 5 minutes.

Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made to the system in chronological order 
(ie, the timestamp is monotonically increasing). 
You may assume that the earliest timestamp starts at 1.

It is possible that several hits arrive roughly at the same time.

Example:

HitCounter counter = new HitCounter();

// hit at timestamp 1.
counter.hit(1);

// hit at timestamp 2.
counter.hit(2);

// hit at timestamp 3.
counter.hit(3);

// get hits at timestamp 4, should return 3.
counter.getHits(4);

// hit at timestamp 300.
counter.hit(300);

// get hits at timestamp 300, should return 4.
counter.getHits(300);

// get hits at timestamp 301, should return 3.
counter.getHits(301); 

Follow up:
What if the number of hits per second could be very large? Does your design scale?
*/

class HitCounter {
private:
    const static int MIN_LIMIT = 5;
    std::queue<std::pair<int,int>> Q;
    int num_hits;

    void evict_timestamps(const int curr_time, const bool insert) {
        while (not Q.empty() and Q.front().first <= curr_time - MIN_LIMIT*60) {
            num_hits -= Q.front().second;
            Q.pop();
        }
        if (insert) {
            if (not Q.empty() and Q.front().first == curr_time) {
                Q.front().second++;
            } else {
                Q.push({curr_time, 1});
            }
            ++num_hits;
        }
    }
public:
    /** Initialize your data structure here. */
    HitCounter() {
        num_hits = 0; 
    }
    
    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        evict_timestamps(timestamp, true);
    }
    
    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        evict_timestamps(timestamp, false);
        return num_hits; 
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
