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
#include <fstream>
#include "functions.h"

namespace compilation
{
  /**
   * 
   * @brief
   *  This function returns the compiler requested by the user
   * 
   * @param comp
   *  Program executable input from argv[]
   * 
   * @return
   *  Returns the compiler being used
   * 
   */
  COMPIL compiler(std::string comp)
  {
    if (comp.compare("gcc") == 0)
    {
      return GCC;
    } 
    else if (comp.compare("g++") == 0)
    {
      return GPP;
    } 
    else if (comp.compare("cl") == 0)
    {
      return MICROSOFT;
    } 
    else if (comp.compare("cc") == 0)
    {
      return UNIX;
    } 
    else if(comp.compare("clang") == 0)
    {
      return CLANG;
    } 
    else if(comp.compare("clang++") == 0)
    {
      return CLANGPP;
    } 
    else 
    {
      return ERR;
    }
  }
 
  /**
   * 
   * @brief
   *  This function returns the compiler requested by the user
   * 
   * @param compiler
   *  Compiler requested by the user
   * 
   * @return
   *  Returns the compiler arguments to be used (CS170 - ANSI C++ standards)
   * 
   */
  std::string compilargs(COMPIL compiler)
  {
    switch (compiler)
    {
    case GCC:
      return "-g -ansi -pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicated-cond -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o \n";
      break;

    case GPP:
      return "-g -ansi -pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicated-cond -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o \n";
      break;

    case MICROSOFT:
      return "-W4 -WX -EHa -Za -Fehw-ms.exe -D_CRT_SECURE_NO_DEPRECATE \n";
      break;

    case CLANG:
      return "-g -O0 -v -ansi -pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicate-enum -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o \n"; //-c is applicable for .o generation
      break;

    case CLANGPP:
      return "-g -O0 -v -std=c++98 -pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicate-enum -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o \n"; //-c is applicable for .o generation
      break;

    case UNIX:
      return " \n";
      break;

    case ERR:
      return "ERROR\n";
      break;
    
    default:
      return "ERROR\n";
      break;
    }
  }

  /**
   * 
   * @brief
   *  This function injects the compiler and arguments into the makefile
   * 
   * @param comp
   *  Program executable input from argv[]
   * 
   * @return
   *  Returns the compiler being used
   * 
   */
  STATUS inject(COMPIL cc, std::string cliargs, std::string makename)
  {
    std::string textin;
    textin = "CC=";
    switch (cc)
    {
      case GCC: 
        textin += "gcc\n";
        break;

      case GPP: 
        textin += "g++\n";
        break;
      
      case MICROSOFT: 
        textin += "cl\n";
        break;
      
      case CLANG: 
        textin += "clang\n";
        break;

      case CLANGPP: 
        textin += "clang++\n";
        break;
      
      case UNIX: 
        textin += "cc\n";
        break;
      
      case ERR:
        return FAILED;
        break;
      
      default:
        return FAILED;
        break;
    }
    std::ofstream makefile;
    // std::ios::app is the open mode "append" meaning
    // new data will be written to the end of the file.
    const char *makefname = makename.c_str();
    makefile.open(makefname, std::ios::app);
    if (makefile.is_open() == 0)
    {
      return FAILED;
    }
    
    makefile << textin << "\n";
    textin = "CLIARGS=";
    textin += cliargs;
    makefile << textin << "\n";
    textin = "OUTDIR=build/";
    switch (cc)
    {
      case GCC: 
        textin += "gnu/\n";
        break;

      case GPP: 
        textin += "gnu/\n";
        break;
      
      case MICROSOFT: 
        textin += "win/\n";
        break;
      
      case CLANG: 
        textin += "clg/\n";
        break;
      
      case CLANGPP: 
        textin += "clg/\n";
        break;
      
      case UNIX: 
        textin += "unx/\n";
        break;
      
      case ERR:
        return FAILED;
        break;
      
      default:
        return FAILED;
        break;
    }
    makefile << textin << "\n";
    makefile.close();
    return OK;
  }

}
