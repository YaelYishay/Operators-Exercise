#include "List.h"


//default constractor
List::List() :m_head(nullptr), m_size(0) {}

//decstructor
List::~List()
{
	Node *p1, *p2;
	p1 = m_head;

	while (p1 != nullptr) {
		p2 = p1;
		p1 = p1->getNext();
		delete p2;
	}
}

//copy constructor
List::List(const List &other)
{
	Node *p = other.m_head;

	if (p == nullptr)
		return;
	
	insertFirst(p->getDeg(), p->getCoeff());

	for (p = p->getNext(); p != nullptr; p = p->getNext()) {
		insert(p->getDeg(), p->getCoeff());

		if (p->getNext() == nullptr)
			break;
	}
	m_size = other.m_size;
}

// assign operator
List& List::operator=(const List &other)
{

	Node *p = other.m_head;

	if (p == nullptr)
		return *this;

	insertFirst(p->getDeg(), p->getCoeff());

	for (p = p->getNext(); p != nullptr; p = p->getNext()) {
		insert(p->getDeg(), p->getCoeff());

		if (p->getNext() == nullptr)
			break;
	}
	m_size = other.m_size;
	return *this;
}

//insert first link in linked list
void List::insertFirst(int deg, double coeff)
{
	m_head = new Node(deg, coeff, NULL);

	if (m_head == nullptr) {
		cerr << "Cannot allocate memory\n";
		exit(EXIT_FAILURE);
	}
	m_size++;
}

//insert to linked list
void List::insert(int deg, double coeff)
{
	Node *p1 = m_head, *p2;

	if (p1 == nullptr) {
		insertFirst(deg, coeff);
		return;
	}

	while (p1->getNext() != nullptr)
		p1 = p1->getNext();

	p2 = new Node(deg, coeff, nullptr);
	if (p2 == nullptr) {
		cerr << "Cannot allocate memory\n";
		exit(EXIT_FAILURE);
	}

	p1->setNext(p2);

	m_size++;

}







