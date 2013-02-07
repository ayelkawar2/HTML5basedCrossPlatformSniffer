////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sniffer.h  - Sniffs for new files, processes and ports							    					  //
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
* The sniffer class provides functions to perform sniffing of new files, processes and ports. It uses the FileSniffer,
* ProcessSniffer and PortSniffer classes for generating this data.
*
* Public Interface :
* ==================
* Sniffer sniffer;														//create new sniffer
* sniffer.startSniffer(std::string);									//start sniffing of files, processes and ports
* std::set<std::string> files = sniffer.getSniffedFiles();				//retrieve sniffed files
* std::map<std::string,int> procs = sniffer.getSniffedProcesses();		//retrive sniffed processes
* std::set<std::string> t4 = sniffer.getTcp4();							//get sniffed tcp4 ports
* std::set<std::string> t6 = sniffer.getTcp6();							//get sniffed tcp6 ports
* std::set<std::string> u4 = sniffer.getUdp4();							//get sniffed udp4 ports
* std::set<std::string> u6 = sniffer.getUdp6();							//get sniffed udp6 ports
* sniffer.saveFiles();													//save sniffed files to database		
* sniffer.saveProcesses();												//save sniffed processes to database
* sniffer.savetcp4Ports();												//save sniffed tcp4 ports to database
* sniffer.saveudp4Ports();												//save sniffed udp4 ports to database
* sniffer.savetcp6Ports();												//save sniffed tcp6 ports to database
* sniffer.saveudp6Ports();												//save sniffed udp6 ports to database
* 
* Build Process:
* ==============
* msbuild Sniffer.sln
* or
* devenv Sniffer.sln/ rebuild
* 
* Requirement Files/ Headers:
* ==========================
* FileSniffer.h
* Nav.h
* NavWrapper.h
* PortsFinder.h
* PortSniffer.h
* ProcessFinder.h
* ProcessSniffer.h
* StringConversion.h
* WinTools.h
* XmlReader.h
* XmlWriter.h
* 
* Maintenance History:
* ====================
* ver 1.0 : 1 May 2012
* - first release
*/

#ifndef SNIFFER_H
#define SNIFFER_H

#include"PortSniffer.h"
#include"ProcessSniffer.h"
#include"FileSniffer.h"

class Sniffer
{
	PortSniffer portSniffer;
	ProcessSniffer processSniffer;
	FileSniffer fileSniffer;
public:

	void startSniffer(std::string);
	std::set<std::string> getSniffedFiles();
	std::map<std::string,int> getSniffedProcesses();
	std::set<std::string> getTcp4();
	std::set<std::string> getTcp6();
	std::set<std::string> getUdp4();
	std::set<std::string> getUdp6();
	void saveFiles();
	void saveProcesses();
	void savetcp4Ports();
	void saveudp4Ports();
	void savetcp6Ports();
	void saveudp6Ports();

};

#endif