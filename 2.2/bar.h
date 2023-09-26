#pragma once
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include "color.h"
using namespace std;

class Bar
{
public:
	friend class Multibar;
	Bar(size_t id, size_t lenght);
	Bar(size_t id, size_t lenght, Code code);
	void update(size_t value);
private:
	void set_progress(size_t progress);
	void output(ostream& os);
private:
	color _color;
	mutex _mutex;
	once_flag _flag;
	atomic<bool> _done;
	thread::id _thread_id;
	const unsigned char _arrow;
	const unsigned char _filler;
	const unsigned char _remainder;
	size_t _progress;
	const size_t _id;
	const size_t _width;
	const size_t _lenght;
	chrono::seconds _duration;
};