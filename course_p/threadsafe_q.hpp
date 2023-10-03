#pragma once
#include <mutex>
#include <memory>
#include <condition_variable>
#include "q.hpp"
using namespace std;

namespace mtd
{
	template <typename T>
	class threadsafe_queue
	{
	public:
		threadsafe_queue();
		threadsafe_queue(const threadsafe_queue& other) = delete;
		threadsafe_queue(threadsafe_queue&& other) noexcept = delete;
		threadsafe_queue& operator = (const threadsafe_queue& other) = delete;
		threadsafe_queue& operator = (threadsafe_queue&& other) noexcept = delete;
	public:
		void push(T new_value);
		bool pop(T& value);
		bool wait_and_pop(T& value);
		bool empty() const;
		uint32_t size() const;
	private:
		mtd::queue<T> m_queue;
		mutable mutex m_mutex;
		condition_variable m_interaction;
	};

	template <typename T>
	threadsafe_queue<T>::threadsafe_queue()
	{

	}

	template <typename T>
	void threadsafe_queue<T>::push(T new_value)
	{
		lock_guard<mutex> lk(m_mutex);
		m_queue.push(move(new_value));
		m_interaction.notify_one();
	}

	template <typename T>
	bool threadsafe_queue<T>::pop(T& value)
	{
		lock_guard<mutex> lk(m_mutex);
		if (m_queue.empty())
		{
			return false;
		}
		value = move(m_queue.front());
		return true;
	}

	template <typename T>
	bool threadsafe_queue<T>::wait_and_pop(T& value)
	{
		unique_lock<mutex> lock(m_mutex);
		m_interaction.wait(lock, [this]()
			{
				return !m_queue.empty();
			});
		value = move(m_queue.front());
		return true;
	}

	template <typename T>
	bool threadsafe_queue<T>::empty() const
	{
		lock_guard<mutex> lk(m_mutex);
		return m_queue.empty();
	}

	template <typename T>
	uint32_t threadsafe_queue<T>::size() const
	{
		lock_guard<mutex> lk(m_mutex);
		return m_queue.size();
	}
}