# ghake
A C++ Program that writes makefiles for you. Based on the programming standards of my C++ programming class.

Run "ghake help" for assistance concerning the command-line switches.

Usage (CLI switches in order: ): 
Compiler options:
- `cc`      [UNIX C compiler]
- `cl`      [Microsoft C compiler] (not tested)
- `clang`   [LLVM C compiler]
- `clang++` [LLVM C++ compiler]
- `gcc`     [GNU C Compiler]
- `g++`     [GNU C++ Compiler]

Memory Debugger: 
- `drmemory` [Dr. Memory] (not tested)
- `valgrind` [Valgrind]

Project name:
- Input project title in "Double Quotation Marks"

Source code file extensions:
- I've only tested .c and .cpp, and the Compiler flags are set for C and C++ programs. !!Filenames cannot currently have '.' anywhere other than right before the file extension. I'm working on fixing it.

Makefile file Extensions:
- `yes` ('makefile' -> .gnu, .wcl, . clg, .unx  -- must be run through "`make -f makefile.###`")
- `no`  ('makefile')

Diff File:
- `nodiff` will not inject a diff command
- Any other string (including `.txt`) will check for a file matching that name.

Quiet mode?
- `on`  (Will not repeat the input values to affirm them)
- `off` (Will repeat the input values to affirm them)

To compile from source, clone this git repo and simply run `make rebuild` from within the directory; this should generate all the necessary files -- Default compiler is g++ with ANSI C++ and all error flags set.
