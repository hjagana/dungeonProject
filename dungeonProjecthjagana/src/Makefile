CXX = g++
CXX_FLAGS = -std=c++14 -g -I /usr/local/Cellar/xerces-c/3.2.3/include/ -L /usr/local/Cellar/xerces-c/3.2.3/lib/
SRC = *.cpp
INCLUDE =
LIBS =

WARNING = #-Wall
ERROR = -lxerces-c -lncurses #-Wvla -lxerces-c -lncurses #-Wvla -Werror -lxerces-c
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose
TESTFLAGS =
INPUTS =

main:
	$(CXX) $(CXX_FLAGS) $(WARNING) $(ERROR) $(TESTFLAGS) $(SRC) -o main
	#$(CXX) $(CXX_FLAGS) $(WARNING) $(ERROR) $(TESTFLAGS) $(SRC) -o main && ./main $(INPUTS)

badScroll: main
	./main ../xmlFiles/badScroll.xml
.PHONY: badScroll

death: main
	./main ../xmlFiles/death.xml
.PHONY: death

dropPack: main
	./main ../xmlFiles/dropPack.xml
.PHONY: dropPack

dungeon: main
	./main ../xmlFiles/dungeon.xml
.PHONY: dungeon

hallucinate: main
	./main ../xmlFiles/hallucinate.xml
.PHONY: hallucinate

testDrawing: main
	./main ../xmlFiles/testDrawing.xml
.PHONY: testDrawing

wear: main
	./main ../xmlFiles/wear.xml
.PHONY: wear

clean:
	-rm -f main
.PHONY: clean
