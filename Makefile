# 編譯器
CXX = g++

# 編譯選項
CXXFLAGS = -Wall -Wextra -std=c++17

# 專案目錄和檔案
SRC_DIR = src
SRC_FILES = $(SRC_DIR)/main.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
TARGET = main

# 預設目標
all: $(TARGET)

# 編譯目標
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ_FILES)

# 物件檔的生成規則
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清除生成檔案
clean:
	rm -f $(OBJ_FILES) $(TARGET)

# Phony targets
.PHONY: all clean
