/**
 * @file    functions.h 
 * @author  Ghassan Younes
 * @date    February 8th 2020
 * @par     email: ghassan\@ghassanyounes.com
 * 
 * @brief
 *  This file contains the function declarations for the autogen makefiles.
 * 
 */

#include <iostream> /// string

/**
 * 
 * @brief
 *  Outputs the help menu (until I can make a manpage)
 * 
 */
void help();

/**
 * 
 * @brief
 *  Generates output file directories
 * 
 */
void gendirs();

/**
 * 
 * @brief
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
  /**
  * 
  * @brief
  *  Which compiler is being used
  * 
  */
  enum COMPIL
  {
  CC, 
  CL,
  CLANG,
  CLANGPP,
  GCC,
  GPP
  };

  /**
   *
   * @brief 
   *  Compiler debugger info struct
   * 
   */
  typedef struct compinfo{
    compinfo( COMPIL compil,
              std::string descr,
              std::string name,
              std::string args);
    COMPIL comptype;            ///< Which compiler to use
    std::string description;    ///< Description of compiler for output
    std::string compilername;   ///< String containing name of compiler command
    std::string compilargs;     ///< Compiler arguments/command-line flags
  } compinfo;

}

namespace memorydebug
{
  /**
   * 
   * @brief
   *  Which memory debugger is being used
   * 
   */
  enum MMCHK
  {
    VALG,
    DRMEM
  };


  /**
   *
   * @brief 
   *  Memory debugger info struct
   * 
   */
  typedef struct mdinfo{
    mdinfo( MMCHK type,
            std::string name,
            std::string args,
            std::string supp,
            std::string supp_file
    );
    MMCHK debugtype;            ///< Which memory debugger is requested
    std::string debugname;      ///< String containing name of memory debugger
    std::string debugargs;      ///< Memory debugger command line args
    std::string false_supp;     ///< Location of false.supp file (or equivalent)
    std::string false_supp_file;///< Name of false.supp file (or equivalent)
  } mdinfo;
}

/**
 *
 * @brief 
 *  Project information struct
 * 
 */
typedef class info{
  public:
  info( std::string name = "Unnamed_Project", 
        std::string args = " ",
        std::string makefile = "makefile", 
        std::string filex = "cpp", 
        std::string diff = " ",
        compilation::COMPIL compiler = compilation::GPP,
        memorydebug::MMCHK debugger = memorydebug::VALG);
  
  /// Settor functions
  void ansi();
  void effective();
  void set_compiler(compilation::COMPIL compiler);
  void set_debugger(memorydebug::MMCHK debugger);
  void set_filex(std::string);
  void set_name(std::string);
  void set_diff(std::string);
  void set_runargs(std::string);
  void set_false_supp(std::string);
  void set_makex();
  void inject();
  void out();

  ///Gettor functions
  std::string get_diff() const;
  std::string get_pname() const;
  std::string get_filex() const;
  std::string get_compname() const;
  compilation::COMPIL get_comptype() const;

  private:
  bool is_ansi = false;             ///< --ansi flag or equivalent for compilers
  bool is_effective = false;        ///< -Weffc++ flag for clang++ and g++
  std::string project_name;         ///< Name of project
  std::string makefile_name;        ///< Name of makefile
  std::string filext;               ///< File extensions to use
  std::string diff_file;            ///< Name of file to diff against
  std::string runargs;              ///< Runtime arguments for built executable
  compilation::compinfo compinfo;   ///< Compiler info struct
  memorydebug::mdinfo mdinfo;       ///< Memory debugger info struct
} info;

namespace doxygen {

  /**
   * 
   * @brief
   *  Checks if Doxyfile is present
   * 
   * @return
   *  Returns if Doxyfile is present
   * 
   */
        bool doxypresent(void);
  /**
   * 
   * @brief
   *  Generates the Doxyfile
   * 
   * @return
   *  Returns the status of the function
   * 
   */
          STATUS gendoxy(void);
  
  /**
   * 
   * @brief
   *  Edits the Doxyfile, modifying it to the CS170 standards 
   *  (but keeping LaTeX)
   * 
   * @param pinfo
   *  Information struct containing details of the program
   * 
   * @return
   *  Returns the status of the function
   * 
   */
         STATUS editdoxy(const info pinfo);
}

namespace compilation
{
  /**
   * 
   * @brief
   *  This function generates the file dependencies for the makefile
   * 
   * @param pinfo
   *  Reference to class type info containing details of the program
   * 
   * @return
   *  Status of file I/O
   * 
   */
  STATUS generatedeps(const info &pinfo);
}
