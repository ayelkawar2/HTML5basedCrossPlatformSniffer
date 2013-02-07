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
#include <fstream>
#include <sstream>
#include <iostream>
#include "ProcessFinder.h"

std::map<std::string,int> ProcessFinder::getProcesses()
{
	std::map<std::string,int> procList;
	    FILE* f = popen( "ps -eo comm", "r" );
	    std::stringstream ss;
	    if ( f == 0 ) {
	        fprintf( stderr, "Could not execute\n" );
	        return procList;
	    }
	    const int BUFSIZE = 1000;
	    char buf[ BUFSIZE ];
	    while( fgets( buf, BUFSIZE,  f ) )
	    	ss << buf;
	    pclose( f );
	    std::string tempstr;
	    getline(ss,tempstr);
	    while(!ss.eof())
	    {
	    	getline(ss,tempstr);
	    	std::map<std::string,int>::iterator it;
	    	it = procList.find(tempstr);
	    	if(it!=procList.end())
	    	{
	    		(*it).second++;
	    	}
	    	else{
	    		std::pair<std::string,int> elem;
	    		elem.first = tempstr;
	    		elem.second = 1;
	    		procList.insert(elem);
	    	}

	    }
	    std::map<std::string,int>::iterator it;
	    for(it=procList.begin();it!=procList.end();it++)
	    	std::cout << (*it).first << " : " << (*it).second<<"\n";
	    return procList;
}
