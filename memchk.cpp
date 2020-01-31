/*!
 * \file    compile.cpp
 * \author  Ghassan Younes
 * \date    January 27th 2020
 * 
 * \brief
 *  This file contains the function definitions for the compilation namespace.
 * 
 */

#include <iostream>       //! cout, cin, endl
#include <cstring>        // strcmp
#include <fstream>        //! File IO
#include "functions.h"

namespace memorydebug
{
  /*!
   * 
   * \brief
   *  Quantifies the memory debugger
   * 
   * \param debugger
   *  Memory debugger string input by the user
   * 
   * \return
   *  Returns the memory debugger to be used
   * 
   */
  MMCHK memdebug(std::string debugger)
  {
    if (debugger.compare("valgrind") == 0)
    {  
      return VALG;
    }
    else if (debugger.compare("drmemory") == 0)
    {
      return DRMEM;
    }
    else
    {
      return ERR;
    }
  }

    /*!
   * 
   * \brief
   *  Determines the CLI switches to use for the memory debugger
   * 
   * \param debugger
   *  Which debugger's CLI switches to use
   * 
   * \return
   *  Returns the CLI switches
   * 
   */
  std::string memdargs(MMCHK debugger)
  {
    switch (debugger)
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

  /*!
   * 
   * \brief
   *  Injects the mamory debugger file targets into the makefile
   * 
   * \param makename
   *  Name of the makefile to inject into
   * 
   * \return
   *  Returns the status of the function
   * 
   */
  STATUS inject(std::string makename)
  {
    std::string target;
    std::ofstream makefile;
    const char* makefname = makename.c_str();

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
