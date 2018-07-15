CXX = g++
CXXFLAGS = -lm -fopenmp
OBJS = main.o simd.p5.o
SRCS = main.cpp simd.p5.cpp

all: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o main

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm -f ${OBJS} main