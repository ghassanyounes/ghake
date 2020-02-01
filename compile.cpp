/*!
 * \file    functions.h 
 * \author  Ghassan Younes
 * \date    January 27th 2020
 * \par     email: ghassan\@ghassanyounes.com
 * 
 * \brief
 *  This file contains the function implementations for the autogen makefiles.
 * 
 */

#include <iostream>       //! cout, cin, endl, string
#include <fstream>        //! ofstream, ifstream, .open, .is_open(), .close()
#include "functions.h"    //! COMPIL, compiler, compilargs, inject, STATUS

namespace compilation
{
  COMPIL compiler(info pinfo)
  {
    if (pinfo.compinfo.compilername.compare("gcc") == 0)
    {
      return GCC;
    } 
    else if (pinfo.compinfo.compilername.compare("g++") == 0)
    {
      return GPP;
    } 
    else if (pinfo.compinfo.compilername.compare("cl") == 0)
    {
      return MICROSOFT;
    } 
    else if (pinfo.compinfo.compilername.compare("cc") == 0)
    {
      return UNIX;
    } 
    else if(pinfo.compinfo.compilername.compare("clang") == 0)
    {
      return CLANG;
    } 
    else if(pinfo.compinfo.compilername.compare("clang++") == 0)
    {
      return CLANGPP;
    } 
    else 
    {
      return ERR;
    }
  }
 
  std::string compilargs(info pinfo)
  {
    switch (pinfo.compinfo.comptype)
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

  STATUS inject(info pinfo)
  {
    std::ofstream makefile;
    const char *makefname = pinfo.makefile.c_str();
    std::string textin;

    textin = "CC=";
    switch (pinfo.compinfo.comptype)
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
    makefile.open(makefname, std::ios::app);
    if (makefile.is_open() == 0)
    {
      return FAILED;
    }
    
    makefile << textin << "\n";
    textin = "CFLAGS=";
    textin += pinfo.compinfo.compilargs;
    makefile << textin << "\n";
    textin = "OUTDIR=build/";
    switch (pinfo.compinfo.comptype)
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
