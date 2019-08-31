#include <iostream>
#include <string>
#include <vector>
#include "SelfBalancingTree.h"

void recurse(Node* node, int depth) {
    if ( !node ) {
        //std::cout << "NULL\t@depth " << depth << std::endl;
        return;
    }
    std::cout << "KEY: " << node->key << "\t@depth " << depth <<std::endl;
    std::cout << "LEFT\t@depth " << depth << std::endl;
    recurse( node->left, depth+1 );
    std::cout << "RIGHT\t@depth " << depth << std::endl;
    recurse( node->right, depth+1 );
}

void print_and_exit(Node* node) {
    std::cout << "PRINTING TREE STACK" << std::endl;
    recurse(node, 0);
    exit(0);   
}

int check_balance(Node* node, int& cnt) {
    if ( !node ) {
        return 0;
    }
    ++cnt;
    int left_height = check_balance(node->left, cnt);
    int right_height = check_balance(node->right, cnt);
    
    int bal = left_height - right_height;
    
    if (bal > 1) {
        std::cerr << "UNBALANCED TOWARDS LEFT AT KEY: " << node->key << std::endl;
        print_and_exit(node);
    } else if (bal < -1) {
        std::cerr << "UNBALANCED TOWARDS RIGHT AT KEY: " << node->key << std::endl;
        print_and_exit(node);
    }

    return 1 + std::max(left_height, right_height);
}

void insert_and_check(Node** root, int key, int sz) {
    //std::cout << "Inserting: " << key << std::endl;
    *root = insert(*root, key);
    int cnt = 0;
    check_balance(*root, cnt);
    if (cnt != sz) {
        std::cerr << "NON-MATCHING SIZES AFTER INSERTING KEY: " 
                    << key << ".\nExpected: " << sz << ", Actual: " 
                    << cnt << std::endl;
        print_and_exit(*root);
    } else if (size(*root) != sz) {
        std::cerr << "NON-MATCHING SIZES VIA SIZE(Node*) AFTER "
            << "INSERTING KEY: " << key <<  ".\nExpected: " 
            << sz << ", Actual: " << size(*root) << std::endl; 

        print_and_exit( *root );
    }
}

void print(std::vector<int>::iterator begin,
                std::vector<int>::iterator end) { 
    std::cout << "[";
    for (; begin != end; ++begin) {
        std::cout << *begin 
            << ((begin != (end-1)) ? ", " : "");    
    }
    std::cout << "]" << std::endl;
}

int min(std::vector<int>::iterator begin,
                std::vector<int>::iterator end) { 
    int ret = *begin;
    for (begin = begin+1; begin != end; ++begin) {
        ret = std::min(ret, *begin);
    }
    return ret;
}

int max(std::vector<int>::iterator begin,
                std::vector<int>::iterator end) { 
    int ret = *begin;
    for (begin = begin+1; begin != end; ++begin) {
        ret = std::max(ret, *begin);
    }
    return ret;
}

double median(std::vector<int>::iterator begin,
                std::vector<int>::iterator end) { 
    std::vector<int> vec(begin, end);
    std::sort(vec.begin(), vec.end());
    const size_t N = vec.size();
    if (N%2 == 0) {
        return (double(vec[N/2]) + double(vec[N/2 - 1])) / 2.0;
    } else {
        return double(vec[ N / 2 ]);
    }
}

void test1() {

    Node* root = NULL;
    std::vector<int> keys{ 2, 1, 3, 7, 10, 21, 5, 8, 6, 4 };
    const int N = keys.size();
    
    for (int i = 0; i < N; ++i) {
        insert_and_check( &root, keys[i], i+1 );
    }

    std::cout << "PASSED TEST 1" << std::endl;
}

template <class T>
void print_expectations(T expected, T actual) {
    std::cout << "Expected:\t" << expected 
        << "\nActual:\t\t" << actual << std::endl;
}

template <class T>
void check_results(std::string fn, 
                    std::vector<int>::iterator begin,
                    std::vector<int>::iterator end, 
                    T expected, T actual) {
    if (expected != actual) {
        std::cerr << "ERROR IN " << fn << "(*)\nInserted:\t";
        print(begin, end);
        print_expectations(expected, actual);
        exit(0);
    }
}

void check_min(std::vector<int>::iterator begin,
                std::vector<int>::iterator end, 
                Node* root) {
    check_results("min", begin, end, min(begin, end), min(root) ); 
}

void check_max(std::vector<int>::iterator begin,
                std::vector<int>::iterator end, 
                Node* root) { 
    check_results("max", begin, end, max(begin, end), max(root) );
}

void check_median(std::vector<int>::iterator begin,
                std::vector<int>::iterator end, 
                Node* root) { 
    check_results("median", begin, end, median(begin, end), median(root));
}

void test2() {
    Node* root = NULL;
    std::vector<int> keys{ 2, 1, 3, 7, 10, 21, 5, 8, 6, 4 };
    const size_t N = keys.size();
     
    for (size_t i = 0; i < N; ++i) {
        root = insert(root, keys[i]);
        check_min(keys.begin(), keys.begin() + i + 1, root );
        check_max(keys.begin(), keys.begin() + i + 1, root );
        check_median(keys.begin(), keys.begin() + i + 1, root );
    }
    std::cout << "PASSED TEST 2" << std::endl;
}

void test3() {
    Node* root = NULL;
    std::vector<int> keys{ 2, 1, 3, 7, 1, 10, 7, 21, 9, 5, 8, 9, 6, -1, 10, 4 };
    const size_t N = keys.size();
     
    for (size_t i = 0; i < N; ++i) {
        root = insert(root, keys[i]);
    }
    check_results("dupicates", keys.begin(), keys.begin()+N, N, size_t(size(root))); 
    std::cout << "PASSED TEST 3" << std::endl;
}

void test4() {
    Node* root = NULL;
    std::vector<int> keys{ 2, 1, 4, 2, 8, 11 };
    const size_t N = keys.size();
     
    for (size_t i = 0; i < N; ++i) {
        root = insert(root, keys[i]);
        check_min(keys.begin(), keys.begin() + i + 1, root);
        check_max(keys.begin(), keys.begin() + i + 1, root);
    }
    std::cout << "PASSED TEST 4" << std::endl;
}

void test5() {
    Node* root = NULL;
    std::vector<int> keys{ 2, 1, 3, 7, 2, 10, 1, 17, 7,
                            21, -1, 9, 5, 8, 9, 6, -1, 10, 4, 
                            21, 8, 17, -9, 11, 101, 
                            21, 8, 1, 18, -178, 17 };
    const size_t N = keys.size();
     
    for (size_t i = 0; i < N; ++i) {
        root = insert(root, keys[i]);
        check_min(keys.begin(), keys.begin() + i + 1, root);
        check_max(keys.begin(), keys.begin() + i + 1, root);
        check_median(keys.begin(), keys.begin() + i + 1, root);
    }
    std::cout << "PASSED TEST 5" << std::endl;
}

int main(int , char** __) {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
