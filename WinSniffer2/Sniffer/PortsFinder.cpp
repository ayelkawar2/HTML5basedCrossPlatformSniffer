//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PortsFinder.cpp  - Lists currently open ports										    					//
// ver 1.0																										//
// Language:    Visual C++, 2010																				//
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium														//
// Application: CSE775 - Project #2, Spring 2012																//
// Author:      Aditya Yelkawar, Syracuse University.															//
// Source:		MSDN library																					//
// E-mail:      ayelkawa@syr.edu																				//
// Cell:        (703) 618-6101																					//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PortsFinder.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <sstream>
#include<iostream>


// Need to link with Iphlpapi.lib and Ws2_32.lib
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

/////////////////////////////////////////////////
//scan for open tcp6 ports
std::set<std::string> PortsFinder::getTcp6Ports()
{
	std::set<std::string> tcp6ports;
	try{
	PMIB_TCP6TABLE pTcpTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;
    int i;

    pTcpTable = (MIB_TCP6TABLE *) MALLOC(sizeof (MIB_TCP6TABLE));
    if (pTcpTable == NULL) {
        wprintf(L"Error allocating memory\n");
        return tcp6ports;
    }
    dwSize = sizeof (MIB_TCP6TABLE);
// Make an initial call to GetTcp6Table to
// get the necessary size into the dwSize variable
    if ((dwRetVal = GetTcp6Table(pTcpTable, &dwSize, TRUE)) ==
        ERROR_INSUFFICIENT_BUFFER) {
        FREE(pTcpTable);
        pTcpTable = (MIB_TCP6TABLE *) MALLOC(dwSize);
        if (pTcpTable == NULL) {
            wprintf(L"Error allocating memory\n");
            return tcp6ports;
        }
    }
	if ((dwRetVal = GetTcp6Table(pTcpTable, &dwSize, TRUE)) == NO_ERROR) {
  //      wprintf(L"\tNumber of entries: %d\n", (int) pTcpTable->dwNumEntries);
		for (i = 0; i < (int) pTcpTable->dwNumEntries; i++) 
		{
			std::stringstream ss;
			ss<<pTcpTable->table[i].dwLocalPort;
			std::string str = ss.str();
			tcp6ports.insert(str);
		}
	}
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
	return tcp6ports;
}
/////////////////////////////////////////////////
//scan for open udp 6 ports
std::set<std::string> PortsFinder::getUdp6Ports()
{
	std::set<std::string> udp6ports;
	try{
	PMIB_UDP6TABLE pUdpTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;
    int i;
    pUdpTable = (MIB_UDP6TABLE *) MALLOC(sizeof (MIB_UDP6TABLE));
    if (pUdpTable == NULL) {
        wprintf(L"Error allocating memory\n");
        return udp6ports;
    }
    dwSize = sizeof (MIB_TCP6TABLE);
// Make an initial call to GetTcp6Table to
// get the necessary size into the dwSize variable
    if ((dwRetVal = GetUdp6Table(pUdpTable, &dwSize, TRUE)) ==
        ERROR_INSUFFICIENT_BUFFER) {
        FREE(pUdpTable);
        pUdpTable = (MIB_UDP6TABLE *) MALLOC(dwSize);
        if (pUdpTable == NULL) {
            wprintf(L"Error allocating memory\n");
            return udp6ports;
        }
    }
	if ((dwRetVal = GetUdp6Table(pUdpTable, &dwSize, TRUE)) == NO_ERROR) {
      //  wprintf(L"\tNumber of entries: %d\n", (int) pUdpTable->dwNumEntries);
		for (i = 0; i < (int) pUdpTable->dwNumEntries; i++) 
		{
			std::stringstream ss;
			ss<<pUdpTable->table[i].dwLocalPort;
			std::string str = ss.str();
			udp6ports.insert(str);
		}
	}
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
	return udp6ports;
}
//////////////////////////////////////////////
///scan for open tcp4 ports
std::set<std::string> PortsFinder::getTcp4Ports()
{
	std::set<std::string> tcp4ports;
	try{
	// Declare and initialize variables
    PMIB_TCPTABLE pTcpTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;
	int i;
	pTcpTable = (MIB_TCPTABLE *) MALLOC(sizeof (MIB_TCPTABLE));
    if (pTcpTable == NULL) {
        printf("Error allocating memory\n");
        return tcp4ports;
    }

    dwSize = sizeof (MIB_TCPTABLE);
// Make an initial call to GetTcpTable to
// get the necessary size into the dwSize variable
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) ==
        ERROR_INSUFFICIENT_BUFFER) {
        FREE(pTcpTable);
        pTcpTable = (MIB_TCPTABLE *) MALLOC(dwSize);
        if (pTcpTable == NULL) {
            printf("Error allocating memory\n");
            return tcp4ports;
        }
    }
// Make a second call to GetTcpTable to get
// the actual data we require
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR) {
     //   printf("\tNumber of entries: %d\n", (int) pTcpTable->dwNumEntries);
        for (i = 0; i < (int) pTcpTable->dwNumEntries; i++) {
           
			std::stringstream ss;
			ss<<pTcpTable->table[i].dwLocalPort;
			std::string str = ss.str();
			tcp4ports.insert(str);
		}
	}
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
	return tcp4ports;
}
//////////////////////////////////////////
//scan for open udp 4 ports
std::set<std::string> PortsFinder::getUdp4Ports()
{
	std::set<std::string> udp4ports;
	try{
	// Declare and initialize variables
    PMIB_UDPTABLE pUdpTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;
    int i;

    pUdpTable = (MIB_UDPTABLE *) MALLOC(sizeof (MIB_UDPTABLE));
    if (pUdpTable == NULL) {
        printf("Error allocating memory\n");
        return udp4ports;
    }

    dwSize = sizeof (MIB_TCPTABLE);
// Make an initial call to GetTcpTable to
// get the necessary size into the dwSize variable
    if ((dwRetVal = GetUdpTable(pUdpTable, &dwSize, TRUE)) ==
        ERROR_INSUFFICIENT_BUFFER) {
        FREE(pUdpTable);
        pUdpTable = (MIB_UDPTABLE *) MALLOC(dwSize);
        if (pUdpTable == NULL) {
            printf("Error allocating memory\n");
            return udp4ports;
        }
    }
// Make a second call to GetTcpTable to get
// the actual data we require
    if ((dwRetVal = GetUdpTable(pUdpTable, &dwSize, TRUE)) == NO_ERROR) {
      //  printf("\tNumber of entries: %d\n", (int) pUdpTable->dwNumEntries);
        for (i = 0; i < (int) pUdpTable->dwNumEntries; i++) {
           	std::stringstream ss;
			ss<<pUdpTable->table[i].dwLocalPort;
			std::string str = ss.str();
			udp4ports.insert(str);
		}
	}
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
	return udp4ports;
}

///////////////////////////////////////////
////////////TEST STUB /////////////////////
///////////////////////////////////////////
#ifdef TEST_PORTSFINDER
int main()
{
	PortsFinder pfinder;
	std::set<std::string> t4 = pfinder.getTcp4Ports();	//get open tcp4 ports
	std::set<std::string> u4 = pfinder.getUdp4Ports();	//get open udp4 ports
	std::set<std::string> t6 = pfinder.getTcp6Ports();	//get open tcp6 ports
	std::set<std::string> u6 = pfinder.getUdp6Ports();	//get open udp6 ports
}

#endif