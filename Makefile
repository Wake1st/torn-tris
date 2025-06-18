SRC_DIR				:= src
BIN_DIR				:= bin
INC_DIR				:= inc
OBJ_DIR				:= obj

SOURCES				:= $(shell find $(SRC_DIR) -name "*.cpp")
HEADERS				:= $(shell find $(INC_DIR) -name "*.h")
HEADERDIRS		:= $(sort $(dir $(HEADERS)))
OBJECTS				:= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

CXX						:= g++
CXXFLAGS			:= -std=c++17 -g -Wall
INCLUDEFLAGS	:= $(addprefix -I,$(HEADERDIRS))

TARGET				:= $(BIN_DIR)/program

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ -lraylib

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
