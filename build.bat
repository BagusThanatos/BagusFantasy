@echo off

IF NOT EXIST build\windows mkdir build\windows
pushd build\windows
cl -Zi ..\..\src\win32_bagusfantasy.cpp user32.lib gdi32.lib /link /incremental:no
popd