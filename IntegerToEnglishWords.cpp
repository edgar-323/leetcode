/*
Convert a non-negative integer to its english words representation. Given input is guaranteed to be less than 231 - 1.

Example 1:
Input: 123
Output: "One Hundred Twenty Three"

Example 2:
Input: 12345
Output: "Twelve Thousand Three Hundred Forty Five"

Example 3:
Input: 1234567
Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"

Example 4:
Input: 1234567891
Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One"
*/
class Solution {
private:
    std::string one(const int num) {
        switch (num) {
            case 1: return "One";
            case 2: return "Two";
            case 3: return "Three";
            case 4: return "Four";
            case 5: return "Five";
            case 6: return "Six";
            case 7: return "Seven";
            case 8: return "Eight";
            case 9: return "Nine";
            default: return "";
        }
    }

    std::string two_less_than_20(const int num) {
		switch(num) {
            case 10: return "Ten";
            case 11: return "Eleven";
            case 12: return "Twelve";
            case 13: return "Thirteen";
            case 14: return "Fourteen";
            case 15: return "Fifteen";
            case 16: return "Sixteen";
            case 17: return "Seventeen";
            case 18: return "Eighteen";
            case 19: return "Nineteen";
            default: return "";
        }
    }

    std::string ten(const int num) {
       	switch(num) {
            case 2: return "Twenty";
            case 3: return "Thirty";
            case 4: return "Forty";
            case 5: return "Fifty";
            case 6: return "Sixty";
            case 7: return "Seventy";
            case 8: return "Eighty";
            case 9: return "Ninety";
            default: return "";
        }
    }

    std::string two(const int num) {
        if (not num) {
            return "";
        } else if (num < 10) {
            return one(num);
        } else if (num < 20) {
            return two_less_than_20(num);
        } else {
            int tenner = num / 10;
            int rest = num - tenner * 1e1;
            return  ten(tenner) +
                    (rest ? std::string(" ") + one(rest) : "");
        }
    } 

    std::string three(const int num) {
        int hundred = num / 1e2;
        int rest = num - hundred * 1e2;
        auto result = std::string("");
        if (hundred*rest) {
            result = one(hundred) + " Hundred " + two(rest);
        } else if (not hundred and rest) {
            result = two(rest);
        } else if (hundred and not rest) {
            result = one(hundred) + " Hundred";
        }
        return result;
    }

    std::string solution1(const int N) {
        if (not N) {
            return "Zero";
        }
        int billion = N / 1e9;
        int million = (N - billion * 1e9) / 1e6;
        int thousand = (N - billion * 1e9 - million * 1e6) / 1e3;
        int rest = N - billion * 1e9 - million * 1e6 - thousand * 1e3;
        
        auto result = std::string("");
        if (billion) {
            result += three(billion) + " Billion";
        }
        if (million) {
            result += (result.empty() ? "" : " ") + three(million) + " Million";
        }
        if (thousand) {
            result += (result.empty() ? "" : " ") + three(thousand) + " Thousand";
        }
        if (rest) {
            result += (result.empty() ? "" : " ") + three(rest);
        }
        return result;
    }
public:
    string numberToWords(int num) {
        return solution1(num);        
    }
};
