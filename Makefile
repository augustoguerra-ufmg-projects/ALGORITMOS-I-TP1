CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -std=c++11

SRC = src
OBJ = obj
INCLUDE = include

OUT = tp1

SOURCES = $(wildcard $(SRC)/*.cc)
OBJECTS = $(SOURCES:$(SRC)/%.cc=$(OBJ)/%.o)

all: $(OUT)

$(OUT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -I$(INCLUDE)

$(OBJ)/%.o: $(SRC)/%.cc
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OUT) $(OBJECTS)

.PHONY: all clean