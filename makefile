CC=g++
LD=ld

CFLAGS=-O2 -std=c++20

SOURCES=$(shell find src/ -name "*.cpp")
OUTPUTS=$(SOURCES:src/%.cpp=lib/%.o)
EXECUTABLE=attendance

default: $(EXECUTABLE)

$(EXECUTABLE): lib/ $(OUTPUTS)
	$(CC) $(OUTPUTS) -o $(EXECUTABLE)

%/:
	mkdir -pv $@

lib/%.o:src/%.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf ./lib/**
	rm -f $(EXECUTABLE)
