#include "Sniffer.h"
#include<iostream>
void Sniffer::startSniffer(std::string path)
{
	fileSniffer.sniffFiles(path);
	processSniffer.sniffProcesses();
	portSniffer.sniffPorts();
}

std::set<std::string> Sniffer::getSniffedFiles()
{
	return fileSniffer.getFiles();
}
std::map<std::string,int> Sniffer::getSniffedProcesses()
{
	return processSniffer.getProcesses();
}
std::set<std::string> Sniffer::getTcp4()
{
	return portSniffer.tcp4ports();
}
std::set<std::string> Sniffer::getTcp6()
{
	return portSniffer.tcp6ports();
}
std::set<std::string> Sniffer::getUdp4()
{
	return portSniffer.udp4ports();
}
std::set<std::string> Sniffer::getUdp6()
{
	return portSniffer.udp6ports();
}

void Sniffer::saveFiles()
{
	fileSniffer.saveFiles();
}
void Sniffer::saveProcesses()
{
	processSniffer.saveProcesses();
}
void Sniffer::savetcp4Ports()
{
	portSniffer.savetcp4Ports();
}
void Sniffer::saveudp4Ports()
{
	portSniffer.saveudp4Ports();
}
void Sniffer::savetcp6Ports()
{
	portSniffer.savetcp6Ports();
}
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
