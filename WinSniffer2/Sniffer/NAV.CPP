///////////////////////////////////////////////////////////////////
//  Nav.cpp - Recursively walk a directory tree starting at a    //
//  ver 2.0   specified path                                     //
//                                                               //
//  Language:      Visual C++, Visual Studio 2010, SP1           //
//  Platform:      Toshiba Portege R705, Win 7 Home Premium, SP1 //
//  Application:   Summer Projects, 2011                         //
//  Author:        Jim Fawcett, Syracuse University CST 4-187    //
//                 (315) 443-3948, jfawcett@twcny.rr.com         //
///////////////////////////////////////////////////////////////////

//----< test stub >--------------------------------------------
//
//  - Recursively walk directory subtree pointed to
//    by the last command line argument.
//  - use default navig processing each time a directory
//    or file is encountered
//  - replace default processing with user defined processing
//    and repeat
//
#ifdef TEST_NAV

#include <iostream>     // standard output for test
#include <iomanip>      // output formatting
#include <vector>
#include "nav.h"
#include "conio.h"

using namespace Win32Tools;

//----< wait for key press: requires conio >-------------------

#pragma warning(disable:4996)  // remove deprecated getch() warning

void waitForKeyPress()
{
  std::cout << "\n  Press key to exit: ";
  getch();
}
void main(int argc, char *argv[]) {

  std::cout << "\n  Testing Directory Navigator "
       << "\n =============================\n";

  if(argc == 1) {
    std::cout << "\n  please enter starting path\n";
    waitForKeyPress();
    return;
  }

  try {
    // create default processing object and start navigation

    std::cout << "\n  testing default dir/file processing: "
         << "\n --------------------------------------\n";

    std::cout << "\n  starting path = " << fileInfo::getPath() << "\n";

    defproc dp;
    navig nav(dp);
    nav.walk(argv[argc-1],"*.*");

    std::cout << "\n  ending path = " << fileInfo::getPath() << "\n\n";

  // User defined processing definded here.  Note that
  // local classes can be defined as long as all members
  // are inline.  Otherwise, just declare and define above
  // main.
  //
  // These do nothing but prepend each output with some
  // "-" characters to show that user defined processing
  // is actually being used.  In a real application user 
  // defined processing will certainly be quite different
  // from the default
  //
    class userProc : public defproc
    {
    public:
      virtual void fileProc(const fileInfo &fi) {
        fileInfo newfi = fi;
        newfi.showDate(false);
        newfi.showData(std::cout); 
      }
      virtual void dirsProc(const std::string &dir) {
        std::cout << "\n  " << dir.c_str() << std::endl;
      }
    };

  // restart with user defined processing

    std::cout << "\n  testing modified dir/file processing: "
              << "\n ---------------------------------------\n";

    std::cout << "\n  starting path = " << fileInfo::getPath() << "\n";

    userProc udp;
    navig newNav(udp);
    newNav.walk(argv[argc-1],"*.*");
    std::cout << "\n  ending path = " << newNav.getPath();
    std::cout << "\n\n";

    std::cout << "\n  Testing wnavig and wdefproc";
    std::cout << "\n -----------------------------";

    class wuserProc : public wdefproc
    {
    public:
      virtual void fileProc(const wfileInfo &fi) {
        wfileInfo newfi = fi;
        newfi.showDate(false);
        newfi.showData(std::wcout); 
      }
      virtual void dirsProc(const std::wstring &dir) {
        std::wcout << L"\n  " << dir.c_str() << std::endl;
      }
    };

    std::wcout << L"\n  starting path = " << wfileInfo::getPath() << "\n";

    wuserProc wudp;
    wnavig newerNav(wudp);
    newerNav.walk(Convert::ToWstring(argv[argc-1]),L"*.*");
    std::wcout << L"\n  ending path = " << newerNav.getPath();
    std::cout << "\n\n";

    waitForKeyPress();
  }
  catch(std::exception& ex)
  {
    std::cout << ex.what();
  }
}

#endif
