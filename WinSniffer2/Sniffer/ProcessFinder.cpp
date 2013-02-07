////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProcessFinder.cpp  - Lists currently running processes							    					  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #2, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// Source:		http://msdn.microsoft.com/en-us/library/windows/desktop/ms682623%28v=vs.85%29.aspx			  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include"ProcessFinder.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include<sstream>

///////////////////////////////////////////////////////
///function to get running processes
std::map<std::string,int> ProcessFinder::getProcesses()
{
	// Get the list of process identifiers.
	DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return processes;
    }
	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);
	// Print the name and process identifier for each process.
	for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            PrintProcessNameAndID( aProcesses[i] );
        }
    }
	return processes;
}

void ProcessFinder::PrintProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
    // Get a handle to the process.
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );
    // Get the process name.
    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }
    // Print the process name and identifier.
	std::map<std::string,int>::iterator it = processes.find(szProcessName);
	if(it!=processes.end())
	{
		(*it).second++;
	}
	else
	{
		std::pair<std::string,int> elem;
		elem.first = szProcessName;
		elem.second = 1;
		processes.insert(elem);
	}
    CloseHandle( hProcess );
}

///////////////////////////////////////////
////////////TEST STUB /////////////////////
///////////////////////////////////////////
#ifdef TEST_PROCESSFINDER

int main()
{
	ProcessFinder pfinder;		//create new process finder
	std::map<std::string,int> procs = pfinder.getProcesses();	//get list of running processes
	return 0;
}

#endif