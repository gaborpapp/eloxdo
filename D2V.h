#ifndef D2V_H
#define D2V_H

#include <iostream>

//Two dimensional vector
class D2V
{
public:
	D2V(double h_=0.0, double v_=0.0):
		_h(h_),
		_v(v_)
	{}
	double getH() {
		return _h;
	}
	double getV() {
		return _v;
	}
	D2V operator+(const D2V& other_);
	D2V& operator+=(const D2V& other_);
	D2V operator*(double c_);
	D2V& operator*=(double c_);
	friend
	std::istream& operator>>( std::istream& is_, D2V&  d2v_);

	friend
	std::ostream& operator<<( std::ostream& os_, D2V&  d2v_);

protected:
private:
	double _h, _v;
};

#endif // D2V_H
