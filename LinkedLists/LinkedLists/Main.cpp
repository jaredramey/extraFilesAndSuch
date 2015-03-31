#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node{
	int value;
	Node *next;

};

template <typename T>
class LinkedList{
private:
	Node *start;
public:
	LinkedList()
	{
		
	}

	~LinkedList()
	{
		
	}


	void DisplayList()
	{
		Node *current = start;

		while (current != nullptr)
		{
			cout << current->value << " ";
			current = current->next;
		}
	}

	void AddToFront(T value)
	{
		Node *n = new Node;
		n->value = value;
		n->next = start;
		start = n;

	}

	void Remove(int pos)
	{
		Node *n= start;
		for (int i = 0; n && i < pos; i++)
		{
			n = n->next;
			
		}

		Node *r = n->next;
		n->next = r->next;
		delete r;
	}

	T Get(int pos)
	{
		Node *n = start;
		for (int i = 1; n && i < pos; i++)
		{
			n = n->next;
		}

		return n->value;
	}

	bool Search(int value)
	{
		Node *n = start;
		for (int i = 1; n && i < listSize; i++)
		{
			n = n->next;
			if (n->value == value)
			{
				return true;
			}
		}

		if (n->value != value)
		{
			return false;
		}
	}
};


LinkedList<int> MyList;
int listSize;
bool numberIsFound = false;

int main()
{
	

	for (int i = 0; i < 29; i++)
	{
		MyList.AddToFront(rand() % 100 + 1);
		listSize++;
	}
	MyList.DisplayList();

	cout << endl;
	cout << listSize << endl;

	while (listSize != 5)
	{
		for (int i = 1; i < listSize; i++)
		{
			if (listSize == 5)
			{
				break;
			}

			for (int j = 0; j < 100; j++)
			{
				if (MyList.Search(j) == true)
				{
					numberIsFound = true;
				}
			}

			if (numberIsFound == true)
			{
				cout << MyList.Get(i) << " was found and removed" << endl;
				MyList.Remove(i);
				listSize--;
				numberIsFound = false;
			}
		}
	}
		cout << listSize << endl;
		MyList.DisplayList();
		cout << endl;


	system("PAUSE");
	return 0;
}



