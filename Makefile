CC = g++
LOADLIBES = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CXXFLAGS = -Wall -O2 -Wno-narrowing

SRC_MAIN = Driver.cpp
SRC_ALT = Object.cpp
SRC = Driver.cpp Object.cpp
BUILD = $(SRC:.cpp=)
OBJS = $(SRC:.cpp=.o)

all: $(SRC) $(OBJS) Driver;

Driver: Driver.cpp Object.cpp
	$(CC) $(SRC_MAIN) -o main $(SRC_ALT) $(LOADLIBES) $(CXXFLAGS) 
 
clean:
	rm -rf $(BUILD) $(OBJS)
