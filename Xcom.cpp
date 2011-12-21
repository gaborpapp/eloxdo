#include "Xcom.h"
#include <stdlib.h>
#include "Debug/debug.h"

#ifdef DEBUG
#include <unistd.h>
#endif

using namespace std;


Xcom::Xcom(const string &configFileName_):
		_myxdo(NULL)
		//:::,_mouseDownReceived(false)
{
	ConfigPlus config(configFileName_);
	string display(":0.0");

	try {
	config.readInto_check(_monitorHres,"MonitorHorizontalResolution");
	config.readInto_check(_monitorVres,"MonitorVerticalResolution");
	config.readInto_check(_monitorHsize,"MonitorHorizontalSize");
	config.readInto_check(_monitorVsize,"MonitorVerticalSize");

	config.readInto_check(_tSPos,"TouchScreenPosition");
	config.readInto_check(_tSHMultiplier,"TouchScreenHorizontalMultiplier");
	config.readInto_check(_tSVMultiplier,"TouchScreenVerticalMultiplier");

	config.readInto(display,"Display"); //go with the default if not found
	_myxdo = xdo_new(const_cast<char *>(display.c_str()));

	//delete _config;
	}
	catch (ConfigFile::key_not_found s) {
		cerr << "*** Error: " << s.key << " not found in " << configFileName_ << endl;
		if (_myxdo) delete _myxdo;
		exit(1);
	}
}


void Xcom::action(L3Message m_){
	D2V point(_tSPos);
	point+=_tSHMultiplier*m_._h;
	point+=_tSVMultiplier*m_._v;
	int HCord = max(min(point.getH()/_monitorHsize*_monitorHres,(double)_monitorHres),1.0);
	int VCord = max(min(point.getV()/_monitorVsize*_monitorVres,(double)_monitorHres),1.0);
	DEBUG_OSTREAM << "Action H:" << HCord << " V:" << VCord << "\n";



	xdo_mousemove(_myxdo,HCord,VCord,0); //last param: screen
#ifdef DEBUG
	usleep(60000);
	DEBUG_VALUE(HCord);
	DEBUG_STRING("\n");
	DEBUG_VALUE(VCord);
	DEBUG_STRING("\n");
#endif



	if (m_._event == ELO_PRESS){
		DEBUG_STRING("PRESS\n");
		xdo_mousedown(_myxdo, CURRENTWINDOW, 1);
		//::: _mouseDownReceived = true;
	}
	if (m_._event == ELO_RELEASE){
		DEBUG_STRING("RELEASE\n");
		//::: if(_mouseDownReceived)
			xdo_mouseup(_myxdo, CURRENTWINDOW, 1);
		//::: else
				//::: xdo_click(_myxdo, CURRENTWINDOW, 1);
		//::: _mouseDownReceived = false;
	}

}

Xcom::~Xcom(){
	delete _myxdo;
}
