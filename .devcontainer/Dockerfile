# 使用官方的 C++ 開發基礎映像
FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-22.04

# 更新 apt 並安裝必要工具
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    clang-format \
    && rm -rf /var/lib/apt/lists/*
