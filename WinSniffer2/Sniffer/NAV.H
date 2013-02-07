#ifndef NAV_H
#define NAV_H
///////////////////////////////////////////////////////////////////
//  Nav.h    --    Recursively walk a directory tree             //
//  ver 2.0        starting at a specified path                  //
//                                                               //
//  Language:      Visual C++, Visual Studio 2010, SP1           //
//  Platform:      Toshiba Portege R705, Win 7 Home Premium, SP1 //
//  Application:   Summer Projects, 2011                         //
//  Author:        Jim Fawcett, Syracuse University CST 4-187    //
//                 (315) 443-3948, jfawcett@twcny.rr.com         //
///////////////////////////////////////////////////////////////////
/*
    class Navig Operations:
    -----------------------
    An object of the navig class walks a directory (sub)tree,
    processing files and directories encountered along the walk.
    Root of the walk is passed to member function start.  The 
    root can be any valid path including "." and ".."

      userProc udp;      construct a user defined proc object
      navig nav(udp);    construct a navigator object
      nav.walk(root);   start a recursive walk at root

    When the walk is completed the starting directory will be
    restored.  Note that you will have to define the userProc
    class.  See the test stub in nav.cpp for an example of
    how to do that.
*/
///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required:                                          //
//    nav.h, nav.cpp, fileInfo.h, fileInfo.cpp,              //
//    WinTools.h, WinTools.cpp,                              //
//    StringConversion.h, StringConversion.cpp               //
//                                                           //
//  Building with Visual C++ , ver 7.1, from command line:   //
//    cl /GX /DTEST_NAV nav.cpp fileInfo.cpp Wintools.cpp \  //
//       StringConversion.cpp                                //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 2.0 : 03 Jul 2011
    - converted to parameterized classes Navig<stdStr> and 
      defProc<stdStr>.
    - many changes throughout code
    ver 1.9 : 14 Feb 2011
    - fixed build errors reported by Shawn Mueller
    - made Navig::getPath an inline function to avoid multiple
      definitions of this function at link time.
    - getPath return type changed to stdStr
    - included fileInfo header
    ver 1.8 : 18 Jan 2009
    - fixed bug in navig::walk(path,pattern)
    - cosmetic fixes to manual page
    ver 1.7 : 13 Jan 2009
    - added namespace Win32Tools
    ver 1.6 : 19 Jan 2006
    - added getPath()
    ver 1.5 : 14 Mar 2005
    - added using relationship arrow to diagram below.
    ver 1.4 : 17 Jan 2005
    - simplified processing in walk function
    ver 1.3 : 30 Jan 2000
    - incorporated use of fileInfo objects to simplify
      navig processing
    - changed default and user defined processing objects
      to eliminate requirement for them to be allocated
      on the heap, e.g., dynamically
    ver 1.2 : 27 Apr 1999
    - cosmetic changes to these pages
    ver 1.1 : 22 Apr 1999
    - cosmetic changes to walk and start functions
    ver 1.0 : 30 Jan 1998
    - first release


    Design Notes:
    =============
    The navig object owns a fileInfo object that provides all the
    intelligence about extracting file information from a directory.
    Navig's job is simply to do a depth-first traversal of the dir
    structure rooted at the path provided its start function.

                                         The navig object also contains
     +-------+             +---------+   a reference to a base class
     |       |-----------> | defProc |   defProc object that defines
     | navig |             +---------+   default processing of file
     |       |<>-+          |  |         and directory information.
     +-------+   |      +---+ / \        This reference is obtained
                 |      |      |         by passing one when the object
            +--------+  | +----------+   is constructed.
            |fileInfo|<-+ | userProc |
            +--------+    +----------+   The user may override that
                                         default processing by defining
                                         a derived userProc class with
                                         the desired processing and
                                         passing that instead.

    An example of how to override the default processing by defining
    a userProc class is presented in the test stub.  That should be
    enough to show you how to implement your own processing.

*/


///////////////////////////////////////////////////////////////
//                         Declarations                      //
///////////////////////////////////////////////////////////////


#include <string>
#include <windows.h>
#include "StringConversion.h"
#include "Fileinfo.h"
#include "WinTools.h"

///////////////////////////////////////////////////////////////
// default file and directory processing
//
namespace Win32Tools
{
  template <typename stdStr>
  class DefProc 
  {
  public:
    virtual ~DefProc() { }
    virtual void dirsProc(const stdStr& dir);
    virtual void fileProc(const FileInfo<stdStr>& fi);
  };

  typedef DefProc<std::string> defproc;
  typedef DefProc<std::wstring> wdefproc;

  //----< default dir name display function >--------------------

  template <>
  void DefProc<std::string>::dirsProc(const std::string& dir) 
  {
    std::cout << "\n  " << dir.c_str() << std::endl;
  }

  template <>
  void DefProc<std::wstring>::dirsProc(const std::wstring& dir) 
  {
    std::wcout << L"\n  " << dir.c_str() << std::endl;
  }

  //----< default file data display function >-------------------

  template <>
  void DefProc<std::string>::fileProc(const FileInfo<std::string>& fi) 
  {
    if(!fi.isDirectory())
      fi.showData(std::cout); 
  }

  template <>
  void DefProc<std::wstring>::fileProc(const FileInfo<std::wstring>& fi) 
  {
    if(!fi.isDirectory())
      fi.showData(std::wcout); 
  }

  ///////////////////////////////////////////////////////////////
  // directory navigator

  template <typename stdStr>
  class Navig 
  {
  public:

    Navig(DefProc<stdStr> &dp);         // accept user defined proc
    ~Navig();                           // restore user's dir
    stdStr getPath();                   // get current path
    void walk(const stdStr &dir, const stdStr& fileMask);
                                        // start dir Navigation
  private:
    static const int PathBufferSize = 256;
    stdStr userDir_;                     // user's working directory
    DefProc<stdStr> &dp_;                // provides extendable processing
                                         //   of file and directory names
  };

  typedef Navig<std::string> navig;
  typedef Navig<std::wstring> wnavig;

  //----< get current path >-----------------------------------------

  template <typename stdStr>
  inline stdStr Navig<stdStr>::getPath() 
  { 
    return Win32Tools::FileInfo<stdStr>::getPath(); 
  }

  ///////////////////////////////////////////////////////////////
  // Note:
  //   The fact that Navig holds a reference member implies that copy
  //   operations will fail to compile.
  //
  //----< save user's working directory >------------------------

  template <>
  Navig<std::string>::Navig(DefProc<std::string> &DP) : dp_(DP) 
  {
  // save user's working directory
    char buffer[PathBufferSize];
    ::GetCurrentDirectoryA( PathBufferSize, buffer);
    userDir_ = buffer;
  }

  template <>
  Navig<std::wstring>::Navig(DefProc<std::wstring> &DP) : dp_(DP) 
  {
  // save user's working directory
    wchar_t buffer[PathBufferSize];
    ::GetCurrentDirectoryW( PathBufferSize, buffer);
    userDir_ = buffer;
  }

  //----< restore user's working directory >---------------------

  template <>
  Navig<std::string>::~Navig() { ::SetCurrentDirectoryA(userDir_.c_str()); }

  template <>
  Navig<std::wstring>::~Navig() { ::SetCurrentDirectoryW(userDir_.c_str()); }

  //----< walk directory tree rooted at dir >--------------------

  template <>
  void Navig<std::string>::walk(const std::string& dir, const std::string& fileMask) 
  {
    std::string path = Path<std::string>::getFullPath(dir);
    dp_.dirsProc(path);
    std::vector<std::string> dirs;
    std::vector<FileInfo<std::string>> fis;
    fis = Directory<std::string>::GetFileInfos(path,fileMask);
    for(size_t i=0; i<fis.size(); ++i)
    {
      dp_.fileProc(fis[i]);
    }

    dirs = Directory<std::string>::GetDirectories(path,"*.*");
    for(size_t i=0; i<dirs.size(); ++i)
      walk(dirs[i],fileMask);
  }

  //----< walk directory tree rooted at dir >--------------------

  template <>
  void Navig<std::wstring>::walk(const std::wstring& dir, const std::wstring& fileMask) 
  {
    std::wstring path = Path<std::wstring>::getFullPath(dir);
    dp_.dirsProc(path);
    std::vector<std::wstring> dirs;
    std::vector<FileInfo<std::wstring>> fis;
    fis = Directory<std::wstring>::GetFileInfos(path,fileMask);
    for(size_t i=0; i<fis.size(); ++i)
    {
      dp_.fileProc(fis[i]);
    }

    dirs = Directory<std::wstring>::GetDirectories(path,L"*.*");
    for(size_t i=0; i<dirs.size(); ++i)
      walk(dirs[i],fileMask);
  }
}
#endif
