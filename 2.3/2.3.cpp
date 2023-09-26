#include <mutex>
#include <iostream>
using namespace std;

class Big_object;
void swap(Big_object& lhs, Big_object& rhs);

class Wrapper
{
public:
	Wrapper(Big_object& bg) : _big_object(bg) {}
	friend void swap_with_lock(Wrapper& lhs, Wrapper& rhs);
	friend void swap_with_scoped_lock(Wrapper& lhs, Wrapper& rhs);
	friend void swap_with_unique_lock(Wrapper& lhs, Wrapper& rhs);
private:
	mutex _mutex;
	Big_object _big_object;
};

void swap_with_lock(Wrapper& lhs, Wrapper& rhs)
{
	if (&lhs == &rhs)
	{
		return;
	}
	else
	{
		lock(lhs, rhs);
		lock_guard<mutex> lock_lhs(lhs._mutex, adopt_lock);
		lock_guard<mutex> lock_rhs(rhs._mutex, adopt_lock);
		swap(lhs._big_object, rhs._big_object);
	}
}

void swap_with_scoped_lock(Wrapper& lhs, Wrapper& rhs)
{
	if (&lhs == &rhs)
	{
		return;
	}
	else
	{
		scoped_lock<mutex, mutex> lk(lhs._mutex, rhs._mutex);
		swap(lhs._big_object, rhs._big_object);
	}
}

void swap_with_unique_lock(Wrapper& lhs, Wrapper& rhs)
{
	if (&lhs == &rhs)
	{
		return;
	}
	else
	{
		unique_lock<mutex> lock_lhs(lhs._mutex, defer_lock);
		unique_lock<mutex> lock_rhs(rhs._mutex, defer_lock);
		lock(lhs, rhs);
		swap(lhs._big_object, rhs._big_object);
	}
}

int main(int argc, const char* argv[])
{
	return 0;
}