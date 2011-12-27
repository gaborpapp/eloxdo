#include <stdlib.h>
#include "DataReader_Serial.h"


using namespace std;
using namespace LibSerial ;


DataReader_Serial::DataReader_Serial(Elo *elo_, const string &inputFileName_, int algo_type_):
	DataReader_Base(elo_,new LibSerial::SerialStream(inputFileName_,ios::in), algo_type_)
{
	LibSerial::SerialStream &serialPort = * (static_cast<LibSerial::SerialStream *>(_inputFileP));
	if ( ! serialPort.good() )
    {
        std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] "
                  << "Error: Could not open serial port " << inputFileName_ << std::endl ;
        exit(1) ;
    }

    // Set the baud rate of the serial port.
    serialPort.SetBaudRate( SerialStreamBuf::BAUD_9600 ) ;
    if ( ! serialPort.good() )
    {
        std::cerr << "Error: Could not set the baud rate." << std::endl ;
        exit(1) ;
    }

    // Set the number of data bits.
    serialPort.SetCharSize( SerialStreamBuf::CHAR_SIZE_8 ) ;
    if ( ! serialPort.good() )
    {
        std::cerr << "Error: Could not set the character size." << std::endl ;
        exit(1) ;
    }

    // Disable parity.
    serialPort.SetParity( SerialStreamBuf::PARITY_NONE ) ;
    if ( ! serialPort.good() )
    {
        std::cerr << "Error: Could not disable the parity." << std::endl ;
        exit(1) ;
    }

    // Set the number of stop bits.
    serialPort.SetNumOfStopBits( 1 ) ;
    if ( ! serialPort.good() )
    {
        std::cerr << "Error: Could not set the number of stop bits."
                  << std::endl ;
        exit(1) ;
    }

    // Turn off hardware flow control.
    serialPort.SetFlowControl( SerialStreamBuf::FLOW_CONTROL_NONE ) ;
    if ( ! serialPort.good() )
    {
        std::cerr << "Error: Could not use hardware flow control."
                  << std::endl ;
        exit(1) ;
    }
}



