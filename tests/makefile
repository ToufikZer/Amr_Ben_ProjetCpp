CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g 
SRC= $(wildcard ../*.cpp)
OBJ= $(SRC:.cc=.o)
TST= $(wildcard *.cpp)
OBJ_TEST = $(filter-out ../main.o, $(filter-out ../main.cpp, $(OBJ))) $(TST:.cpp=.o)

testcase.out : $(OBJ_TEST) 
	$(CC) $(CCFLAGS)  -o $@ $^ -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-window

%.o: %.cpp
	$(CC) $(CCFLAGS) -I../ -o $@ -c $< -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-window

clean :
	rm -f testcase.out tests.o

depends:
	g++ -MM $(SRC) >.depends
-include .depends
