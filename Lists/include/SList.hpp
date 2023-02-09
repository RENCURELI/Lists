#pragma once
#include "DListNode.hpp"
#include <iostream>
#include <initializer_list>
#include <stdexcept>

// Update to also set prevNode pointer as this is doubly linked list

template<class T>
class List
{
public:
	List() {};
	List(std::initializer_list<T> l)
	{
		for (const auto& it : l)
		{
			push_back(it);
		}
	}

	~List()
	{
		// Go from m_Head to m_Tail and free memory
		while (m_Head != nullptr)
		{
			DListNode<T>* temp = m_Head->GetNext();
			delete m_Head;
			m_Head = temp;
		}
	}

	// Keeping for reference when implementing DoublyLinked List and Forward List
	DListNode<T>* AddToFront(T data)
	{
		DListNode<T>* newNode = new DListNode<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
			m_IsEmpty = false;
		}
		else
		{
			newNode->SetNext(m_Head);
			m_Head = newNode;
		}
		m_Size++;
		return newNode;
	}

	DListNode<T>* push_back(T data)
	{
		DListNode<T>* newNode = new DListNode<T>(data);

		// We are adding the first node
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
			m_IsEmpty = false;
		}
		else
		{
			m_Tail->SetNext(newNode);
			newNode->SetPrev(m_Tail);
			m_Tail = newNode;
		}
		m_Size++;
		return newNode;
	}

	DListNode<T>* InsertAt(T data, int index)
	{
		//assert(index >= 0 && index <= m_Size); // We assert that we pass a valid index
		CheckIndex(index, true);
		DListNode<T>* newNode = new DListNode<T>(data);

		// Empty list case handled by creating first element
		if (m_Head == nullptr)
		{
			m_Head = newNode;
			m_Tail = newNode;
			m_IsEmpty = false;
		}
		else
		{
			// We insert at index 0, specific behaviour
			if (index == 0)
			{
				newNode->SetNext(m_Head);
				m_Head = newNode;
			}
			else if (index == m_Size)
			{
				m_Tail->SetNext(newNode);
				newNode->SetPrev(m_Tail);
				m_Tail = newNode;
			}
			else
			{
				DListNode<T>* prevNode = AdvanceTo(index - 1);
				newNode->SetNext(prevNode->GetNext());
				prevNode->SetNext(newNode);
			}
		}

		m_Size++;
		return newNode;
	}

	// Remove last node
	void Remove()
	{
		if (m_Size == 0)
			return;
		
		if (m_Size == 1)
		{
			delete m_Tail;
			m_Head = nullptr;
			m_Tail = nullptr;
			m_IsEmpty = true;
		}
		else if (m_Size > 1)
		{
			//DListNode<T>* newTail = AdvanceTo(m_Size - 2);
			DListNode<T>* newTail = m_Tail->GetPrev();
			newTail->SetNext(nullptr);
			delete m_Tail;
			m_Tail = newTail;
		}

		m_Size--;
	}

	// Remove node at specified Index
	void RemoveAt(int index)
	{
		CheckIndex(index);
		if (index == 0)
		{
			DListNode<T>* currHead = m_Head;
			m_Head = m_Head->GetNext();
			delete currHead;
		}
		else if (index == m_Size - 1)
		{
			DListNode<T>* newTail = AdvanceTo(index - 1);
			m_Tail = newTail;
			delete m_Tail->GetNext();
			m_Tail->SetNext(nullptr);
		}
		else
		{
			DListNode<T>* prevNode = AdvanceTo(index - 1);
			DListNode<T>* nodeToDel = AdvanceTo(index);
			prevNode->SetNext(nodeToDel->GetNext());
			delete nodeToDel;
		}

		m_Size--;
		if (m_Size == 0)
			m_IsEmpty = true;
	}

	inline bool IsEmpty() { return m_IsEmpty; }
	inline int GetSize() { return m_Size; }

	void PrintList()
	{
		DListNode<T>* current = m_Head;
		while (current != nullptr)
		{
			std::cout << " -> " << current->GetData();
			current = current->GetNext();
		}
	}

private:
	DListNode<T>* m_Head = nullptr;
	DListNode<T>* m_Tail = nullptr;
	bool m_IsEmpty = true;
	int m_Size = 0;

	DListNode<T>* AdvanceTo(int index) const
	{
		// If we are accessing already allocated values, return those
		if (index == 0)
			return m_Head;
		else if (index == m_Size - 1)
			return m_Tail;
		else
		{
			// Loop within the list to find the proper element
			DListNode<T>* prevNode = m_Head;
			int i = 0;

			do
			{
				prevNode = prevNode->GetNext();
				++i;
			} while (i < index);
			
			return prevNode;
		}
	}

	// AllowExtra is to allow using InsertAt the same way as AddToBack
	bool CheckIndex(const int index, bool allowExtra = false)
	{
		if (allowExtra)
		{
			if (index < 0 || index > m_Size)
			{
				throw std::runtime_error("[ERROR] : Index Out of Bounds.");
				return false;
			}
		}
		else if (index < 0 || index > m_Size - 1)
		{
			throw std::runtime_error("[ERROR] : Index Out of Bounds.");
			return false;
		}

		return true;
	}
};
