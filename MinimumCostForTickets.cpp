/*
In a country popular for train travel, you have planned some train travelling one year in advance.  
The days of the year that you will travel is given as an array days.  
Each day is an integer from 1 to 365.

Train tickets are sold in 3 different ways:

a 1-day pass is sold for costs[0] dollars;
a 7-day pass is sold for costs[1] dollars;
a 30-day pass is sold for costs[2] dollars.
The passes allow that many days of consecutive travel.  
For example, if we get a 7-day pass on day 2, then we can travel for 7 days: day 2, 3, 4, 5, 6, 7, and 8.

Return the minimum number of dollars you need to travel every day in the given list of days.

Example 1:
Input: days = [1,4,6,7,8,20], costs = [2,7,15]
Output: 11
Explanation: 
For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
In total you spent $11 and covered all the days of your travel.

Example 2:
Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
Output: 17
Explanation: 
For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
In total you spent $17 and covered all the days of your travel.

Note:
1 <= days.length <= 365
1 <= days[i] <= 365
days is in strictly increasing order.
costs.length == 3
1 <= costs[i] <= 1000
*/


class Solution {
private:
    int N;
    int one_day_cost;
    int seven_day_cost;
    int thirty_day_cost;
    
    void costs_init(const std::vector<int>& costs) {
        one_day_cost    = costs[0];
        seven_day_cost  = costs[1];
        thirty_day_cost = costs[2];
    }
    
    std::vector<int> day_indices(const std::vector<int>& days, const int index) {
        const int today = days[index];
     	int one_day_index;
        int seven_day_index;
        int thirty_day_index;
        for (one_day_index      = index + 1;
             one_day_index < N      and days[one_day_index]     < (today + 1);
             ++one_day_index);
        for (seven_day_index    = index + 1;
             seven_day_index < N    and days[seven_day_index]   < (today + 7);
             ++seven_day_index);
        for (thirty_day_index   = index + 1;
             thirty_day_index < N   and days[thirty_day_index]  < (today + 30);
             ++thirty_day_index);
      
        return { one_day_index, seven_day_index, thirty_day_index }; 
    }

    /*************************************************************************************************/
    int recurse1(const std::vector<int> days, 
                 const int index, 
                 const int current_cost) {
        if (index >= N) {
            return current_cost; 
        }

        auto indices            = day_indices( days, index );
        auto one_day_index      = indices[0];
        auto seven_day_index    = indices[1];
        auto thirty_day_index   = indices[2];

        return  std::min( 
                std::min( 
                    recurse1( days, one_day_index,      current_cost + one_day_cost ), 
                    recurse1( days, seven_day_index,    current_cost + seven_day_cost ) ), 
                    recurse1( days, thirty_day_index,   current_cost + thirty_day_cost ) );
    }

	int solution1(const std::vector<int>& days, const std::vector<int>& costs) {
        N = days.size();
        if ( !N ) {
            return 0;
        }
        costs_init( costs );
        return recurse1( days, 0, 0 );
	}
    /*************************************************************************************************/
    static const int MAX_DAYS = 365;
    static const int MAX_COST = 1000;
    static const int MAX_TOTAL_COST  = MAX_DAYS * MAX_COST;
    int** cache2;
    void cache2_init() {
        cache2 = new int*[N];
        for (int i = 0; i < N; ++i) {
            cache2[i] = new int[MAX_TOTAL_COST + 1];
            for (int j = 0; j <= MAX_TOTAL_COST; ++j) {
                cache2[i][j] = -1;
            }
        }
    }

    void cache2_cleanup() {
        for (int i = 0; i < N; ++i) {
            delete[] cache2[i];
        }
        delete [] cache2;
        cache2 = NULL;
    }

    bool in_cache2(const int index, const int current_cost) {
        return cache2[index][current_cost] >= 0;
    }

    int get_cache2_value(const int index, const int current_cost) {
        return cache2[index][current_cost];
    }

    int set_cache2_value(const int index, const int current_cost, const int val) {
        return (cache2[index][current_cost] = val);
    }

    int recurse2(const std::vector<int>& days,
                 const int index,
                 const int current_cost) {
        if (index >= N) {
            return current_cost;
        } else if (in_cache2( index, current_cost )) {
            return get_cache2_value( index, current_cost );
        }
    
		auto indices            = day_indices( days, index );
        auto one_day_index      = indices[0];
        auto seven_day_index    = indices[1];
        auto thirty_day_index   = indices[2];

        int min_cost =  std::min(
                	    std::min(
                    		recurse2( days, one_day_index,      current_cost + one_day_cost ),
						    recurse2( days, seven_day_index,    current_cost + seven_day_cost ) ),
							recurse2( days, thirty_day_index,   current_cost + thirty_day_cost ) );
    
        return set_cache2_value( index, current_cost, min_cost );    
	}

    int solution2(const std::vector<int>& days, const std::vector<int>& costs) {
        N = days.size();
        if ( !N ) {
            return 0;
        }
		
        costs_init( costs );
        cache2_init();
        int min_cost = recurse2( days, 0, 0 );
        cache2_cleanup();
        return min_cost;
    }
    /*************************************************************************************************/
    int cache3[MAX_DAYS + 1];
    bool  day_set[MAX_DAYS + 1];
    
    void params3_init(const std::vector<int>& days) {
        memset( cache3, -1, sizeof(cache3) ); 
        memset( day_set, false, sizeof( day_set ) );
        for (const int day : days) {
            day_set[day] = true;
        }
    }
    
    int recurse3(const int day) {
        if (day > MAX_DAYS) {
            return 0;
        } else if (cache3[day] >= 0) {
            return cache3[day];
        }
        
        return cache3[day] = day_set[day] ?
                                std::min(
                                    std::min( 
                                    recurse3( day + 1  ) + one_day_cost,
                                    recurse3( day + 7  ) + seven_day_cost ),
                                    recurse3( day + 30 ) + thirty_day_cost ) : 
                                recurse3( day + 1 );
    }

    int solution3(const std::vector<int>& days, const std::vector<int>& costs) {
        N = days.size();
        if ( !N ) {
            return 0;
        }
        
        costs_init( costs );
        params3_init( days );
        return recurse3( 1 );
    }
    /*************************************************************************************************/
    int* cache4;
    
    void cache4_init() {
        cache4 = new int[N];
        memset( cache4, -1, N );
    }

    void cache4_cleanup() {
        delete [] cache4;
        cache4 = NULL;
    }
        
    int recurse4(const std::vector<int>& days, const int index) {
        if (index >= N) {
            return 0;
        } else if (cache4[index] >= 0) {
            return cache4[index];
        }

       	auto indices            = day_indices( days, index );
        auto one_day_index      = indices[0];
        auto seven_day_index    = indices[1];
        auto thirty_day_index   = indices[2]; 

        return cache4[index] =  std::min<int>(
                                        {
                                            recurse4(days, one_day_index)       + one_day_cost,
                                            recurse4(days, seven_day_index)     + seven_day_cost,
                                            recurse4(days, thirty_day_index)    + thirty_day_cost
                                        });
	}

    int solution4(const std::vector<int>& days, const std::vector<int>& costs) {
        N = days.size();
        if ( !N ) {
            return 0;
        }

        costs_init( costs );
        cache4_init();
        int min_cost = recurse4( days, 0 );
        cache4_cleanup();
        
        return min_cost;
    } 
    /*************************************************************************************************/
public:
    int mincostTickets(std::vector<int>& days, std::vector<int>& costs) {
		return solution4( days, costs );        
    }
};
