#include "DataReader_File.h"

using namespace std;

DataReader_File::DataReader_File(Elo *elo_, const string &inputFileName_, int algo_type_):
	DataReader_Base(elo_,new std::ifstream(inputFileName_.c_str(),ios::in|ios::binary), algo_type_)

{}






