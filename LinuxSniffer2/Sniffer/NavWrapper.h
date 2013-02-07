////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NavWrapper.h  - Provides Wrapper class for Nav.h.						    							  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #1, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* Consist of class NavWrapper which act as a wrapper class for Nav. It consists of 1 function which takes folder path as input and
* return a set of folder and file paths found on that path.
*
* Public Interface :
* ==================
* std::set<std::string> getFileDirList(std::string path);  // Returns set of folder and file paths found on the specifed path taken as input
*
* Build Process:
* ==============
* g++ -o NavWrapper NavWrapper.cpp Nav.cpp
*
* Requirement Files/ Headers:
* ==========================
* Nav.h
*
* Maintenance History:
* ====================
* ver 1.0 : 18 Feb 2012
* - first release
*/

#ifndef NAVWRAPPER_H
#define NAVWRAPPER_H
#include<set>
#include<string>
class NavWrapper
{
public:
        std::set<std::string> getFileDirList(std::string path);
};


#endif
