#pragma once
#include <atomic>
#include <thread>
#include <vector>
#include <functional>
#include "threadsafe_q.hpp"
using namespace std;

namespace mtd
{
	class thread_pool
	{
	public:
		thread_pool();
		~thread_pool();
		thread_pool(const thread_pool& other) = delete;
		thread_pool(thread_pool&& other) noexcept = delete;
		thread_pool& operator = (const thread_pool& other) = delete;
		thread_pool& operator = (thread_pool&& other) noexcept = delete;
	public:
		template <typename F>
		void submit(F func);
	private:
		void work();
	private:
		atomic<bool> m_done;
		vector<thread> m_threads;
		threadsafe_queue<function<void()>> m_queue;
	};

	thread_pool::thread_pool() : m_done(false)
	{
		const auto threads{ thread::hardware_concurrency() };
		try
		{
			for (unsigned int i{}; i < threads; ++i)
			{
				m_threads.push_back(thread(&thread_pool::work, this));
			}
		}
		catch (...)
		{
			m_done = true;
			throw;
		}
	}

	thread_pool::~thread_pool()
	{
		m_done = true;
		for (auto& thread : m_threads)
		{
			if (thread.joinable())
			{
				thread.join();
			}
		}
	}

	template <typename F>
	void thread_pool::submit(F func)
	{
		m_queue.push(function<void()>(func));
	}

	void thread_pool::work()
	{
		while (!m_done)
		{
			function<void()> task;
			if (m_queue.pop(task))
			{
				task();
			}
			else
			{
				this_thread::yield();
			}
		}
	}
}