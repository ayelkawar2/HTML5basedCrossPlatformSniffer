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

#include "nav.h"
#include "NavWrapper.h"
using namespace Win32Tools;


//////////////////////////////////////////////////////////////////////////////////
///Takes folder path as input and returns file and folder paths by recursive scan
std::set<std::string> NavWrapper::getFileDirList(std::string path)
{
	//Class to provide functionality for creating a set of file and folder paths by running navig
	class navProc : public defproc
    {
	private:
		std::set<std::string> filelist;	//set for storing file and folder paths
		std::string dirpath;			//for temporarily storing directory path

    public:
		
		virtual void fileProc(const fileInfo &fi) 
		{
			fileInfo newfi = fi;
			std::string filepath = dirpath + "\\" + newfi.name();	//create file/folder path by combining directory path and file/folder name
			filelist.insert(filepath);
		}
		virtual void dirsProc(const std::string &dir) {	//stores directory path
			dirpath = dir;
		}
		std::set<std::string>& getList()	//returns set of file/folder paths
		{
			return filelist;
		}
    };
	navProc udp;
	try{
    navig newNav(udp);	//creates new navigator
    newNav.walk(path,"*.*");	//recursively scans for files and directories
	}catch(std::exception& ex){
      std::cout << "\n\n    " << ex.what() << "\n\n"; }	
	return udp.getList();
}

///////////////////////////////////////////
////////////TEST STUB /////////////////////
///////////////////////////////////////////
#ifdef TEST_FILESNIFFER
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

