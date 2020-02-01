# MACROS =======================================================================

CC=g++

ERASE=rm -rf

CFLAGS=-g -O0 -ansi -pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicated-cond -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o
# CLANG -g -O0 -v -std=c++98 -pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicate-enum -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o

OUTDIR=build/gnu/

DRIVER=main

OBJECTS=$(OUTDIR)$(DRIVER).o $(OUTDIR)compile.o $(OUTDIR)diffing.o \
$(OUTDIR)doxy.o $(OUTDIR)memchk.o $(OUTDIR)makers.o

EXE=ghake

RUNARGS=g++ valgrind "Making My Makefile" cpp yes nodiff off

MMCHK=valgrind

MMCHKARGS=-q --quiet --leak-check=full --show-reachable=yes --tool=memcheck --trace-children=yes --suppressions=false.supp 

DIFFDIR=diff/

DIFFILE=test0.txt

# TARGETS ======================================================================

run : $(OUTDIR)$(EXE) $(OBJECTS)
#$(MAKE) doxygen
#$(MAKE) memchk
	./$(OUTDIR)$(EXE) $(RUNARGS)
	$(MAKE) doxygen
	echo "Made executable successfully. You can find the built executable at $(OUTDIR)$(EXE)"

$(OUTDIR)$(EXE) : $(OBJECTS) makefile
	$(CC) $(OBJECTS) $(CFLAGS) $(OUTDIR)$(EXE)

$(OUTDIR)$(DRIVER).o : $(DRIVER).cpp functions.h
	$(CC) $(DRIVER).cpp -c $(CFLAGS) $(OUTDIR)$(DRIVER).o 

$(OUTDIR)compile.o : compile.cpp functions.h
	$(CC) compile.cpp -c $(CFLAGS) $(OUTDIR)compile.o 

$(OUTDIR)diffing.o : diffing.cpp functions.h
	$(CC) diffing.cpp -c $(CFLAGS) $(OUTDIR)diffing.o 

$(OUTDIR)doxy.o : doxy.cpp functions.h
	$(CC) doxy.cpp -c $(CFLAGS) $(OUTDIR)doxy.o 

$(OUTDIR)memchk.o : memchk.cpp functions.h
	$(CC) memchk.cpp -c $(CFLAGS) $(OUTDIR)memchk.o 

$(OUTDIR)makers.o : makers.cpp functions.h
	$(CC) makers.cpp -c $(CFLAGS) $(OUTDIR)makers.o 

clean : 
	@$(ERASE) $(OUTDIR)*

rebuild :
	$(MAKE) clean
	$(MAKE)

doxygen :
	-@$(ERASE) html/
	-@$(ERASE) latex/
	( cat Doxyfile ; echo "EXTRACT_ALL=YES" ) | doxygen -
	( cat Doxyfile ; echo "EXTRACT_ALL=NO" ) | doxygen -

doxyclean :
	-@$(ERASE) Doxyfile
	-@$(ERASE) html/
	-@$(ERASE) latex/

memchk : $(OUTDIR)$(EXE) $(OBJECTS)
	@$(MMCHK) $(MMCHKARGS) $(OUTDIR)$(EXE) $(RUNARGS)
