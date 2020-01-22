/*
In a project, you have a list of required skills req_skills, and a list of people.  
The i-th person people[i] contains a list of skills that person has.

Consider a sufficient team: a set of people such that for every required skill in req_skills, 
                            there is at least one person in the team who has that skill.  
We can represent these teams by the index of each person:  for example, team = [0, 1, 3] represents the people with skills people[0], people[1], and people[3].

Return any sufficient team of the smallest possible size, represented by the index of each person.

You may return the answer in any order.  
It is guaranteed an answer exists.

 

Example 1:
Input: req_skills = ["java","nodejs","reactjs"], people = [["java"],["nodejs"],["nodejs","reactjs"]]
Output: [0,2]

Example 2:
Input: req_skills = ["algorithms","math","java","reactjs","csharp","aws"], people = [["algorithms","math","java"],["algorithms","math","reactjs"],["java","csharp","aws"],["reactjs","csharp"],["csharp","math"],["aws","java"]]
Output: [1,2]

Constraints:
1 <= req_skills.length <= 16
1 <= people.length <= 60
1 <= people[i].length, req_skills[i].length, people[i][j].length <= 16
Elements of req_skills and people[i] are (respectively) distinct.
req_skills[i][j], people[i][j][k] are lowercase English letters.
Every skill in people[i] is a skill in req_skills.
It is guaranteed a sufficient team exists.
*/

class Solution {
private:
    int M,N;
    int** cache1;

    void init_cache1() {
        cache1 = new int*[1 << M];
        for (int i = 0; i < (1 << M); ++i) {
            cache1[i] = new int[N+1];
            for (int j = 0; j <= N; ++j) {
                cache1[i][j] = -1;
            }
        }
    } 

    void destroy_cache1() {
        for (int i = 0; i < (1 << M); ++i) {
            delete[] cache1[i];
        }
        delete[] cache1;
    }

    std::unordered_map<std::string, int>* skill_map;
    
    void init_skill_map(const std::vector<std::string>& req_skills) {
        skill_map = new std::unordered_map<std::string, int>();
        for (int i = 0; i < M; ++i) {
            skill_map->insert(std::make_pair(req_skills[i], i));
        }
    }
    
    void destroy_skill_map() {
        delete skill_map;
    }
    
    int get_skills(const int skills, const std::vector<std::string>& person) {
        int new_skills = skills;
        for (const auto& skill : person) {
            const int i = skill_map->at(skill);
            new_skills = new_skills | (1 << i);
        }

        return new_skills; 
    }
    
    int recurse1(const int skills, const int i, const std::vector<std::vector<std::string>>& ppl) {
        if (cache1[skills][i] >= 0) {
            return cache1[skills][i];
        }
        int min_ppl;
        if (i == N) {
            // No more ppl left
            // Either all sklls are cover, in which case answer is 0, or its not covered in which
            // case answer is infinity
            min_ppl = skills == ((1 << M) - 1) ? 0 : INT_MAX;
        } else {
            min_ppl = recurse1(skills, i+1, ppl);
            const int x = recurse1(get_skills(skills, ppl[i]), i+1, ppl);
            if (x < INT_MAX) {
                min_ppl = std::min(min_ppl, 1 + x);
            }
        }

        return cache1[skills][i] = min_ppl;
    }
    
    void build1(const int skills, const int i, const std::vector<std::vector<std::string>>& ppl, std::vector<int>& result) {
        if (i == N) {
            return;
        }
        
        const int x = recurse1(skills, i+1, ppl);
        const int y = recurse1(get_skills(skills, ppl[i]), i+1, ppl);
        if (x <= y) {
            // We don't need ith person
            build1(skills, i+1, ppl, result);
        } else {
            // We need ith person
            result.push_back(i);
            build1(get_skills(skills, ppl[i]), i+1, ppl, result);
        }
    }
    
    std::vector<int> solution1(const std::vector<std::string>& req_skills, const std::vector<std::vector<std::string>>& ppl) {
        /* Time-Complexity:     O(2^M * N)
         * Space-Complexity:    O(2^M * N)
         */
        M = req_skills.size();
        N = ppl.size();

        init_skill_map(req_skills);
        init_cache1();
        auto result = std::vector<int>();
        build1(0, 0, ppl, result);
        destroy_cache1();
        destroy_skill_map();

        return result;
    }
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        return solution1(req_skills, people); 
    }
};
