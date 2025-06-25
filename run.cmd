@echo off
cmake -S . -B build
msbuild build/barren-project.sln
build\barren-test\Debug\barren_test.exe