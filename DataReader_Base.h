#ifndef DATAREADER_BASE_H
#define DATAREADER_BASE_H
#include <iostream>
#include <fstream>
#include "Elo.h"
#include "elo_consts.h"

class DataReader_Base
{
public:
	int read();
	virtual ~DataReader_Base();
protected:
	//DataReader_Base(Elo *elo_, std::basic_istream<char> *inputFileP_,bool async_);
	DataReader_Base(Elo *elo_, std::basic_istream<char> *inputFileP_,int algo_type_);
	Elo *_elo;
	int _packetno;
	char _packet[ELO_PACKET_SIZE-1];
	int read_one();
	std::basic_istream<char> *_inputFileP;
	//bool _async;
	int _algo_type;

};

#endif // DATAREADER_BASE_H
