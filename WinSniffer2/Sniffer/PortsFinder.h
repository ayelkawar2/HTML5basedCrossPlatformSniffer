//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PortsFinder.h  - Lists currently open ports										    						//
// ver 1.0																										//
// Language:    Visual C++, 2010																				//
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium														//
// Application: CSE775 - Project #2, Spring 2012																//
// Author:      Aditya Yelkawar, Syracuse University.															//
// Source:		MSDN library																					//
// E-mail:      ayelkawa@syr.edu																				//
// Cell:        (703) 618-6101																					//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* Generates a list of open ports. It creates different lists for tcp4, udp4, tcp6 and udp6 ports. These ports are
* stored in a set of strings and returned to the caller.
*
* Public Interface :
* ==================
* PortsFinder pfinder;
* std::set<std::string> t4 = pfinder.getTcp4Ports();	//get open tcp4 ports
* std::set<std::string> u4 = pfinder.getUdp4Ports();	//get open udp4 ports
* std::set<std::string> t6 = pfinder.getTcp6Ports();	//get open tcp6 ports
* std::set<std::string> u6 = pfinder.getUdp6Ports();	//get open udp6 ports
*
* Build Process:
* ==============
* msbuild Sniffer.sln
* or
* devenv Sniffer.sln/ rebuild
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


#ifndef PORTSFINDER_H
#define PORTSFINDER_H
#include<set>
#include<string>
class PortsFinder
{
public:
	std::set<std::string> getTcp4Ports();
	std::set<std::string> getUdp4Ports();
	std::set<std::string> getTcp6Ports();
	std::set<std::string> getUdp6Ports();

};
#endif