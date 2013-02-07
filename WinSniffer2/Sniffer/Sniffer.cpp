////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sniffer.cpp  - Sniffs for new files, processes and ports							    					  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #2, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Sniffer.h"
#include<iostream>

////////////////////////////////////
///function to run sniffer
void Sniffer::startSniffer(std::string path)
{
	try{
	fileSniffer.sniffFiles(path);
	processSniffer.sniffProcesses();
	portSniffer.sniffPorts();
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

//////////////////////////////////////
//function to get sniffed files
std::set<std::string> Sniffer::getSniffedFiles()
{
	return fileSniffer.getFiles();
}
///////////////////////////////////////////////
////function to get sniffed processes
std::map<std::string,int> Sniffer::getSniffedProcesses()
{
	return processSniffer.getProcesses();
}
//////////////////////////////////////////////
///function to sniff tcp4 ports
std::set<std::string> Sniffer::getTcp4()
{
	return portSniffer.tcp4ports();
}
//////////////////////////////////////////////
///function to get tcp6 ports
std::set<std::string> Sniffer::getTcp6()
{
	return portSniffer.tcp6ports();
}

//////////////////////////////////////////
//function to get udp4 ports
std::set<std::string> Sniffer::getUdp4()
{
	return portSniffer.udp4ports();
}
/////////////////////////////////////////////
///function to get udp 6 ports
std::set<std::string> Sniffer::getUdp6()
{
	return portSniffer.udp6ports();
}
/////////////////////////////////////
//function to save sniffed files
void Sniffer::saveFiles()
{
	fileSniffer.saveFiles();
}
///////////////////////////////////////////
///function to save sniffed processes
void Sniffer::saveProcesses()
{
	processSniffer.saveProcesses();
}
//////////////////////////////////////////
///function to save tcp4 ports
void Sniffer::savetcp4Ports()
{
	portSniffer.savetcp4Ports();
}
//////////////////////////////////////////
///function to save udp4 ports
void Sniffer::saveudp4Ports()
{
	portSniffer.saveudp4Ports();
}
///////////////////////////////////////
//function to save tcp6 ports
void Sniffer::savetcp6Ports()
{
	portSniffer.savetcp6Ports();
}
////////////////////////////////////////
///function to save udp6 ports
void Sniffer::saveudp6Ports()
{
	portSniffer.saveudp6Ports();
}

///////////////////////////////////////////
////////////TEST STUB /////////////////////
///////////////////////////////////////////
#ifdef TEST_SNIFFER
int main()
{
	Sniffer sniffer;
	sniffer.startSniffer(".");
	sniffer.saveFiles();
	std::set<std::string> filelist = sniffer.getSniffedFiles();
	std::set<std::string> t4ports = sniffer.getTcp4();
	std::set<std::string> u4ports = sniffer.getUdp4();
	std::set<std::string> t6ports = sniffer.getTcp6();
	std::set<std::string> u6ports = sniffer.getUdp6();
	sniffer.saveProcesses();
	sniffer.savetcp4Ports();
	sniffer.savetcp6Ports();
	sniffer.saveudp4Ports();
	sniffer.saveudp6Ports();
	std::cin.get();
	return 0;
}
#endif