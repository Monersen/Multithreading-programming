#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void client(int& clients, int max_value) noexcept
{
	do
	{
		cout << "Clients: " << ++clients << '\n';
		this_thread::sleep_for(chrono::seconds(1));
	} while (clients != max_value);
	cout << "No more clients for today!\n";
}

void manager(int& clients) noexcept
{
	do
	{
		cout << "Manager: " << --clients << '\n';
		this_thread::sleep_for(chrono::seconds(2));
	} while (clients != 0);
	cout << "All clients served!\n";
}

int main()
{
	cout << "Enter maximum number of clients: ";
	int clients{};
	int max_value{};
	while (!(cin >> max_value) || max_value < 0)
	{
		cin.clear();
		while (cin.get() != '\n') {
			continue;
		}
		cout << "Please enter a valid value: ";
	}
	thread thread_client{ client, ref(clients), max_value };
	thread thread_manager{ manager, ref(clients) };
	thread_client.join();
	thread_manager.join();
	return 0;
}