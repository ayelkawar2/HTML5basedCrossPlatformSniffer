////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PortSniffer.h  - Sniffs for new open ports										    					  //
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
* This class provides functions to sniff for open ports (tcp4, udp4, tcp6, udp6), get the list of these ports, and save
* these ports to the database. Each of port types has a seperete function of sniffing, getting the list and saving to 
* the database.
*
* Public Interface :
* ==================
* PortSniffer psniffer;			//create new port sniffer
* psniffer.sniffPorts();		//start port sniffer
* psniffer.snifftcp4();			//sniff only tcp4 ports
* psniffer.sniffudp4();			//sniff only udp4 ports
* psniffer.snifftcp6();			//sniff only tcp6 ports
* psniffer.sniffudp6();			//sniff only udp6 ports
* psniffer.savetcp4Ports();		//save tcp4 ports to database
* psniffer.savetcp6Ports();		//save tcp6 ports to database
* psniffer.saveudp4Ports();		//save udp4 ports to database
* psniffer.saveudp6Ports();		//save udp6 ports to database
* std::set<std::string> t4 = psniffer.tcp4ports();	//retrive tcp4 ports
* std::set<std::string> u4 = psniffer.udp4ports();	//retrive udp4 ports
* std::set<std::string> t6 = psniffer.tcp6ports();	//retrive tcp6 ports
* std::set<std::string> u6 = psniffer.udp6ports();	//retirve udp6 ports
*
* Build Process:
* ==============
* msbuild Sniffer.sln
* or
* devenv Sniffer.sln/ rebuild
* 
* Requirement Files/ Headers:
* ==========================
* PortsFinder.h
* XmlReader.h
* XmlWriter.h
* 
* Maintenance History:
* ====================
* ver 1.0 : 1 May 2012
* - first release
*/

#ifndef PORTSNIFFER_H
#define PORTSNIFFER_H

#include<set>
#include<string>
class PortSniffer
{
	std::set<std::string> tcp4;
	std::set<std::string> udp4;
	std::set<std::string> tcp6;
	std::set<std::string> udp6;

	std::set<std::string> oldtcp4;
	std::set<std::string> oldudp4;
	std::set<std::string> oldtcp6;
	std::set<std::string> oldudp6;
	std::string tcp4path;
	std::string tcp6path;
	std::string udp4path;
	std::string udp6path;
	bool fexists(const char *nfilename);
	std::string loadFile(std::string filepath);
	void loadDatabase(std::string portsFilePath,std::set<std::string>& oldPorts);
	void findNewPorts(std::set<std::string> oldPorts,std::set<std::string> newPorts,std::set<std::string>&);
	void createDatabase(std::set<std::string> allPorts,std::string filename);
	
public:
	PortSniffer();
	void sniffPorts();
	void snifftcp4();
	void sniffudp4();
	void snifftcp6();
	void sniffudp6();
	void savetcp4Ports();
	void savetcp6Ports();
	void saveudp4Ports();
	void saveudp6Ports();
	void ClearT4();
	void ClearU4();
	void ClearT6();
	void ClearU6();
	std::set<std::string> tcp4ports();
	std::set<std::string> udp4ports();
	std::set<std::string> tcp6ports();
	std::set<std::string> udp6ports();
};

#endif
