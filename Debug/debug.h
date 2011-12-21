#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include <iostream>
//#define DEBUG

class null_ostream: public std::ostream {
public:
    template <class T>
    null_ostream& operator<<(T anything_){
    	return *this;
	};
};


#ifdef DEBUG
#define DEBUG_OSTREAM std::cerr
#define DEBUG_VALUE(X) DEBUG_OSTREAM << #X << ":" << X
#define DEBUG_STRING(X) DEBUG_OSTREAM << X
#else //DEBUG
extern null_ostream DEBUG_OSTREAM;
#define DEBUG_VALUE(X)
#define DEBUG_STRING(X)
#endif // DEBUG

#endif
