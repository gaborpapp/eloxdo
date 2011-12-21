#include "ConfigPlus.h"

ConfigPlus::ConfigPlus (string filename,string delimiter ,string comment ,string sentry  ):
	ConfigFile(filename, delimiter, comment, sentry)
{}


ConfigPlus::ConfigPlus():
	ConfigFile()
{}
