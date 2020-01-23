#include "Poly.h"


//default constructor
Poly::Poly() :m_deg(0), m_poly() {
}

//constructor to skalar 
Poly::Poly(double skalar) {
	m_poly.insertFirst(0, skalar);
	m_deg = 0;
}

//constructor to monom
Poly::Poly(int deg, double coeff)
	:m_deg(deg) {

	m_poly.insertFirst(deg, coeff);
}

//constructor to vactor
Poly::Poly(const std::vector<double>& coeffs)
{
	for (int index = 0, index2 = coeffs.size() - 1;
		index < coeffs.size() && index2 >= 0;
		index++, index2--) {

		if (coeffs[index] != 0)
			m_poly.insert(index2, coeffs[index]);
	}
	m_deg = m_poly.getHead()->getDeg();
}

//equality operator
bool Poly::operator==(const Poly &other) const
{
	Node *p1 = other.m_poly.getHead(),
		 *p2 = this->m_poly.getHead();

	while (p1 && p2) {

		if (p1 == NULL || p2 == NULL)
			return false;

		if (*p1 != *p2)
			return false;

		p1 = p1->getNext();
		p2 = p2->getNext();
	}
	return true;
}

//unequality operator
bool Poly::operator!=(const Poly &other) const
{
	if (*this == other)
		return false;
	return true;
}

//add to this polinom operator
Poly & Poly::operator+=(const Poly &other){
	return(*this = *this + other);
}

//subtract from this polinum operator
Poly & Poly::operator-=(const Poly &other){
	return *this = *this + other*(-1);
}

//multiply to this polinum operator
Poly & Poly::operator*=(const Poly &other){
	return(*this = *this*other);
}

Poly & Poly::operator/=(const Poly &other)
{
	return *this = *this / other;
}

Poly & Poly::operator%=(const Poly &other)
{
	return *this = *this% other;

}

double Poly::operator[](int deg) const
{
	for (Node* p = getPolyHead(); p != nullptr; p = p->getNext())
		if (p->getDeg() == deg)
			return p->getCoeff();
	return 0;
}

double Poly::operator()(double x) const
{
	double val = 0;
	for (Node* p = getPolyHead(); p != nullptr; p = p->getNext())
		val += p->getCoeff()*pow(x, p->getDeg());

	return val;
}

//print operator
std::ostream& operator<<(std::ostream &os, const Poly &other)
{
	Node* p = other.getPolyHead();

	if (other.deg() == 0)
		return os << 0;

	for (; p != nullptr; p = p->getNext()) {

		if (p->getCoeff() != 0 && p->getDeg() == 0)
			os << p->getCoeff();

		else if (p->getCoeff() == 1)
			os << "x^" << p->getDeg();

		else os << p->getCoeff() << "x^" << p->getDeg();
		
		if (p->getNext() != nullptr && p->getNext()->getCoeff())
				os << " + ";
	}
	os << endl;
	return os;
}

//multiply two polinums operator
Poly operator*(const Poly & a, const Poly & b)
{
	int deg;
	double coeff;
	Poly c;
	Node *aPtr,*bPtr;

	for (aPtr = a.getPolyHead(); aPtr != nullptr; aPtr = aPtr->getNext()) {
		for (bPtr = b.getPolyHead(); bPtr != nullptr; bPtr = bPtr->getNext()) {

			deg = aPtr->getDeg() + bPtr->getDeg();
			coeff = aPtr->getCoeff() * bPtr->getCoeff();

			if (coeff != 0) {
				Poly temp(deg, coeff);
				c += temp;
			}
		}
	}

	return Poly(c);
}

//calculate the additive of two plinums
Poly operator+(const Poly & a, const Poly & b)
{
	Poly sum;
	Node *aPtr = a.getPolyHead();
	Node *bPtr = b.getPolyHead();
	
	calcSum(a, b,sum);
		
	if(sum.getPolyHead() != nullptr)
		sum.setDeg(sum.getPolyHead()->getDeg());
	return sum;
}

//calculate sums
void calcSum(const Poly & a, const Poly & b, Poly& sum)
{
	Node *aPtr = a.getPolyHead();
	Node *bPtr = b.getPolyHead();

	while (aPtr != nullptr && bPtr != nullptr) {

		if (aPtr->getDeg() == bPtr->getDeg()) {

			insertToPoly(aPtr->getCoeff() + bPtr->getCoeff(), sum, aPtr->getDeg());
			aPtr = aPtr->getNext();
			bPtr = bPtr->getNext();
		}
		else if (aPtr->getDeg() < bPtr->getDeg()) {

			insertToPoly(bPtr->getCoeff(), sum, bPtr->getDeg());
			bPtr = bPtr->getNext();
		}
		else if (aPtr->getDeg() > bPtr->getDeg()) {

			insertToPoly(aPtr->getCoeff(), sum, aPtr->getDeg());
			aPtr = aPtr->getNext();
		}
	}
	addOtherVal(aPtr, bPtr, sum);
}

//clculation of sum
void addOtherVal(Node* aPtr, Node* bPtr,Poly & sum)
{
	while (aPtr != nullptr) {
		insertToPoly(aPtr->getCoeff(), sum, aPtr->getDeg());
		aPtr = aPtr->getNext();
	}
	while (bPtr != nullptr) {
		insertToPoly(bPtr->getCoeff(), sum, bPtr->getDeg());
		bPtr = bPtr->getNext();
	}
}
//for the plus operator
void insertToPoly(double coeff, Poly &sum, int deg)
{
	if (coeff != 0)
		sum.getPoly().insert(deg, coeff);
}

//calculates the subtraction of two polinums
Poly operator-(const Poly & a, const Poly & b){
	return Poly( a + b*(-1));
}

//calculates the remain between two polinums
Poly operator%(const Poly & a, const Poly & b)
{
	Poly r;
	Poly c = gcd(a, b, r);
	return r;
}

//calculates the division of two polinums
Poly operator/(const Poly & a, const Poly & b)
{
	Poly r;
	return gcd(a, b, r);
}

//calc gcd
Poly gcd(const Poly& a ,const Poly & b, Poly& r)
{
	Poly q;
	r = a;
	int d = b.getPolyHead()->getDeg();
	double c = b.getPolyHead()->getCoeff();

	while (r.deg() >= d) {

		//if deg = 0 is skalar
		if (r.deg() - d == 0) {
			Poly s(r.getPolyHead()->getCoeff() / c);
			q += s;
			r.setDeg(0);
		}
		else {
			Poly s(r.deg() - d,r.getPolyHead()->getCoeff() / c);
			q += s;
			s *= b;
			r -= s;
		}
	}
	return q;
}
