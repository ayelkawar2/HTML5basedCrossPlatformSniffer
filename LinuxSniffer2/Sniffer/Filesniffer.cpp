////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSniffer.cpp  - Provides functions to sniff for new files and directories not found in previous scans.  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #1, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include "FileSniffer.h"
#include "NavWrapper.h"
#include "XmlReader.h"
#include "XmlWriter.h"
#include <fstream>
#include <sstream>
#include<iostream>


//////////////////////////////////////////////////////////////
///Constructor
FileSniffer::FileSniffer()
{
	excludeFilePath = "./excluded.xml";
	databaseFilePath = "./database.xml";
	resultFilePath = "./result.xml";

	excludeFileExists = false;
	databaseFile = new std::string();
	excludeFile = new std::string();
	summary = false;
	if(fexists(excludeFilePath.c_str()))	//Checks if Exclude file exists
	{
		excludeFileExists = true;
		excludeFile = loadFile(excludeFilePath);
	}
}
void FileSniffer::Clear()
{
	fileset.clear();
	newfilesList.clear();
}
//////////////////////////////////////////////////////////////
///Destructor
FileSniffer::~FileSniffer()
{
	delete databaseFile;
	delete excludeFile;
}

void FileSniffer::saveFiles()
{
	addToDatabase();
}
std::set<std::string> FileSniffer::getFiles()
{
	return newfilesList;
}

std::set<std::string> FileSniffer::getLastResult()
{
	std::set<std::string> lastresult;
	try{

		std::string* resultfile = new std::string();
		if(fexists(resultFilePath.c_str()))	//Check if result text file exists
		{
			resultfile = loadFile(resultFilePath);
			XmlReader rdr(*resultfile);
			while(rdr.next())
			{							//Scan through the xml and search for filepath tag
				if(rdr.tag() == "listsize")
				{
					if(rdr.body() == "0")
						break;
				}
				if(rdr.tag() == "filepath")
					lastresult.insert(rdr.body());
			}
			delete resultfile;
		}

	}catch(std::exception& ex){
    std::cout << "\n\n    " << ex.what() << "\n\n"; }
	return lastresult;
}

//////////////////////////////////////////////////////////////
///Stores results of analysis into a text file
void FileSniffer::StoreResult()
{
	try{
	std::stringstream ss;
	ss<<newfilesList.size();
	XmlWriter writer;	//create new xml
	writer.addDeclaration();
	writer.start("filelist");
	XmlWriter childnode1;
	childnode1.start("listsize");	//add filepath tag for each path
	childnode1.addBody(ss.str());		//add path
	childnode1.end();				//add ending tag
	writer.addBody(childnode1.xml());
	for (std::set<std::string>::iterator it=newfilesList.begin(); it != newfilesList.end(); it++)	//add all paths in fileset to the xml
	{
		XmlWriter childnode;
		childnode.start("filepath");	//add filepath tag for each path
		childnode.addBody(*it);		//add path
		childnode.end();				//add ending tag
		writer.addBody(childnode.xml());

	}
	writer.end();
	std::ofstream myfile;	//create new file and write the xml in it
	myfile.open (resultFilePath.c_str());
	myfile << writer.xml();
	myfile.close();
	}
	catch(std::exception ex)
    {
      std::cout << "\n  " << ex.what() << "\n\n";
    }

}
//////////////////////////////////////////////////////////////
///Sniffs for new files and directories
void FileSniffer::sniffFiles(std::string path)
{
	NavWrapper filescanner;
	std::set<std::string> filelist;
	std::cout<<"Scanning for files and folders..."<<std::endl;
	try{
	filelist = filescanner.getFileDirList(path);	//gets a set of folder and file paths by recursively scanning specified path
//	if(!summary)
//		printList(filelist);
	std::cout<<"\nCompleted\n\n"<<filelist.size()<<" files found on the specified path"<<std::endl;
	if(filelist.size()==0)	//return if no paths in the set
		return;
	std::set<std::string>::iterator it;
	if(!fexists(databaseFilePath.c_str()))	//check if database file exists
	{
		std::cout<<"\nDatabase not found\n";
		newfilesList = filelist;
	/*	std::cout<<"Database not found, Creating new database and adding files to it..."<<std::endl;
		int count = createDatabase(filelist);	//create new database if not found
		if(filelist.size()!=0)
			std::cout<<std::endl<<count<<" file(s) and folder(s) added to the database"<<std::endl;*/
	}
	else
	{
		std::cout<<"\nLoading database into memory...\n";
		loadDatabase();	//load database into memory in form of a set
		std::cout<<"Completed";
		findNewFiles(filelist);	//find new files in the path set by comparing it with database
		StoreResult();	//store analysis results in xml file
	}
	}catch(std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
	}

}

////////////////////////////////////////////////////////////////
///Print analysis results 
void FileSniffer::PrintResult()
{
	try{
	if(fexists(resultFilePath.c_str()))	//Check if result text file exists
	{
		std::cout<<"\nPrevious Analysis Result\n";

		std::string* prevResult = new std::string();
		prevResult = loadFile(resultFilePath);	//load text file
		std::cout <<"\n"<<*prevResult<<std::endl;
		delete prevResult;
	}
	else
		std::cout << "\nPrevious analysis result not found";
	}catch(std::exception& ex){
      std::cout << "\n\n    " << ex.what() << "\n\n"; }	
}
//////////////////////////////////////////////////////////////
///Prints list of filepaths in the console
void FileSniffer::printList(std::set<std::string> listToPrint)
{
	try{
	for (std::set<std::string>::iterator it=listToPrint.begin(); it != listToPrint.end(); it++)	//prints file paths
	{
		std::cout<<"\n"<<*it;
	}
	}catch(std::exception& ex){
      std::cout << "\n\n    " << ex.what() << "\n\n"; }	
}

void FileSniffer::OnlySummary()
{
	summary = true;
}

//////////////////////////////////////////////////////////////
///Loads database from xml file to a set
void FileSniffer::loadDatabase()
{
	try{
	databaseFile = loadFile(databaseFilePath);
	XmlReader rdr(*databaseFile);
	while(rdr.next())					//Scan through the xml and search for filepath tag
		if(rdr.tag() == "filepath")
			fileset.insert(rdr.body());	//insert filepaths into set
	}catch(std::exception& ex){
    std::cout << "\n\n    " << ex.what() << "\n\n"; }	
}

//////////////////////////////////////////////////////////////
///Checks for new files not present in the database
void FileSniffer::findNewFiles(std::set<std::string>& filelist)
{
	try{
		std::cout<<"\n\nScanning for new Files and folders not present in the database..."<<std::endl;
		for (std::set<std::string>::iterator itfiles=filelist.begin(); itfiles != filelist.end(); itfiles++)
		{
			if(!isInExcluded(*itfiles))	//check if the filepath is in excluded list
			{
				if(fileset.find(*itfiles)==fileset.end())	//if filepath does not exist in the database, add it to 'new file' list
					newfilesList.insert(*itfiles);
			}
		}
		int newfilecount = newfilesList.size();	//store the number of new files and folders
		std::cout<<newfilecount<<" new files and folders found\n";

	}
	catch(std::exception& ex){std::cout << "\n\n    " << ex.what() << "\n\n"; }
}

////////////////////////////////////////////////////////////////
///Adds new files to the database
void FileSniffer::addToDatabase()
{
	try{
	for (std::set<std::string>::iterator itfiles=newfilesList.begin(); itfiles != newfilesList.end(); itfiles++)	//insert new files in the fileset
			fileset.insert(*itfiles);
	createDatabase(fileset);	//create new database from fileset
	}catch(std::exception& ex){
      std::cout << "\n\n    " << ex.what() << "\n\n"; }	
}


//////////////////////////////////////////////////////////////////////////////////////////
///Creates the XML database file from a set of filepaths and returns number of new paths
int FileSniffer::createDatabase(std::set<std::string>& filelist)
{
	int count=0;
	try{
	XmlWriter writer;	//create new xml 
	writer.addDeclaration();
	writer.start("filelist");
	newfilesList.clear();
	for (std::set<std::string>::iterator it=filelist.begin(); it != filelist.end(); it++)	//add all paths in fileset to the xml
	{
		if(!isInExcluded(*it))
		{
			count++;
			XmlWriter childnode;
			childnode.start("filepath");	//add filepath tag for each path
			childnode.addBody(*it);		//add path
			childnode.end();				//add ending tag
			writer.addBody(childnode.xml());
			newfilesList.insert(*it);
		}
	}
	writer.end();
	std::ofstream myfile;	//create new file and write the xml in it
	myfile.open (databaseFilePath.c_str());
	myfile << writer.xml();
	myfile.close();
	StoreResult();
	}
	catch(std::exception ex)
    {
      std::cout << "\n  " << ex.what() << "\n\n";
    }
	return count;
}

//////////////////////////////////////////////////////////////
///Checks if the specified file exits or not
bool FileSniffer::fexists(const char *nfilename)
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

//////////////////////////////////////////////////////////////
///Checks if the specified path is the excluded paths
inline bool FileSniffer::isInExcluded(std::string path)
{
	try{
		std::string::reverse_iterator rit;
	rit=path.rbegin();
	if(!path.empty() && *rit=='.')	//remove . and .. dirctories from paths
		return true;
	if(excludeFileExists == false)	//return if excludefile does not exist
		return false;

	XmlReader rdr(*excludeFile);
	std::string dirpath;
	while(rdr.next())
	{
		if(rdr.tag() == "exclude")	//get exclude paths
		{
			dirpath = rdr.body();
			int found=path.find(dirpath);	//check if current path is in the exclude list
			if (found!=std::string::npos)	
				return true;
		}
	}
	}catch(std::exception& ex){
      std::cout << "\n\n    " << ex.what() << "\n\n"; }	
	return false;
}

//////////////////////////////////////////////////////////////
///load a file from specified path
std::string* FileSniffer::loadFile(std::string filepath)
{
	std::string* file = new std::string();
	try
	{
		std::string path = filepath;
		std::ifstream in(path.c_str());	//open file specified on the path
		if(!in.good())
		  return file;
		std::filebuf* tempFilebuf = in.rdbuf();	//store file data into temp buffer
		std::ostringstream out;
		out << tempFilebuf;	//write data from the temp buffer to outstring
		*file = out.str();
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
#ifdef TEST_FILESNIFFER
int main() 
{
	FileSniffer sniffer;
	std::cout<<"\nSniffing for new files on current directory path\n";
	sniffer.sniffFiles(".");
	std::cout<<"\nDisplaying only summary of analysis\n";
	sniffer.OnlySummary();
	sniffer.sniffFiles(".");
	std::cout<<"\nShowing previous analysis result\n";
	sniffer.PrintResult();
	std::cin.ignore();
	std::cin.get();
	return 0;
}

#endif
