#include <chrono>
#include <iostream>
#include <source_location>
#include "thread_pool.hpp"
using namespace std;

class test
{
public:
	test() : m_count_one(), m_count_two()
	{

	}

	void test_func_one()
	{
		{
			lock_guard<mutex> lock(m_mutex);
			m_location = source_location::current();
			cout << setw(3) << left << m_count_one;
			cout << m_location.function_name() << ' ' << this_thread::get_id() << '\n';
		}
		++m_count_one;
	}

	void test_func_two()
	{
		{
			lock_guard<mutex> lock(m_mutex);
			m_location = source_location::current();
			cout << setw(3) << left << m_count_two;
			cout << m_location.function_name() << ' ' << this_thread::get_id() << '\n';
		}
		++m_count_two;
	}
private:
	mutex m_mutex;
	uint32_t m_count_one;
	uint32_t m_count_two;
	source_location m_location;
};

int main(int argc, const char* argv[])
{
	test t;
	constexpr int iterations{ 30 };
	try
	{
		mtd::thread_pool pool;
		for (int i{}; i < iterations; ++i)
		{
			pool.submit([&]()
				{
					t.test_func_one();
				});
			pool.submit([&t]()
				{
					t.test_func_two();
				});
			this_thread::sleep_for(chrono::milliseconds(2000));
		}
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}