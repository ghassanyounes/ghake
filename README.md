# ghake v3.0.0 By Ghassan Younes 
([www.ghassanyounes.com/ghake/])

`ghake` is a C++ Program that writes makefiles for you, based on programming standards of my C++ programming class.

Run `ghake --help` for assistance concerning the command-line switches.

> Versions 3.x.x+ now use dynamic runtime arguments, as detailed below, with defaults listed: 
-------
## Usage 
-------
### Compiler options 
- `--cc`      [UNIX C compiler] (partially tested)
- `--cl`      [Microsoft C compiler] (not tested)
- `--clang`   [LLVM C compiler]
- `--clang++` [LLVM C++ compiler]
- `--gcc`     [GNU C Compiler]
- `--g++`     [GNU C++ Compiler] (default)

### ANSI/ISO standard 
- `--ansi` adds the equivalent flag for each compiler to enforce the ANSI/ISO standard (`C89`; `C++98`)

### Memory Debugger 
- `--drmemory` [Dr. Memory] (not tested)
- `--valgrind` [Valgrind] (default)

### False Leak Suppression for Memory Debugger (`--mdsupp 'path/to/file'`)
- Tells the memory debugger to ignore specific memory leaks that are not the result of your program. Must be configured prior to compiling.

### Project name (`--name "PRJNAME"`) 
- Input project title in "Double Quotation Marks"

### Runtime Arguments (`--run_args "ARGS"`) 
- Input runtime arguments for generated program in "Double Quotation Marks"

### Source code file extensions (`--ext EXT`): 
- I've only tested `--ext c` and `--ext cpp` (*no `.` in runtime argument*), and the Compiler flags are set for C and C++ programs. Default is `cpp`. 

### Makefile file Extensions (`--makext`)
- `--makext` (`makefile` will be appended with `.gnu`, `.wcl`, `.clg`, or `.unx`  -- make must be run as \`make -f makefile.###`\)
- nothing  (file name of `makefile` will remain unchanged) (default)

### Diff File (`--diff "DIFF_FILE"`) 
- `nodiff` will not inject a diff command (default)
- Any other string (should include the file extension (normally `.txt`)) will run a check for a file matching that name. It will also pipe the output of your program into a text file called `myout.txt` when running make, so that it has something to diff.

### Quiet mode 
- `--quiet`   (Will not repeat the input values to affirm them) (default)
- `--verbose` (Will repeat the input values to affirm them)
---

## To compile from source: 
[Download the latest release from the RELEASES page], and simply run `make` from within the directory; this should generate all the necessary files -- Default compiler is g++ with ANSI C++ and all error flags set.

---

# FAQ:

Does this work on all operating systems?
> This *should* work on Windows, macOS, and Linux - you just need to have the right compiler(s) and a UNIX/POSIX-compatible shell installed. I use Bash, but I don't think Zsh or Fish should have any issues. I also haven't tested this on Windows, so feel free to flag a new issue if something doesn't work.

What's the difference between the versions?
> Versions 1.x.x have been deprecated as I am only able to check through source files up to the first `.` in the name of the source file, even if it is not the period preceding the file extension. This means that names like `cabbage.pasta.cpp` are incompatible with `ghake v1.x.x`. Versions 2.x.x onwards use the most current version of C++ (as of February 1st 2020 that is c++17, though C++20 is coming soon). 2.x.x+ support having `.` anywhere in the name of a file. 
1.x.x is also only portable and must be compiled from source. You must add it to your PATH or add aliases to it to use it from the command line. 2.x.x+ have an 'installer' make target which will add it to your PATH and store it in the typical places upon compilation.

Why aren't there any precompiled binaries yet? 
> Well, I only run Linux, and I haven't tried compiling for other platforms before. If I decide to try it out and make precompiled binaries for `ghake`, this question won't be here anymore.

tHiS hAs `sYsTEm()` cALls!!!11!1!!!
> Yeah. And? I need to check the current version of Doxygen, create files and directories, yada yada yada. I've thrown in the flags to run the right commands for the right operating system. Don't like it? Change it yourself.

Where does the name `ghake` come from? 
> Well, it's my name + `make`. Yes, very original, I know.

Couldn't you have made this with `make` or a scripting language like Perl or Python?
> Well, yes. This is more of a proof of concept than anything else. Plus I needed some sort of project to put on [my crappy website] heheh.

You could have literally even done this in bash. There's absolutely no reason for you to do this.
> First of all don't call me out like this, second of all, I know.

Cmake. Cmake exists.
> I KNOW! I'M AWARE! (check out cmake [here])

## Old update notes:

> With v2.x.x+, upon downloading the source code, on Linux platforms you can run `sudo make install` to install `ghake` to  `/usr/bin`. It will also update your `PATH` to include `/usr/bin/ghake` as the directory where `ghake` is installed. Windows support might be coming soon, depends if I feel like it. Feel free to install to your 'Program Files' directory and update your `PATH` yourself ([here's a guide]). 
Ghake 3.0.1 will not update your PATH as running `sudo make install` will simply copy the executable to `/usr/bin`

[here's a guide]: https://www.howtogeek.com/118594/how-to-edit-your-system-path-for-easy-command-line-access/

[Download the latest release from the RELEASES page]: https://github.com/ghassanyounes/ghake/releases

[www.ghassanyounes.com/ghake/]: http://www.ghassanyounes.com/ghake

[my crappy website]: http://www.ghassanyounes.com

[here]: https://cmake.org/
