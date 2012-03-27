#ifndef _BASECLIENT_SMARTPTR_H
#define _BASECLIENT_SMARTPTR_H

namespace BaseClient
{

template<class T>
class RefObject
{
public:
	RefObject(T *p):_pObject(p)
	{
		_pCount = new int(1);
	}

	RefObject(const RefObject &r) 
	: _pCount(r._pCount), _pObject(r._pObject)
	{
		++*_pCount;
	}

	RefObject& operator= (const RefObject &r) 
	{ 
		if(_pCount != r._pCount)
		{
			release();
			_pCount = r._pCount;
			_pObject = r._pObject;
			++*_pCount;
		}
		return *this; 
	}

	~RefObject() 
	{
		release();
	}

	int count()
	{
		return *_pCount;
	}

private:
	void release()
	{
		--*_pCount;
		if(*_pCount <= 0){
			delete _pCount;	
			delete _pObject;
		}
	}

private:
	int *_pCount;
	T *_pObject;
};

template<class T>
class SmartPtr
{
public:
	SmartPtr(T *p)
	:_ptr(p), 
	 _ref(p)
	{
	}

	SmartPtr(const SmartPtr &ptr)
	:_ptr(ptr._ptr),
	 _ref(ptr._ref)
	{
	}

	~SmartPtr()
	{
	}

	SmartPtr& operator=(const SmartPtr &ptr)
	{
		_ptr = ptr._ptr;
		_ref = ptr._ref;
	}

	bool operator==(const SmartPtr &ptr)
	{
		return _ptr == ptr._ptr;
	}

	bool operator!=(const SmartPtr &ptr)
	{
		return _ptr != ptr._ptr;
	}

	T *operator->()
	{
		return _ptr;
	}

	T operator*()
	{
		return *_ptr;
	}

	int count()
	{
		return _ref.count();
	}

private:
	T *_ptr;
	RefObject<T> _ref;
};

}

#endif
