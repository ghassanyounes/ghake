#include <iostream>       //! cout, cin, endl, string
#include <fstream>        //! ofstream, ifstream, .open, .is_open(), .close()
#include <cstdlib>        //! system
#include "functions.h"    //! doxypresent, gendoxy, editdoxy, inject, STATUS

namespace doxygen 
{
  bool doxypresent(void)
  {
    bool opclo;
    std::ifstream Doxyfile;  
    Doxyfile.open("Doxyfile");
    opclo = Doxyfile.is_open();
    Doxyfile.close();
    return opclo;
  }

  STATUS gendoxy(void)
  {
    system("touch doxyversion.txt; doxygen --version >> doxyversion.txt");
    std::string doxvers;
    std::ifstream version;
    version.open ("doxyversion.txt");
    getline(version,doxvers);
    version.close();
    system("rm doxyversion.txt");
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
    std::string linetext;
    std::ifstream doxyin;
    std::ofstream doxyfile;
    system("mv Doxyfile Doxyfile.old");
    doxyin.open("Doxyfile.old");
    doxyfile.open ("Doxyfile");

    if (doxyfile.is_open() == 0)
    {
      return FILE_ERR;
    }

    while(getline(doxyin,linetext))
    {
      if (linetext.compare("PROJECT_NAME           = \"My Project\"") == 0)
      {
        doxyfile << "PROJECT_NAME           = \"" << pinfo.project_name << "\"\n";
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
  
  STATUS inject(const info pinfo)
  {
    std::string textin;
    std::ofstream makefile;
    const char* makefname = pinfo.makefile.c_str();

    textin = "doxygen :\n\t-@$(ERASE) html/\n\t-@$(ERASE) latex/\n\t( cat Doxyfile ; echo \"EXTRACT_ALL=YES\" ) | doxygen -\n\t( cat Doxyfile ; echo \"EXTRACT_ALL=NO\" ) | doxygen -\n\n";

    textin += "doxyclean :\n";
	  textin += "\t-@$(ERASE) Doxyfile\n";
	  textin += "\t-@$(ERASE) html/\n";
	  textin += "\t-@$(ERASE) latex/\n\n";
    makefile.open(makefname, std::ios::app);
    if (makefile.is_open() == 0)
    {
      return FILE_ERR;
    }
    
    makefile << textin;
    makefile.close();
    return OK;
  }

}
