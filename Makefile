CXX			:= g++
CXX_FLAGS	:= -Wall -std=c++14 

BIN				:= bin
SRC				:= src
INCLUDE			:= include

LIBRARIES	:=
EXECUTABLE	:= main

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

debug: CXX += -DDEBUG -g
debug: CCX_LAGS += -DDEBUG -g
debug: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -O -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

tests: clean all clean all test-IF test-TP test-UI test-ERS test-RB1 test-LS1 test-TS1 test-FR1
test-IF: test-IF1 test-IF2 test-IF3 test-IF4 test-IF5 test-IF6 test-IF7
test-TP: test-TP1 test-TP2 test-TP3 test-TP4 test-TP5 test-TP6 test-TP7 test-TP8 test-TP9 test-TP10 test-TP11 test-TP12
test-UI: test-UI1 test-UI2 test-UI3 test-UI4 test-UI5 test-UI6
test-ERS: test-ERS1 test-ERS2 test-ERS4 test-ERS5 test-ERS6 test-ERS7 test-ERS8
test-EGS: test-EGS1 test-EGS2 test-EGS3

test-IF1:
	@printf "\nTest the game fails to load when the a factory is invalid (missing).\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) IF1 output
test-IF2:
	@printf "\nTest the game fails to load when the players mosaic board is invalid (missing).\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) IF2 output
test-IF3:
	@printf "\nTest the game fails to load when the players broken tiles row is invalid (missing).\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) IF3 output
test-IF4:
	@printf "\nTest the game fails to load when a factory has too many tiles.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) IF4 output
test-IF5:
	@printf "\nTest the game fails to load when a players broken tiles row has too many tiles.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) IF5 output
test-IF6:
	@printf "\nTest the game fails to load when a players storage has too many tiles.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) IF6 output
test-IF7:
	@printf "\nTest the game fails to load when a players mosaic has too many tiles.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) IF7 output
test-TP1:
	@printf "\nTest tile placement from factory 1 to empty storage row.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP1
test-TP2:
	@printf "\nTest tile placement from factory 5 to empty storage row 5.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP2
test-TP3:
	@printf "\nTest tile placement from factory 2 to empty storage row. 2.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP3
test-TP4:
	@printf "\nTest tile placement from factory to 'broken'.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP4
test-TP5:
	@printf "\nTest tile cannot be placed on a full storage row.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP5
test-TP6:
	@printf "\nTest tile cannot be placed on a storage row already containing a different colour.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP6
test-TP7:
	@printf "\nTest tile cannot be placed on a storage row where corresponding mosaic row has already completed tile of the same colour.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP7
test-TP8:
	@printf "\nTest that when the broken row is full (has 7 Tiles in it) any more tiles are added to the box lid instead.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP8
test-TP9:
	@printf "\nTest that when the broken row is full (has 7 Tiles in it) any more tiles are added to the box lid instead.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP9
test-TP10:
	@printf "\nTest tile placement on 1st Center Factory for multiple players.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP10
test-TP11:
	@printf "\nTest tile placement on 2nd Center Factory for multiple players.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP11 TP11.out
test-TP12:
	@printf "\nTest tile placement on broken for multiple players.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TP12
test-UI1:
	@printf "\nTest the game handles out of range factory index input.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) UI1
test-UI2:
	@printf "\nTest the game handles char as factory index input.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) UI2
test-UI3:
	@printf "\nTest the game handles out of range storage index input.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) UI3
test-UI4:
	@printf "\nTest the game handles string as storage index input.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) UI4
test-UI5:
	@printf "\nTest the game handles non existent tile reference.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) UI5
test-UI6:
	@printf "\nTest the game handles multi character tile reference string.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) UI6
test-ERS1:
	@printf "\nTest the players score increases by 1 when 1 tile is placed at the end of a round.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) ERS1
test-ERS2:
	@printf "\nTest a players score increases by 3 when 1 tile is placed adjacent to two others horizontally at the end of a round.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) ERS2
test-ERS3:
	@printf "\nTest a players score increases by 6 when 1 tile is placed adjacent to 2 tiles horizontally and 2 tiles vertically at the end of a round.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) ERS3 ERS3.out
test-ERS4:
	@printf "\nTest a players score decreases 1 per tile for the first two spaces on the broken row.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) ERS4
test-ERS5:
	@printf "\nTest a players score decreases 1 per tile for the first two spaces on the broken row & 2 per tile for the next 3 spaces on the broken row.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) ERS5
test-ERS6:
	@printf "\nTest a players score decreases 1 per tile for the first two spaces on the broken row & 2 per tile for the next 3 spaces on the broken row & 3 per tile for the next 2 spaces on the broken row.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) ERS6
test-ERS7:
	@printf "\nTest a players score ddoes not go below zero when they lose more points than they have.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) ERS7
test-ERS8:
	@printf "\nTest end of round scores for multiple players.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) ERS8 ERS8.out
test-RB1:
	@printf "\nTest the bag refills correctly when it runs empty.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) RB1 RB1.out
test-LS1:
	@printf "\nTest the game loads and saves correctly.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) LS1
test-TS1:
	@printf "\nTest the factories sort tiles into total order.\n"
	@./run_test.sh $(BIN) $(EXECUTABLE) TS1
test-FR1:
	@printf "\nTest 1 round is playable.\n" 
	@./run_test.sh $(BIN) $(EXECUTABLE) FR1 