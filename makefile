# Arquivo de Script Makefile
# 
# Aula de LP1 2018.2
# 20/09/2018
# Clonagem atual para teste :
# 				git clone https://github.com/gdiael/LP01_005_JogoDadosII.git
#
# Gdiael Souto Barros
#

CC = g++

OBJ = ./build
SRC = ./src
BIN = ./bin
INC = ./include

F01 = Node
F02 = LinkedList
F03 = TestList
F04 = main

PROG1 = $(BIN)/TestList

CPPFLAGS = -Wall -pedantic -std=c++11 -I$(INC)

OBJ1 = $(OBJ)/$(F02).o $(OBJ)/$(F03).o $(OBJ)/$(F04).o
OBJDB = $(SRC)/$(F02).cpp $(SRC)/$(F03).cpp $(SRC)/$(F04).cpp

all: mkdirs $(PROG1)

mkdirs:
	mkdir -p $(BIN)
	mkdir -p $(OBJ)

$(PROG1): $(OBJ1)
	$(CC) $(CPPFLAGS) -o $(PROG1) $(OBJ1)

db$(PROG1): $(OBJDB)
	$(CC) -g $(CPPFLAGS) -o $(PROG1) $(OBJDB)

$(OBJ)/$(F02).o: $(SRC)/$(F02).cpp $(INC)/$(F02).h $(INC)/$(F01).h
	$(CC) $(CPPFLAGS) -c $(SRC)/$(F02).cpp -o $(OBJ)/$(F02).o

$(OBJ)/$(F03).o: $(SRC)/$(F03).cpp $(INC)/$(F01).h $(INC)/$(F02).h  $(INC)/$(F03).h
	$(CC) $(CPPFLAGS) -c $(SRC)/$(F03).cpp -o $(OBJ)/$(F03).o

$(OBJ)/$(F04).o: $(SRC)/$(F04).cpp $(INC)/$(F01).h $(INC)/$(F02).h  $(INC)/$(F03).h
	$(CC) $(CPPFLAGS) -c $(SRC)/$(F04).cpp -o $(OBJ)/$(F04).o

clean: 
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

debug: db$(PROG1)
	gdb $(PROG1)

run: all
	$(PROG1)

# propriedades para serem usadas no windows com o MinGW com gcc e gdb
# não usar o comando Make e sim o executável: mingw32-make.exe

mkdirswin:
	if not exist bin mkdir bin
	if not exist build mkdir build

runwin: mkdirswin $(PROG1)
	chcp 65001
	$(PROG1)

debugwin: cleanwin db$(PROG1)

cleanwin: 
	del /q bin\*
	del /q build\*