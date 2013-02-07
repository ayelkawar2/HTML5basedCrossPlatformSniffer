////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProcessSniffer.cpp  - Sniffs for new processes									    					  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #2, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include"ProcessSniffer.h"
#include"ProcessFinder.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include"XmlWriter.h"
#include"XmlReader.h"

///////////////////////////////////
///constructor
ProcessSniffer::ProcessSniffer()
{
	processFilePath = "./processFile.xml";
}
void ProcessSniffer::Clear()
{
	procList.clear();
	oldProcs.clear();
}
//////////////////////////////////////////
///sniff for new processes
void ProcessSniffer::sniffProcesses()
{
	ProcessFinder prfinder;
	std::map<std::string,int> allProc = prfinder.getProcesses();	//get running processes
	if(allProc.size() == 0)
	{
		std::cout<<"\nUnable to find running processes";
		return;
	}
	if(!fexists(processFilePath.c_str()))	//check if database exists
	{
		std::cout<<"\nProcesses database not found\n";
		std::cout<<allProc.size() <<" new processes found (Includes repeated processes)";
		procList = allProc;	//store running process as new processes
	}
	else
	{
		std::cout<<"\nLoading processes database into memory\n";
		loadDatabase();
		findNewProcesses(allProc);	//check for new processes by comparing with process in database
	}
}

////////////////////////////////
////get list of new processes
std::map<std::string,int> ProcessSniffer::getProcesses()
{
	return procList;
}
///////////////////////////////////
///save new processes in database
void ProcessSniffer::saveProcesses()
{
	for (std::map<std::string,int>::iterator itfiles=procList.begin(); itfiles != procList.end(); itfiles++)	//insert new files in the fileset
			oldProcs.insert(*itfiles);
	createDatabase(oldProcs,processFilePath);
}

//////////////////////////////////////////////////////////////
///Loads database from xml file to a set
void ProcessSniffer::loadDatabase()
{
	try{
	databaseFile = loadFile(processFilePath);
	XmlReader rdr(databaseFile);
	while(rdr.next())					//Scan through the xml and search for filepath tag
		if(rdr.tag() == "process")
		{
			std::pair<std::string,int> elem;
			elem.first = rdr.body();
			elem.second = 1;
			oldProcs.insert(elem);	//insert processes into set
		}
	}catch(std::exception& ex){
    std::cout << "\n\n    " << ex.what() << "\n\n"; }	
}

////////////////////////////////////////////////
////Create xml database of processes
void ProcessSniffer::createDatabase(std::map<std::string,int> allProcs,std::string filename)
{
	XmlWriter writer;	//create new xml 
	writer.addDeclaration();
	writer.start("proclist");
	for (std::map<std::string,int>::iterator it=allProcs.begin(); it != allProcs.end(); it++)
	{
		XmlWriter childnode;
		childnode.start("process");	//add process tag for each process
		childnode.addBody((*it).first);		//add path
		childnode.end();				//add ending tag
		writer.addBody(childnode.xml());
	}
	writer.end();
	std::ofstream myfile;	//create new file and write the xml in it
	myfile.open (filename.c_str());
	myfile << writer.xml();
	myfile.close();
}

//////////////////////////////////////////////////////////////
///Checks if the specified file exits or not
bool ProcessSniffer::fexists(const char *nfilename)
{
	try{
	std::string path = nfilename;
	std::ifstream in(path.c_str());
	if(!in.good())	//check if file opened succesfully
		return false;
	return true;
	}
	catch(std::exception ex)
    {
      std::cout << "\n  " << ex.what() << "\n\n";
    }
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
///compare running processes with process in database and find new processes
void ProcessSniffer::findNewProcesses(std::map<std::string,int>& plist)
{
	try{
		std::cout<<"\n\nScanning for new processes not present in the database..."<<std::endl;
		for (std::map<std::string,int>::iterator it=plist.begin(); it != plist.end(); it++)
		{
			if(oldProcs.find((*it).first)==oldProcs.end())	//if filepath does not exist in the database, add it to 'new file' list
					procList.insert(*it);
			
		}		
		int newproccount = procList.size();	//store the number of new files and folders
		std::cout<<newproccount<<" new processes found\n";

	}
	catch(std::exception& ex){std::cout << "\n\n    " << ex.what() << "\n\n"; }	
}
//////////////////////////////////////////////////////////////
///load a file from specified path
std::string ProcessSniffer::loadFile(std::string filepath)
{
	std::string file;
	try
	{
		std::string path = filepath;
		std::ifstream in(path.c_str());	//open file specified on the path
		if(!in.good())
		  return file;
		std::filebuf* tempFilebuf = in.rdbuf();	//store file data into temp buffer
		std::ostringstream out;
		out << tempFilebuf;	//write data from the temp buffer to outstring
		file = out.str();
		in.close();
	}
	catch(std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
	}
	return file;
}

///////////////////////////////////////////
////////////TEST STUB /////////////////////
///////////////////////////////////////////
#ifdef TEST_PROCESSSNIFFER

int main()
{
	ProcessSniffer psniffer;										//create a new process sniffer
	psniffer.sniffProcesses();									//sniff for new processes
	std::map<std::string,int> pmap = psniffer.getProcesses();		//retrive new processes
	psniffer.saveProcesses();										//save new processes
	return 0;
}
#endif