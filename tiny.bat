@echo off
clang-tidy -checks=cppcoreguidelines-* %1 -- -I./include -std=c++17