#pragma once
#include <memory>
#include <stdexcept>
using namespace std;

namespace mtd
{
	template <typename T>
	class queue
	{
	public:
		queue();
		~queue();
		queue(const queue& other);
		queue(queue&& other) noexcept;
		queue& operator = (const queue& other);
		queue& operator = (queue&& other) noexcept;
	public:
		T front();
		void pop();
		void push(T new_value);
		bool empty() const;
		uint32_t size() const;
	private:
		struct node
		{
			node(T new_data) : data(move(new_data)), next() {}
			T data;
			node* next;
		};
		uint32_t m_size;
		unique_ptr<node> m_head;
		node* m_tail;
	};

	template <typename T>
	queue<T>::queue() : m_size(), m_tail()
	{

	}

	template <typename T>
	queue<T>::~queue()
	{
		while (m_head)
		{
			m_head.reset(m_head->next);
		}
	}

	template <typename T>
	queue<T>::queue(const queue<T>& other)
	{
		m_size = 1;
		m_head = make_unique<node>(other.m_head->data);
		m_tail = m_head.get();
		node* other_ptr{ other.m_head->next };
		while (other_ptr)
		{
			this->push(other_ptr->data);
			other_ptr = other_ptr->next;
		}
	}

	template <typename T>
	queue<T>::queue(queue<T>&& other) noexcept
	{
		m_size = other.m_size;
		m_head = move(other.m_head);
		m_tail = other.m_tail;
	}

	template <typename T>
	queue<T>& queue<T>::operator = (const queue<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		else
		{
			// same algorithm as copy constructor
			m_size = 1;
			m_head = make_unique<node>(other.m_head->data);
			m_tail = m_head.get();
			node* other_ptr{ other.m_head->next };
			while (other_ptr)
			{
				this->push(other_ptr->data);
				other_ptr = other_ptr->next;
			}
			return *this;
		}
	}

	template <typename T>
	queue<T>& queue<T>::operator = (queue<T>&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}
		else
		{
			m_size = other.m_size;
			m_head = move(other.m_head);
			m_tail = other.m_tail;
			return *this;
		}
	}

	template <typename T>
	T queue<T>::front()
	{
		if (!m_head)
		{
			throw runtime_error{ "queue is empty!" };
		}
		T data{ move(m_head->data) };
		this->pop();
		if (!m_head)
		{
			m_tail = nullptr;
		}
		--m_size;
		return data;
	}

	template <typename T>
	void queue<T>::pop()
	{
		m_head.reset(m_head->next);
	}

	template <typename T>
	void queue<T>::push(T new_data)
	{
		if (!m_head)
		{
			m_head = make_unique<node>(move(new_data));
			m_tail = m_head.get();
		}
		else
		{
			node* new_tail{ new node(move(new_data)) };
			m_tail->next = new_tail;
			m_tail = new_tail;
		}
		++m_size;
	}

	template <typename T>
	bool queue<T>::empty() const
	{
		return m_size == 0;
	}

	template <typename T>
	uint32_t queue<T>::size() const
	{
		return m_size;
	}
}