#pragma once
#include <queue>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace guling_tools
{
	//读写锁
	typedef boost::shared_mutex R_W_MUTEX;
	typedef boost::shared_lock<R_W_MUTEX> R_LOCK;
	typedef boost::unique_lock<R_W_MUTEX> W_LOCK;

	//线程安全队列
	template<typename T>
	class queue_s
	{
	public:
		queue_s()
		{
		}
		bool empty()
		{
			boost::mutex::scoped_lock lock(m_mutexLock);
			return m_queueData.empty();
		}
		int size()
		{
			boost::mutex::scoped_lock lock(m_mutexLock);
			return m_queueData.size();
		}
		bool clear()
		{
			boost::mutex::scoped_lock lock(m_mutexLock);
			std::queue<T> tempQueue;
			std::swap(m_queueData, tempQueue);
			return m_queueData.size() == 0 ? true : false;
		}

		void push(T const& data)
		{
			{
				boost::mutex::scoped_lock lock(m_mutexLock);
				m_queueData.push(data);
			}
			m_cvCall.notify_one();
		}

		void wait_and_pop(T& popped_value)
		{
			boost::mutex::scoped_lock lock(m_mutexLock);
			while (m_queueData.empty())
			{
				m_cvCall.wait(lock);
			}
			popped_value = m_queueData.front();
			m_queueData.pop();
		}

		bool wait_and_pop_t(T& poped_value, int nSecond)
		{
			boost::mutex::scoped_lock lock(m_mutexLock);
			while (m_queueData.empty())
			{
				if (!m_cvCall.timed_wait(lock, boost::get_system_time() + boost::posix_time::seconds(nSecond)))
					return false;
			}
			poped_value = m_queueData.front();
			m_queueData.pop();
			return true;
		}

	private:
		std::queue<T> m_queueData;
		mutable boost::mutex m_mutexLock;
		boost::condition_variable m_cvCall;
	};
}