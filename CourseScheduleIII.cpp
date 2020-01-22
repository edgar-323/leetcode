/*
There are n different online courses numbered from 1 to n. 
Each course has some duration(course length) t and closed on dth day. 
A course should be taken continuously for t days and must be finished before or on the dth day. 
You will start at the 1st day.
Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.

Example:
Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation: 
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.

Note:
The integer 1 <= d, t, n <= 10,000.
You can't take two courses simultaneously.
*/
class Solution {
private:
    typedef std::vector<int> Course;
    static const int DURATION = 0;
    static const int END = 1;

    int solution1(std::vector<Course>& courses) {
        const int N = courses.size();
        std::sort(courses.begin(), courses.end(),
                    [] (const Course& c1, const Course& c2) -> bool
                    {
                        return c1[END] < c2[END];
                    });
        auto PQ = std::priority_queue<int>(); // Maximum Priority Queue of Integers
        int curr_time = 0;
        for (const auto& course : courses) {
            if (curr_time + course[DURATION] <= course[END]) {
                PQ.push(course[DURATION]);
                curr_time += course[DURATION];
            } else if (not PQ.empty() and PQ.top() > course[DURATION]) {
                curr_time -= (PQ.top() - course[DURATION]);
                PQ.pop();
                PQ.push(course[DURATION]);
            }
        }
        return PQ.size();                
    }
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        return solution1(courses);    
    }
};
