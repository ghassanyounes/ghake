/**
 * @file    memdebug.cpp
 * @author  Ghassan Younes
 * @date    March 19th 2020
 * @par     email: ghassan\@ghassanyounes.com
 * 
 * @brief
 *  This file contains function implementations for the memorydebug namespace
 * 
 */

#include "functions.h" /// memorydebug::MMCHK, info class [set_debugger, set_false_supp]
#include <iostream>    /// ofstream, ifstream, .open, .is_open(), .close()
#include <cstdlib>     /// cout, endl, string

/**
 * 
 * @brief
 *  Sets the memory debugger
 * 
 * @param debugger
 *  User-set debugger
 * 
 */
void info::set_debugger(memorydebug::MMCHK debugger)
{
  switch (debugger)
  {
    case memorydebug::VALG:
      mdinfo.debugtype = memorydebug::VALG;
      mdinfo.debugname = "valgrind";
      mdinfo.debugargs = "-q --leak-check=full --show-reachable=yes --tool=memcheck --trace-children=yes  ";
      break;

    case memorydebug::DRMEM:
      mdinfo.debugtype = memorydebug::DRMEM;
      mdinfo.debugname = "drmemory";
      mdinfo.debugargs = " ";
      break;
      
    default:
      mdinfo.debugtype = memorydebug::VALG;
      mdinfo.debugname = "valgrind";
      mdinfo.debugargs = "-q --leak-check=full --show-reachable=yes --tool=memcheck --trace-children=yes  ";
      break;
      
  }
}

/**
 * 
 * @brief
 *  Sets the false memory leaks suppressions file
 * 
 * @param false_supp
 *  false.supp file to set
 * 
 */
void info::set_false_supp(std::string false_supp)
{
  mdinfo.false_supp_file = false_supp;
  mdinfo.false_supp = " --suppressions=" + false_supp;
}