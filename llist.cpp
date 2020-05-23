#include "llist.h"
#include <stdexcept>

LList::Node::Node(const int value, Node* next)
{
	this->value = value;
	this->next = next;
}

LList::Node::~Node()
{

}

void LList::Node::insertNext(const int& value)
{
	Node* newNode = new Node(value, this->next);
	this->next = newNode;
}


void LList::Node::removeNext()
{
	Node* removeNode = this->next;
	Node* newNext = removeNode->next;
	if (newNext == nullptr) throw std::out_of_range("nonexistent node");
	delete removeNode;
	this->next = newNext;
}

LList::LList()
	: _head(nullptr), _size(0)
{
}

LList::~LList()
{
	delition(_head);
}

LList::Node* LList::getNode(const size_t pos) const
{
	if (pos < 0) {
		throw std::out_of_range("Incorrect index");
	}
	else if (pos >= this->_size) {
		throw std::out_of_range("Incorrect index");
	}

	Node* bufNode = this->_head;
	for (int i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}

void LList::push_back(int val)
{
	if (_size == 0) {
		push_front(val);
		return;
	}
	insert_at(_size, val);
}

void LList::push_front(int val)
{
	_head = new Node(val, _head);
	++_size;
}

void LList::pop_front()
{
	if (_size == 1)
	{
		delete _head;
		_head = nullptr;
		_size = 0;
		return;
	}
	if (_head == nullptr)
	{
		throw std::out_of_range("Incorrect deletion");
	}

	Node* Buf = _head->next;
	delete _head;
	_head = Buf;
	_size--;
}

size_t LList::size() const
{
	return _size;
}

int& LList::operator[](size_t idx)
{
	return getNode(idx)->value;
}

int LList::operator[](size_t idx) const
{
	int a =  getNode(idx)->value;
	return a;

}

void LList::erase_at(size_t idx)
{
	if (idx > _size&& idx < 0) throw std::out_of_range("Incorrect index");
	if (idx == 0) pop_front();
	else
	{
		Node* tmp = _head;
		for (size_t i = 0; i < idx - 1; i++)
		{
			tmp = tmp->next;
		}
		tmp->removeNext();
		_size--;
	}
}

void LList::insert_at(size_t idx, int val)
{
	if (idx < 0) {
		throw std::out_of_range("incorrect index");
	}
	else if (idx > this->_size) {
		throw std::out_of_range("incorrect index");
	}

	if (idx == 0) {
		push_front(val);
	}
	else {
		Node* bufNode = this->_head;
		for (size_t i = 0; i < idx - 1; ++i) {
			bufNode = bufNode->next;
		}
		bufNode->insertNext(val);
		++_size;
	}
}

void LList::reverse()
{
	if (_head == nullptr) return;
	Node* curr, * next, * prev = nullptr;
	curr = _head;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	_head = prev;
}

void LList::pop_back()
{
	if (_size > 1)
	{
		getNode(_size - 2)->removeNext();
		_size--;
	}
	else pop_front();
}




void LList::delition(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->next;
	delete node;
	delition(nextDeleteNode);
}
