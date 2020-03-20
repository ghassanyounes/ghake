/**
 * @file    compiler.cpp
 * @author  Ghassan Younes
 * @date    March 19th 2020
 * @par     email: ghassan\@ghassanyounes.com
 * 
 * @brief
 *  This file contains function implementations for the compilation namespace
 * 
 */

#include "functions.h"  /// compilation::COMPIL, compilation::generatedeps, class info [ansi, set_compiler] 
#include <iostream>     /// cout, endl, string
#include <cstdlib>      /// system

/**
 * 
 * @brief
 *  Sets the ansi flag if needed
 * 
 */
void info::ansi()
{
  is_ansi = true;
}

/**
 * 
 * @brief
 *  Sets the -Weffc++ flag if needed for the g++ compiler
 * 
 */
void info::effective()
{
  is_effective = true;
}

/**
 * 
 * @brief
 *  Sets the compiler
 * 
 * @param compiler
 *  User-set compiler
 * 
 */
void info::set_compiler(compilation::COMPIL compiler)
{
  switch (compiler)
  {
    case compilation::CC:
      compinfo.comptype = compilation::CC;
      compinfo.description = "UNIX C Compiler";
      compinfo.compilername = "cc";
      compinfo.compilargs = "-g -O0 ";
      if (is_ansi)
      {
        compinfo.compilargs += "-ansi ";
      }
      compinfo.compilargs += "-pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicated-cond -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o  \n";
      break;

    case compilation::CL:
      compinfo.comptype = compilation::CL;
      compinfo.description = "Microsoft C Compiler";
      compinfo.compilername = "cl";
      compinfo.compilargs = "-W4 -WX -EHa -Za -Fehw-ms.exe -D_CRT_SECURE_NO_DEPRECATE \n";
      break;
      
    case compilation::CLANG:
      compinfo.comptype = compilation::CLANG;
      compinfo.description = "LLVM C Compiler";
      compinfo.compilername = "clang";
      compinfo.compilargs = "-g -O0 -v ";
      if (is_ansi)
      {
        compinfo.compilargs += "-ansi ";
      }
      compinfo.compilargs += "-pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicate-enum -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o \n"; //-c is applicable for .o generation
      break;
      
    case compilation::CLANGPP:
      compinfo.comptype = compilation::CLANGPP;
      compinfo.description = "LLVM C++ Compiler";
      compinfo.compilername = "clang++";
      compinfo.compilargs = "-g -O0 -v ";
      if (is_ansi)
      {
        compinfo.compilargs += "-std=c++98 ";
      }
      if (is_effective)
      {
        compinfo.compilargs += "-Weffc++ ";
      }
      compinfo.compilargs += "-pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicate-enum -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o \n"; //-c is applicable for .o generation
      break;
      
    case compilation::GCC:
      compinfo.comptype = compilation::GCC;
      compinfo.description = "GNU C Compiler";
      compinfo.compilername = "gcc";
      compinfo.compilargs = "-g -O0 ";
      if (is_ansi)
      {
        compinfo.compilargs += "-ansi ";
      }
      compinfo.compilargs += "-pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicated-cond -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o \n";
      break;
      
    case compilation::GPP:
      compinfo.comptype = compilation::GPP;
      compinfo.description = "GNU C++ Compiler";
      compinfo.compilername = "g++";
      compinfo.compilargs = "-g -O0 ";
      if (is_ansi)
      {
        compinfo.compilargs += "-ansi ";
      }
      if (is_effective)
      {
        compinfo.compilargs += "-Weffc++ ";
      }
      compinfo.compilargs += "-pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicated-cond -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o \n";
      break;

    default:
      compinfo.comptype = compilation::GPP;
      compinfo.description = "GNU C++ Compiler";
      compinfo.compilername = "g++";
      compinfo.compilargs = "-g -O0 ";
      if (is_ansi)
      {
        compinfo.compilargs += "-ansi ";
      }
      if (is_effective)
      {
        compinfo.compilargs += "-Weffc++ ";
      }
      compinfo.compilargs += "-pedantic -Wall -Wextra -Werror -Wall -Wextra -Werror -Wconversion -Winline -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum -Wunreachable-code -Wduplicated-cond -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wpedantic -o \n";
      break;
  }
}

namespace compilation
{
  STATUS generatedeps(const info &pinfo)
  {
    std::string command = pinfo.get_compname();
    switch (pinfo.get_comptype())
    {
      case compilation::GCC: 
        command = "gcc -MM ";
        break;

      case compilation::GPP: 
        command = "g++ -MM ";
        break;
      
      case compilation::CC: 
        command = "cl /I ";
        break;
      
      case compilation::CLANG: 
        command = "clang --user-dependencies ";
        break;

      case compilation::CLANGPP: 
        command = "clang++ --user-dependencies ";
        break;
      
      case compilation::CL: 
        command = "cc -MM ";
        break;
      
      default:
        return FAILED;
        break;
    }

    command += "*.";
    command += pinfo.get_filex();
    command += " > dependencies.txt";

    system(command.c_str());

    return OK;
  }
}
