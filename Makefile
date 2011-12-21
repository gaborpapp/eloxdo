CCFLAGS := -O3 -Wall 
OBJECTS := ConfigPlus.o	DataReader_Base.o DataReader_Serial.o main.o D2V.o	DataReader_File.o Elo.o Xcom.o ConfigFile/ConfigFile.o xdotool/libxdo.so

.cpp.o:
	g++ $(CCFLAGS) -c $<

TouchScreen: $(OBJECTS) Makefile
	g++  -o TouchScreen $(OBJECTS) -l serial

zip: 
	zip -r touchscreen.zip *.cpp Makefile ConfigFile/ConfigFile.h ConfigFile/ConfigFile.cpp Debug xdotool Touchscreen.cbp Touchscreen.layout *.h sample.cfg

