#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
using namespace std;

#define memory_order memory_order_seq_cst

void client(atomic<size_t>& clients, const atomic<size_t>& max_value)
{
	while (clients.load(memory_order) != max_value.load(memory_order))
	{
		cout << "Clients: " << ++clients << '\n';
		this_thread::sleep_for(chrono::seconds(1));
	}
	cout << "No more clients for today!\n";
}

void manager(atomic<size_t>& clients)
{
	do
	{
		cout << "Manager: " << --clients << '\n';
		this_thread::sleep_for(chrono::seconds(2));
	} while (clients.load(memory_order) != 0);
	cout << "All clients served!\n";
}

int main()
{
	cout << "Enter maximum number of clients: ";
	size_t temp{};
	while (!(cin >> temp) || temp > numeric_limits<size_t>::max() / 2)
	{
		cin.clear();
		while (cin.get() != '\n') { continue; }
		cout << "Please, enter valid value: ";
	}

	atomic<size_t> clients{};
	atomic<size_t> max_value{};
	max_value.store(temp);
	thread thread_client{ client, ref(clients), cref(max_value) };
	thread thread_manager{ manager, ref(clients) };
	thread_client.join();
	thread_manager.join();
	return 0;
}