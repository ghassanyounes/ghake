/**
 * @file    doxygen.cpp
 * @author  Ghassan Younes
 * @date    Februaty 8th 2020
 * @par     email: ghassan\@ghassanyounes.com
 * 
 * @brief
 *  This file contains function implementations for the doxygen namespace
 * 
 */

#include "functions.h"  /// doxypresent, gendoxy, editdoxy, STATUS
#include <iostream>     /// cout, endl, string
#include <fstream>      /// ofstream, ifstream, .open, .is_open(), .close()
#include <cstdlib>      /// system

namespace doxygen 
{
  bool doxypresent(void)
  {
    bool opclo;             /// Open or closed?
    std::ifstream Doxyfile; /// Doxyfile instream
    Doxyfile.open("Doxyfile");
    opclo = Doxyfile.is_open();
    Doxyfile.close();
    return opclo;
  }
  STATUS gendoxy(void)
  {
    std::string doxvers;    /// Doxygen version
    std::ifstream version;  /// version.txt file
#if defined (unix) || defined (__unix) || defined(__unix__) || defined (__APPLE__) || defined (__MACH__)
    system("touch doxyversion.txt; doxygen --version > doxyversion.txt");
#elif defined (_WIN32) || defined (_WIN64)
    system("doxygen --version > doxyversion.txt");
#endif
    version.open ("doxyversion.txt");
    getline(version,doxvers);
    version.close();

#if defined (unix) || defined (__unix) || defined(__unix__) || defined (__APPLE__) || defined (__MACH__)
    system("rm doxyversion.txt");
#elif defined (_WIN32) || defined (_WIN64)
    system("del doxyversion.txt");
#endif

    std::cout << "Doxygen version is " << doxvers << std::endl;

    if (doxvers.compare("1.8.15") != 0)
    {
      std::cout << "Wrong Doxygen version. Please install version 1.8.15"
                << std::endl;
      return FAILED;
    } 
    
    std::cout << "Generating Doxyfile" << std::endl;
    system("doxygen -g");

    return OK;
  }

  STATUS editdoxy(const info pinfo)
  {
    std::string linetext;   /// Line of Doxyfile that was read in
    std::ifstream doxyin;   /// Input Doxyfile
    std::ofstream doxyfile; /// Output Doxyfile
#if defined (unix) || defined (__unix) || defined(__unix__) || defined (__APPLE__) || defined (__MACH__)
    system("mv Doxyfile Doxyfile.old");
#elif defined (_WIN32) || defined (_WIN64)
    system("move Doxyfile Doxyfile.old");
#endif
    doxyin.open("Doxyfile.old");
    doxyfile.open ("Doxyfile");

    if (doxyfile.is_open() == 0)
    {
      return FILE_ERR;
    }

    /// Set correct Doxygen flags

    while(getline(doxyin,linetext))
    {
      if (linetext.compare("PROJECT_NAME           = \"My Project\"") == 0)
      {
        doxyfile << "PROJECT_NAME           = \"" << pinfo.get_pname() << "\"\n";
      }
      else if (linetext.compare("QUIET                  = NO") == 0) {
        doxyfile << "QUIET                  = YES\n";
      }
      else if (linetext.compare("EXTRACT_ALL            = NO") == 0) {
        doxyfile << "EXTRACT_ALL            = YES\n";
      }
      else if (linetext.compare("FULL_PATH_NAMES        = YES") == 0) {
        doxyfile << "FULL_PATH_NAMES        = NO";
      }
      else if (linetext.compare("TAB_SIZE               = 4" ) == 0) {
        doxyfile << "TAB_SIZE               = 2\n";
      }
      else if (linetext.compare("EXTRACT_PRIVATE        = NO") == 0) {
        doxyfile << "EXTRACT_PRIVATE        = YES\n";
      }
      else if (linetext.compare("EXTRACT_PACKAGE        = NO") == 0) {
        doxyfile << "EXTRACT_PACKAGE        = YES";
      }
      else if (linetext.compare("EXTRACT_STATIC         = NO") == 0) {
        doxyfile << "EXTRACT_STATIC         = YES";
      }
      else if (linetext.compare("WARN_NO_PARAMDOC       = NO") == 0) {
        doxyfile << "WARN_NO_PARAMDOC       = YES\n";
      }
      else if (linetext.compare("WARN_AS_ERROR          = NO") == 0) {
        doxyfile << "WARN_AS_ERROR          = YES\n";
      }
      else if (linetext.compare("SOURCE_BROWSER         = NO") == 0) {
        doxyfile << "SOURCE_BROWSER         = YES";
      }
      else if (linetext.compare("TAB_SIZE               = 4") == 0) {
        doxyfile << "TAB_SIZE               = 2\n";
      }
      else if (linetext.compare("INLINE_SOURCES         = NO") == 0) {
        doxyfile << "INLINE_SOURCES         = YES\n";
      }
      else if (linetext.compare("STRIP_CODE_COMMENTS    = YES") == 0) {
        doxyfile << "STRIP_CODE_COMMENTS    = NO";
      }
      else if (linetext.compare("REFERENCED_BY_RELATION = NO") == 0) {
        doxyfile << "REFERENCED_BY_RELATION = YES";
      }
      else if (linetext.compare("REFERENCES_RELATION    = NO") == 0) {
        doxyfile << "REFERENCES_RELATION    = YES\n";
      }
      else if (linetext.compare("HTML_TIMESTAMP         = NO") == 0) {
        doxyfile << "HTML_TIMESTAMP         = YES\n";
      }
      else if (linetext.compare("HTML_DYNAMIC_SECTIONS  = NO") == 0) {
        doxyfile << "HTML_DYNAMIC_SECTIONS  = YES\n";
      }
      else if (linetext.compare("GENERATE_TREEVIEW      = NO") == 0) {
        doxyfile << "GENERATE_TREEVIEW      = YES\n";
      }
      else if (linetext.compare("COMPACT_LATEX          = NO") == 0) {
        doxyfile << "COMPACT_LATEX          = YES\n";
      }
      else if (linetext.compare("PAPER_TYPE             = a4") == 0) {
        doxyfile << "PAPER_TYPE             = letter\n";
      }
      else
      {
        doxyfile << linetext << "\n";
      }
      
    }
    doxyfile.close();
    doxyin.close();
    system("rm Doxyfile.*");
    return OK;
  }
}