/**
 * @file    main.cpp 
 * @author  Ghassan Younes
 * @date    January 27th 2020
 * @par     email: ghassan\@ghassanyounes.com
 * 
 * @brief
 *  This program will autogenerate a makefile for your code, with custom CLI 
 *  arguments and a choice of memory checkers.
 * 
 */

#include <iostream>       /// cout, endl, string
#include <fstream>        /// ofstream, ifstream, .open, .is_open(), .close()
#include <cstdlib>        /// system
#include "functions.h"    /** Namespace    | Functions
                           *  ------------ | -----------------------------------
                           *  basemake     |  macros, targets, baserules, dotorules, generatedeps 
                           *  compilation  |  compiler, compilargs, inject, COMPIL 
                           *  doxygen      |  doxypresent, gendoxy, editdoxy,  inject
                           *  memorydebug  |  debug, memdargs, inject, MMCHK 
                           *  global       |  info, STATUS
                           */

/**
 * 
 * \param argc
 *  Number of command-line swithces activated
 * 
 * \param argv
 *  Array of the commands input
 * 
 * \return
 *  0 -- Success; 1 -- Fail
 * 
 */
int main(int argc, const char* argv[])
{
  using std::cout;
  using std::endl;

  std::string quieton = "on";       // String "on" for argument check
  std::string quietoff = "off";     // String "off" for argument check
  std::string help = "help";        // String "help" for argument check
  std::string yes = "yes";          // String "yes" for argument check
  std::string makedirs;             // String for command to make directories

  info pinfo;                       // Project Info struct type info
  
  pinfo.makefile = "makefile";

  if (argc == 2)
  {
    if (help.compare(argv[1]) == 0)
    {
      std::cout << "# ghake\n"
                << "`ghake` is a C++ Program that writes makefiles for you, " 
                << "based on programming standards of my C++ programming class."
                << endl << endl 
                << "ghake help menu:"
                << endl
                << "==========================================================="
                << endl
                << "##Usage"
                << endl
                << "-------"
                << "Runtime Arguments for `ghake` are in the following order:"
                << endl
                << "ghake COMPILER MEMDBUG \"PRJNAME\" FILEX MAKEX DIFF_FILE " 
                << "QUIET" << endl
                << endl
                << "### Compiler options" << endl
                << "- `cc`      [UNIX C compiler] (partially tested)" << endl
                << "- `cl`      [Microsoft C compiler] (not tested)" << endl
                << "- `clang`   [LLVM C compiler]" << endl
                << "- `clang++` [LLVM C++ compiler]" << endl
                << "- `gcc`     [GNU C Compiler]" << endl
                << "- `g++`     [GNU C++ Compiler]" << endl
                << endl
                << "### Memory Debugger " << endl
                << "- `drmemory` [Dr. Memory] (not tested)" << endl
                << "- `valgrind` [Valgrind]" << endl
                << endl
                << "### Project name" << endl
                << "- Input project title in \"Double Quotation Marks\"" << endl
                << endl
                << "### Source code file extensions:"
                << "- I've only tested `c` and `cpp` (*no `.` in runtime "
                << "argument*), and the Compiler flags are set for C and C++ "
                << "programs."  << endl
                << "**Filenames cannot currently have `\'.\'` anywhere other "
                << "than right before the file extension." 
                << "I'm working on fixing it.**"
                << endl
                << "### Makefile file Extensions"
                << "- `yes` (`makefile` will be appended with `.gnu`, `.wcl`, " 
                << "`.clg`, or `.unx`  -- make must be run as" 
                << "\"`make -f makefile.###`\")"
                << "- `no`  (file name of `makefile` will remain unchanged)" 
                << endl << endl
                << "### Diff File"
                << "- `nodiff` will not inject a diff command" << endl
                << "- Any other string (should include the `.txt` extension)" 
                << "will run a check for a file matching that name. It will "
                << "also pipe the output of your program into a text file "
                << "called `myout.txt` when running make, so that it has "
                << "something to diff." << endl
                << endl
                << "### Quiet mode?"
                << "- `on`  (Will not repeat the input values to affirm them)"
                << endl
                << "- `off` (Will repeat the input values to affirm them)" 
                << endl << endl;
     return 0;
    }
    else 
    {
      return 1;
    }
  }
  else if (argc != 8)
  {
    cout  << "Please enter the compiler, memory debugger, \"Project Name\", " 
          << "Source code file extensions, "
          << "whether to enable makefile extensions, diff file (with .txt) " 
          << "and quiet on/off " << endl
          << " Run \'ghake help\' for valid entries." << endl
          << "Exiting..." << endl;
    return 1;
  }

  cout  << "Ghake by Ghassan Younes (www.ghassanyounes.com)" << endl 
        << "Attention: This program will create a makefile calling ALL "
        << "." << argv[4] << " files in the current directory. " << endl 
        << endl;

  if (quieton.compare(argv[7]) != 0 && quietoff.compare(argv[7]) != 0)
  {
    cout << "Invalid identifier for quiet mode. Must be \'on\' or \'off\'"
         << endl;
    return 1;
  }
  
  if (quieton.compare(argv[7]) != 0)
  {
    cout << "You selected: "       << endl
         << "Compiler:           " << argv[1] << endl
         << "Memory Debugger:    " << argv[2] << endl
         << "Project name:       " << argv[3] << endl
         << "File extension:     " << argv[4] << endl
         << "Makefile extension? " << argv[5] << endl
         << "Diff File:          " << argv[6] << endl
         << "Quiet mode?         " << argv[7] << endl;
  }

  pinfo.compinfo.compilername = argv[1];
  pinfo.mdinfo.debugname      = argv[2];
  pinfo.project_name          = argv[3];
  pinfo.filex                 = argv[4];
  pinfo.diff_file             = argv[6];

#if defined (unix) || defined (__unix) || defined(__unix__) || defined (__APPLE__) || defined (__MACH__)
  makedirs  = "if [ -d build ]; then echo \" \"; \n"; 
  makedirs += "else mkdir build; ";
  makedirs += "mkdir build/gnu; mkdir build/win; "; 
  makedirs += "mkdir build/unx; mkdir build/clg; ";
  makedirs += "fi";

#elif defined (_WIN32) || defined (_WIN64)
  makedirs = "IF exist build (echo " ") ELSE (mkdir build && mkdir build\\gnu ";
  makedirs += "&& mkdir build\\clg && mkdir build\\unx &&mkdir build\\win)"
#endif
  system(makedirs.c_str());

  if (doxygen::doxypresent())
  {
    cout  << "Warning: Doxygen file present. I will not generate a new one!" 
          << endl;
  } 
  else 
  {
    STATUS doxystat = doxygen::gendoxy();    // Status of generation of Doxyfile
    if (doxystat == FAILED || doxystat == FILE_ERR)
    {
      return 1;
    }
    doxygen::editdoxy(pinfo);
  }

  pinfo.compinfo.comptype = compilation::compiler(pinfo);
  if (yes.compare(argv[5])==0)
  {
    switch (pinfo.compinfo.comptype)
    {
    case  compilation::GCC:
      pinfo.makefile += ".gnu";
      break;
    
    case  compilation::GPP:
      pinfo.makefile += ".gnu";
      break;
    
    case compilation::MICROSOFT:
      pinfo.makefile += ".wcl";
      break;

    case compilation::CLANG:
      pinfo.makefile += ".clg";
      break;

    case compilation::CLANGPP:
      pinfo.makefile += ".clg";
      break;

    case compilation::UNIX:
      pinfo.makefile += ".unx";
      break;

    case compilation::ERR:
      pinfo.makefile += ".ERROR";
      break;

    default:
      break;
    }
  }

  pinfo.compinfo.compilargs = compilation::compilargs(pinfo);
  pinfo.mdinfo.debugtype    = memorydebug::memdebug(pinfo);
  pinfo.mdinfo.debugargs    = memorydebug::memdargs(pinfo);
  
  // INJECTION INTO MAKEFILE BEGINS HERE  

  STATUS macrostat = basemake::macros(pinfo);       // Status of macro injection
  if (macrostat == FILE_ERR || macrostat == FAILED)
  {
    cout  << "Macro injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1; 
  }

  STATUS compstatus = compilation::inject(pinfo);   // Status of compiler inject
  if (compstatus == FILE_ERR || compstatus == FAILED)
  {
    cout  << "Compiler injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1;
  }

  STATUS targetstat = basemake::targets(pinfo);     // Status of target inject
  if (targetstat == FILE_ERR || targetstat == FAILED)
  {
    cout  << "Macro injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1; 
  }

  STATUS dotostat = basemake::dotorules(pinfo);     // Status object file target
  if (dotostat == FILE_ERR || dotostat == FAILED)
  {
    cout  << "File target injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1; 
  }

  STATUS doxystatus = doxygen::inject(pinfo);       // Status of doxygen targets
  if (doxystatus == FILE_ERR || doxystatus == FAILED)
  {
    cout  << "Doxygen command injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1;
  }

  STATUS memstat = memorydebug::inject(pinfo);      // Status of memdbg inject
  if (memstat == FILE_ERR || memstat == FAILED)
  {
    cout  << "Memory Debug command injection into makefile failed. Please make "
          << "sure that the makefile exists and is writeable." << endl ;
    return 1;
  }

  STATUS basetrg = basemake::baserules(pinfo);      // base rules/targets inject
  if (basetrg == FILE_ERR || basetrg == FAILED)
  {
    cout  << "Base target injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1;
  }

  cout  << "\nTasks completed. Please remember to add \'RUNARGS=\"...\"\' when " 
        << "calling 'make' (or in the makefile) for any runtime arguments of "
        << "the program. \nYou may also want to configure an \'ignore list\' " 
        << "for your memory debugger to ignore false positives." << endl 
        << endl
        << "Thank you for using Ghake!\n\n";

  return 0;
}
