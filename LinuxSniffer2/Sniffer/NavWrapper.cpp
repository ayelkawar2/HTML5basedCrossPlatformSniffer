////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NavWrapper.cpp  - Provides Wrapper class for Nav.h.						    							  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #1, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "NavWrapper.h"
#include "nav.h"
#include<iostream>
#include <string.h>


//Class to provide functionality for creating a set of file and folder paths by running nav
class navProc : public INavProc
{
private:
	std::set<std::string> filelist;	//set for storing file and folder paths
	std::string dirpath;			//for temporarily storing directory path
public:
	void fileProc(const std::string& filename)
	{
		std::string filepath;
		filepath = dirpath + "/" + filename;	//create file/folder path by combining directory path and file/folder name
		//std::cout << "\n  file:" << filepath;
		filelist.insert(filepath);
	}
	void dirProc(const std::string& dirname)	//stores directory path
	{
		dirpath = dirname;
		filelist.insert(dirpath);
		//std::cout << "\n  path: " << dirname;
	}
	std::set<std::string>& getList()		//returns set of file/folder paths
	{
		return filelist;
	}
};

//////////////////////////////////////////////////////////////////////////////////
///Takes folder path as input and returns file and folder paths by recursive scan
std::set<std::string> NavWrapper::getFileDirList(std::string spath)
{
	navProc nproc;
	const char* path = spath.c_str();
	try
	{
		const char* currPath = get_current_dir_name();	//store current path

		chdir(path);	//change path to the one specified by the user
		const char* newPath = get_current_dir_name();	//get current path

		navigate nav(&nproc);//creates new navigator
		nav.walk(newPath);	//recursively scan directories
		chdir(currPath);	//reset the path to original
	}
	catch(std::exception& ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";

	}
	return nproc.getList();
}

///////////////////////////////////////////
////////////TEST STUB /////////////////////
///////////////////////////////////////////
#ifdef TEST_NAVWRAPPER
int main()
{
	NavWrapper filefinder;
	std::set<std::string> filelist=filefinder.getFileDirList(".");
	for (std::set<std::string>::iterator it=filelist.begin(); it != filelist.end(); it++)
	{
		std::cout<<"\n"<<*it;
	}
	std::cin.ignore();
	std::cin.get();
	return 0;
}
#endif


