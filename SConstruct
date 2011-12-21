Target = 'eloxdo'

env = Environment()
env.Append(CCFLAGS = '-O3 -Wall')

LibList = [['xdo', 'xdo.h', 'C'],
		   ['serial', 'SerialPort.h', 'C++']]

if not GetOption('clean'):
	conf = Configure(env)
	for (lib, headers, lang) in LibList:
		if not conf.CheckLibWithHeader(lib, headers, lang, autoadd = 1):
			print "ERROR: '%s' must be installed!" % (lib)

Source = ['ConfigPlus.cpp', 'D2V.cpp', 'DataReader_Base.cpp',
		  'DataReader_File.cpp', 'DataReader_Serial.cpp', 'Elo.cpp',
		  'main.cpp', 'Xcom.cpp', 'ConfigFile/ConfigFile.cpp']

env.Program(source = Source, target = Target)

