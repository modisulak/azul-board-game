#!/bin/bash
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

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -O -o $@ $(LIBRARIES)

clean:
	-rm $(BIN)/*

test1: 
	@printf "\nTest the bag refills correctly when it runs empty.\n"
	@./run_test $(BIN) $(EXECUTABLE) bag_empty_refill
 
test2:
	@printf "\nTest that a player cannot add a tile to a storage row with same tile already completed on the mosaic.\n"
	@./run_test $(BIN) $(EXECUTABLE) cannot_add_to_row_with_same_tile_on_mosaic

test3:
	@printf "\nTest the game loads and saves correctly.\n"
	@./run_test $(BIN) $(EXECUTABLE) game_loads_correctly
test4:
	@printf "\nTest the movement of a tile to the storage area of the board.\n"
	@./run_test $(BIN) $(EXECUTABLE) move_tile_to_board

test5:
	@printf "\nTest the first player for the round to pick a tile from the center 'discard' pile.\n"
	@./run_test $(BIN) $(EXECUTABLE) pick_tile_from_centerpile_first
test6:
	@printf "\nTest picking a tile from the factory and placing it in the tile storage row.\n"
	@./run_test $(BIN) $(EXECUTABLE) pick_tile_from_factory
test7:
	@printf "\nTest the players scores update correctly at the end of the round.\n"
	@./run_test $(BIN) $(EXECUTABLE) update_score_round_end
test8:
	@printf "\nTest the game fails to load when the a factory is invalid (missing).\n"
	@./run_test $(BIN) $(EXECUTABLE) factories_incorrect output
test9:
	@printf "\nTest the game fails to load when the players broken tiles row is invalid (missing).\n"
	@./run_test $(BIN) $(EXECUTABLE) player2_broken_tiles_missing output
test10:
	@printf "\nTest the game fails to load when the players mosaic board is invalid (missing).\n"
	@./run_test $(BIN) $(EXECUTABLE) player1_board_missing output

tests: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10