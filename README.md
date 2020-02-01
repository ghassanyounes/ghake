# ghake
`ghake` is a C++ Program that writes makefiles for you. Based on the programming standards of my C++ programming class.

Run `ghake help` for assistance concerning the command-line switches.

---

## Usage 
Runtime Arguments for `ghake` are in the following order:

`ghake COMPILER MEMDBUG "PRJNAME" FILEX MAKEX DIFF_FILE QUIET`

### Compiler options
- `cc`      [UNIX C compiler] (partially tested)
- `cl`      [Microsoft C compiler] (not tested)
- `clang`   [LLVM C compiler]
- `clang++` [LLVM C++ compiler]
- `gcc`     [GNU C Compiler]
- `g++`     [GNU C++ Compiler]

### Memory Debugger 
- `drmemory` [Dr. Memory] (not tested)
- `valgrind` [Valgrind]

### Project name
- Input project title in "Double Quotation Marks"

### Source code file extensions:
- I've only tested `c` and `cpp` (*no `.` in runtime argument*), and the Compiler flags are set for C and C++ programs. **Filenames cannot currently have `'.'` anywhere other than right before the file extension. I'm working on fixing it.**

### Makefile file Extensions
- `yes` (`makefile` will be appended with `.gnu`, `.wcl`, `.clg`, or `.unx`  -- make must be run as "`make -f makefile.###`")
- `no`  (file name of `makefile` will remain unchanged)

### Diff File
- `nodiff` will not inject a diff command
- Any other string (should include the `.txt` extension) will run a check for a file matching that name. It will also pipe the output of your program into a text file called `myout.txt` when running make, so that it has something to diff.

### Quiet mode?
- `on`  (Will not repeat the input values to affirm them)
- `off` (Will repeat the input values to affirm them)

---

## To compile from source: 
[Download the latest release from the RELEASES page], and simply run `make` from within the directory; this should generate all the necessary files -- Default compiler is g++ with ANSI C++ and all error flags set.

---

# FAQ:

Does this work on all operating systems?
> This *should* work on Windows, macOS, and Linux - you just need to have the right compiler(s) installed. I also haven't tested this on Windows, so feel free to flag a new issue if something doesn't work.

tHiS hAs sYsTEm() cALls!!!11!1!!!
> Yeah. And? I need to check the current version of Doxygen, create files and directories, yada yada yada. I've thrown in the flags to run the right commands for the right operating system. Don't like it? Do it yourself.

Where does the name `ghake` come from? 
> Well, it's my name + `make`. Yes, very original, I know.

Couldn't you have made this with `make` or a scripting language like Perl or Python?
> Well, yes. This is more of a proof of concept than anything else. Plus I needed some sort of project to put on [my crappy website] heheh.

You could have literally even done this in bash. There's absolutely no reason for you to do this.
> First of all don't call me out like this, second of all, I know.

Cmake. Cmake exists.
> I KNOW! I'M AWARE! (check out cmake [here])

[Download the latest release from the RELEASES page]: https://github.com/ghassanyounes/ghake/releases

[my crappy website]: http://www.ghassanyounes.com

[here]: https://cmake.org/
