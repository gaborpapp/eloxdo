#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Xcom.h"
#include "L3Message.h"
//#include "Debug/debug.h"
#include "Elo.h"
#include "DataReader_File.h"
#include "DataReader_Serial.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc<4) {
		cerr << "Usage: " << argv[0] << " config_file input_file async" << endl;
		cerr << "Example: " << argv[0] << " sample.cfg /dev/ttyS0 1" << endl;
		cerr << "Example: " << argv[0] << " sample.cfg elo.log 0" << endl;
		exit(1);
	}

	Xcom c(argv[1]);

	Elo elo(&c,argv[1]);

	if (strcmp(argv[3],"0") == 0) {
		DataReader_File drf(&elo,argv[2]);
		drf.read();
	}
	if (strcmp(argv[3],"1") == 0) {
		DataReader_Serial drf(&elo,argv[2]);
		drf.read();
	}

}
