#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

////////////////////////////////////////////////////////////////

template<class T>
class threadsafe_queue 
{
public:
	void push(T msg);
	T front();
	void pop();
	bool empty();

private:
    std::mutex q_mutex;
    std::condition_variable cond_var;
	std::queue<T> queue;
};

////////////////////////////////////////////////////////////////

template<class T>
void threadsafe_queue<T>::push(T msg)
{
	{
		std::lock_guard<std::mutex> lock(q_mutex);
		queue.push(msg);
	}

	cond_var.notify_one();
}

////////////////////////////////////////////////////////////////

// warning! calling front() on an empty queue will block until there's something in the queue!
template<class T>
T threadsafe_queue<T>::front()
{
	std::unique_lock<std::mutex> lock(q_mutex);
	cond_var.wait(lock, [&]{ return !queue.empty(); });

	return queue.front();
}

////////////////////////////////////////////////////////////////

template<class T>
void threadsafe_queue<T>::pop()
{
	std::lock_guard<std::mutex> lock(q_mutex);
	queue.pop();
}

////////////////////////////////////////////////////////////////

template<class T>
bool threadsafe_queue<T>::empty()
{
	std::lock_guard<std::mutex> lock(q_mutex);
	return queue.size() == 0;
}

////////////////////////////////////////////////////////////////