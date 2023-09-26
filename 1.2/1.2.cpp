#include <array>
#include <vector>
#include <thread>
#include <random>
#include <chrono>
#include <format>
#include <iostream>
#include <algorithm>
using namespace std;

void calculation(const vector<int>& one, const vector<int>& two, vector<int>& result, size_t threads, size_t thread) noexcept
{
	size_t size{ one.size() / threads };
	for (auto i{ thread * size }; i < thread * size + size; ++i)
	{
		result.push_back(one[i] + two[i]);
	}
}

void get_random_values(vector<int>& vector) noexcept
{
	random_device seeder;
	const auto seed{ seeder.entropy() ? seeder() : time(nullptr) };
	mt19937 engine{ static_cast<mt19937::result_type>(seed) };
	uniform_int_distribution<int> distribution{ numeric_limits<short>::min(), numeric_limits<short>::max() };
	generate(vector.begin(), vector.end(), [&engine, &distribution]() -> int
		{
			return distribution(engine);
		});
}

int main()
{
	array<size_t, 4> limits{ 1000, 10'000, 100'000, 1'000'000 };
	array<size_t, 5> threads{ 1, 2, 4, 8, 16 };
	vector<thread> vec_threads;
	vector<int> vec_one;
	vector<int> vec_two;
	vector<int> vec_result;

	cout << format("Hardware concurrency: {}\n\n", thread::hardware_concurrency());
	cout << format("{:26}{:16}{:16}{:16}{:16}\n", threads[0], threads[1], threads[2], threads[3], threads[4]);
	cout << format("{:-<95}\n", "-");

	for (size_t i{}; i < limits.size(); ++i)
	{
		cout << format("{:<15}", limits[i]);
		vec_one.resize(limits[i]);
		vec_two.resize(limits[i]);
		vec_result.resize(limits[i]);
		get_random_values(vec_one);
		get_random_values(vec_two);
		for (auto current_threads : threads)
		{
			for (size_t t{}; t < current_threads; ++t)
			{
				vec_threads.push_back(thread(calculation, cref(vec_one), cref(vec_two), ref(vec_result), current_threads, t));
			}
			auto begin{ chrono::steady_clock::now() };
			for (size_t t{}; t < current_threads; ++t)
			{
				vec_threads[t].join();
			}
			chrono::duration<float> duration{ chrono::steady_clock::now() - begin };
			cout << format("{:13.5f} s.", duration.count());
			vec_threads.clear();
			vec_result.clear();
		}
		vec_one.clear();
		vec_two.clear();
		cout << "\n";
	}
	return 0;
}