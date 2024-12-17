# 預設從 uname -m 取得架構（可被外部指定 ARCH 覆蓋）
ARCH ?= $(shell uname -m)

ifeq ($(ARCH), x86_64)
    ARCH_DEB = amd64
    CXX = g++
else ifeq ($(ARCH), aarch64)
    ARCH_DEB = arm64
    CXX = g++
else ifeq ($(ARCH), arm64)
    ARCH_DEB = arm64
    CXX = aarch64-linux-gnu-g++
else
    $(error Unsupported architecture: $(ARCH))
endif

CXXFLAGS = -Wall -Wextra -std=c++17

SRC_DIR = src
SRC_FILES = $(SRC_DIR)/main.cpp
OBJ_FILES = $(SRC_FILES:.cpp=.o)
TARGET = main

# 尋找 jp2a 的可執行檔路徑
JP2A_PATH := $(shell which jp2a)

.PHONY: all clean deb

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ_FILES)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(TARGET) nuguseyo-package.deb
	rm -rf debian

deb: all
	rm -rf debian
	mkdir -p debian/DEBIAN
	mkdir -p debian/usr/local/bin
	mkdir -p debian/usr/local/share/nuguseyo

	# 複製主程式
	cp $(TARGET) debian/usr/local/bin/nuguseyo
	
	# 複製 jp2a 執行檔 (確保系統上有 jp2a)
	cp $(JP2A_PATH) debian/usr/local/bin/

	# 複製圖片檔案
	cp images.png debian/usr/local/share/nuguseyo/

	# 建立控制檔 (不需要 Depends，因為我們直接內含 jp2a)
	echo "Package: nuguseyo" > debian/DEBIAN/control
	echo "Version: 1.0" >> debian/DEBIAN/control
	echo "Section: utils" >> debian/DEBIAN/control
	echo "Priority: optional" >> debian/DEBIAN/control
	echo "Architecture: $(ARCH_DEB)" >> debian/DEBIAN/control
	echo "Maintainer: Your Name <you@example.com>" >> debian/DEBIAN/control
	echo "Description: Nuguseyo app with jp2a embedded" >> debian/DEBIAN/control
	echo " This package includes nuguseyo and jp2a, as well as images.png." >> debian/DEBIAN/control

	dpkg-deb --build debian nuguseyo-package.deb
