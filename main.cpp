#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include "container.hpp"
#include "classA.h"
#include "classB.h"

using namespace std;

// Внимание!
// Вообще-то тесты так писать не принято. Потому что эта реализация на коленке (а) хрупкая и (б) много чего не умеет.
// Сейчас всё же оставим так, чтобы вы могли всё это использовать, не разбираясь с дополнительными инструментами.
// Но в реальном проекте используйте Boost.Test или gtest или ещё какой-нибудь аналог.

// Подключите свой хэдер вместо SimpleList.h

// Больше ничего править не требуется, просто соберитесь и запуститесь с этим main-ом с тестами
#define IMPL AvlTree


// Больше ничего править не требуется, просто соберитесь и запуститесь с этим main-ом с тестами


bool test1()
{
    int size = 10;
    Container<int>* impl = new IMPL<int>();
    bool test_ok = true;

    for(int i = 0; i < size; i++) {
        impl->insert(i * i);
    }

    for(int i = 0; i < size; i++) {
        if (!impl->exists(i * i)) {
            test_ok = false;
        }
        impl->remove(i * i);
        if (impl->exists(i * i)) {
            test_ok = false;
        }
    }

    delete impl;

    cout << boolalpha << "Container<int> basic API works: " << test_ok << endl;
    return test_ok;
}

bool test2()
{
    int size = 10;
    Container<string>* impl = new IMPL<string>();
    bool test_ok = true;

    for(int i = 0; i < size; i++) {
        string s = "a";
        s[0] += i;
        impl->insert(s);
    }

    for(int i = 0; i < size; i++) {
        string s = "a";
        s[0] += i;
        if (!impl->exists(s)) {
            test_ok = false;
        }
        impl->remove(s);
        if (impl->exists(s)) {
            test_ok = false;
        }
    }

    delete impl;

    cout << boolalpha << "Container<string> basic API works: " << test_ok << endl;
    return test_ok;
}

bool test3()
{
    bool test_ok = true;

    int size = 10;
    vector<int> reference;
    vector<int> from_impl;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
        reference.push_back(i);
    }

    for(const auto& el: impl)
        from_impl.push_back(el);

    sort(reference.begin(), reference.end());
    sort(from_impl.begin(), from_impl.end());

    cout << boolalpha << "Iterator provides access to all elements: " << (from_impl == reference) << endl;
    return test_ok;
}

bool test4()
{
    bool test_ok = true;

    int size = 10;
    vector<int> from_impl;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
    }

    for(int i = 0; i < size; i++) {
        impl.remove(i);
    }

    for(const auto& el: impl)
        from_impl.push_back(el);

    cout << boolalpha << "Method remove() really removes: " << (from_impl.size() == 0) << endl;
    return test_ok;
}

bool test5()
{
    bool test_ok = true;

    int size = 10;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
    }

    cout << boolalpha << "Looking for non-existing element works: " << (!impl.exists(42)) << endl;
    return test_ok;
}

bool test6()
{
    bool test_ok = true;

    int size = 10;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
    }
    impl.remove(42);

    cout << boolalpha << "Calling remove() for non-existing element does not die: " << (test_ok) << endl;
    return test_ok;
}

bool test7()
{
    bool test_ok = true;

    IMPL<int> impl;
    impl.exists(42);
    impl.remove(42);

    vector<int> from_impl;
    for(const auto& el: impl)
        from_impl.push_back(el);

    cout << boolalpha << "Empty container does not die: " << (from_impl.size() == 0) << endl;
    return test_ok;
}

bool test8()
{
    bool test_ok = true;

    int size = 10;
    vector<int> reference;
    vector<int> from_impl;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
        reference.push_back(i);
    }

    int to_delete = int(size / 2);
    auto position = find(reference.begin(), reference.end(), to_delete);
    reference.erase(position);
    impl.remove(to_delete);

    for(const auto& el: impl)
        from_impl.push_back(el);

    sort(reference.begin(), reference.end());
    sort(from_impl.begin(), from_impl.end());

    cout << boolalpha << "Elements are still reachable after remove(): " << (from_impl == reference) << endl;
    return test_ok;
}

bool test9()
{
    bool test_ok = true;

    int size = 10;
    set<int> reference;
    set<int> from_impl;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        auto it=reference.cbegin();
        impl.insert(i);
        impl.insert(i);
        impl.insert(i);
        reference.insert(it, i);
        reference.insert(it, i);
        reference.insert(it, i);
    }

    for(const auto& el: impl)
    {
        auto it1=from_impl.cbegin();
        from_impl.insert(it1, el);
    }

    //sort(reference.begin(), reference.end()); - в set и так отсортированные значения;
    //sort(from_impl.begin(), from_impl.end());

    cout << boolalpha << "Duplicate values are possible: " << (from_impl == reference) << endl;
    return test_ok;
}

bool test10()
{
    bool test_ok = true;

    IMPL<int> impl1;
    impl1.insert(42);
    impl1.insert(0);
    impl1.remove(42);

    IMPL<int> impl2;
    impl2.insert(0);
    impl2.insert(42);
    impl2.remove(42);

    test_ok = (impl1.exists(0) && impl2.exists(0));

    cout << boolalpha << "Removing head element probably works: " << (test_ok) << endl;
    return test_ok;
}

bool test11()
{
    bool test_ok = true;

    IMPL<int> impl1;

    try {
        int a = *impl1.begin();
        a++;
    } catch (const exception& e) {
        //
    }

    cout << boolalpha << "Dereference corner cases probably handled: " << (test_ok) << endl;
    return test_ok;
}

bool test12()
{
    bool test_ok = true;

    IMPL<int> impl1;

    try {
        ++impl1.begin();
        impl1.begin()++;
        ++impl1.end();
        impl1.end()++;
    } catch (const exception& e) {
        //
    }

    cout << boolalpha << "Iterator increment corner cases probably handled: " << (test_ok) << endl;
    return test_ok;
}

bool test13()
{
    bool test_ok = true;

    int size = 10;
    vector<int> reference;
    vector<int> from_impl;

    IMPL<int> impl1;
    for(int i = 0; i < size; i++) {
        impl1.insert(i);
        reference.push_back(i);
    }

    IMPL<int> impl2(impl1);
    IMPL<int> impl3;
    impl3 = impl2;
    impl3 = impl3;

    sort(reference.begin(), reference.end());

    from_impl.clear();
    for(const auto& el: impl2)
        from_impl.push_back(el);
    sort(from_impl.begin(), from_impl.end());
    test_ok = test_ok && (from_impl == reference);
    from_impl.clear();
    for(const auto& el: impl3)
        from_impl.push_back(el);

    sort(from_impl.begin(), from_impl.end());
    test_ok = test_ok && (from_impl == reference);

    cout << boolalpha << "Copy and assignment probably works: " << (test_ok) << endl;
    return test_ok;
}

bool test14()
{
    int size = 10;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
    }
    int mycount = count_if(impl.begin(), impl.end(), [size](int i) { return i < size; });

    bool test_ok = (mycount == size);
    cout << boolalpha << "STL algo can be applied: " << test_ok << endl;
    return test_ok;
}

int main()
{
    vector<function<bool(void)>> tests = {test1, test2, test3, test4,test5, test6, test7, test8, test9, test10,
                                          test11, test12, test13, test14};

    bool verdict = true;

    unsigned int count = 1;
    for(auto test : tests) {
        cout << count << ". ";
        verdict = verdict && test();
        count++;
    }

    cout << "=================================" << endl;
    cout << "Run " << (count - 1) << " tests. Verdict: " << (verdict ? "PASSED" : "FAILED") << endl;

    return 0;
}


