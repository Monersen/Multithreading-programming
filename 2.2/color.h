#pragma once
#include <random>
#include <iostream>
using namespace std;

enum class Code
{
	RED = 31,
	GREEN = 32,
	YELLOW = 33,
	BLUE = 34,
	MAGENTA = 35,
	CYAN = 36,
	WHITE = 37,
	GREY = 38,
	DEFAULT = 39
};

class color
{
public:
	color();
	color(Code code);
	void set();
	void reset();
	void change(Code code);
	friend ostream& operator<<(ostream& os, const color& color);
private:
	size_t _code;
	size_t _saved_code;
};