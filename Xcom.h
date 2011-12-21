#ifndef XCOM_H
#define XCOM_H
#include "D2V.h"
#include "L3Message.h"
//#include "ConfigFile/ConfigFile.h"
#include "ConfigPlus.h"

#include <map>
#include <string>
extern "C" {
	#include "xdo.h"
}

class Xcom
{
public:
	Xcom(const std::string &configFileName_);
	void action(L3Message);
	~Xcom();
private:
	int _monitorHres, _monitorVres;
	double _monitorHsize, _monitorVsize;
	D2V _tSPos;  //TouchScreen reference corner position,
	D2V _tSHMultiplier, _tSVMultiplier; //TouchScreen coordinates multiplier, Ideally |_tSHMultiplier| = |_tSVMultiplier| =1, but this is not checked

	xdo_t *_myxdo;

	//::: Note: sometimes the MousePRESS messages are lost. X may be confused about this.
	//::: If we find this to be the case then we generate a click if a RELEASE is found without PRESS
	//::: Uncomment all the lines beginning with //::: here and in the .cpp file
	//::: Not tested!
	//::: bool _mouseDownReceived;

};

#endif // XCOM_H
