#pragma once

#include "Node.h"

using std::cout;

class List
{
public:
	List(); //default constructor
	~List(); //destructor
	List(const List&); // copy constructor
	List& operator=(const List&); // assign operator

	//get function
	Node *getHead() const { return m_head; }
	unsigned int getSize()const { return m_size; }

	void insertFirst(int, double);
	void insert(int, double);
	
private:
	Node* m_head;
	unsigned int m_size;
};

