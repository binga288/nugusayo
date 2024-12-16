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

# deb打包目標
deb: all
	rm -rf debian
	mkdir -p debian/DEBIAN
	mkdir -p debian/usr/local/bin
	mkdir -p debian/usr/local/share/nuguseyo

	# 將已編譯完成的 main 複製為 nuguseyo
	cp $(TARGET) debian/usr/local/bin/nuguseyo
	cp images.png debian/usr/local/share/nuguseyo/

	# 建立控制檔
	echo "Package: nuguseyo" > debian/DEBIAN/control
	echo "Version: 1.0" >> debian/DEBIAN/control
	echo "Section: utils" >> debian/DEBIAN/control
	echo "Priority: optional" >> debian/DEBIAN/control
	echo "Architecture: amd64" >> debian/DEBIAN/control
	echo "Maintainer: Your Name <you@example.com>" >> debian/DEBIAN/control
	echo "Description: Nuguseyo app" >> debian/DEBIAN/control
	echo " This is the nuguseyo application that uses images.png." >> debian/DEBIAN/control

	dpkg-deb --build debian nuguseyo-package.deb

.PHONY: all clean deb
