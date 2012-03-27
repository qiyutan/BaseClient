#ifndef _SMART_PTR_H
#define _SMART_PTR_H

namespace qy
{

template<class T>
class RefObject
{
public:
	RefObject(T *p):m_pObject(p)
	{
		m_pCount = new int(1);
	}

	RefObject(const RefObject &r) 
	: m_pCount(r.m_pCount), m_pObject(r.m_pObject)
	{
		++*m_pCount;
	}

	RefObject& operator= (const RefObject &r) 
	{ 
		if(m_pCount != r.m_pCount)
		{
			release();
			m_pCount = r.m_pCount;
			m_pObject = r.m_pObject;
			++*m_pCount;
		}
		return *this; 
	}

	~RefObject() 
	{
		release();
	}

	int count()
	{
		return *m_pCount;
	}

private:
	void release()
	{
		--*m_pCount;
		if(*m_pCount <= 0)
		{
			delete m_pCount;	
			delete m_pObject;
		}
	}

private:
	int *m_pCount;
	T *m_pObject;
};

template<class T>
class SmartPtr
{
public:
	SmartPtr(T *p)
	:m_ptr(p), 
	 m_ref(p)
	{
	}

	SmartPtr(const SmartPtr &ptr)
	:m_ptr(ptr.m_ptr),
	 m_ref(ptr.m_ref)
	{
	}

	~SmartPtr()
	{
	}

	SmartPtr& operator=(const SmartPtr &ptr)
	{
		m_ptr = ptr.m_ptr;
		m_ref = ptr.m_ref;
	}

	bool operator==(const SmartPtr &ptr)
	{
		return m_ptr == ptr.m_ptr;
	}

	bool operator!=(const SmartPtr &ptr)
	{
		return m_ptr != ptr.m_ptr;
	}

	T *operator->()
	{
		return m_ptr;
	}

	T operator*()
	{
		return *m_ptr;
	}

	int count()
	{
		return m_ref.count();
	}

private:
	T *m_ptr;
	RefObject<T> m_ref;
};

}

#endif
