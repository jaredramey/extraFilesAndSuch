#include <iostream>
#include <stdlib.h>

using namespace std;

template <typename T>
class Node{
public:
	T value;
	Node *next;

};

template <typename T>
class LinkedList{
private:
	Node<T> *start;
public:
	LinkedList();
	~LinkedList();

	Node<T> *Begin();
	Node<T> *End();

	void AddToFront(T value)
	{
		Node<T> *n = new Node<T>;
		n->value = value;
		n->next = start;
		start = n;
	}

	void Remove(int n)
	{
		Node<T> = *start;
		for (int i = 1; n && i < pos; i++)
		{
			n = n->next;

			if (n && n->next)
			{
				Node *r = n->next;
				n->next = r->next;
				delete r;
			}
		}
	}
};


int main()
{
	Node<int> MyNode;
	LinkedList<int> MyList;

	for (int i = 0; i < 29; i++)
	{
		MyList.AddToFront(rand() % 100 + 1);
	}

	system("PAUSE");
	return 0;
}



