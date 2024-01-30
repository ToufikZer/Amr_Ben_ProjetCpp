
CC=g++
CCFLAGS= -Wall  -std=c++14 -g 
LIBFLAGS= 
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
EXEC= eco.out


all: $(EXEC)


$(EXEC): $(OBJ)
	$(CC) $(LIBFLAGS) $^ -o $@  -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-window

%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<  -lsfml-graphics -lsfml-system -lsfml-audio -lsfml-window


depends:
	g++ -MM $(SRC) > .depends

-include .depends

test:
	cd tests ; make
	./tests/testcase.out

clean:
	rm -f $(OBJ) $(EXEC) *.*~