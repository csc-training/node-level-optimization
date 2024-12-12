# SPDX-FileCopyrightText: 2013 Christian Terboven <christian@terboven.com>
#
# SPDX-License-Identifier: GPL-2.0-or-later

BIN_DIR=./
PROGRAM=$(BIN_DIR)/sudoku-tsk

CC=g++
CFLAGS=-c -O3 -fopenmp -DUSE_SEQUENTIAL_CUTOFF
LDFLAGS=-fopenmp

OBJS=SudokuBoard.o sudoku.o

all: $(PROGRAM) 

$(PROGRAM): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $^ 

$(BIN_DIR): 
	mkdir $@

clean:
	rm -rf $(PROGRAM) *.o

wipe: clean
	rm -rf *.out *.err
