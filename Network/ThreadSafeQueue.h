#pragma once


#include "CommonLibraries.h"

namespace network
{	
	template<typename T>
	class ThreadSafeQueue
	{
	private:

		std::deque<T> mMessagesQueue;
		std::mutex lockQueue;


	public:

		ThreadSafeQueue() = default;
		ThreadSafeQueue(const ThreadSafeQueue<T>&) = delete;
		virtual ~ThreadSafeQueue()
		{
			Clear();
		}

	public:

		void PushBack(const T& message)
		{
			std::scoped_lock lock(lockQueue);
			mMessagesQueue.push_back(message);
		}
		void PushFront(const T& message)
		{
			std::scoped_lock lock(lockQueue);
			mMessagesQueue.push_front(message);
		}

		
		T PopFront()
		{
			std::scoped_lock lock(lockQueue);
			T popMessage = std::move(mMessagesQueue.front());
			mMessagesQueue.pop_front();
			return popMessage;
		}
		T PopBack()
		{
			std::scoped_lock lock(lockQueue);
			T popMessage = std::move(mMessagesQueue.back());
			mMessagesQueue.pop_back();
			return popMessage;
		}

	
		const T& Front()
		{
			std::scoped_lock lock(lockQueue);
			return mMessagesQueue.front();
		}
		const T& Back()
		{
			std::scoped_lock lock(lockQueue);
			return mMessagesQueue.back();
		}
	

		bool Empty()
		{
			std::scoped_lock lock(lockQueue);
			return mMessagesQueue.empty();
		}
		size_t Size()
		{
			std::scoped_lock lock(lockQueue);
			return mMessagesQueue.size();
		}
		void Clear()
		{
			std::scoped_lock lock(lockQueue);
			mMessagesQueue.clear();
		}

	};
}