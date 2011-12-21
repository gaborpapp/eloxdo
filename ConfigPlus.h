#ifndef CONFIGPLUS_H
#define CONFIGPLUS_H
#include "ConfigFile/ConfigFile.h"
#include "Debug/debug.h"

//Extends ConfigFile with readInto_check(...) which checks for the existence of key
class ConfigPlus:public ConfigFile {
public:
	ConfigPlus (string filename,
		string delimiter = "=",
		string comment = "#",
		string sentry = "EndConfigFile" );
	ConfigPlus();

	template<class T>
	bool readInto_check( T& var, const string& key ) const;



};


template<class T>
bool ConfigPlus::readInto_check( T& var, const string& key ) const
{
// Get the value corresponding to key and store in var
// Return true if key is found
// Otherwise leave var untouched
	mapci p = myContents.find(key);
	bool found = ( p != myContents.end() );
	if( found ){
		var = string_as_T<T>( p->second );
		DEBUG_VALUE(key);
		DEBUG_STRING(", ");
		DEBUG_VALUE(var);
		DEBUG_STRING("\n");
		return found;
	}
	else{
		throw key_not_found(key);
	}
}


#endif
