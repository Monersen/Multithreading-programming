#pragma once
#include <mutex>
#include <memory>
#include <vector>
#include <thread>
#include <atomic>
#include <random>
#include <format>
#include <iostream>
#include "bar.h"
using namespace std;

enum class Speed
{
	STATIC,
	DYNAMIC
};

class Multibar
{
public:
	Multibar(size_t threads, size_t lenght, Speed speed);
	void run();
private:
	void update(size_t id, size_t progress);
	void output(ostream& os);
	size_t get_random_value();
private:
	Speed _speed;
	mutex _mutex;
	once_flag _flag;
	atomic<bool> _started;
	const size_t _lenght;
	vector<thread> _threads;
	vector<size_t> _sleeping_time;
	vector<unique_ptr<Bar>> _bars;
};