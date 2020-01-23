#pragma once
#include <iostream>
#include <cstdlib> //for exit failure


using std::cout;
using std::endl;
using std::cerr;

class Node
{
public:
	Node(); //default constractor
	Node(int = 0, double = 0, Node* = nullptr); // constractor

	//oprator function
	bool operator!=(const Node&)const;
	bool operator==(const Node&)const;

	//set function
	void setNext(Node* next){ m_next = next; }

	//get function
	Node* getNext()const { return m_next; }
	int getDeg()const { return m_deg; }
	double getCoeff()const { return m_coeff; }

private:
	int m_deg;
	double m_coeff;
	Node *m_next;
};

