#include "Node.h"

//default constractor
Node::Node()
	:m_deg(0), m_coeff(0),m_next(nullptr) {}

//constractor
Node::Node(int deg, double coeff, Node* next)
	: m_deg(deg), m_coeff(coeff), m_next(next) {}

//unequal operator
bool Node::operator!=(const Node &other) const
{
	if (*this == other)
		return false;
	return true;
}

//equal operator
bool Node::operator==(const Node &other) const
{
	if (m_deg != other.m_deg && abs(m_coeff - other.m_coeff) > 0.0001)
		return false;
	return true;
}

