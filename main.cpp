#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Xcom.h"
#include "L3Message.h"
#ifdef DEBUG
#	include "Debug/debug.h"
#endif
#include "Elo.h"
#include "DataReader_File.h"
#include "DataReader_Serial.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc !=3 ) {
		cerr << "Usage: " << argv[0] << " config_file input_file" << endl;
		cerr << "Example: " << argv[0] << " sample.cfg /dev/ttyS0" << endl;
		cerr << "Example: " << argv[0] << " sample.cfg elo.log" << endl;
		exit(1);
	}

	bool initialize;
	int algo_type;
	{
		ConfigPlus config(argv[1]);
		try {
			config.readInto_check(initialize,"Initialize");
			config.readInto_check(algo_type,"AlgorithmType");
		}
		catch (ConfigFile::key_not_found s) {
		cerr << "*** Error: " << s.key << " not found in " << argv[1] << endl;
		exit(1);
		}
	}

	Xcom c(argv[1]);

	Elo elo(&c,argv[1]);

	if (!initialize) {
		DataReader_File drf(&elo,argv[2],algo_type);
		drf.read();
	}
	if (initialize) {
		DataReader_Serial drf(&elo,argv[2],algo_type);
		drf.read();
	}

}
