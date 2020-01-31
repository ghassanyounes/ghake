/**
 * @file    main.cpp 
 * @author  Ghassan Younes
 * @date    January 27th 2020
 * 
 * @brief
 *  This program will autogenerate a makefile for your code, with custom CLI 
 *  arguments and a choice of memory checkers.
 * 
 */

#include <iostream>       //! cout, cin, endl
#include <cstdlib>
#include <fstream>        //! File IO
#include "functions.h"    /* helper functions 
                           * (compiling, memory checks, doxygen, diff) */ 

int main(int argc, const char* argv[])
{
  using std::cout;
  using std::cin;
  using std::endl;

  if (argc == 2)
  {
    std::string help = "help";
    if (help.compare(argv[1]) == 0)
    {
      std::cout << "Valid entries are:" <<  endl
                << "For compiler:        cc, cl, clang, gcc, & g++" << endl
                << "For memory debugger: drmemory & valgrind" << endl
                << "Project name should be in \"double quotation marks\"" 
                << endl
                << "Type \"yes\" to append makefile with \'.COMP\', where " 
                << "COMP is .unx, .wcl, .gnu, and .clg, depending on the " 
                << "compiler you choose."
                << endl; 
     return 0;
    }
    else 
    {
      return 0;
    }
  }
  else if (argc != 7)
  {
    cout  << "Please enter the compiler, memory debugger, \"Project Name\", " 
          << "name of driver (\"driver\" or \"main\"), & whether to enable" 
          << "makefile extensions \n"
          << " Run \'ghake help\', \'ghake -h\', or \'ghake --help\' "
          << "for valid entries." << endl
          << "Exiting..." << endl;
    return 0;
  }

  cout  << "Ghake by Ghassan Younes (www.ghassanyounes.com)" << endl 
        << "Attention: This program will create a makefile calling ALL .c/.cpp "
        << "files in the current directory. " << endl << endl;

  std::string makefname = "makefile";

  std::cout << "You selected: " << std::endl
            << "Compiler:           " << argv[1] << std::endl
            << "Memory Debugger:    " << argv[2] << std::endl
            << "Project name:       " << argv[3] << std::endl
            << "Driver file name:   " << argv[4] << std::endl
            << "File extension:     " << argv[5] << std::endl
            << "Makefile extension? " << argv[6] << std::endl;

  if (doxygen::doxypresent())
  {
    cout  << "Warning: Doxygen file present. I will not generate a new one!" 
          << endl;
  } 
  else 
  {
    doxygen::gendoxy();
    doxygen::editdoxy(argv[3]);
  }
  compilation::COMPIL cc = compilation::compiler(argv[1]);

  std::string yes = "yes";

  if (yes.compare(argv[6])==0)
  {
    switch (cc)
    {
    case  compilation::GCC:
      makefname += ".gnu";
      break;
    
    case  compilation::GPP:
      makefname += ".gnu";
      break;
    
    case compilation::MICROSOFT:
      makefname += ".wcl";
      break;

    case compilation::CLANG:
      makefname += ".clg";
      break;

    case compilation::UNIX:
      makefname += ".unx";
      break;

    case compilation::ERR:
      makefname += ".ERROR";
      break;

    default:
      break;
    }
  }

  std::string cliargs = compilation::compilargs(cc);

  // INJECTION INTO MAKEFILE BEGINS HERE  

  STATUS macrostat = basemake::macros(makefname, argv[4]);

  if (macrostat == FILE_ERR || macrostat == FAILED)
  {
    cout  << "Macro injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 0; 
  }

  STATUS compstatus = compilation::inject(cc, cliargs, makefname);
  if (compstatus == FILE_ERR || compstatus == FAILED)
  {
    cout  << "Compiler injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 0;
  }

  memorydebug::MMCHK md = memorydebug::memdebug(argv[2]);
  std::string mdargs = memorydebug::memdargs(md);

  STATUS targetstat = basemake::targets(makefname);

  if (targetstat == FILE_ERR || targetstat == FAILED)
  {
    cout  << "Macro injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 0; 
  }

  STATUS dotostat = basemake::dotorules(makefname, cc, argv[5]);

  if (dotostat == FILE_ERR || dotostat == FAILED)
  {
    cout  << "File target injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 0; 
  }

  STATUS doxystatus = doxygen::inject(makefname); 

  if (doxystatus == FILE_ERR || doxystatus == FAILED)
  {
    cout  << "Doxygen command injection into makefile failed. Please make sure "
          << "that the makefile exists and is writeable." << endl ;
    return 0;
  }

  cout  << "\nTasks completed. You may want to configure an \'ignore list\' " 
        << "for your memory debugger to ignore false positives." << endl 
        << endl
        << "Thank you for using Ghake!\n\n";

  return 0;
}
