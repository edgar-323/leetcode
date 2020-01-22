/*
On a single threaded CPU, we execute some functions.  Each function has a unique id between 0 and N-1.
We store logs in timestamp order that describe when a function is entered or exited.
Each log is a string with this format: "{function_id}:{"start" | "end"}:{timestamp}".  For example, "0:start:3" means the function with id 0 started at the beginning of timestamp 3.  "1:end:2" means the function with id 1 ended at the end of timestamp 2.
A function's exclusive time is the number of units of time spent in this function.  Note that this does not include any recursive calls to child functions.
The CPU is single threaded which means that only one function is being executed at a given time unit.
Return the exclusive time of each function, sorted by their function id.

Example 1:
Input:
n = 2
logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]
Output: [3, 4]
Explanation:
Function 0 starts at the beginning of time 0, then it executes 2 units of time and reaches the end of time 1.
Now function 1 starts at the beginning of time 2, executes 4 units of time and ends at time 5.
Function 0 is running again at the beginning of time 6, and also ends at the end of time 6, thus executing for 1 unit of time. 
So function 0 spends 2 + 1 = 3 units of total time executing, and function 1 spends 4 units of total time executing.

Note:
1 <= n <= 100
Two functions won't start or end at the same time.
Functions will always log when they exit.
*/
class Solution {
private:
    void parse_log(const std::string& log, int& id, bool& is_start_log, int& time) {
        // parses some function's log according to the given spec.
        // Assumes log string is correctly formatted (i.e., no error can arise via parsing).
        int i = 0;
        while (log[i] != ':') {
            ++i;
        }
        id = std::stoi(log.substr(0, i++));
        if (log[i] == 's') {
            is_start_log = true;
            i += 6; // start:
        } else {
            is_start_log = false;
            i += 4; // end:
        }
        time = std::stoi(log.substr(i));
    }

    int recurse1(const std::vector<std::string>& logs, int& log_index, std::vector<int>& exclusive_time) {
        // This routine assumes that we are at the start of some function currently.
        // So we record the start_time of this function (along with its id so that we can update exclusive_time[]).
        // Additionally, this rountine will return the total time the current function (along with its child functions)
        // ran for.
        int fn_id;
        bool is_start_log; // assumed to be true (initially)
        int start_time;
        parse_log(logs[log_index], fn_id, is_start_log, start_time);
        log_index++;

        int inclusive_time = 0; // There may be more functions between start and end time of the current function and so this variable will record their total execution time

        int curr_time;
        parse_log(logs[log_index], fn_id, is_start_log, curr_time);
        // while we havent reached the end of current function
        while (is_start_log) {
            inclusive_time += recurse1(logs, log_index, exclusive_time); // add execution time of child functions to inclusive_time
            parse_log(logs[log_index], fn_id, is_start_log, curr_time);
        }
        ++log_index;

        exclusive_time[fn_id] += (1 + curr_time - start_time - inclusive_time); // this is how long current function actually ran for
        
        return 1 + curr_time - start_time; // this is how long current (and child) function took in total
    }

    std::vector<int> solution1(const int N, const std::vector<std::string>& logs) {
        /* Time-Complexity:     O(N + L)
         * Space-Complexity:    O(N + L)
         *      Where:
         *          N = # of functions
         *          L = # of logs
         */
        auto exclusive_time = std::vector<int>(N, 0);

        const int L = logs.size();
        int log_index = 0;
        // while we haven't read all the logs
        while (log_index < L) {
            recurse1(logs, log_index, exclusive_time);
        }

        return exclusive_time;
    }
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        return solution1(n, logs);        
    }
};
