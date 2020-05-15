# Build details

CXX = clang++
CXXFLAGS = -W -Wall -g
BD = ./build

# Compile to objects

$(BD)/%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Build Executable

bin = Calc

ifneq ($(shell uname), Linux)
	bin = Calc.exe
endif

.PHONY: all
all: $(bin)

.PHONY: prepare
prepare:
	$(if $(wildcard $(BD)),,mkdir -p $(BD))

.PHONY: rebuild
rebuild: clean all

# Executable 1

obj = Calc.o Common.o Algorithm.o
obj_bd = $(obj:%=$(BD)/%)

$(bin): prepare $(obj_bd)
	$(CXX) -o $(bin) $(obj_bd) $(CXXFLAGS)

# Dependencies

$(BD)/Common.o: Common.h
$(BD)/Algorithm.o: Algorithm.h Common.h
$(BD)/Calc.o: Calc.h Cache.h Symbol.h Common.h Algorithm.h

# Clean up

.PHONY: clean
clean:
	rm -f "$(bin)" $(obj_bd)
	rm -fd "$(BD)"
