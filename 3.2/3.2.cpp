#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <future>
using namespace std;

const unsigned long MAX_CHUNK_SIZE = 2;

template<class Iterator, class UnaryFunction>
void foreach(Iterator first, Iterator last, UnaryFunction fx)
{
    unsigned long const len = distance(first, last);

    if (len <= MAX_CHUNK_SIZE)
    {
        for (; first != last; ++first)
            fx(*first);
    }
    else
    {
        Iterator mid_point = first;
        advance(mid_point, len / 2);
        future<void> first_half_res = async(launch::async,
            foreach<Iterator, UnaryFunction>,
            first,
            mid_point,
            fx);

        future<void> second_half_res = async(launch::async,
            foreach<Iterator, UnaryFunction>,
            mid_point,
            last,
            fx);
        first_half_res.wait();
        second_half_res.wait();
    }
}

int main()
{
    vector<int> v(10, 5);
    int x = 0;
    foreach(v.begin(), v.end(), [&x](int n) { x += n; });
    cout << x << endl;
    return 0;
}