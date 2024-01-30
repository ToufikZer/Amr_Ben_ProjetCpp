CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g 
SRC= $(wildcard ../*.cc)
OBJ= $(SRC:.cc=.o)
TST= $(wildcard *.cc)
OBJ_TEST = $(filter-out ../main.o, $(OBJ)) $(TST:.cc=.o)

testcase.out : $(OBJ_TEST) 
	$(CC) $(CCFLAGS)  -o $@ $^ -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-window

%.o: %.cc
	$(CC) $(CCFLAGS) -I../ -o $@ -c $< -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-window

clean :
	rm -f $(OBJ_TEST) testcase.out

depends:
	g++ -MM $(SRC) >.depends
-include .depends
