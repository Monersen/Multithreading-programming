#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

template<typename T>
void min_idx(const T& v,
    int start_idx,
    promise<int>&& pr)
{
    auto m = start_idx;
    for (; start_idx < v.size(); ++start_idx)
        if (v[start_idx] < v[m])
            m = start_idx;

    pr.set_value(m);
}

template<typename T>
void selectionSort(T& arr, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        promise<int> pr;
        future<int> ft_res = pr.get_future();
        future<void> task = async(launch::async, min_idx<T>, arr, i, move(pr));
        auto midx = ft_res.get();
        swap(arr[i], arr[midx]);
    }
}

int main()
{
    vector v(10, 0);
    mt19937 gen(time(nullptr));
    uniform_int_distribution<int> dis(0, 10);
    auto rand_num([=]() mutable { return dis(gen); });
    generate(begin(v), end(v), rand_num);

    selectionSort(v, v.size());

    for (const auto& i : v)
        cout << i << " ";

    cout << endl;
    return 0;
}