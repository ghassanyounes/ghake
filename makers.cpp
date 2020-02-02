/**
 * @file    makers.cpp
 * @author  Ghassan Younes
 * @date    January 27th 2020
 * @par     email: ghassan\@ghassanyounes.com
 * 
 * @brief
 *  This file contains the function implementations for the makefiles 
 *  (macros and targets).
 * 
 */
#include <iostream>      /// cout, cin, endl, string
#include <fstream>       /// ofstream, ifstream, .open, .is_open(), .close()
#include <cstdlib>       /// system
#include "functions.h"   /** macros, targets, baserules, dotorules, generatedeps
                          *  COMPIL, STATUS
                          */

namespace basemake
{
  using idx_t = std::string::size_type;             /// Simpilified name
  STATUS macros(const info pinfo)
  {
    std::string exec = pinfo.project_name;          /// Executable (const pinfo)
    std::string textin1;                            /// First string to write
    std::string textin2;                            /// Second set of text
    std::string dbg;                                /// Which debugger?
    std::string objects;                            /// List of object files
    std::ofstream makefile;                         /// Makefile to write to
    const char* makefname = pinfo.makefile.c_str(); /// C String makefile name
    std::ifstream dependencylist;                   /// File dependencies list
    std::string linetext;                           /// File's text on each line

    STATUS dps = generatedeps(pinfo);
    if (dps == FILE_ERR || dps == FAILED)
    {
    std::cout  << "Dependency detection of source failed. Please make sure "
               << "that the current directory is writeable." << std::endl ;
    
    return FAILED; 
    }

    dependencylist.open("dependencies.txt");
    if (dependencylist.is_open() == 0)
    {
      return FILE_ERR;
    }

    textin1  = "# Makefile generated by Ghake 1.2.0 -- Ghake by Ghassan Younes";
    textin1 += "\n#\n# MACROS ================================================";
    textin1 += "======================\n\n";

    textin2 = "ERASE=";
#if defined (unix) || defined (__unix) || defined(__unix__) || defined (__APPLE__) || defined (__MACH__)
    textin2 += "rm -rf\n\n";
#elif defined (_WIN32) || defined (_WIN64)
    textin2 += "del \n\n";
#endif

    for (std::size_t i = 0; i < exec.length(); i++)
    {
      if (( exec[i] == ' '  || exec[i] == '\n' ) 
        ||( exec[i] == '\t' || exec[i] == '.'  ))
      {
        exec[i] = '_';
      }
    }

    textin2 += "EXE=";
    textin2 += exec;
    textin2 += "\n\n";

    switch (pinfo.mdinfo.debugtype)
    {
    case memorydebug::VALG:
      dbg = "valgrind";
      break;
    
    case memorydebug::DRMEM:
      dbg = "drmemory";
      break;

    case memorydebug::ERR:
      dbg = " ";
      break;

    default:
      dbg = " ";
      break;
    }

    textin2 += "MDEBUG=";
    textin2 += dbg;
    textin2 += "\n\n";
    
    textin2 += "MDARGS=";
    textin2 += pinfo.mdinfo.debugargs;
    textin2 += "\n\n";


    if (pinfo.diff_file.compare("nodiff") != 0)
    {
      textin2 += "OUTFILE=myout.txt";
      textin2 += "\n\n";;
      textin2 += "DIFF_FILE=";
      textin2 += pinfo.diff_file;
      textin2 += "\n\n";;
    }

    makefile.open(makefname, std::ios::app);
    if (makefile.is_open() == 0)
    {
      return FILE_ERR;
    }

    objects = "OBJECTS=";

    while (std::getline(dependencylist, linetext))
    {
      if (linetext.empty()) continue;
      
      std::string target(linetext.size(), '\0') ;
      // Note: the above will not compile prior to C++11,
      // because I'm using uniform initializer brace syntax.
      
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
      objects += ".o";
    }

    objects += "\n\n";

    makefile << textin1 << textin2 << objects << "RUNARGS=\n\n";
    dependencylist.close();
    makefile.close();
    return OK;
  }

  STATUS targets(const info pinfo)
  {
    std::string targets;                            /// List of targets
    std::ofstream makefile;                         /// Makefile to write to 
    const char* makefname = pinfo.makefile.c_str(); /// C String makefile name

    targets = "# TARGETS =====================================================";
    targets += "=================\n\n";
    targets += "run : $(OUTDIR)$(EXE) $(OBJECTS)\n";
    targets += "\t$(MAKE) doxygen\n";
    targets += "\t$(MAKE) memchk\n";
    targets += "\t./$(OUTDIR)$(EXE) $(RUNARGS) ";
    if (pinfo.diff_file.compare("nodiff") != 0)
    {
      targets += "> $(OUTFILE) \n";
      targets += "\t$(MAKE) diff ";
    } 
    targets += "\n\n";

    targets += "$(OUTDIR)$(EXE) : $(OBJECTS) ";
    targets += pinfo.makefile;
    targets += "\n";
    targets += "\t$(CC) $(OBJECTS) $(CFLAGS) $(OUTDIR)$(EXE)\n\n";

    makefile.open(makefname, std::ios::app);
    if (makefile.is_open() == 0)
    {
      return FILE_ERR;
    }
    
    makefile << targets;
    makefile.close();

    return OK;
  }

  STATUS baserules(info pinfo)
  {
    std::string target;                             /// List of targets
    std::ofstream makefile;                         /// Makefile to write to 
    const char* makefname = pinfo.makefile.c_str(); /// C String makefile name

    target  = "clean : \n";
    target += "\t@$(ERASE) $(OUTDIR)*\n\n";

    target += "rebuild :\n";
    target += "\t$(MAKE) clean\n";
    target += "\t$(MAKE)\n\n";

    if (pinfo.diff_file.compare("nodiff") != 0)
    {
      target += "diff :\n";
      target += "\tdiff -y --color=always --suppress-common-lines ";
      target += "$(OUTFILE) $(DIFF_FILE) \n\n";
    }
    

    makefile.open(makefname, std::ios::app);
    if (makefile.is_open() == 0)
    {
      return FILE_ERR;
    }

    makefile << target;
    makefile.close();

    return OK;
  }
  
  STATUS dotorules(const info pinfo)
  {
    std::ifstream dependencylist;                   /// File dependencies list
    std::ofstream makefile;                         /// Makefile to write to
    std::string linetext;                           /// File's text on each line
    const char* makefname = pinfo.makefile.c_str(); /// C String makefile name

    dependencylist.open("dependencies.txt");
    if (dependencylist.is_open() == 0)
    {
      return FILE_ERR;
    }

    makefile.open(makefname, std::ios::app);
    if (makefile.is_open() == 0)
    {
      return FILE_ERR;
    }

    while(getline(dependencylist,linetext))
    {
      std::string target(sizeof(linetext), '\0');
      for (int i = 0; linetext[i] != '.'; i++)
      {
        target[i] = linetext[i];
      }
      
      makefile << "$(OUTDIR)" << linetext << "\n"
               << "\t$(CC) " << target.c_str() << "." << pinfo.filex 
               << " -c $(CFLAGS) $(OUTDIR)" 
               << target.c_str() << ".o \n\n";
    }
    
    dependencylist.close();
    makefile.close();

    system("rm dependencies.txt");

    return OK;
  }

  STATUS generatedeps(const info pinfo)
  {
    std::string command;    /// Command to run to generate file dependency list
    switch (pinfo.compinfo.comptype)
    {
      case compilation::GCC: 
        command = "gcc -MM ";
        break;

      case compilation::GPP: 
        command = "g++ -MM ";
        break;
      
      case compilation::MICROSOFT: 
        command = "cl /I ";
        break;
      
      case compilation::CLANG: 
        command = "clang --user-dependencies ";
        break;

      case compilation::CLANGPP: 
        command = "clang++ --user-dependencies ";
        break;
      
      case compilation::UNIX: 
        command = "cc -MM ";
        break;
      
      case compilation::ERR:
        return FAILED;
        break;
      
      default:
        return FAILED;
        break;
    }

    command += "*.";
    command += pinfo.filex;
    command += " > dependencies.txt";

    system(command.c_str());

    return OK;

  }
}
