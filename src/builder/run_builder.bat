REM @echo off

:START

del *.exe *.obj *.map *.prj *.tds
pcc builder.c -o builder.exe
builder.exe
PAUSE

del *.exe *.obj *.map *.prj *.tds
..\tcc\tcc builder.c
builder.exe
PAUSE

del *.exe *.obj *.map *.prj *.tds
dmc builder.c
builder.exe
PAUSE

del *.exe *.obj *.map *.prj *.tds
bcc32 builder.c
builder.exe
PAUSE

del *.exe *.obj *.map *.prj *.tds
gcc -Wall -Werror -pedantic builder.c -o builder.exe
builder.exe
PAUSE

GOTO START