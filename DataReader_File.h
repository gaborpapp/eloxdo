#ifndef DATAREADER_FILE_H
#define DATAREADER_FILE_H
#include "DataReader_Base.h"

class DataReader_File: public DataReader_Base
{
public:
	DataReader_File(Elo *elo_, const std::string &inputFileName_, int algo_type_);
};

#endif // DATAREADER_FILE_H
