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

config.h:
	@echo "Make a copy of config.tmpl.h called config.h and do configuration there."
	@false

$(BIN): $(OBJ)
	$(CC) $^ -lcurl -o $@

$(OBJDIR)/%.o: %.c $(HEADERS) config.h
	$(CC) -Wall -O3 -std=gnu99 -c $< -o $@

dirs:
	mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm $(OBJDIR) $(BINDIR) -rf
