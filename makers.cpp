/*!
 * \file    makers.cpp
 * \author  Ghassan Younes
 * \date    January 27th 2020
 * \par     Email: ghassan\@ghassanyounes.com
 * 
 * \brief
 *  This file contains the function implementations for the autogen makefiles.
 * 
 */
#include <iostream>      //! cout, cin, endl, string
#include <fstream>       //! ofstream, ifstream, .open, .is_open(), .close()
#include <cstdlib>       //! system
#include "functions.h"   /*! macros, targets, baserules, dotorules, generatedeps
                          *  COMPIL, STATUS
                          */

namespace basemake
{
  STATUS macros(const info pinfo)
  {
    std::string exec = pinfo.project_name;      //! Executable since pinfo const
    std::string textin1;                        //! First set of text to write
    std::string textin2;                        //! Second set of text
    std::string dbg;                            //! Wich debugger?
    std::string objects;
    std::ofstream makefile;
    const char* makefname = pinfo.makefile.c_str();
    std::ifstream dependencylist;
    std::string linetext;

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

    textin1  = "# Makefile generated by Ghake 1.1.0 -- Ghake by Ghassan Younes";
    textin1 += "\n#\n# MACROS ================================================";
    textin1 += "======================\n\n";

    textin2 = "ERASE=";
    textin2 += "rm -rf\n\n";

    for (int i = 0; i < (int)sizeof(exec); i++)
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

    makefile.open(makefname, std::ios::app);
    if (makefile.is_open() == 0)
    {
      return FILE_ERR;
    }

    objects = "OBJECTS=";

    while(getline(dependencylist,linetext))
    {
      std::string target(sizeof(linetext), '\0');
      for (int i = 0; linetext[i] != '.'; i++)
      {
        target[i] = linetext[i];
      }

      objects += "$(OUTDIR)";
      objects += target.c_str(); 
      objects += ".o ";
    }

    objects += "\n\n";

    makefile << textin1 << textin2 << objects << "RUNARGS=\n\n";
    dependencylist.close();
    makefile.close();
    return OK;
  }

  STATUS targets(const info pinfo)
  {
    std::string targets; 
    std::ofstream makefile;
    const char* makefname = pinfo.makefile.c_str();

    targets = "# TARGETS =====================================================";
    targets += "=================\n\n";
    targets += "run : $(OUTDIR)$(EXE) $(OBJECTS)\n";
    targets += "\t$(MAKE) doxygen\n";
    targets += "\t$(MAKE) memchk\n";
    targets += "\t./$(OUTDIR)$(EXE) $(RUNARGS)\n\n";

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

  STATUS baserules(const info pinfo)
  {
    std::string target;
    std::ofstream makefile;
    const char* makefname = pinfo.makefile.c_str();

    target  = "clean : \n";
    target += "\t@$(ERASE) $(OUTDIR)*\n\n";

    target += "rebuild :\n";
    target += "\t$(MAKE) clean\n";
    target += "\t$(MAKE)\n\n";

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
    std::ifstream dependencylist;
    std::ofstream makefile;
    std::string linetext;
    const char* makefname = pinfo.makefile.c_str();

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
    std::string command;
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
