#ifndef DATAREADER_SERIAL_H
#define DATAREADER_SERIAL_H
#include <SerialStream.h>
#include "DataReader_Base.h"



class DataReader_Serial : public DataReader_Base
{
public:
	DataReader_Serial(Elo *elo_, const string &inputFileName_, int algo_type_);
};

#endif // DATAREADER_SERIAL_H
