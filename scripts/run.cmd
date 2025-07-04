@echo off
cmake -S . -B build
msbuild build/sailboat-project.sln
build\sailboat-test\Debug\sailboat-test.exe