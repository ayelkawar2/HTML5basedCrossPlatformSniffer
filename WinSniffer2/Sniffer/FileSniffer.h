////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSniffer.h  - Provides functions to sniff for new files and directories not found in previous scans.	  //
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
* This class provides functions to sniff for new files and directories not found in previous scans. On first run, this class will create
* a new database of files and folders found on the path specified by the user. It does this by checking if the database.xml file
* exists or not. If the database is found, then each file and folder found on the user specified path is checked against this database.
* All the files and folders not found in the database are reported as new files and folders. User is provided with an option to add
* these files and folders to the database or ignore them. 
* This class can also be set to show only the summary statistics by setting an option. It can also show previous analysis results without
* any need to run a new scan.
*
* Public Interface :
* ==================
* std::set<std::string> sniffFiles(std::string);	//Sniffs for new files on the path specified by the user
* void PrintResult();								//Prints previous analysis results
* void OnlySummary();								//Sets variable to show only summary statistics
*
*
* Build Process:
* ==============
* msbuild FileSniffer.sln
* or
* devenv FileSniffer.sln/ rebuild
* 
* Requirement Files/ Headers:
* ==========================
* NavWrapper.h
* XmlReader.h
* XmlWriter.h
* Fileinfo.h
* StringConversion.h
* Nav.h
* WinTools.h
* 
* Maintenance History:
* ====================
* ver 1.0 : 18 Feb 2012
* - first release
*/

#ifndef FILESNIFFER_H
#define FILESNIFFER_H
#include<string>
#include<list>
#include<set>
class FileSniffer
{
private:
	bool isInExcluded(std::string);
	std::string* loadFile(std::string);
	bool fexists(const char *);
	int createDatabase(std::set<std::string>&);
	void loadDatabase();
	void findNewFiles(std::set<std::string>&);
	void addToDatabase();
	void printList(std::set<std::string>);
	void StoreResult();

	bool summary;
	std::string resultFilePath;
	std::string* databaseFile;
	std::string* excludeFile;
	std::set<std::string> fileset;
	std::set<std::string> newfilesList;
	bool excludeFileExists;
	std::string excludeFilePath;
	std::string databaseFilePath;

public:
	void sniffFiles(std::string);
	void PrintResult();
	std::set<std::string> getLastResult();
	std::set<std::string> getFiles();
	void saveFiles();
	void OnlySummary();
	void Clear();
	FileSniffer();
	~FileSniffer();
	

};


#endif