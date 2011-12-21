#include "Elo.h"
#include <iostream>
#include <stdlib.h>
#include "Debug/debug.h"

#define ELO_TOUCH	'T'
#define WORD_ASSEMBLY(byte1, byte2) (((byte2) << 8) | (byte1))




using namespace std;

Elo::Elo(Xcom *xcom_, const std::string &configFileName_):
	_xcom(xcom_)
{
	ConfigPlus config(configFileName_);
	int tsXres, tsYres;
	double tsXsize, tsYsize;

	try {
		config.readInto_check(tsXres,"TouchScreenXResolution");
		config.readInto_check(tsYres,"TouchScreenYResolution");
		config.readInto_check(tsXsize,"TouchScreenXSize");
		config.readInto_check(tsYsize,"TouchScreenYSize");
		_tsXmul = tsXsize/tsXres;
		_tsYmul = tsYsize/tsYres;

	}
	catch (ConfigFile::key_not_found s) {
		cerr << "*** Error: " << s.key << " not found in " << configFileName_ << endl;
		exit(1);
	}
}

/*
 *          Byte 0 :  ELO_TOUCH
 *          Byte 1 :  Packet type
 *            Bit 2 : Pen Up   (Release)
 *            Bit 1 : Position (Stream)
 *            Bit 0 : Pen Down (Press)
 *          Byte 2 :  X coordinate (lower bits)
 *          Byte 3 :  X coordinate (upper bits)
 *          Byte 4 :  Y coordinate (lower bits)
 *          Byte 5 :  Y coordinate (upper bits)
 *          Byte 6 :  Z coordinate (lower bits)
 *          Byte 7 :  Z coordinates (upper bits)
*/

void Elo::action(char *c_){
	unsigned char * uc;
	uc = (unsigned char *)c_;

	int cur_x, cur_y;
	int state;

	cur_x = WORD_ASSEMBLY(uc[2], uc[3]);
	cur_y = WORD_ASSEMBLY(uc[4], uc[5]);
	state = uc[1] & 0x07;
	DEBUG_OSTREAM << "Coordinates received:" << cur_x << "," << cur_y << "\n";

	if (uc[0] == ELO_TOUCH) {
		_l3m._h = _tsXmul * cur_x;
		_l3m._v = _tsYmul * cur_y;
		_l3m._event = state;
		_xcom->action(_l3m);
	}

}


