/*
Design an in-memory file system to simulate the following functions:

`ls`:
Given a path in string format.
If it is a file path, return a list that only contains this file's name.
If it is a directory path, return the list of file and directory names in this directory.
Your output (file and directory names together) should in lexicographic order.

`mkdir`:
Given a directory path that does not exist, you should make a new directory according to the path.
If the middle directories in the path don't exist either, you should create them as well.
This function has void return type.

`addContentToFile`:
Given a file path and file content in string format.
If the file doesn't exist, you need to create that file containing given content.
If the file already exists, you need to append given content to original content.
This function has void return type.

`readContentFromFile`:
Given a file path, return its content in string format.

Example:
Input:
["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]
Output:
[null,[],null,null,["a"],"hello"]
Explanation:
<See Image>

Note:
    1)  You can assume all file or directory paths are absolute paths 
        which begin with / and do not end with / except that the path is just "/".
    2)  You can assume that all operations will be passed valid parameters 
        and users will not attempt to retrieve file content 
        or list a directory or file that does not exist.
    3)  You can assume that all directory names and file names only contain lower-case letters, 
        and same names won't exist in the same directory.
*/

class FileNode {
private:
    std::map<std::string, FileNode*> children;
    std::string node_name;
    bool is_file;
    std::string file_contents;

    FileNode* get_file_node(const std::string& path, const int start, const bool as_file) {
        const int N = path.size();
        int end = start;
        while (end < N and path[end] != '/') {
            ++end;
        }
        if (start == end) {
            return this;
        }
        const auto file_name = path.substr(start, end - start);
        if (not children.count(file_name)) {
            children[file_name] = new FileNode(file_name, end == N ? as_file : false);
        }
        return children[file_name]->get_file_node(path, end+1, as_file);
    }
public:
    FileNode(const std::string& name, const bool as_file) {
        node_name = name;
        is_file = as_file;
        file_contents = "";
    }

    FileNode* get_file_node(const std::string& path, const bool as_file = false) {
        return get_file_node(path, 1, as_file);
    }

    std::vector<std::string> ls() const {
        if (is_file) {
            return {node_name};
        }
        auto results = std::vector<std::string>();
        results.reserve(children.size());
        for (const auto& child : children) {
            results.push_back(child.first);
        }
        return results;
    }

    void add_contents(const std::string& contents) {
        file_contents += contents;
    }

    std::string read_contents() const {
        return file_contents;
    }
};

class FileSystem {
private:
    FileNode* root;
public:
    FileSystem() {
        root = new FileNode("", false); 
    }
    
    vector<string> ls(string path) {
        return root->get_file_node(path)->ls();
    }
    
    void mkdir(string path) {
        root->get_file_node(path);
    }
    
    void addContentToFile(string filePath, string content) {
        root->get_file_node(filePath, true)->add_contents(content);
    }
    
    string readContentFromFile(string filePath) {
        return root->get_file_node(filePath, true)->read_contents();
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * vector<string> param_1 = obj->ls(path);
 * obj->mkdir(path);
 * obj->addContentToFile(filePath,content);
 * string param_4 = obj->readContentFromFile(filePath);
 */
