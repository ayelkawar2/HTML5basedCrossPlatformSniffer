////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProcessSniffer.h  - Sniffs for new processes										    					  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #2, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* Sniffs for new processes. If the database of processes does not exist, it creates a new database. Process Sniffer is 
* divided in 3 parts. First is starting the sniffer. The sniffProcesses function loads the database if it exists and 
* compares it with currently running processes. Second part is retriving the list of new processes. We can use getProcesses()
* function to retrive a map of processes. This map contains the process name as key and the count of number of instances of the
* same processes as the value. Third part is saving this list. The saveProcess() function can be used to save the sniffed
* processes in a database. If database already exists, these new processes are added to the existing list.
*
* Public Interface :
* ==================
* ProcessSniffer psniffer;										//create a new process sniffer
* psniffer.sniffProcesses();									//sniff for new processes
* std::map<std::string,int> pmap = psniffer.getProcesses();		//retrive new processes
* psniffer.saveProcesses();										//save new processes
* 
* Build Process:
* ==============
* msbuild Sniffer.sln
* or
* devenv Sniffer.sln/ rebuild
* 
* Requirement Files/ Headers:
* ==========================
* ProcessFinder.h
* 
* Maintenance History:
* ====================
* ver 1.0 : 1 May 2012
* - first release
*/

#ifndef PROCESSSNIFFER_H
#define PROCESSSNIFFER_H
#include"ProcessFinder.h"

class ProcessSniffer
{
	std::string processFilePath;
	std::map<std::string,int> procList;
	std::map<std::string,int> oldProcs;
	std::string databaseFile;

	bool fexists(const char *nfilename);
	void createDatabase(std::map<std::string,int>,std::string);
	std::string loadFile(std::string filepath);
	void loadDatabase();
	void findNewProcesses(std::map<std::string,int>& plist);
public:
	void sniffProcesses();
	std::map<std::string,int> getProcesses();
	void saveProcesses();
	ProcessSniffer();
	void Clear();
};
#endif