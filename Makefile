# Makefile

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

# 編譯器選項
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -MMD -MP

# 目錄設置
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# 源文件：包含 src/ 目錄下的所有 .cpp 文件
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# 物件文件：將 src/*.cpp 轉換為 obj/*.o
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# 依賴文件
DEPS = $(OBJS:.o=.d)

# 目標執行檔
TARGET = $(BIN_DIR)/nuguseyo

.PHONY: all clean deb

# 預設目標
all: $(TARGET)

# 建立目標執行檔
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# 通用的編譯規則：將 src/*.cpp 編譯為 obj/*.o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 自動包含依賴文件
-include $(DEPS)

# 建立物件文件目錄
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 建立執行檔目錄
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# 清理編譯生成的文件
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	rm -f nuguseyo-package.deb
	rm -rf debian

# 建立 Debian 套件
deb: all
	rm -rf debian
	mkdir -p debian/DEBIAN
	mkdir -p debian/usr/local/bin
	mkdir -p debian/usr/local/share/nuguseyo
	mkdir -p debian/usr/share/man/man1

	# 複製主程式
	cp $(TARGET) debian/usr/local/bin/nuguseyo
	
	# 複製圖片檔案
	cp images/image*.png debian/usr/local/share/nuguseyo/
	
	# 複製並壓縮 man 頁面
	cp man1/nuguseyo.1 debian/usr/share/man/man1/
	gzip -f debian/usr/share/man/man1/nuguseyo.1

	# 建立控制檔
	echo "Package: nuguseyo" > debian/DEBIAN/control
	echo "Version: 1.0" >> debian/DEBIAN/control
	echo "Section: utils" >> debian/DEBIAN/control
	echo "Priority: optional" >> debian/DEBIAN/control
	echo "Architecture: $(ARCH_DEB)" >> debian/DEBIAN/control
	echo "Depends: jp2a" >> debian/DEBIAN/control
	echo "Maintainer: Ann Liao, Ga Bin, YaoEn Liu" >> debian/DEBIAN/control
	echo "Description: Nuguseyo app with jp2a dependency" >> debian/DEBIAN/control
	echo " This package includes nuguseyo, depends on jp2a, and includes images/image1.png to images/image15.png as selectable images." >> debian/DEBIAN/control

	dpkg-deb --build debian nuguseyo-package.deb
