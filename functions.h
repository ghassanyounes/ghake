/*!
 * \file    functions.h 
 * \author  Ghassan Younes
 * \date    January 27th 2020
 * \par     email: ghassan\@ghassanyounes.com
 * 
 * \brief
 *  This file contains the function declarations for the autogen makefiles.
 * 
 */

#include <iostream>

/*!
 * 
 * \brief
 *  Status of file IO
 * 
 */
enum STATUS {
  OK, 
  FAILED,
  FILE_ERR
};

namespace compilation
{
  /*!
  * 
  * \brief
  *  Which compiler is being used
  * 
  */
  enum COMPIL {
    GCC,
    GPP,
    MICROSOFT,
    CLANG,
    CLANGPP,
    UNIX,
    ERR
  };

  /*!
   *
   * \brief 
   *  Compiler debugger info struct
   * 
   */
  typedef struct compinfo{
    COMPIL comptype;            ///< Which compiler to use
    std::string compilername;   ///< String containing name of compiler command
    std::string compilargs;     ///< Compiler arguments/command-line flags
  } compinfo;

}

namespace memorydebug
{
  /*!
   * 
   * \brief
   *  Which memory debugger is being used
   * 
   */
  enum MMCHK
  {
    DRMEM,
    VALG,
    ERR
  };


  /*!
   *
   * \brief 
   *  Memory debugger info struct
   * 
   */
  typedef struct mdinfo{
    MMCHK debugtype;        ///< Which memory debugger is requested
    std::string debugname;  ///< String containing name of memory debugger
    std::string debugargs;  ///< Memory debugger command line args
  } mdinfo;
}

/*!
 *
 * \brief 
 *  Project information struct
 * 
 */
typedef struct info{
  std::string project_name;         ///< Name of project
  std::string makefile;             ///< Name of makefile
  std::string filex;                ///< File extensions to use
  std::string diff_file;            ///< Name of file to diff against
  compilation::compinfo compinfo;   ///< Compiler info struct
  memorydebug::mdinfo mdinfo;       ///< Memory debugger info struct
} info;

namespace doxygen {

  /*!
   * 
   * \brief
   *  Checks if Doxyfile is present
   * 
   * \return
   *  Returns if Doxyfile is present
   * 
   */
        bool doxypresent(void);
  /*!
   * 
   * \brief
   *  Generates the Doxyfile
   * 
   * \return
   *  Returns the status of the function
   * 
   */
          STATUS gendoxy(void);
  
  /*!
   * 
   * \brief
   *  Edits the Doxyfile, modifying it to the CS170 standards 
   *  (but keeping LaTeX)
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the status of the function
   * 
   */
         STATUS editdoxy(const info pinfo);
  /*!
   * 
   * \brief
   *  Injects the doxyfile into the makefile
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the status of the function
   * 
   */
           STATUS inject(const info pinfo);
}

namespace compilation
{
  /*!
   * 
   * \brief
   *  This function returns the compiler requested by the user
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the compiler being used
   * 
   */
         COMPIL compiler(const info pinfo);

  /*!
   * 
   * \brief
   *  This function returns the compiler arguments requested by the user
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the compiler arguments to be used (CS170 - ANSI C++ standards)
   * 
   */
  std::string compilargs(const info pinfo);

  /*!
   * 
   * \brief
   *  This function injects the compiler and arguments into the makefile
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Status of file IO
   * 
   */
           STATUS inject(const info pinfo);
}

namespace memorydebug
{
  /*!
   * 
   * \brief
   *  Quantifies the memory pinfo.mdinfo.debugname
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the memory pinfo.mdinfo.debugname to be used
   * 
   */
          MMCHK memdebug(const info pinfo);

  /*!
   * 
   * \brief
   *  Determines the CLI switches to use for the memory pinfo.mdinfo.debugname
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the CLI switches
   * 
   */
    std::string memdargs(const info pinfo);

  /*!
   * 
   * \brief
   *  Injects the mamory pinfo.mdinfo.debugname file targets into the makefile
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the status of the function
   * 
   */
           STATUS inject(const info pinfo);

}

namespace basemake
{
  /*!
   * 
   * \brief
   *  This function generates the macros in the makefile
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the status of the write operations
   * 
   */
           STATUS macros(const info pinfo);
  
  /*!
   * 
   * \brief
   *  Injects the generic targets into the makefile (executable and run command)
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the status of the function
   * 
   */
          STATUS targets(const info pinfo);
  
  /*!
   * 
   * \brief
   *  Injects the base targets into the makefile (clean, rebuild)
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the status of the function
   * 
   */
        STATUS baserules(const info pinfo);
        
  /*!
   * 
   * \brief
   *  Injects the object file targets into the makefile
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the status of the function
   * 
   */
        STATUS dotorules(const info pinfo);

  /*!
   * 
   * \brief
   *  Injects the object file targets into the makefile
   * 
   * \param pinfo
   *  Information struct containing details of the program
   * 
   * \return
   *  Returns the status of the function
   * 
   */
     STATUS generatedeps(const info pinfo);
}
