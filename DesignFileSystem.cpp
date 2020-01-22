/*
You are asked to design a file system which provides two functions:
    1)  createPath(path, value): 
        Creates a new path and associates a value to it if possible and returns True. 
        Returns False if the path already exists or its parent path doesn't exist.
    2)  get(path): 
        Returns the value associated with a path or returns -1 if the path doesn't exist.

The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. 
For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.
Implement the two functions.

Please refer to the examples for clarifications.

Example 1:
Input: 
["FileSystem","createPath","get"]
[[],["/a",1],["/a"]]
Output: 
[null,true,1]
Explanation: 
FileSystem fileSystem = new FileSystem();
fileSystem.createPath("/a", 1); // return true
fileSystem.get("/a"); // return 1
Example 2:

Input: 
["FileSystem","createPath","createPath","get","createPath","get"]
[[],["/leet",1],["/leet/code",2],["/leet/code"],["/c/d",1],["/c"]]
Output: 
[null,true,true,2,false,-1]
Explanation: 
FileSystem fileSystem = new FileSystem();
fileSystem.createPath("/leet", 1); // return true
fileSystem.createPath("/leet/code", 2); // return true
fileSystem.get("/leet/code"); // return 2
fileSystem.createPath("/c/d", 1); // return false because the parent path "/c" doesn't exist.
fileSystem.get("/c"); // return -1 because this path doesn't exist.
 
Constraints:
The number of calls to the two functions is less than or equal to 10^4 in total.
2 <= path.length <= 100
1 <= value <= 10^9
NOTE: create method has been changed on August 29, 2019 to createPath. Please reset to default code definition to get new method signature.
*/
class FileNode {
private:
    std::string file_name;
    int val;
    std::unordered_map<std::string,FileNode*> child;    

    bool create_path(const std::string& path, const int start, const int val) {
        const int N = path.size();
        int i = start;
        
        while (i < N and path[i] != '/') {
            ++i;
        }
        if (i == start) {
            this->val = val;
            return true;
        }

        const auto child_name = path.substr(start, i - start);
        if (not child.count(child_name)) {
            if (i != N) {
                return false;
            }
             
        }
    }

    int get(const std::string& path, const int pos) {

    }
public:
    FileNode(const std::string& my_name):
        file_name(my_name) {}
    
    bool create_path(const std::string& path, const int val) {
        return create_path(path, 1, val);
    }
};

class FileSystem {
public:
    FileSystem() {
        
    }
    
    bool createPath(string path, int value) {
        
    }
    
    int get(string path) {
        
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->createPath(path,value);
 * int param_2 = obj->get(path);
 */
