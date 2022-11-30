#pragma once

/*
//cout << "TArray test :" << endl;

//TArray<int> _intArray = TArray<int>();

 ** Create and filling ** 

//_intArray.Init(5, 3);

for (int _index(0); _index < 5; _index++)
{
	//_intArray.Add(_index + 1);
	_intArray.Emplace(_index + 1);
}

/*const int _array[2] = { 78, 43 };
_intArray.Append(_array, 2);

_intArray.AddUnique(2);
_intArray.AddUnique(178);

_intArray.Insert(25, 70);
_intArray.Insert(6, 2);

//_intArray.SetNum(8);

 ** Removal ** 

//_intArray.RemoveSingle(2);
//_intArray.RemoveAt(0);

//_intArray.Display();

*/

template <typename T>
struct Node
{
	T data;
	Node<T>* previous;
	Node<T>* next;
};

template <typename T>
class List
{

private:

	Node<T>* first;
	Node<T>* last;
	int counter;

public:

	List()
	{
		counter = 0;
		first = nullptr;
		last = nullptr;
	}
	~List()
	{
		Remove(counter);
	}

private:

	Node<T>* CreateNode(const T& _data)
	{
		Node<T>* _node = new Node<T>();
		_node->data = _data;
		_node->next = nullptr;
		_node->previous = nullptr;
		
		if (counter == 0)
		{
			first = _node;
		}
		
		return _node;
	}

	void PushBack(const T& _data)
	{
		Node<T>* _newNode = CreateNode(_data);

		if (last)
		{
			last->next = _newNode;
			_newNode->previous = last;
		}

		last = _newNode;
		counter++;
	}

	void PopFront(const int& _amount)
	{
		Node<T>* _current = first;
		for (int _index(0); _index < _amount && _current; _index++)
		{
			Node<T>* _next = _current->next;

			delete _current;
			counter--;

			_current = _next;

			if (_index < _amount)
			{
				first = _current;
			}
		}
	}

public:

	/*  *** Create and Filling ***  */ 

	void Init(const T& _data, const int& _amount)
	{
		Empty();
		for (int _index(0); _index < _amount; _index++)
		{
			Emplace(_data);
		}
	}

	void Add(const T& _data)
	{
		const T& _dataCopy = _data;
		PushBack(_dataCopy);
	}

	void Emplace(const T& _data)
	{
		PushBack(_data);
	}

	void Append(const T* _array, const int& _amount)
	{
		for (int _index(0); _index < _amount; _index++)
		{
			Emplace(_array[_index]);
		}
	}

	void AddUnique(const T& _data)
	{
		Node<T>* _current = first;
		for (int _index(0); _index < counter; _index++)
		{
			if (_current->data == _data)
			{
				cerr << "Warning : There is already " << _data  << " into this array !" << endl;
				return;
			}
			_current = _current->next;
		}

		Emplace(_data);
	}

	void Insert(const T& _data, const int& _index)
	{
		Node<T>* _current = first;
		for (int _currentIndex(0); _currentIndex < counter; _currentIndex++)
		{
			if (_currentIndex == _index - 1)
			{
				Node<T>* _newNode = CreateNode(_data);
				counter++;

				Node<T>* _previous = _current->previous;

				// Pb la dessus
				_previous->next = _newNode;
				_current->previous = _newNode;
				_newNode->previous = _previous;
				_newNode->next = _current;

				return;
			}
			_current = _current->next;
		}

		Emplace(_data);
	}

	void SetNum(const int& _index)
	{
		if (counter == _index) return;

		if (counter > _index)
		{
			Remove(counter - _index);
		}

		else if (counter < _index)
		{
			const int& _toAddCount = _index - counter;
			for (int _currentIndex(0); _currentIndex < _toAddCount; _currentIndex++)
			{
				Emplace(T());
			}
		}
	}


	/*  *** Removal ***  */

	void Remove(const int& _amount)
	{
		Node<T>* _current = last;
		for (int _index(0); _index < _amount && _current; _index++)
		{
			Node<T>* _previous = _current->previous;

			delete _current;
			counter--;

			_current = _previous;

			if (_index < _amount)
			{
				last = _current;
			}
		}
	}

	void RemoveSingle(const T& _data)
	{
		Node<T>* _current = first;
		for (int _index(0); _index < counter && _current; _index++)
		{
			if (_current->data == _data)
			{
				RemoveAt(_index + 1);
				return;
			}
			_current = _current->next;
		}
	}

	void RemoveAt(const int& _index)
	{
		Node<T>* _current = first;
		for (int _currentIndex(0); _currentIndex < counter; _currentIndex++)
		{
			if (_currentIndex == _index - 1)
			{
				// 1 2 3

				if (_current != first)
				{
					_current->previous->next = _current->next;
				}

				else
				{
					first = _current->next;
				}
				
				if (_current != last)
				{
					_current->next->previous = _current->previous;
				}

				else
				{
					last = _current->previous;
				}
				
				/*Node<T>* _previous = _current->previous;
				Node<T>* _next = _current->next;

				_previous->next = _next;

				if (_next)
				{
					_next->previous = _previous;
				}*/

				delete _current;
				counter--;

				return;
			}
			_current = _current->next;
		}
	}

	// void RemoveAll();
	// void RemoveSwap();
	// void RemoveAtSwap();
	// void RemoveAllSwap();

	void Empty()
	{
		Remove(counter);
	}


	// Queries

	Node<T>* Last(const int& _index = 0)
	{
		return last;
	}

	const int Lenght()
	{
		return counter;
	}

	void Display()
	{
		Node<T>* _current = first;
		cout << endl;
		for (int _index = 0; _index < counter; _index++)
		{
			cout << "Node " << _index + 1 << " => " << _current->data << endl;
			_current = _current->next;
		}
	}

	// Operators
	const T& operator [] (int _index) const
	{
		if (_index >= counter)
		{
			return default(T);
		}

		Node<T>* _current = first;
		for (int _currentIndex(0); _currentIndex < counter; _currentIndex++)
		{
			if (_currentIndex == _index - 1)
			{
				return _current;
			}
			_current = _current->next;
		}

		return default(T);
	};
};