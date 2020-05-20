CXX			:= g++
CXX_FLAGS	:= -Wall -std=c++14 

BIN				:= bin
SRC				:= src
INCLUDE			:= include
TEST_INPUTS 	:= resources/tests/
TEST_OUTPUTS 	:= save_files/save_tests/

LIBRARIES	:=
EXECUTABLE	:= main

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -O -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

test1:
	@echo "\nTest the score updates correctly at the end of a round.\n"
	./$(BIN)/$(EXECUTABLE) < $(TEST_INPUTS)update_score_round_end/update_score_round_end_player.txt > /dev/null
	diff $(TEST_INPUTS)update_score_round_end/update_score_round_end_expected.txt $(TEST_OUTPUTS)update_score_round_end_output.txt 

test2:
	./$(BIN)/$(EXECUTABLE) < $(TEST_INPUTS)player1_board_missing/player1_board_missing_player.txt > $(TEST_OUTPUTS)player1_board_missing_output.txt
	diff $(TEST_INPUTS)player1_board_missing/player1_board_missing_expected.txt $(TEST_OUTPUTS)player1_board_missing_output.txt 


tests: clean all test1 test2