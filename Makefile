CXXFLAGS = -g -Wall -O0
CXX = g++

OBJECTS = AIContest.o BoardV3.o Message.o PlayerV2.o conio.o contest.o \
	amwplayer.o CleanPlayerV2.o

contest: $(OBJECTS)
	g++ -o contest $(OBJECTS)

clean:
	rm -f contest $(OBJECTS) 

contest.o: contest.cpp
contest.cpp: defines.h Message.cpp
Message.o: Message.cpp
Message.cpp: Message.h defines.h
conio.o: conio.cpp
conio.cpp: conio.h

AIContest.o: AIContest.cpp
AIContest.cpp: AIContest.h Message.h defines.h

# Players here
amwplayer.o: amwplayer.cpp Message.cpp
amwplayer.cpp: amwplayer.h defines.h PlayerV2.h conio.cpp

# CleanPlayerV2.o is only available as a linkable Linux binary, not as source code.
CleanPlayerV2.o: 
	tar -xvf binaries.tar CleanPlayerV2.o
BoardV3.o:
	tar -xvf binaries.tar BoardV3.o
