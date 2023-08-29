# BUILD DETAILS

CXX      = g++
CXXFLAGS = -W -Wall -g
LFLAGS   = -lm
BUILD    = build

# BUILD EXECUTABLE

TARGET   = Calc

all: $(TARGET)

# CLEAN UP

clean:
	rm -rf "$(TARGET)" "$(BUILD)"

# EXECUTABLE

OBJ      = main.o Algorithm.o Calc.o Common.o Operator.o
OBJBD    = $(OBJ:%=$(BUILD)/%)

$(TARGET): $(OBJBD)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

# COMPILE TO OBJECTS

$(BUILD)/%.o: %.cpp
	@mkdir -p "$(BUILD)"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# PHONY

.PHONY: all clean

# DEPENDENCIES

SRC = $(wildcard *.h *.hpp *.c *.cpp *.cc)

$(BUILD)/depend.mk: $(SRC)
	@mkdir -p "$(BUILD)"
	@rm -f "$@"
	@$(CXX) -MM *.cpp | sed 's/^\(.*\).o:/$$(BUILD)\/\1.o:/' >> $@

include $(BUILD)/depend.mk

