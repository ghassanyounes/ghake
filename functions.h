/*!
 * \file    functions.h 
 * \author  Ghassan Younes
 * \date    January 27th 2020
 * 
 * \brief
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
         STATUS editdoxy(const std::string projname);
           STATUS inject(const std::string makefile);
}

namespace compilation
{
  enum COMPIL {
    GCC,
    GPP,
    MICROSOFT,
    CLANG,
    CLANGPP,
    UNIX,
    ERR
  };

         COMPIL compiler(const std::string);
  std::string compilargs(const COMPIL compiler);
           STATUS inject(const COMPIL cc, 
                         const std::string cliargs, 
                         const std::string makename);
}

namespace memorydebug
{
  enum MMCHK
  {
    DRMEM,
    VALG,
    ERR
  };

          MMCHK memdebug(const std::string debugger);
    std::string memdargs(const MMCHK debugger);
           STATUS inject(const std::string makename);

}

namespace basemake
{
           STATUS macros(const std::string makename,
                         const std::string projname, 
                         const compilation::COMPIL compiler, 
                         const std::string extension,
                         const memorydebug::MMCHK debugger,
                         const std::string debugargs);
          STATUS targets(const std::string makename);
        STATUS baserules(const std::string makename);
        STATUS dotorules(const std::string makename, 
                         const std::string extension);
     STATUS generatedeps(const compilation::COMPIL compiler, 
                         const std::string extension);
}
