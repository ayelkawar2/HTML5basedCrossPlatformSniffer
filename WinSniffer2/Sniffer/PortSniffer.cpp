////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ProcessSniffer.cpp  - Sniffs for new processes										    				  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #2, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include"PortsFinder.h"
#include"PortSniffer.h"
#include"XmlReader.h"
#include"XmlWriter.h"
#include<iostream>
#include<fstream>
#include<sstream>

///////////////////////////////
//Constructor
PortSniffer::PortSniffer()
{
	//set file paths
	tcp4path = "./tcp4file.xml";
	tcp6path = "./tcp6file.xml";
	udp4path = "./udp4file.xml";
	udp6path = "./udp6file.xml";
}

void PortSniffer::ClearT4()
{
	oldtcp4.clear();
	tcp4.clear();
}

void PortSniffer::ClearU4()
{
	oldudp4.clear();
	udp4.clear();
}
void PortSniffer::ClearT6()
{
	oldtcp6.clear();
	tcp6.clear();
}
void PortSniffer::ClearU6()
{
	oldudp6.clear();
	udp6.clear();
}
/////////////////////////////////////
///function to sniff new open ports
void PortSniffer::sniffPorts()
{
	try{
	snifftcp4();	//sniff tcp4 ports
	sniffudp4();	//sniff udp4 ports
	snifftcp6();	//sniff tcp6 ports
	sniffudp6();	//sniff udp6 ports
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

////////////////////////////////////////////
/////function to sniff for tcp4 ports
void PortSniffer::snifftcp4()
{
	try{
	PortsFinder pfinder;
	std::set<std::string> t4ports = pfinder.getTcp4Ports();	//find open tcp4 ports
	if(!fexists(tcp4path.c_str()))		//check if database exists
	{
		std::cout<<"\nTCP4 Ports database not found";
		std::cout<<"\nFound "<<t4ports.size()<<" open tcp4 ports\n";
		tcp4 = t4ports;	//store open ports as new ports
	}
	else
	{
		std::cout<<"\nLoading tcp4 ports from database\n";
		loadDatabase(tcp4path,oldtcp4);	
		findNewPorts(oldtcp4, t4ports,tcp4);
	}
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

////////////////////////////////
///sniff for open udp4 ports
void PortSniffer::sniffudp4()
{
	try{
	PortsFinder pfinder;
	std::set<std::string> u4ports = pfinder.getUdp4Ports();	//get open udp 4 ports
	if(!fexists(udp4path.c_str()))
	{
		std::cout<<"\nUDP4 Ports database not found";
		std::cout<<"\nFound "<<u4ports.size()<<" open udp4 ports\n";
		udp4 = u4ports;	//store open ports as new port
	}
	else
	{
		std::cout<<"\nLoading udp4 ports from database\n";
		loadDatabase(udp4path,oldudp4);		//load database if found
		findNewPorts(oldudp4, u4ports,udp4);	//find new ports by checking open ports against ports in database
	}
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

/////////////////////////////////////
///sniff for tcp6 ports
void PortSniffer::snifftcp6()
{
	try{
	PortsFinder pfinder;
	std::set<std::string> t6ports = pfinder.getTcp6Ports();
	if(!fexists(tcp6path.c_str()))
	{
		std::cout<<"\nTCP6 Ports database not found";
		std::cout<<"\nFound "<<t6ports.size()<<" open tcp6 ports\n";
		tcp6 = t6ports;
	}
	else
	{
		std::cout<<"\nLoading tcp6 ports from database\n";
		loadDatabase(tcp6path,oldtcp6);
		findNewPorts(oldtcp6, t6ports,tcp6);
	}
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

//////////////////////////////////////
/////sniff for udp6 ports
void PortSniffer::sniffudp6()
{
	try{
	PortsFinder pfinder;
	std::set<std::string> u6ports = pfinder.getUdp6Ports();
	if(!fexists(udp6path.c_str()))
	{
		std::cout<<"\nUDP6 Ports database not found";
		std::cout<<"\nFound "<<u6ports.size()<<" open udp6 ports\n";
		udp6 = u6ports;
	}
	else
	{
		std::cout<<"\nLoading udp6 ports from database\n";
		loadDatabase(udp6path,oldudp6);
		findNewPorts(oldudp6, u6ports,udp6);
	}
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

////////////////////////////////////////
///return sniffed tcp4 ports
std::set<std::string> PortSniffer::tcp4ports()
{
	return tcp4;
}
////////////////////////////////////////
///return sniffed udp4 ports
std::set<std::string> PortSniffer::udp4ports()
{
	return udp4;
}

//////////////////////////////////////
///return sniffed tcp6 ports
std::set<std::string> PortSniffer::tcp6ports()
{
	return tcp6;
}
/////////////////////////////////////////////
////return sniffed udp6 ports
std::set<std::string> PortSniffer::udp6ports()
{
	return udp6;
}

////////////////////////////////////////////////
////save sniffed tcp4 ports
void PortSniffer::savetcp4Ports()
{
	for (std::set<std::string>::iterator itfiles=tcp4.begin(); itfiles != tcp4.end(); itfiles++)	//insert new files in the fileset
			oldtcp4.insert(*itfiles);
	createDatabase(oldtcp4,tcp4path);
}

////////////////////////////////////////////////////
////save sniffed udp 4 ports
void PortSniffer::saveudp4Ports()
{
	for (std::set<std::string>::iterator itfiles=udp4.begin(); itfiles != udp4.end(); itfiles++)	//insert new files in the fileset
			oldudp4.insert(*itfiles);
	createDatabase(oldudp4,udp4path);
}
//////////////////////////////////////////////////////
///save sniffed tcp6 ports
void PortSniffer::savetcp6Ports()
{
	for (std::set<std::string>::iterator itfiles=tcp6.begin(); itfiles != tcp6.end(); itfiles++)	//insert new files in the fileset
			oldtcp6.insert(*itfiles);
	createDatabase(oldtcp6,tcp6path);
}
//////////////////////////////////////////////////////
////save sniffed udp6 ports
void PortSniffer::saveudp6Ports()
{
	for (std::set<std::string>::iterator itfiles=udp6.begin(); itfiles !=udp6.end(); itfiles++)	//insert new files in the fileset
			oldudp6.insert(*itfiles);
	createDatabase(oldudp6,udp6path);
}

///////////////////////////////////////////////////
//create  xml database
void PortSniffer::createDatabase(std::set<std::string> allPorts,std::string filename)
{
	XmlWriter writer;	//create new xml 
	writer.addDeclaration();
	writer.start("portlist");
	for (std::set<std::string>::iterator it=allPorts.begin(); it != allPorts.end(); it++)
	{
		XmlWriter childnode;
		childnode.start("port");	//add port tag for each path
		childnode.addBody(*it);		//add path
		childnode.end();				//add ending tag
		writer.addBody(childnode.xml());
	}
	writer.end();
	std::ofstream myfile;	//create new file and write the xml in it
	myfile.open (filename.c_str());
	myfile << writer.xml();
	myfile.close();
}

/////////////////////////////////////////////////////////
////find new ports by comparing with ports in database
void PortSniffer::findNewPorts(std::set<std::string> oldPorts,std::set<std::string> newPorts,std::set<std::string>& ports)
{
	try{
		std::cout<<"\n\nScanning for new ports not present in the database..."<<std::endl;
		for (std::set<std::string>::iterator it=newPorts.begin(); it != newPorts.end(); it++)
		{
			if(oldPorts.find(*it)==oldPorts.end())	//if filepath does not exist in the database, add it to 'new file' list
					ports.insert(*it);
			
		}		
		int newproccount = ports.size();	//store the number of new files and folders
		std::cout<<newproccount<<" new ports found\n";

	}
	catch(std::exception& ex){std::cout << "\n\n    " << ex.what() << "\n\n"; }	
}
//////////////////////////////////////////////////////////////
///Loads database from xml file to a set
void PortSniffer::loadDatabase(std::string portsFilePath,std::set<std::string>& oldPorts)
{
	try{
	std::string databaseFile = loadFile(portsFilePath);
	XmlReader rdr(databaseFile);
	while(rdr.next())					//Scan through the xml and search for filepath tag
		if(rdr.tag() == "port")
		{
			oldPorts.insert(rdr.body());	//insert filepaths into set
		}
	}catch(std::exception& ex){
    std::cout << "\n\n    " << ex.what() << "\n\n"; }	
}

//////////////////////////////////////////////////////////////
///load a file from specified path
std::string PortSniffer::loadFile(std::string filepath)
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

//////////////////////////////////////////////////////////////
///Checks if the specified file exits or not
bool PortSniffer::fexists(const char *nfilename)
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

///////////////////////////////////////////
////////////TEST STUB /////////////////////
///////////////////////////////////////////
#ifdef TEST_PORTSNIFFER

int main()
{
	PortSniffer psniffer;			//create new port sniffer
	psniffer.sniffPorts();		//start port sniffer
	psniffer.snifftcp4();			//sniff only tcp4 ports
	psniffer.sniffudp4();			//sniff only udp4 ports
	psniffer.snifftcp6();			//sniff only tcp6 ports
	psniffer.sniffudp6();			//sniff only udp6 ports
	psniffer.savetcp4Ports();		//save tcp4 ports to database	
	psniffer.savetcp6Ports();		//save tcp6 ports to database
	psniffer.saveudp4Ports();		//save udp4 ports to database
	psniffer.saveudp6Ports();		//save udp6 ports to database
	std::set<std::string> t4 = psniffer.tcp4ports();	//retrive tcp4 ports
	std::set<std::string> u4 = psniffer.udp4ports();	//retrive udp4 ports
	std::set<std::string> t6 = psniffer.tcp6ports();	//retrive tcp6 ports
	std::set<std::string> u6 = psniffer.udp6ports();	//retirve udp6 ports
	return 0;
}

#endif