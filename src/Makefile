# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Chua Hou

override CFLAGS += -Wall -O3 -std=gnu99
override LDFLAGS += -lcurl

OBJDIR := obj
BINDIR := bin

SRC := $(wildcard *.c)
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
BIN := $(BINDIR)/wrtele

HEADERS := $(wildcard *.h)

.PHONY: build dirs clean

build: | dirs $(BIN)

$(BIN): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

dirs:
	mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm $(OBJDIR) $(BINDIR) -rf
