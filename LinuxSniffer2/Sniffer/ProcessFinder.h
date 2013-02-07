////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProcessFinder.h  - Lists currently running processes								    					  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #2, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// Source:		http://msdn.microsoft.com/en-us/library/windows/desktop/ms682623%28v=vs.85%29.aspx			  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* Generates a list of running processes. This list is stored in a map with key as the process name and value the count
* of number times the same process was found. If a process could not be opened because the user program doesn't have
* permission to open it, it is stored as unknown process.
*
* Public Interface :
* ==================
* ProcessFinder pfinder;		//create new process finder
* std::map<std::string,int> procs = pfinder.getProcesses();	//get list of running processes
*
* Build Process:
* ==============
* g++ -o ProcessFinder ProcessFinder.cpp
*
* Requirement Files/ Headers:
* ==========================
* none
*
* Maintenance History:
* ====================
* ver 1.0 : 1 May 2012
* - first release
*/

#ifndef PROCESSFINDER_H
#define PROCESSFINDER_H

#include<map>
#include<string>

class ProcessFinder
{
public:
	std::map<std::string,int> getProcesses();
};

#endif /* PROCESSFINDER_H */
