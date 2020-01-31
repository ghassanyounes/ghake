/**
 * @file    functions.h 
 * @author  Ghassan Younes
 * @date    January 27th 2020
 * 
 * @brief
 *  This file contains the function declarations for the autogen makefiles.
 * 
 */

#include <iostream>

enum STATUS {
  OK, 
  FAILED,
  FILE_ERR
};

namespace doxygen {

  bool doxypresent(void);
  STATUS gendoxy(void);
  STATUS editdoxy(std::string projname);
  STATUS inject(std::string makefile);
}

namespace compilation
{
  enum COMPIL {
    GCC,
    GPP,
    MICROSOFT,
    CLANG,
<<<<<<< HEAD
    CLANGPP,
=======
>>>>>>> master
    UNIX,
    ERR
  };

  COMPIL compiler(std::string);
  std::string compilargs(COMPIL compiler);
  STATUS inject(COMPIL cc, std::string cliargs, std::string makename);
}

namespace memorydebug
{
  enum MMCHK
  {
    DRMEM,
    VALG,
    ERR
  };

  MMCHK memdebug(std::string debugger);
  std::string memdargs(MMCHK debugger);

}

namespace basemake
{
<<<<<<< HEAD
  STATUS macros(std::string makename, 
                std::string projname, 
                compilation::COMPIL compiler, 
                std::string extension);
  STATUS targets(std::string makename);
  STATUS baserules(std::string makename);
  STATUS dotorules(std::string makename, 
                   std::string extension);
  STATUS generatedeps(compilation::COMPIL compiler, std::string extension);
=======
  STATUS macros(std::string makename, std::string driver);
  STATUS targets(std::string makename);
  STATUS baserules(std::string makename);
  STATUS dotorules(std::string makename, 
                   compilation::COMPIL compiler, 
                   std::string extension);
>>>>>>> master
}
