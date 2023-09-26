#include "bar.h"
using namespace std;

Bar::Bar(size_t id, size_t lenght) : _done(false),
_color(),
_arrow('>'),
_filler('-'),
_remainder(' '),
_id(id),
_width(60),
_lenght(lenght),
_progress(),
_duration() {}

Bar::Bar(size_t id, size_t lenght, Code code) : _done(false),
_color(code),
_arrow('>'),
_filler('-'),
_remainder(' '),
_id(id),
_width(60),
_lenght(lenght),
_progress(),
_duration() {}

void Bar::update(size_t progress)
{
	this->set_progress(progress);
	this->output(cout);
}

void Bar::set_progress(size_t value)
{
	unique_lock lk{ _mutex };
	call_once(_flag, [this]() {this->_thread_id = this_thread::get_id(); });
	_progress = value;
}

void Bar::output(ostream& os)
{
	unique_lock lk{ _mutex };
	if (_done)
	{
		return;
	}
	else
	{
		if (_progress == _lenght) { _done = true; }
		_color.set();
		static auto start{ chrono::system_clock::now() };
		size_t completed{ static_cast<size_t>(_progress * _width / _lenght) };
		os << '\r' << _id << '\t' << _thread_id << _color << "\t[";
		for (size_t i{}; i < _width; ++i)
		{
			if (i < completed)
			{
				os << _filler;
			}
			else if (i == completed)
			{
				os << _arrow;
			}
			else
			{
				os << _remainder;
			}
		}
		_color.reset();
		_duration = chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - start);
		os << "] " << _color << static_cast<size_t>(_progress * 100 / _lenght) << '\t' << _duration.count();
	}
}