////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Executive.h  - Executive class for the Sniffer with embedded server				    					  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #2, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* This class provides a function to create a new http server which listens on port 8080. The server is capable of serving
* files such as .html, .css, .js etc. and it is also capable of sending replies to ajax calls. It implements ajax calls for
* differnt sniffer functionalities such as file sniffing, process sniffing, port sniffing. Each of the sniffer runs on 
* a seperate thread. Port sniffing is done using 4 differnt port sniffers for tcp4, udp4, tcp6 and udp6. Sniffed data is
* automatically added to the database.
*
* Public Interface :
* ==================
* void startServer()  // Starts the server
*
* Build Process:
* ==============
* msbuild Sniffer.sln
* or
* devenv Sniffer.sln/ rebuild
* 
* Requirement Files/ Headers:
* ==========================
* mongoose.h
* FileSniffer.h
* Nav.h
* NavWrapper.h
* PortsFinder.h
* PortSniffer.h
* ProcessFinder.h
* ProcessSniffer.h
* Sniffer.h
* StringConversion.h
* WinTools.h
* XmlReader.h
* XmlWriter.h
* 
* Maintenance History:
* ====================
* ver 1.0 : 1 May 2012
* - first release
*/




#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include"mongoose.h"
#include"Sniffer.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>

class Executive
{
	char *ajax_reply_start;
	char *json_reply_start;

	void ajaxReply(struct mg_connection *conn, const struct mg_request_info *request_info);
	void savefiles(struct mg_connection *conn, const struct mg_request_info *request_info);
	void procReply(struct mg_connection *conn, const struct mg_request_info *request_info);
	void saveprocs(struct mg_connection *conn, const struct mg_request_info *request_info);
	void tcp4Reply(struct mg_connection *conn, const struct mg_request_info *request_info);
	void savet4(struct mg_connection *conn, const struct mg_request_info *request_info);
	void udp4Reply(struct mg_connection *conn, const struct mg_request_info *request_info);
	void saveu4(struct mg_connection *conn, const struct mg_request_info *request_info);
	void tcp6Reply(struct mg_connection *conn, const struct mg_request_info *request_info);
	void savet6(struct mg_connection *conn, const struct mg_request_info *request_info);
	void udp6Reply(struct mg_connection *conn, const struct mg_request_info *request_info);
	void saveu6(struct mg_connection *conn, const struct mg_request_info *request_info);
	void listReply(struct mg_connection *conn, const struct mg_request_info *request_info);

	static void *callback(enum mg_event event, struct mg_connection *conn, const struct mg_request_info *request_info);
	void get_psvar(const char *pdata, const char *name, char *dst, size_t dst_len);
	void get_qsvar(const struct mg_request_info *request_info, const char *name, char *dst, size_t dst_len);
	int handle_jsonp(char * pdata, struct mg_connection *conn, const struct mg_request_info *request_info);
	FileSniffer fsniffer;
	//ProcessSniffer prsniffer;
	/*PortSniffer t4sniffer;
	PortSniffer u4sniffer;
	PortSniffer t6sniffer;
	PortSniffer u6sniffer;*/
public:
	Executive();
	void startServer();
};

#endif
