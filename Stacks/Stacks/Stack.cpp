#include "Stack.h"

template<class T>
MyStack<T>::MyStack()
{
	
}

template<class T>
bool MyStack<T>::IsEmpty() const
{
	return (m_iTop == -1)?true:false;
}

template<class T>
int MyStack<T>::GetSize() const
{
	return m_iYop + 1;
}

template<class T>
void MyStack<T>::Push(T &a_rValue)
{
	//Check for space in the stack and resize if necessary

	//add value to back of stack
}

template<class T>
void MyStack<T>::Pop()
{
	//remove value from back of stack
}

template<class T>
const T* MyStack<T>::Top()
{
	//Return value from back of stack
}

template<class T>
void MyStack<T>::Draw(void (*drawCallback)(const T*))
{
	T* pEnd = m_paData + m_iTop;
	for (T* p = pEnd; p > m_paData; --p)
	{
		drawCallback(p);
	}
}