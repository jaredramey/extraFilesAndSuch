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
	MyStack(unsigned int a_uiSize, unsigned int a_uiGrowSize = 1);
	MyStack(const MyStack &a_rStack);
	~MyStack(void);

	MyStack();


	//Accessory Functions
	bool IsEmpty() const;
	int GetSize() const;

	//Access Functions
	void Push(T &a_rValue);
	void Pop();
	const T* Top();

	//Callback Function
	void Draw(void(*drawCallBack) (const T*));

};