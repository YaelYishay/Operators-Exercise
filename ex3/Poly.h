#pragma once
#include <vector>
#include "List.h"
#include <cmath>


class Poly
{
public:

	Poly(); //default constructor
	Poly(double); // constructor to skalar 
	Poly(int, double); //constructor to monom
	Poly(const std::vector <double> &); //constructor to vactor

	bool operator==(const Poly&)const;
	bool operator!=(const Poly&)const;
	Poly& operator+=(const Poly&);
	Poly& operator-=(const Poly&);
	Poly& operator*=(const Poly&);
	Poly& operator/=(const Poly&);
	Poly& operator%=(const Poly&);
	double operator[](int)const;
	double operator()(double)const;

	//get and set function
	List& getPoly(){ return m_poly; }
	Node *getPolyHead()const  { return m_poly.getHead(); }
	int getPolySize()const { return m_poly.getSize(); }
	int deg() const{ return((m_deg >= 0) ? m_deg : -1); }
	void setDeg(int deg) { m_deg = deg; }

private:
	int m_deg;
	List m_poly;
};

std::ostream& operator<<(std::ostream&,const  Poly&);
Poly operator * (const Poly& a, const Poly& b);
Poly operator + (const Poly& a, const Poly& b);
Poly operator - (const Poly& a, const Poly& b);
Poly operator % (const Poly & a, const Poly & b);
Poly operator / (const Poly & a, const Poly & b);

Poly gcd(const Poly& a, const Poly & b, Poly& r);
void calcSum(const Poly & a, const Poly & b, Poly& sum);
void addOtherVal(Node* aPtr, Node* bPtr, Poly & sum);
void insertToPoly(double coeff, Poly &sum, int deg);

