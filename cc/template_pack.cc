#include <iostream>
#include <functional>
#include <vector>

class A {
public:
    int test(int a, int b) {
        return a + b;
    }
};

template<typename... Args>
int sum(Args... args) {
    return (1 + ... + args);
}



template<typename T, typename... Args>
void push_back_vec(std::vector<T>& v, Args&&... args) {
    (v.push_back(std::forward<Args>(args)), ...);
}
int main() {
    A a;
    std::function<int (int)> f;
    f = std::bind(&A::test, a, std::placeholders::_1 , 1);
    std::cout << f(2);

    std::cout << sum(1, 2, 3);

    std::vector<int> vv;
    push_back_vec(vv, 1, 2, 3);

    auto aa = [=](auto b){decltype(b) c = b + 1; return c;};
    std::cout << aa(1);



}
