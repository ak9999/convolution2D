# Written by Abdullah Khan

#Compiler and compiler flags for standard g++
CC=g++
C++FLAGS=-Wall -std=c++11 -pedantic
DEBUG=-g

# It is important that "-l OpenCL" is the final argument when calling g++.

# Compiler flags differ depending on platform.
# Need to check whether we're on Linux or Mac.
PLATFORM := $(shell uname -s)
ifeq ($(PLATFORM),Linux)
	C++FLAGS += -l OpenCL
endif
ifeq ($(PLATFORM),Darwin)
	C++FLAGS += -framework OpenCL
endif

# Math Library
MATH_LIBS = -lm
EXEC_DIR=.

#Including
INCLUDES= -I.
LIBS_ALL= -L/usr/lib -L $(MATH_LIBS)

all:
	make convolution
	make ocl_convolution

convolution:
	$(CC) convolution.cpp -o convolution \
		$(C++FLAGS)

ocl_convolution:
	$(CC) opencl_convolution.cpp -o ocl_convolution \
		$(C++FLAGS)

clean:
	(rm -f *.o;)
	(rm -f *.out;)
	(rm -f *.txt;)
	(rm -f debug;)
	(rm -f convolution;)
	(rm -f ocl_convolution;)
	(rm -f ocl_debug;)
