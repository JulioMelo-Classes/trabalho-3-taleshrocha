# Snaze: a SNAke trapped in a MaZE, programming project

# Flags
FLAGS = -Wall -g -fsanitize=address -std=c++20 -lm

# Source and include files
SRC = ../src/*.cpp
INC = ../include

all:
	g++ $(SRC) -o Snaze -I $(INC) $(FLAGS)

clean:
	rm Snaze

.PHONY: all clean
