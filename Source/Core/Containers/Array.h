#pragma once
#include <iostream>

template <typename T>
class Array
{
private:
	struct Node
	{
		T data;
		Node* previous;
		Node* next;
	};
	
	int count;
	Node* first;
	Node* last;

public:
	Array()
	{
		count = 0;
		first = nullptr;
		last = nullptr;
	}
	Array(const Array& _other)
	{
		count = 0;
		first = nullptr;
		last = nullptr;
		
		Node* _currentNode = _other.first;
		while (_currentNode != nullptr)
		{
			Add(_currentNode->data);
			_currentNode = _currentNode->next;
		}
	}
	Array(std::initializer_list<T> _array)
	{
		count = 0;
		first = nullptr;
		last = nullptr;
		
		for (auto& item : _array)
		{
			Add(item);
		}
	}
	~Array()
	{
		Remove(count);
	}

public:
	#pragma region Create and Filling

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
		Node* _node = new Node();
		_node->data = _data;
		_node->next = nullptr;
		_node->previous = nullptr;
		
		if (count == 0)
		{
			first = _node;
			last = _node;
		}

		else
		{
			last->next = _node;
			_node->previous = last;
			last = _node;
		}

		count++;
	}
	void Emplace(const T& _data)
	{
		Add(_data);
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
		Node* _current = first;
		for (int _index(0); _index < count; _index++)
		{
			if (_current->data == _data)
			{
				std::cerr << "Warning : There is already " << _data  << " into this array !" << std::endl;
				return;
			}
			_current = _current->next;
		}

		Emplace(_data);
	}
	void Insert(const T& _data, const int& _index)
	{
		if (_index < 0 || _index > count)
		{
			// Vérifier si l'index est valide
			throw std::out_of_range("Index out of range");
		}

		if (_index == 0 || _index == count)
		{
			// Si l'index est 0 ou si l'index est égal au nombre d'éléments, appeler simplement la méthode Add pour ajouter au début ou  à la fin
			Add(_data);
		}
		
		else
		{
			// Sinon, parcourir jusqu'à l'index spécifié
			Node* current = first;
			for (int i = 0; i < _index; i++)
			{
				current = current->next;
			}

			// Créer un nouveau nœud avec la valeur donnée
			Node* newNode = new Node;
			newNode->data = _data;
			newNode->previous = current->previous;
			newNode->next = current;

			// Mettre à jour les pointeurs des nœuds voisins pour pointer vers le nouveau nœud
			current->previous->next = newNode;
			current->previous = newNode;

			// Augmenter le compteur d'éléments
			count++;
		}
	}
	void SetNum(const int& _index)
	{
		if (count == _index) return;

		if (count > _index)
		{
			Remove(count - _index);
		}

		else if (count < _index)
		{
			const int& _toAddCount = _index - count;
			for (int _currentIndex(0); _currentIndex < _toAddCount; _currentIndex++)
			{
				Emplace(T());
			}
		}
	}

	#pragma endregion

	#pragma region Removal

	void Remove(const int& _amount)
	{
		Node* _current = last;
		for (int _index(0); _index < _amount && _current; _index++)
		{
			Node* _previous = _current->previous;

			delete _current;
			count--;

			_current = _previous;

			if (_index < _amount)
			{
				last = _current;
			}
		}
	}
	void RemoveSingle(const T& _data)
	{
		Node* _current = first;
		for (int _index(0); _index < count && _current; _index++)
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
		Node* _current = first;
		for (int _currentIndex(0); _currentIndex < count; _currentIndex++)
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
				
				/*Node* _previous = _current->previous;
				Node* _next = _current->next;

				_previous->next = _next;

				if (_next)
				{
					_next->previous = _previous;
				}*/

				delete _current;
				count--;

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
		while (first != nullptr)
		{
			const Node* _node = first;
			first = first->next;
			delete _node;
		}
		
		count = 0;
		first = nullptr;
		last = nullptr;
	}

	#pragma endregion 

	#pragma region Queries

	Node* begin()
	{
		return first;
	}
	Node* end()
	{
		return nullptr;
	}
	Node* Last(const int& _index = 0)
	{
		return last;
	}
	int Lenght() const
	{
		return count;
	}
	void Display()
	{
		Node* _current = first;
		std::cout << std::endl;
		for (int _index = 0; _index < count; _index++)
		{
			std::cout << "Node " << _index + 1 << " => " << _current->data << std::endl;
			_current = _current->next;
		}
	}

	#pragma endregion

	#pragma region Operators

	Array& operator=(std::initializer_list<T> _initializer)
	{
		Empty();

		for (const T& element : _initializer)
		{
			Add(element);
		}

		return *this;
	}
	Array& operator=(const Array& _array)
	{
		if (this != &_array)
		{
			Empty();

			Node* _currentNode = _array.first;
			while (_currentNode != nullptr)
			{
				Add(_currentNode->data);
				_currentNode = _currentNode->next;
			}
		}
		
		return *this;
	}
	T& operator[](int _index)
	{
		if (_index < 0 || _index >= count)
		{
			throw std::out_of_range("Index out of bounds");
		}

		Node* current = first;
		for (int i = 0; i < _index; i++)
		{
			current = current->next;
		}

		return current->data;
	}
	const T& operator[](int index) const
	{
		if (index < 0 || index >= count)
		{
			throw std::out_of_range("Index out of bounds");
		}

		const Node* current = first;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}

		return current->data;
	}

	#pragma endregion
};