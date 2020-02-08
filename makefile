# MACROS =======================================================================

CC=g++

ERASE=rm -rf

CFLAGS=-g -O0 -pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicated-cond -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o

CLANGFLAGS= -g -O0 -v -pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicate-enum -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o

OUTDIR=build/gnu/

DRIVER=main

OBJECTS=$(OUTDIR)$(DRIVER).o $(OUTDIR)compile.o $(OUTDIR)doxy.o \
$(OUTDIR)memchk.o $(OUTDIR)makers.o 

EXE=ghake

P=P

RUNARGS=g++ valgrind "Ghake" cpp yes nodiff off

MMCHK=valgrind

MMCHKARGS=-q --quiet --leak-check=full --show-reachable=yes --tool=memcheck --trace-children=yes 

DIFFDIR=diff/

DIFFILE=test0.txt

# TARGETS ======================================================================
:
	echo " --no-print-directory" | $(MAKE) run 

run : $(OUTDIR)$(EXE) $(OBJECTS)
#$(MAKE) doxygen
#$(MAKE) memchk
	./$(OUTDIR)$(EXE) $(RUNARGS)
#$(MAKE) doxygen
	clear; echo "Made executable successfully. \
	You can find the built executable at $(OUTDIR)$(EXE)"

install : $(OUTDIR)$(EXE) $(OBJECTS)
	-mkdir /usr/bin/ghake
	cp $(OUTDIR)$(EXE) /usr/bin/ghake/ghake
	echo 'PATH+=$PATH:/usr/bin/ghake' >> ~/.bash_profile
	echo 'PATH+=$PATH:/usr/bin/ghake' >> /root/.bash_profile
	echo 'PATH+=$PATH:/usr/bin/ghake' >> ~/.bashrc;
	echo 'PATH+=$PATH:/usr/bin/ghake' >> /root/.bashrc;
	PATH+=$PATH:/usr/bin/ghake; export PATH

$(OUTDIR)$(EXE) : $(OBJECTS) makefile
	$(CC) $(OBJECTS) $(CFLAGS) $(OUTDIR)$(EXE)

$(OUTDIR)$(DRIVER).o : $(DRIVER).cpp functions.h
	$(CC) $(DRIVER).cpp -c $(CFLAGS) $(OUTDIR)$(DRIVER).o 

$(OUTDIR)compile.o : compile.cpp functions.h
	$(CC) compile.cpp -c $(CFLAGS) $(OUTDIR)compile.o 

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
	echo " --no-print-directory" | $(MAKE) run 

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
