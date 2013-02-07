//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PortsFinder.cpp  - Lists currently open ports										    					//
// ver 1.0																										//
// Language:    Visual C++, 2010																				//
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium														//
// Application: CSE775 - Project #2, Spring 2012																//
// Author:      Aditya Yelkawar, Syracuse University.															//
// E-mail:      ayelkawa@syr.edu																				//
// Cell:        (703) 618-6101																					//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include"PortsFinder.h"
#include<iostream>
#include <fstream>
#include <sstream>

std::set<std::string> PortsFinder::getTcp4Ports() {
	std::set<std::string> portList;
	FILE* f = popen("netstat --inet -ant", "r");
	std::stringstream ss;
	if (f == 0) {
		fprintf(stderr, "Could not execute\n");
		return portList;
	}
	const int BUFSIZE = 1000;
	char buf[BUFSIZE];
	while (fgets(buf, BUFSIZE, f))
		ss << buf;
	pclose(f);
	std::string tempstr;
	getline(ss, tempstr);
	getline(ss, tempstr);
	while (!ss.eof()) {
		getline(ss, tempstr);
		size_t found;
		found = tempstr.find_first_of(":");
		if (found != std::string::npos)
			tempstr = tempstr.substr(found + 1);
		found = tempstr.find_first_of(" ");
		if (found != std::string::npos)
			tempstr = tempstr.substr(0, found);
		portList.insert(tempstr);
	}
	std::cout << "\nTcp4 ports\n";
	for (std::set<std::string>::iterator it = portList.begin(); it
			!= portList.end(); it++)
		std::cout << *it << "\n";

	return portList;
}
std::set<std::string> PortsFinder::getTcp6Ports() {
	std::set<std::string> portList;
	FILE* f = popen("netstat -ant", "r");
	std::stringstream ss;
	if (f == 0) {
		fprintf(stderr, "Could not execute\n");
		return portList;
	}
	const int BUFSIZE = 1000;
	char buf[BUFSIZE];
	while (fgets(buf, BUFSIZE, f))
		ss << buf;
	pclose(f);
	std::string tempstr;
	getline(ss, tempstr);
	getline(ss, tempstr);
	while (!ss.eof()) {
		getline(ss, tempstr);
		if (tempstr[3] != '6')
			continue;
		size_t found;
		found = tempstr.find_first_of(":");
		if (found != std::string::npos)
			tempstr = tempstr.substr(found + 1);
		found = tempstr.find_first_of(" ");
		if (found != std::string::npos)
			tempstr = tempstr.substr(0, found);
		found = tempstr.find_last_of(":");
		if (found != std::string::npos)
			tempstr = tempstr.substr(found + 1);
		portList.insert(tempstr);
	}
	std::cout << "\nTcp6 ports\n";
	for (std::set<std::string>::iterator it = portList.begin(); it
			!= portList.end(); it++)
		std::cout << *it << "\n";
	return portList;
}
std::set<std::string> PortsFinder::getUdp4Ports() {
	std::set<std::string> portList;
	FILE* f = popen("netstat --inet -anu", "r");
	std::stringstream ss;
	if (f == 0) {
		fprintf(stderr, "Could not execute\n");
		return portList;
	}
	const int BUFSIZE = 1000;
	char buf[BUFSIZE];
	while (fgets(buf, BUFSIZE, f))
		ss << buf;
	pclose(f);
	std::string tempstr;
	getline(ss, tempstr);
	getline(ss, tempstr);
	while (!ss.eof()) {
		getline(ss, tempstr);
		size_t found;
		found = tempstr.find_first_of(":");
		if (found != std::string::npos)
			tempstr = tempstr.substr(found + 1);
		found = tempstr.find_first_of(" ");
		if (found != std::string::npos)
			tempstr = tempstr.substr(0, found);
		portList.insert(tempstr);
	}
	std::cout << "\nUdp4 ports\nCount: " << portList.size();
	for (std::set<std::string>::iterator it = portList.begin(); it
			!= portList.end(); it++)
		std::cout << *it << "\n";
	return portList;
}
std::set<std::string> PortsFinder::getUdp6Ports() {
	std::set<std::string> portList;
	FILE* f = popen("netstat -anu", "r");
	std::stringstream ss;
	if (f == 0) {
		fprintf(stderr, "Could not execute\n");
		return portList;
	}
	const int BUFSIZE = 1000;
	char buf[BUFSIZE];
	while (fgets(buf, BUFSIZE, f))
		ss << buf;
	pclose(f);
	std::string tempstr;
	getline(ss, tempstr);
	getline(ss, tempstr);
	while (!ss.eof()) {
		getline(ss, tempstr);
		if (tempstr[3] != '6')
			continue;
		size_t found;
		found = tempstr.find_first_of(":");
		if (found != std::string::npos)
			tempstr = tempstr.substr(found + 1);
		found = tempstr.find_first_of(" ");
		if (found != std::string::npos)
			tempstr = tempstr.substr(0, found);
		found = tempstr.find_last_of(":");
		if (found != std::string::npos)
			tempstr = tempstr.substr(found + 1);
		portList.insert(tempstr);
	}
	std::cout << "\nUDP6 ports\n";
	for (std::set<std::string>::iterator it = portList.begin(); it
			!= portList.end(); it++)
		std::cout << *it << "\n";
	return portList;
}
