# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Chua Hou

OBJDIR := obj
BINDIR := bin

SRC := $(wildcard *.c)
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
BIN := $(BINDIR)/wrtele

HEADERS := $(wildcard *.h)

.PHONY: build dirs clean

build: | dirs $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ -o $@

$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) -Wall -O3 -c $< -o $@

dirs:
	mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm $(OBJDIR) $(BINDIR) -rf
