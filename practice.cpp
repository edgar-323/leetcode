#include <functional>
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Hello Edgar!" << std::endl;

    std::function<int(int)> f = [](int x) -> int { return x + 1;};

    std::cout << "f(5) = " << f(5) << std::endl;

    return 0;
}
