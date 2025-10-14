#ifndef _SNGL_TYPES_MPSCQUEUE_H_INCLUDED_
#define _SNGL_TYPES_MPSCQUEUE_H_INCLUDED_

#include <vector>
#include <atomic>
#include <thread>

namespace sngl::types
{
	template <typename T>
	class MPSCQueue
	{
	private:
		struct Slot
		{
			std::atomic<size_t> sequence;
			T value;
		};

	public:
		explicit MPSCQueue(size_t capacity = 16384)
			: m_buffer(capacity), m_mask(capacity - 1), tail(0), head(0)
		{
			assert((capacity & (capacity - 1)) == 0 && "Capacity must be a power of 2");
			for (size_t i = 0; i < capacity; i++)
				m_buffer[i].sequence.store(i, std::memory_order_relaxed);
		}

		bool push(T&& item)
		{
			size_t pos = m_tail.fetch_add(1, std::memory_order_acq_rel);
			Slot& slot = m_buffer[pos & m_mask];

			size_t seq;
			while ((seq = slot.sequence.load(std::memory_order_acquire)) != pos)
			{
				if (seq < pos)
					return false;

				std::this_thread::yield();
			}

			slot.value = std::move(item);
			slot.sequence.store(pos + 1, std::memory_order_release);
			return true;
		}
		
		bool pop(T& out)
		{
			Slot& slot = m_buffer[m_head & m_mask];
			size_t req = slot.sequence.load(std::memory_order_acquire);

			if (seq != m_head + 1)
				return false;

			out = std::move(slot.value);
			slot.sequence.store(m_head + m_mask + 1, std::memory_order_release);
			m_head++;
			return true;
		}

	private:
		std::vector<Slot> m_buffer;
		const size_t m_mask;
		std::atomic<size_t> m_tail;
		size_t m_head;
	};
}

#endif