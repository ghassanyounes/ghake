/**
 * @file    memchk.cpp
 * @author  Ghassan Younes
 * @date    January 27th 2020
 * @par     email: ghassan\@ghassanyounes.com
 * 
 * @brief
 *  This file contains the function definitions for the memorydebug namespace.
 * 
 */

#include <iostream>       /// cout, cin, endl, string
#include <fstream>        /// ofstream, ifstream, .open, .is_open(), .close()
#include "functions.h"    /// MMCHK, debug, memdargs, inject

namespace memorydebug
{
  MMCHK memdebug(const info pinfo)
  {
    if (pinfo.mdinfo.debugname.compare("valgrind") == 0)
    {  
      return VALG;
    }
    else if (pinfo.mdinfo.debugname.compare("drmemory") == 0)
    {
      return DRMEM;
    }
    else
    {
      return ERR;
    }
  }

  std::string memdargs(const info pinfo)
  {
    switch (pinfo.mdinfo.debugtype)
    {
      case VALG: 
        return "-q --leak-check=full --show-reachable=yes --tool=memcheck --trace-children=yes --suppressions=false.supp";
        break;
      
      case DRMEM:
        return " ";
        break;
      
      case ERR:
        return "ERROR";
        break;
      
      default:
        return "ERROR";
        break;
    }
  }

  STATUS inject(const info pinfo)
  {
    std::string target;
    std::ofstream makefile;
    const char* makefname = pinfo.makefile.c_str();

    target  = "memchk : $(OUTDIR)$(EXE) $(OBJECTS)\n";
	  target += "\t@$(MDEBUG) $(MDARGS) $(OUTDIR)$(EXE) $(RUNARGS)\n\n";

    makefile.open(makefname, std::ios::app);
    if (makefile.is_open() == 0)
    {
      return FILE_ERR;
    }

    makefile << target;
    makefile.close();

    return OK;
  }
}
