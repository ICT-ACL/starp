.PHONY: clean all

CUR_DIR = $(shell pwd)

RM = rm -rf
AR = ar rv
MAKE = make
CXX = g++
CXXFLAGS = -O3 -std=c++11 
ECXXFLAGS = 
INC = -I../src -I../deps
LDFLAGS = 
LDLIBS = -lgtest -lgtest_main -lpthread

#SRCS = $(wildcard ../*.cpp)
SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

#TARGETS = $(patsubst %.cpp, %.exe, $(SRCS))
TARGETS = test.exe

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $(ECXXFLAGS) $(INC) -c $< -o $@

all: $(TARGETS)
	@for t in $(TARGETS); do ./$$t ; done

test.exe: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)
	
clean:
	$(RM) $(OBJS) $(TARGETS)
