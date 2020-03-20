/**
 * @file    main.cpp
 * @author  Ghassan Younes
 * @date    March 19th 2020
 * @par     email: ghassan\@ghassanyounes.com
 * 
 * @brief
 *  This file contains main() function for the memorydebug namespace
 * 
 */
#include <iostream>     /// cout, endl, string
#include <getopt.h>     /// getopt_long for runtime arguments
#include "functions.h"  /** Namespace/Class | Functions
                         *  --------------- | -----------------------------------
                         *  class info      |  ansi, set_compiler, set_debugger, set_filex, set_name, set_diff, set_runargs, set_false_supp, set_makex, inject, out, get_pname, get_filex, get_compname, get_comptype
                         *  compilation     |  compinfo, COMPIL 
                         *  doxygen         |  doxypresent, gendoxy, editdoxy
                         *  memorydebug     |  MMCHK, mdinfo
                         *  global          |  info, STATUS, help, gendirs
                         */

/**
 * 
 * @brief
 *  Main function. Calls all the other functions
 * 
 * @param argc
 *  Number of runtime arguments entered
 * 
 * @param argv
 *  Array of all the runtime arguments entered
 * 
 * @return 
 *  0 == success; 1+ == fail
 * 
 */
int main (int argc, char **argv)
{
  using std::cout;
  using std::endl;

  int runargs;                      /// Runtime arguments for getopt_long
  int verbose_flag = false;         /// Verbose Flag
  int makefile_ext = false;         /// Makefile Extension flag
  int compiler = compilation::GPP;  /// Compiler flag default g++
  int memdbug = memorydebug::VALG;  /// Memory Debugger flag default valgrind
  info pinfo;                       /// Class of type info; Stores info of everything

  
  while (1)
  {
    static struct option long_options[] =
    {
    // These options set a flag.
      {"verbose",  no_argument,        &verbose_flag, true                },
      {"quiet",    no_argument,        &verbose_flag, false               },

      {"makext",   no_argument,        &makefile_ext, true                },

      {"cc",       no_argument,        &compiler,     compilation::CC     },
      {"cl",       no_argument,        &compiler,     compilation::CL     },
      {"clang",    no_argument,        &compiler,     compilation::CLANG  },
      {"clang++",  no_argument,        &compiler,     compilation::CLANGPP},
      {"gcc",      no_argument,        &compiler,     compilation::GCC    },
      {"g++",      no_argument,        &compiler,     compilation::GPP    },

      {"valgrind", no_argument,        &memdbug,      memorydebug::VALG   },
      {"drmemory", no_argument,        &memdbug,      memorydebug::DRMEM  },

    // These options don’t set a flag. We distinguish them by their indices.
      {"ansi",     no_argument,        0,             'a'                 },
      {"Weffc++",  no_argument,        0,             'f'                 },
      {"help",     no_argument,        0,             'h'                 },
      {"diff",     required_argument,  0,             'd'                 },
      {"name",     required_argument,  0,             'n'                 },
      {"ext",      required_argument,  0,             'e'                 },
      {"mdsupp",   required_argument,  0,             's'                 },
      {"run_args", required_argument,  0,             'r'                 },
      {0, 0, 0, 0}
    };
    int option_index = 0; /// getopt_long stores the option index here

    runargs = getopt_long (argc, argv, "abc:d:f:", long_options, &option_index);

  // Detect the end of the options.
    if (runargs == -1)
      break;

    switch (runargs)
      {
      case 'h':
        help();
        return 0;
        break;

      case 'f':
        pinfo.effective();
        break;

      case 'a':
        pinfo.ansi();
        break;

      case 'n':
        pinfo.set_name(optarg);
        break;

      case 'd':
        //Debugging stuff
        //cout << "diff file is: " << optarg << endl;
        pinfo.set_diff(optarg);
        //cout << "diff file set to: " << pinfo.get_diff() << endl;
        break;

      case 'e':
        pinfo.set_filex(optarg);
        break;

      case 'r':
        pinfo.set_runargs(optarg);
        break;

      case 's':
        pinfo.set_false_supp(optarg);
      default:
        break;
      }
  }
  
  pinfo.set_compiler((compilation::COMPIL)compiler);
  pinfo.set_debugger((memorydebug::MMCHK)memdbug);

  if (makefile_ext)
  {
    pinfo.set_makex();
  }

  if(doxygen::doxypresent())
  {
    cout << "Doxyfile present, I will not generate a new file" << endl;
  } 
  else
  {
    switch (doxygen::gendoxy())
    {
      case FILE_ERR:
        cout << "Could not create Doxyfile. Is the directory writeable?";
        return 1;
        break;

      case FAILED: 
        cout << "Could not create Doxyfile. Do you have the right version installed?";
        return 1;
        break;

      case OK: 
        if (verbose_flag)
        {
          cout << "Doxyfile generated" << endl;
        }
        break;

      default:
        cout << "Could not create Doxyfile. Is the directory writeable?";
        return 1;
        break;
    }
    switch (doxygen::editdoxy(pinfo))
    {
      case FILE_ERR:
        cout << "Could not edit Doxyfile. Did you delete it?";
        return 1;
        break;

      case FAILED: 
        cout << "Could not create Doxyfile. Do you have the right version installed?";
        return 1;
        break;

      case OK: 
        if (verbose_flag)
        {
          cout << "Doxyfile modified" << endl;
        }
        break;

      default:
        cout << "Could not edit Doxyfile. Did you delete it?";
        return 1;
        break;
    }
  }

  gendirs();
  pinfo.inject();

  // Output time
  // If Quiet Mode is off
  if (verbose_flag)
  { 
    cout << "     Verbose mode: On" << endl;
    if (makefile_ext)
    {
      cout << "     Makefile ext: On" << endl;
    }
    else
    {
      cout << "     Makefile ext: Off" << endl;
    }

    cout << pinfo << endl;
  }
  else
  {
    cout << "Quiet mode on" << endl;
  }

  // Print any remaining command line arguments (not options). 
  if (optind < argc)
    {
      cout << endl << "Invalid arguments: " << endl;
      while (optind < argc)
        cout << "  -> " << argv[optind++] << endl << endl;
    }

  cout  << endl 
        << "Makefile generation complete! Thank you for using ghake." << endl;

  return 0;
}