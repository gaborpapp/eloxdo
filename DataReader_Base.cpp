#include <numeric>
#include <algorithm>
#include "DataReader_Base.h"
#include "Debug/debug.h"
#include "Debug/debug.h"
#ifdef DEBUG
#include "stdio.h"
#endif
#include "elo_consts.h"

using namespace std;


//DataReader_Base::DataReader_Base(Elo *elo_,std::basic_istream<char> *inputFileP_, bool async_):
DataReader_Base::DataReader_Base(Elo *elo_,std::basic_istream<char> *inputFileP_, int algo_type_):
	_elo(elo_),
	_packetno(0),
	_inputFileP(inputFileP_),
	_algo_type(algo_type_)
{}

int DataReader_Base::read_one(){
	char c='\0';
	char checksum;

	/* read_ptr gives the location (within packet), where we should continue reading,
	in the case when the checksum was incorrect, but happened to find a sync byte in the middle of
	the ELO_PACKET_SIZE-1 bytes. I.e. we assume a few bytes may have been lost */
	char *read_ptr = _packet;

	while (_inputFileP->good()) {
		if (_algo_type == 1)
			while( !(_inputFileP->rdbuf()->in_avail()) )
				usleep(1000) ;
		//find sync byte
		c = _inputFileP->get();

		if (_inputFileP->good() && c == ELO_SYNC_BYTE) {
			DEBUG_STRING("SYNC FOUND\n");
			_inputFileP->read(read_ptr,ELO_PACKET_SIZE-1-(read_ptr-_packet));
			if (_inputFileP->gcount() == ELO_PACKET_SIZE-1-(read_ptr-_packet)) {
				DEBUG_STRING("ENOUGH BYTES READ\n");
#ifdef DEBUG
				for ( char *dbg_ptr = _packet; dbg_ptr !=_packet+ELO_PACKET_SIZE-1; ++dbg_ptr)
					fprintf(stderr,"%i,",(unsigned char)(*dbg_ptr));
				fprintf(stderr,"\n");
#endif
				read_ptr = _packet;
				checksum = accumulate(_packet,_packet+ELO_PACKET_SIZE-2,ELO_INIT_CHECKSUM);
				DEBUG_VALUE((unsigned int)checksum %256);
				DEBUG_STRING("\n");
				if ((checksum - _packet[ELO_PACKET_SIZE-2])  == 0) {
					DEBUG_STRING("Checksum OK\n");
					return 1;
				} //if: checksum ok
				else {
					DEBUG_STRING("Checksum Incorrect\n");
					// Search for another SYNC BYTE in the buffer
					read_ptr = find(_packet,_packet+ELO_PACKET_SIZE-1,ELO_SYNC_BYTE);

					if (read_ptr != _packet+ELO_PACKET_SIZE-1) {
						DEBUG_STRING("Found ELO_SYNC_BYTE in the buffer\n");
						c = ELO_SYNC_BYTE;
						copy(read_ptr+1,_packet+ELO_PACKET_SIZE-1,_packet);
						read_ptr = _packet + (_packet-read_ptr + ELO_PACKET_SIZE -2);
					}
					else {
						DEBUG_STRING("ELO_SYNC_BYTE not found in the buffer\n");
						read_ptr = _packet;
						c = '\0';
					}
				} //else: checksum incorrect
			} //if: enough bytes read
			else {
				DEBUG_STRING("NOT ENOUGH BYTES READ\n");
				if (_algo_type == 1){
					//we need to continue, by setting read_ptr appropriately
					read_ptr=_packet+_inputFileP->gcount();
				}
				else {
					//game over
					return 0;
				}
			}
		} //if: SYNC FOUND
	} //while loop
	return 0;
}

int DataReader_Base::read(){
	while(read_one()){
		++_packetno;
		DEBUG_VALUE(_packetno);
		DEBUG_STRING("\n");
		_elo->action(_packet);
	}
	return _packetno;
}

DataReader_Base::~DataReader_Base(){
	DEBUG_STRING("Destructing DataReader_Base\n");
	delete _inputFileP;
}
