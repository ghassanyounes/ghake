/*!
 * \file    main.cpp 
 * \author  Ghassan Younes
 * \date    January 27th 2020
 * 
 * \brief
 *  This program will autogenerate a makefile for your code, with custom CLI 
 *  arguments and a choice of memory checkers.
 * 
 */

#include <iostream>       //! cout, cin, endl, string
#include <fstream>        //! ofstream, ifstream, .open, .is_open(), .close()
#include <cstdlib>        //! system
#include "functions.h"    /*! Namespace       Functions
                           *  ==================================================
                           *  basemake    ==> macros, targets, baserules, 
                           *                  dotorules, generatedeps 
                           *  compilation ==> compiler, compilargs, inject, 
                           *                  COMPIL 
                           *  doxygen     ==> doxypresent, gendoxy, editdoxy, 
                           *                  inject
                           *  memorydebug ==> debug, memdargs, inject, MMCHK 
                           *  global      ==> info, STATUS
                           */

/*!
 * 
 * \param argc
 *  Number of command-line swithces activated
 * 
 * \param argv
 *  Array of the commands input
 * 
 * \return
 *  Int 0
 * 
 */
int main(int argc, const char* argv[])
{
  using std::cout;
  using std::cin;
  using std::endl;

  std::string quieton = "on";
  std::string quietoff = "off";
  std::string help = "help";
  std::string yes = "yes";
  std::string makedirs;

  info pinfo;
  pinfo.makefile = "makefile";

  if (argc == 2)
  {
    if (help.compare(argv[1]) == 0)
    {
      std::cout << "Valid entries are:" <<  endl
                << "For compiler:        cc, cl, clang, clang++, gcc, & g++" 
                << endl
                << "For memory debugger: drmemory & valgrind" << endl
                << "Project name should be in \"double quotation marks\"" 
                << endl
                << "Type \"yes\" to append makefile with \'.COMP\', where " 
                << "COMP is .unx, .wcl, .gnu, and .clg, depending on the " 
                << "compiler you choose." 
                << endl
                << "Diff File can be any file in the current directory. " 
                << "Entering \'nodiff\' will not inject a diff command into "
                << "the generated makefile."
                << endl
                << "Quiet mode on will disable the readout of your entries."
                << endl; 
     return 1;
    }
    else 
    {
      return 1;
    }
  }
  else if (argc != 8)
  {
    cout  << "Please enter the compiler, memory debugger, \"Project Name\", " 
          << "Source code file extensions, "
          << " whether to enable makefile extensions, and quiet on/off \n"
          << " Run \'ghake help\', \'ghake -h\', or \'ghake --help\' "
          << "for valid entries." << endl
          << "Exiting..." << endl;
    return 1;
  }

  cout  << "Ghake by Ghassan Younes (www.ghassanyounes.com)" << endl 
        << "Attention: This program will create a makefile calling ALL "
        << "." << argv[4] << " files in the current directory. " << endl 
        << endl;

  if (quieton.compare(argv[7]) != 0 && quietoff.compare(argv[7]) != 0)
  {
    cout << "Invalid identifier for quiet mode. Must be \'onn\' or \'off\'"
         << endl;
    return 1;
  }
  
  if (quieton.compare(argv[7]) != 0)
  {
    std::cout << "You selected: " << std::endl
              << "Compiler:           " << argv[1] << std::endl
              << "Memory Debugger:    " << argv[2] << std::endl
              << "Project name:       " << argv[3] << std::endl
              << "File extension:     " << argv[4] << std::endl
              << "Makefile extension? " << argv[5] << std::endl
              << "Diff File:          " << argv[6] << std::endl
              << "Quiet mode?         " << argv[7] << std::endl;
  }

  pinfo.compinfo.compilername = argv[1];
  pinfo.mdinfo.debugname      = argv[2];
  pinfo.project_name          = argv[3];
  pinfo.filex                 = argv[4];
  pinfo.diff_file             = argv[6];


  makedirs  = "if [ -d build ]; then echo \" \"; \n"; 
  makedirs += "else mkdir build; ";
  makedirs += "mkdir build/gnu; mkdir build/win; "; 
  makedirs += "mkdir build/unx; mkdir build/clg; ";
  makedirs += "fi";
  system(makedirs.c_str());

  if (doxygen::doxypresent())
  {
    cout  << "Warning: Doxygen file present. I will not generate a new one!" 
          << endl;
  } 
  else 
  {
    doxygen::gendoxy();
    doxygen::editdoxy(pinfo);
  }

  pinfo.compinfo.comptype = compilation::compiler(pinfo); // VARNAME WAS cc
  if (yes.compare(argv[5])==0)
  {
    switch (pinfo.compinfo.comptype)
    {
    case  compilation::GCC:
      pinfo.makefile += ".gnu";
      break;
    
    case  compilation::GPP:
      pinfo.makefile += ".gnu";
      break;
    
    case compilation::MICROSOFT:
      pinfo.makefile += ".wcl";
      break;

    case compilation::CLANG:
      pinfo.makefile += ".clg";
      break;

    case compilation::CLANGPP:
      pinfo.makefile += ".clg";
      break;

    case compilation::UNIX:
      pinfo.makefile += ".unx";
      break;

    case compilation::ERR:
      pinfo.makefile += ".ERROR";
      break;

    default:
      break;
    }
  }

  pinfo.compinfo.compilargs = compilation::compilargs(pinfo);
  pinfo.mdinfo.debugtype = memorydebug::memdebug(pinfo);
  pinfo.mdinfo.debugargs = memorydebug::memdargs(pinfo);
  
  // INJECTION INTO MAKEFILE BEGINS HERE  

  STATUS macrostat = basemake::macros(pinfo);
  if (macrostat == FILE_ERR || macrostat == FAILED)
  {
    cout  << "Macro injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1; 
  }

  STATUS compstatus = compilation::inject(pinfo);
  if (compstatus == FILE_ERR || compstatus == FAILED)
  {
    cout  << "Compiler injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1;
  }

  STATUS targetstat = basemake::targets(pinfo);
  if (targetstat == FILE_ERR || targetstat == FAILED)
  {
    cout  << "Macro injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1; 
  }

  STATUS dotostat = basemake::dotorules(pinfo);
  if (dotostat == FILE_ERR || dotostat == FAILED)
  {
    cout  << "File target injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1; 
  }

  STATUS doxystatus = doxygen::inject(pinfo); 
  if (doxystatus == FILE_ERR || doxystatus == FAILED)
  {
    cout  << "Doxygen command injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1;
  }

  STATUS memstat = memorydebug::inject(pinfo);
  if (memstat == FILE_ERR || memstat == FAILED)
  {
    cout  << "Memory Debug command injection into makefile failed. Please make "
          << "sure that the makefile exists and is writeable." << endl ;
    return 1;
  }

  STATUS basetrg = basemake::baserules(pinfo);
  if (basetrg == FILE_ERR || basetrg == FAILED)
  {
    cout  << "Base target injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 1;
  }

  cout  << "\nTasks completed. Please make sure to add \'RUNARGS=\"...\"\' at " 
        << "the end of your make command for any runtime arguments of your "
        << "program. \nYou may also want to configure an \'ignore list\' " 
        << "for your memory debugger to ignore false positives." << endl 
        << endl
        << "Thank you for using Ghake!\n\n";

  return 0;
}
