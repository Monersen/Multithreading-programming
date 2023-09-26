#include <iostream>
#include "multibar.h"
using namespace std;

void clear()
{
#if defined(_WIN32)
	system("cls");
#else
	system("clear");
#endif
}

template <typename T>
void check_input(T& variable)
{
	while (!(cin >> variable) || variable > numeric_limits<T>::max() / 2)
	{
		cin.clear();
		while (cin.get() != '\n') { continue; }
		cout << "Please, enter valid value: ";
	}
}

int main(int argc, const char* argv[])
{
	clear();
	size_t lenght{};
	cout << "Enter lenght: ";
	check_input<size_t>(lenght);
	size_t threads{};
	cout << "Enter number of threads: ";
	check_input<size_t>(threads);
	clear();
	Multibar multibar(threads, lenght, Speed::DYNAMIC);
	multibar.run();
	cout << '\n';
	return 0;
}