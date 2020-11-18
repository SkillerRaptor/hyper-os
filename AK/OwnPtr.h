#pragma once

template<typename T>
class OwnPtr
{
private:
	T* m_Ptr;

public:
	OwnPtr() {}
	explicit OwnPtr(T* ptr)
		: m_Ptr(ptr) {}
	OwnPtr(OwnPtr&& ownPtr)
		: m_Ptr(ownPtr.LeakPtr()) {}
	template<typename U>
	OwnPtr(OwnPtr<U>&& ownPtr)
		: m_Ptr(static_cast<T*>(ownPtr.LeakPtr())) {}
	OwnPtr(nullptr) {};
	~OwnPtr() { Clear(); }

	OwnPtr& operator=(OwnPtr& ownPtr)
	{
		if (this != &ownPtr)
		{
			delete m_Ptr;
			m_Ptr = ownPtr.LeakPtr();
		}
		return *this;
	}

	template<typename U>
	OwnPtr& operator=(OwnPtr<U>&& ownPtr)
	{
		if (this != static_cast<void*>(&ownPtr)) {
			delete m_Ptr;
			m_Ptr = ownPtr.LeakPtr();
		}
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
		Clear();
		return *this;
	}
	
	void Clear()
	{
		delete m_Ptr;
		m_Ptr = nullptr;
	}

	typedef T* OwnPtr::* UnspecifiedBoolType;
	operator UnspecifiedBoolType() const { return m_Ptr ? &OwnPtr::m_Ptr : nullptr; }

	T* LeakPtr()
	{
		T* leakedPtr = m_Ptr;
		m_Ptr = nullptr;
		return leakedPtr;
	}

	T* GetPtr() { return m_Ptr; }
	const T* GetPtr() const { return m_Ptr; }

	T* operator->() { return m_Ptr; }
	const T* operator->() const { return m_Ptr; }

	T& operator*() { return *m_Ptr; }
	const T& operator*() const { return *m_Ptr; }

	operator bool() { return !!m_Ptr; }

	bool operator!() const { return !m_Ptr; }
};