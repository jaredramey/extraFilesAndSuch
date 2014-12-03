#include <iostream>

using namespace std;

template <class T>
class MyStack{

private:
	T* m_paData;
	unsigned int m_uiSize;
	int m_iTop;
	unsigned int m_uiGrowSize;

public:
	MyStack(unsigned int a_uiSize, unsigned int a_uiGrowSize = 1) : m_paData(NULL), m_uiSize(a_uiSize), m_uiGrowSize(a_uiGrowSize), m_iTop(-1)
	{
		if (m_uiSize)
		{
			m_paData = new T[m_uiSize];
			memset(m_paData, 0, sizeof(T) * m_uiSize);
		}
	}
	MyStack(const MyStack &a_rStack)
	{
		
	}
	~MyStack(void)
	{
		if (m_paData != NULL)
		{
			delete[] m_paData;
			m_paData = NULL;
		}
	}

	MyStack()
	{
	
	}


	//Accessory Functions
	bool IsEmpty() const
	{
			return (m_iTop == -1) ? true : false;
	}

	int GetSize() const
	{
			return m_iYop + 1;
	}

	//Access Functions
	void Push(T &a_rValue)
	{
		MyStack *n = new MyStack<T>;

		//add value to back of stack
	}

	void Pop()
	{
			//remove value from back of stack
	}

	const T* Top()
	{
		//Return value from back of stack
	}

	//Callback Function
	void Draw(void(*drawCallBack) (const T*))
	{
		T* pEnd = m_paData + m_iTop;
		for (T* p = pEnd; p > m_paData; --p)
		{
			drawCallback(p);
		}
	}

};