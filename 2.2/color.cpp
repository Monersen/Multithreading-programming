#include "color.h"
using namespace std;

color::color(Code code) : _code(static_cast<size_t>(code)), _saved_code(_code) {}

color::color()
{
	random_device rd;
	mt19937 engine{ rd() };
	uniform_int_distribution<size_t> distribution{ 31, 39 };
	_code = distribution(engine);
	_saved_code = _code;
}

ostream& operator<<(ostream& os, const color& color)
{
	return os << "\033[" << color._code << "m";
}

void color::set()
{
	_code = _saved_code;
}

void color::reset()
{
	_code = static_cast<size_t>(Code::DEFAULT);
}

void color::change(Code code)
{
	_code = static_cast<size_t>(code);
}