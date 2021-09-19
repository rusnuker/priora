@echo off

rem ABOBUS TROJAN BULDER ORIGINAL 

rd temp /q /s

md temp 

windres build\resources.rc temp\resources.o
gcc -o release\priora.exe build\main.c temp\resources.o -mwindows -static -lntdll -lwinmm
pause