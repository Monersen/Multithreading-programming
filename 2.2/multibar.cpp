#include "multibar.h"
using namespace std;

Multibar::Multibar(size_t threads, size_t lenght, Speed speed) : _speed(speed), _started(false), _lenght(lenght)
{
	for (size_t id{}; id < threads; ++id)
	{
		_bars.push_back(make_unique<Bar>(id, _lenght));
		if (_speed == Speed::STATIC)
		{
			_sleeping_time.push_back(get_random_value());
		}
		_threads.push_back(thread([this, id]()
			{
				for (size_t progress{}; progress <= _lenght; ++progress)
				{
					this->update(id, progress);
					if (_speed == Speed::STATIC)
					{
						this_thread::sleep_for(chrono::milliseconds(_sleeping_time[id]));
					}
					else
					{
						this_thread::sleep_for(chrono::milliseconds(get_random_value()));
					}
				}
			}));
	}
}

void Multibar::run()
{
	for (auto& thread : _threads)
	{
		thread.join();
	}
}

void Multibar::update(size_t id, size_t progress)
{
	_bars[id]->set_progress(progress);
	output(cout);
}

void Multibar::output(ostream& os)
{
	unique_lock lk{ _mutex };
	call_once(_flag, [&os]()
		{
			os << format("{}{:>10}{:>42}{:>28}{:>12}\n", "#", "id", "Progress Bar", "%", "Time, s");
		});
	if (_started)
	{
		for (size_t i{}; i < _bars.size(); ++i)
		{
			os << "\x1b[A";
		}
	}
	for (size_t i{}; i < _bars.size(); ++i)
	{
		_bars[i]->output(os);
		os << '\n';
	}
	if (!_started)
	{
		_started = true;
	}
}

size_t Multibar::get_random_value()
{
	unique_lock lk{ _mutex };
	random_device rd;
	mt19937 engine{ rd() };
	uniform_int_distribution<size_t> distribution{ 50, 750 };
	return distribution(engine);
}