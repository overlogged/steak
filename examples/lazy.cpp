#include <iostream>
#include <unistd.h>
#include "../include/runtime.h"

using namespace std;
using namespace steak;

int time_consuming_compute() {
    cout << "start computing\n";
    sleep(1);
    cout << "end computing\n";
    return 666;
}

void f(std::pair<int, char> x) {
    cout << x.second << endl;
}

void lazy_unit_test() {
    auto l4 = lazy_call(time_consuming_compute).async();

    sleep(1);

    auto l1 = lazy_type_t(1);
    auto l2 = l1.transform([](int x) { return 'a'; });
    const auto l3 = lazy_call([]() {
        cout << "eval l3\n";
        return 'v';
    });

    cout << l2 << endl;
    cout << l3 << endl;

    cout << l4 << endl;
    cout << l4 << endl;

    lazy_type_t<std::pair<int, char>> l5(std::pair(1, 'a'));
    cout << l5.get().first;
    f(l5);

    auto l6 = lazy_type_t(1)
              | [](int x) { return x + 1; }
              | [](int x) { return x * 2; }
              | [](int x) {
        cout << x << endl;
        return "hello world";
    };

    cout << l6 << endl;
}


int main() {
    lazy_unit_test();
    return 0;
}