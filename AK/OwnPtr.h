#pragma once

#include <AK/Utility.h>

namespace AK
{
	template<typename T>
	class OwnPtr
	{
	private:
		T* m_Ptr = nullptr;

	public:
		OwnPtr() = default;

		explicit OwnPtr(T* ptr)
			: m_Ptr(ptr) {}

		OwnPtr(OwnPtr&& ownPtr)
			: m_Ptr(ownPtr.leak_ptr()) {}

		template<typename U>
		OwnPtr(OwnPtr<U>&& ownPtr)
			: m_Ptr(ownPtr.leak_ptr()) {}

		~OwnPtr()
		{
			clear();
		}

		OwnPtr(const OwnPtr&) = delete;

		template<typename U>
		OwnPtr(const OwnPtr<U>&) = delete;

		OwnPtr& operator=(const OwnPtr&) = delete;

		template<typename U>
		OwnPtr& operator=(const OwnPtr<U>&) = delete;

		template<typename U>
		OwnPtr(const RefPtr<U>&) = delete;

		template<typename U>
		OwnPtr& operator=(const RefPtr<U>&) = delete;

		template<typename U>
		OwnPtr(const WeakPtr<U>&) = delete;

		template<typename U>
		OwnPtr& operator=(const WeakPtr<U>&) = delete;

		OwnPtr& operator=(OwnPtr& other)
		{
			OwnPtr ptr(move(other));
			swap(ptr);
			return *this;
		}

		OwnPtr& operator=(T* ptr)
		{
			if (m_Ptr != ptr)
				delete m_Ptr;
			m_Ptr = ptr;
			return *this;
		}

		OwnPtr& operator=(nullptr)
		{
			clear();
			return *this;
		}

		void clear()
		{
			delete m_Ptr;
			m_Ptr = nullptr;
		}

		T* leak_ptr()
		{
			T* leakedPtr = m_Ptr;
			m_Ptr = nullptr;
			return leakedPtr;
		}

		T* ptr() { return m_Ptr; }
		const T* ptr() const { return m_Ptr; }

		T* operator->() { return m_Ptr; }
		const T* operator->() const { return m_Ptr; }

		T& operator*() { return *m_Ptr; }
		const T& operator*() const { return *m_Ptr; }

		operator bool() { return !!m_Ptr; }
		bool operator!() const { return !m_Ptr; }

		void swap(OwnPtr& other)
		{
			::swap(m_Ptr, other.m_Ptr);
		}

		template<typename U>
		void swap(OwnPtr<U>& other)
		{
			::swap(m_Ptr, other.m_Ptr);
		}
	};

	template<typename T, typename U>
	inline void swap(OwnPtr<T>& a, OwnPtr<U>& b)
	{
		a.swap(b);
	}
}