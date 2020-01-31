/**
 * @file    compile.cpp
 * @author  Ghassan Younes
 * @date    January 27th 2020
 * 
 * @brief
 *  This file contains the function definitions for the compilation namespace.
 * 
 */

#include <iostream>       //! cout, cin, endl
#include <cstring>        // strcmp
#include "functions.h"

namespace memorydebug
{
  MMCHK memdebug(std::string debugger)
  {
    if (debugger.compare("valgrind"))
    {  
      return VALG;
    }
    else if (debugger.compare("drmemory"))
    {
      return DRMEM;
    }
    else
    {
      return ERR;
    }
  }
  std::string memdargs(MMCHK debugger)
  {
    switch (debugger)
    {
      case VALG: 
        return "-q --leak-check=full --show-reachable=yes --tool=memcheck --trace-children=yes";
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
}
