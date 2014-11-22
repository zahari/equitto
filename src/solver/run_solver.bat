REM @ECHO OFF
:START

del *.exe *.obj *.map *.prj *.tds
..\tcc\tcc solver.c
..\tcc\tcc solver_gen.c
solver_gen.exe
move input_auto.txt input.txt
solver.exe
PAUSE

del *.exe *.obj *.map *.prj *.tds
pcc solver.c -o solver.exe
pcc solver_gen.c -o solver_gen.exe
solver_gen.exe
move input_auto.txt input.txt
solver.exe
PAUSE

del *.exe *.obj *.map *.prj *.tds *.prj *.tds
dmc solver.c
dmc solver_gen.c
solver_gen.exe
move input_auto.txt input.txt
solver.exe
PAUSE

REM C++ Builder

del *.exe *.obj *.map *.prj *.tds
bcc32 solver.c
bcc32 solver_gen.c
solver_gen.exe
move input_auto.txt input.txt
solver.exe
PAUSE

REM TDM-GCC

del *.exe *.obj *.map *.prj *.tds
gcc -Wall -Werror -pedantic solver.c -o solver.exe
gcc -Wall -Werror -pedantic solver_gen.c -o solver_gen.exe
solver_gen.exe
move input_auto.txt input.txt
solver.exe
PAUSE

GOTO START