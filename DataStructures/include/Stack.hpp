#pragma once

template<typename T, typename Container = Vector<T>>
class Stack
{
public:
	Stack()
	{
		m_Container = Container();
	};

	explicit Stack(const Container& cont) : m_Container(cont) {}

	Stack(const Stack<T>& other)
	{
		m_Container = other.GetContainer();
	}

	~Stack() {}

	inline T& top() { return m_Container.back(); }
	inline const T& top() const { return m_Container.back(); }
	inline int size() const { return m_Container.size(); }
	inline bool empty() const { return m_Container.empty(); }
	
	void push(const T& value)
	{
		m_Container.push_back(value);
	}

	void pop()
	{
		m_Container.pop_back();
	}

	Stack& operator=(const Stack& other)
	{
		m_Container = other.GetContainer();
	}

	const Container& GetContainer() const
	{
		return m_Container;
	}

protected:
	Container m_Container;
};