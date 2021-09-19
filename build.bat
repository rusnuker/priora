@echo off

md temp >nul 2>&1
md release >nul 2>&1

windres build\resources.rc temp\resources.o
gcc -o release\priora.exe build\main.c temp\resources.o -mwindows -static -lntdll -lwinmm
pause
