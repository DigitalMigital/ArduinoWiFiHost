#ifndef sergomor_List_h
#define sergomor_List_h

#include <Arduino.h>
#include <inttypes.h>

namespace sergomor
{

template <typename T>
class List
{
public:
	struct Node
	{
		T data;
		Node *next = nullptr;
		Node() {}
		Node(const T &_data)
			: data(_data)
		{
		}
		~Node() { delete next; }
	};

	class Iterator
	{
	public:
		Iterator(Node *node) {}
		bool operator==(const Iterator &other) const
		{
			return this == &other ? true : node == other.node;
		}
		bool operator!=(const Iterator &other) const { return !operator==(other); }
		T operator*() const { return node != nullptr ? node->data : T(); }
		void operator++()
		{
			if (node)
				node = node->next;
		}

	private:
		Node *node = nullptr;
	};

	List() {}
	~List() { delete head; }

	void append(const T &t);
	void remove();

	Iterator begin() const { return Iterator(head); }
	Iterator end() const { return Iterator(nullptr); }

	size_t size() const;

private:
	Node *head = nullptr;
};

template <typename T>
void List<T>::append(const T &t)
{
	Node *node = new Node(t);
	node->next = head;
	head = node;
}

template <typename T>
void List<T>::remove()
{
	if (head != nullptr)
	{
		Node *node = head->next;
		delete head;
		head = node;
	}
}

template <typename T>
size_t List<T>::size() const
{
	size_t s = 0;
	for (Node *n = head; n != nullptr; n = n->next)
		++s;
	return s;
}
}; // namespace sergomor
#endif