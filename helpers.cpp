/**
 * @file    helpers.cpp
 * @author  Ghassan Younes
 * @date    March 19th 2020
 * @par     email: ghassan\@ghassanyounes.com
 * 
 * @brief
 *  This file contains function implementations for helper functions
 * 
 */

#include "functions.h"  /// help, gendirs, compilation::COMPIL, compilation::generatedeps, memorydebug::MMCHK, class info [set_diff, set_filex, set_name, get_pname, set_makex, set_runargs, get_filex, get_compname, get_comptypeinject, out]
#include <iostream>     /// cout, endl, string, string::size_type
#include <fstream>      /// ofstream, ifstream, .open, .is_open(), .close()
#include <cstdlib>      /// system
#include <filesystem>   /// rename, exists, create_directory

using std::cout;
using std::endl;

/**
 * 
 * @brief
 *  Constructor for strcut of type compinfo
 * 
 * @param compil
 *  Name of compiler
 * 
 * @param descr
 *  Description of compiler
 * 
 * @param name 
 *  Name of compiler
 * 
 * @param args
 *  Compiler arguments
 * 
 */
compilation::compinfo::compinfo(compilation::COMPIL compil,
                                std::string descr,
                                std::string name,
                                std::string args)
                                :
                                comptype (compil),
                                description (descr),
                                compilername (name),
                                compilargs (args) {}

memorydebug::mdinfo::mdinfo(MMCHK type,
                            std::string name,
                            std::string args,
                            std::string supp,
                            std::string supp_file
                            )
                            :
                            debugtype (type),
                            debugname (name),
                            debugargs (args),
                            false_supp (supp),
                            false_supp_file (supp_file)
                            {}

/**
 * 
 * @brief
 *  Constructor for class of type info
 * 
 * @param name
 *  Name of program
 * 
 * @param args
 *  Runtime arguments for program
 * 
 * @param makefile 
 *  Name of makefile to be generated
 * 
 * @param filex
 *  File extension to scan for
 * 
 * @param diff
 *  File to diff against
 * 
 * @param compiler
 *  Struct detailing compiler info
 * 
 * @param debugger 
 *  Struct detailing memory debugger info
 * 
 */
info::info( std::string name, 
            std::string args,
            std::string makefile, 
            std::string filex, 
            std::string diff,
            compilation::COMPIL compiler,
            memorydebug::MMCHK debugger) 
            :
            project_name (name), 
            makefile_name (makefile),
            filext (filex),
            diff_file (diff),
            runargs (args),
            compinfo (compiler, "", "", ""),
            mdinfo (debugger, "", "", "", ""){}

/**
 * 
 * @brief
 *  Sets the diff file
 * 
 * @param diff
 *  Name of diff file
 * 
 */
void info::set_diff(std::string diff)
{
  diff_file = diff;
}

/**
 * 
 * @brief
 *  Returns the name of the diff file
 * 
 * @param diff
 *  Name of diff file
 * 
 */
std::string info::get_diff() const
{
  return diff_file;
}

/**
 * 
 * @brief
 *  Sets the file extension to scan
 * 
 * @param filex
 *  File extension
 * 
 */
void info::set_filex(std::string filex)
{
  filext = filex;
}

/**
 * 
 * @brief
 *  Sets the project name
 * 
 * @param name
 *  Name of project
 * 
 */
void info::set_name(std::string name)
{
  project_name = name;
}

/**
 * 
 * @brief
 *  Returns the name of the project
 * 
 * @return
 *  Project Name
 * 
 */
std::string info::get_pname() const
{
  return project_name;
}

/**
 * 
 * @brief
 *  Sets file extension of makefile
 * 
 */
void info::set_makex()
{
  switch (compinfo.comptype)
  {
    case compilation::CC:
      makefile_name += ".unx";
      break;

    case compilation::CL:
      makefile_name += ".win";
      break;

    case compilation::CLANG:
      makefile_name += ".clg";
      break;

    case compilation::CLANGPP:
      makefile_name += ".clg";
      break;
      
    case compilation::GCC:
      makefile_name += ".gnu";
      break;
      
    case compilation::GPP:
      makefile_name += ".gnu";
      break;

    default:
      makefile_name += ".gnu";
      break;
  }
}

/**
 * 
 * @brief
 *  Sets the runtime arguments for the generated program
 * 
 * @param args
 *  Runtime arguments
 * 
 */
void info::set_runargs(std::string args)
{
  runargs = args; 
}

/**
 * 
 * @brief
 *  Returns the file extension being scanned
 * 
 * @return
 *  File extension
 * 
 */
std::string info::get_filex() const
{
  return filext;
}

/**
 * 
 * @brief
 *  Returns the compiler name
 * 
 * @return
 *  Compiler name
 * 
 */
std::string info::get_compname() const
{
  return compinfo.compilername;
}

/**
 * 
 * @brief
 *  Returns the compiler type
 * 
 * @return
 *  Compiler type
 * 
 */
compilation::COMPIL info::get_comptype() const
{
  return compinfo.comptype;
}

/**
 * 
 * @brief
 *  Injects information into the makefile
 * 
 */
void info::inject()
{
  using idx_t = std::string::size_type;           ///< Simpilified name
  using std::string;

  const char* makefname = makefile_name.c_str();  /// C String makefile name
  std::ifstream dependencylist;                   /// File dependencies list
  std::ofstream makefile;                         /// Makefile to write to
  string linetext;                                /// File's text on each line
  string objects; 

  makefile.open(makefname, std::ios::app);
  makefile << "# Makefile generated by ghake v" << VERSION << endl
           << "# ghake by Ghassan Younes (www.ghassanyounes.com/ghake)" << endl 
           << "#" << endl
           << "# MACROS ======================================================================\n"
           << endl
           << "ERASE=" 
#if defined (unix) || defined (__unix) || defined(__unix__) || defined (__APPLE__) || defined (__MACH__)
           << "rm -rf\n"
#elif defined (_WIN32) || defined (_WIN64)
           << "del \n"
#endif
           << endl;
  for (std::size_t i = 0; i < project_name.length(); i++)
  {
    if (( project_name[i] == ' '  || project_name[i] == '\n' ) 
      ||( project_name[i] == '\t' || project_name[i] == '.'  ))
    {
      project_name[i] = '_';
    }
  }
  makefile << "EXE=" << project_name << endl
           << endl
           << "OUTDIR=build/";
  
  switch (compinfo.comptype)
  {
    case compilation::CC:
      makefile << "unx/" << endl;
      break;

    case compilation::CL:
      makefile << "win/" << endl;
      break;

    case compilation::CLANG:
      makefile << "clg/" << endl;
      break;

    case compilation::CLANGPP:
      makefile << "clg/" << endl;
      break;
      
    case compilation::GCC:
      makefile << "gnu/" << endl;
      break;
      
    case compilation::GPP:
      makefile << "gnu/" << endl;
      break;

    default:
      makefile << "gnu/" << endl;
      break;
  }
  makefile << endl;

  makefile << "MDEBUG=" << mdinfo.debugname << endl
           << endl
           << "MDARGS=" << mdinfo.debugargs << mdinfo.false_supp << endl
           << endl;
  
  if (diff_file.compare("nodiff") != 0)
  {
    makefile << "OUTFILE=myout.txt" << endl 
             << endl 
             << "DIFF_FILE=" << diff_file << endl
             << endl;
  }

  makefile << "CC=" << compinfo.compilername << endl
           << endl
           << "CFLAGS=" << compinfo.compilargs
           << endl;

  compilation::generatedeps(*this);
  dependencylist.open("dependencies.txt");

  objects = "OBJECTS=";
  while (std::getline(dependencylist, linetext))
    {
      if (linetext.empty()) continue;
      
      std::string target(linetext.size(), '\0') ;
      
      idx_t last_dot = std::string::npos;
      
      for (idx_t i = 0; i < linetext.size(); ++i)
      {
        if (linetext[i] == '.')
        {
          // keep track of the last dot seen
          last_dot = i;
        }
        else if (linetext[i] == ':')
        {
          if (last_dot == std::string::npos)
          {
            // no extension detected, cut from the colon
            target.resize(i);
          }
          else
          {
            // cut at the last dot
            target.resize(last_dot);
          }
          
          break;
        }
        
        target[i] = linetext[i];
      }
      
      objects += "$(OUTDIR)";
      objects += target;
      objects += ".o ";
    }

  dependencylist.close();

  makefile << objects << endl
           << endl
           << "RUNARGS=" << runargs
           << endl;

  // Insert Targets

  makefile << endl
           << "# TARGETS ======================================================================" << endl
           << endl
           << ": " << endl
           << "\t$(MAKE) run --no-print-directory -j" << endl
           << endl
           << "run : $(OUTDIR)$(EXE) $(OBJECTS)" << endl
           << "\t@echo -e \"Running program ...\"" << endl
           << "\t./$(OUTDIR)$(EXE) $(RUNARGS) " << endl;
              if (diff_file.compare("nodiff") != 0)
              {
                makefile << "\t./$(OUTDIR)$(EXE) $(RUNARGS) > $(OUTFILE) " << endl;
              }
  makefile << "\t$(MAKE) doxygen" << endl
           << "\t$(MAKE) memchk" << endl;
              if (diff_file.compare("nodiff") != 0)
              {
                makefile << "\t$(MAKE) diff " << endl
                         << "\t$(MAKE) diffsupp " << endl;
              }

  makefile << endl
           << "$(OUTDIR)$(EXE) : $(OBJECTS) " << makefile_name << endl
           << "\t$(CC) $(OBJECTS) $(CFLAGS) $(OUTDIR)$(EXE)" << endl
           << endl;

  dependencylist.open("dependencies.txt");
  while(getline(dependencylist,linetext))
  {
    std::string target(linetext.size(), '\0');
    for (int i = 0; linetext[i] != '.'; i++)
    {
      target[i] = linetext[i];
    }
    
    makefile << "$(OUTDIR)" << linetext << endl
             << "\t$(CC) " << target.c_str() << "." << filext << " -c $(CFLAGS) $(OUTDIR)" << target.c_str() << ".o " << endl
             << endl;
  }
  dependencylist.close();

  // Base Targets
  makefile << "memchk : $(OUTDIR)$(EXE) $(OBJECTS)" << endl
           << "\t@echo -e \'\\n\\n\\n Checking for memory leaks\'" << endl
           << "\t$(MDEBUG) $(MDARGS) $(OUTDIR)$(EXE) $(RUNARGS)" << endl
           << endl;

  makefile << "clean :" << endl
           << "\t@$(ERASE) $(OUTDIR)*" << endl
           << endl
           << "rebuild :" << endl
           << "\t$(MAKE) clean" << endl
           << "\t$(MAKE)" << endl
           << endl;

  if (diff_file.compare("nodiff") != 0)
  {
    makefile << "diff : $(OUTDIR)$(EXE) $(OUTFILE)" << endl 
             << "\t@echo -e \'\\n\\n\\n Running Diff\'" << endl
             << "\tdiff -y --color=always $(OUTFILE) $(DIFF_FILE)" << endl
             << endl;

    makefile << "diffsupp : $(OUTDIR)$(EXE) $(OUTFILE)" << endl 
           << "\t@echo -e \'\\n\\n\\n Running Diff: Common Lines Suppressed\'" << endl
             << "\tdiff -y --color=always --suppress-common-lines $(OUTFILE) $(DIFF_FILE)" << endl
             << endl;
  }

  makefile << "doxygen :" << endl
           << "\t@echo -e \'\\n\\n\\n Running dOxygen\'" << endl
           << "\t-@$(ERASE) html/" << endl
           << "\t-@$(ERASE) latex/" << endl
           << "\t( cat Doxyfile ; echo \"EXTRACT_ALL=YES\" ) | doxygen -" << endl
           << "\t( cat Doxyfile ; echo \"EXTRACT_ALL=NO\" ) | doxygen -" << endl
           << endl
           << "doxyclean :" << endl
           << "\t-@$(ERASE) Doxyfile" << endl
           << "\t-@$(ERASE) html/" << endl
           << "\t-@$(ERASE) latex/" << endl
           << endl;
  
  std::filesystem::remove("dependencies.txt");
  makefile.close();
}

void help()
{
  cout  << "# ghake v" << VERSION << endl << "By Ghassan Younes (www.ghassanyounes.com/ghake/)" << endl
        << "`ghake` is a C++ Program that writes makefiles for you, based on programming standards of my C++ programming class." << endl
        << endl 
        << "ghake help menu:" << endl
        << "===========================================================" << endl
        << "##Usage" << endl
        << "-------" << endl
        << "### Compiler options " << endl
        << "- `--cc`      [UNIX C compiler] (partially tested)" << endl
        << "- `--cl`      [Microsoft C compiler] (not tested)" << endl
        << "- `--clang`   [LLVM C compiler]" << endl
        << "- `--clang++` [LLVM C++ compiler]" << endl
        << "- `--gcc`     [GNU C Compiler]" << endl
        << "- `--g++`     [GNU C++ Compiler] (default)" << endl
        << endl
        << "### ANSI/ISO standard " << endl
        << "- `--ansi` adds the equivalent flag for each compiler to enforce the ANSI/ISO standard (C89; C++98)" << endl
        << endl
        << "### Memory Debugger " << endl
        << "- `--drmemory` [Dr. Memory] (not tested)" << endl
        << "- `--valgrind` [Valgrind] (default)" << endl
        << endl
        << "### False Leak Suppression for Memory Debugger (--mdsupp \'path/to/file\')" << endl
        << "- Tells the memory debugger to ignore specific memory leaks that are not the result of your program. Must be configured prior to compiling." << endl
        << endl
        << "### Project name (--name \"PRJNAME\") " << endl
        << "- Input project title in \"Double Quotation Marks\"" << endl
        << endl
        << "### Runtime Arguments (--run_args \"ARGS\") " << endl
        << "- Input runtime arguments for generated program in \"Double Quotation Marks\"" << endl
        << endl
        << "### Source code file extensions (--ext EXT): " << endl
        << "- I've only tested `--ext c` and `--ext cpp` (*no `.` in runtime argument*), and the Compiler flags are set for C and C++ programs. Default is `cpp`"  << endl
        << endl
        << "### Makefile file Extensions (--makext)" << endl
        << "- `yes` (`makefile` will be appended with `.gnu`, `.wcl`, `.clg`, or `.unx`  -- make must be run as \"`make -f makefile.###`\")" << endl
        << "- `no`  (file name of `makefile` will remain unchanged) (default)" << endl
        << endl
        << "### Diff File (--diff \"DIFF_FILE\") " << endl
        << "- `nodiff` will not inject a diff command (default)" << endl
        << "- Any other string (should include the file extension (normally `.txt`)) will run a check for a file matching that name. It will also pipe the output of your program into a text file called `myout.txt` when running make, so that it has something to diff." << endl
        << endl
        << "### Quiet mode " << endl
        << "- `--quiet`   (Will not repeat the input values to affirm them) (default)" << endl
        << "- `--verbose` (Will repeat the input values to affirm them)" << endl
        << endl;
  return;
}

void gendirs()
{
  if (std::filesystem::exists("build"))
  {
    if (std::filesystem::exists("build/clg") == false)
    {
      std::filesystem::create_directory("build/clg");
    }
    if (std::filesystem::exists("build/gnu") == false)
    {
      std::filesystem::create_directory("build/gnu");
    }
    if (std::filesystem::exists("build/unx") == false)
    {
      std::filesystem::create_directory("build/unx");
    }
    if (std::filesystem::exists("build/win") == false)
    {
      std::filesystem::create_directory("build/win");
    }
  }
  else
  {
    std::filesystem::create_directory("build");
    std::filesystem::create_directory("build/clg");
    std::filesystem::create_directory("build/gnu");
    std::filesystem::create_directory("build/unx");
    std::filesystem::create_directory("build/win");
  }
  return;
}

/*
void gendirs()
{
  std::string makedirs; /// String for command to make directories
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
}
*/

/**
 * \brief 
 *  Overloaded input operator
 * 
 * \param os
 *  Output stream to write to
 * 
 * \param rhs
 *  Info class to output
 * 
 * \return 
 *  The output stream
 */ 
std::ostream& operator<<(std::ostream &os, const info& rhs)
{
  os << "     Project Name: " << rhs.project_name << endl
     << "    Makefile Name: " << rhs.makefile_name << endl
     << "         Compiler: " << rhs.compinfo.compilername << " [" << rhs.compinfo.description << "]"<< endl;
  if (rhs.is_ansi)
  {
    os << "     ISO/ANSI std: " << "Yes" << endl;
  }
  else 
  {
    os << "     ISO/ANSI std: " << "No" << endl;
  }
  if (rhs.is_effective && (rhs.compinfo.comptype == compilation::GPP || rhs.compinfo.comptype == compilation::CLANGPP))
  {
    os << "    Effective C++: " << "Yes" << endl;
  }
  else 
  {
    os << "    Effective C++: " << "No" << endl;
  }
  if (rhs.diff_file.compare("nodiff") == 0)
  {
    os << "        Diff File: " << "None" << endl;
  }
  else 
  {
    os << "        Diff File: " << rhs.diff_file << endl;
  }
  os << " Scanned File ext: " << rhs.filext << endl
     << "     Runtime Args: " << rhs.runargs << endl
     << "  Memory debugger: " << rhs.mdinfo.debugname << endl
     << "    |- Supp. File: " << rhs.mdinfo.false_supp_file << endl;

  return os;
}
