#ifndef ELO_H
#define ELO_H
#include "Xcom.h"
#include "ConfigPlus.h"
#include "L3Message.h"

class Elo
{
public:
	void action( char *);
	Elo(Xcom *xcom_, const std::string &configFileName_);

protected:
private:
	double _tsXmul, _tsYmul;
	Xcom *_xcom;
	L3Message _l3m;
};

#endif // ELO_H
