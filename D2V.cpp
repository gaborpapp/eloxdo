#include "D2V.h"


D2V D2V::operator+(const D2V& other_){
	return D2V(_h+other_._h, _v+other_._v);
}

D2V& D2V::operator+=(const D2V& other_){
	_h+=other_._h;
	_v+=other_._v;
	return *this;
}

D2V D2V::operator*(double c_){
	return D2V(_h*c_,_v*c_);
}

D2V& D2V::operator*=(double c_){
	_h*=c_;
	_v*=c_;
	return *this;
}

std::istream& operator>>( std::istream& is_, D2V&  d2v_){
	is_ >> d2v_._h >> d2v_._v;
	return is_;
}

std::ostream& operator<<( std::ostream& os_, D2V&  d2v_){
	os_ << "D2V(" << d2v_._h <<","<< d2v_._v<<")";
	return os_;
}
