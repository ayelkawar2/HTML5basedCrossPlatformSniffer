////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Executive.cpp  - Executive class for the Sniffer with embedded server				    				  //
// ver 1.0																									  //
// Language:    Visual C++, 2010																			  //
// Platform:    Dell Inspiron N5010, Windows 7 Home Premium													  //
// Application: CSE775 - Project #2, Spring 2012															  //
// Author:      Aditya Yelkawar, Syracuse University.														  //
// E-mail:      ayelkawa@syr.edu																			  //
// Cell:        (703) 618-6101																				  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Executive.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

#define array_length(array) (sizeof (array) / sizeof (array)[0])
static FileSniffer fsniffer2;
static ProcessSniffer prsniffer;
static PortSniffer t4sniffer;
static PortSniffer u4sniffer;
static PortSniffer t6sniffer;
static PortSniffer u6sniffer;
//structure for HTML encoding
struct HTMLReplace 
{
	std::string match;
	std::string replace;
} codes[] = {
			{"&", "&amp;"},
			{"<", "&lt;"},
			{">", "&gt;"},
			{"\\","	&#92;"},
			{"/","&#47;"}
			};


//function to perform HTML encoding
std::string HTMLEncode( const std::string& s )
{
	
	std::string rs = s;
	// Replace each matching token in turn
	try{
	for ( size_t i = 0; i < array_length( codes ); i++ ) 
	{
		// Find the first match
		const std::string& match = codes[i].match;
		const std::string& repl = codes[i].replace;
		std::string::size_type start = rs.find_first_of( match );
		// Replace all matches
		while ( start != std::string::npos ) 
		{
			rs.replace( start, match.size(), repl );
			// Be sure to jump forward by the replacement length
			start = rs.find_first_of( match, start + repl.size() );
		}
	}
	}
	catch(std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
	}
return rs;
}

////////////////////////////////////////////////////////////////
///Constructor for exective class, intializes header strings
Executive::Executive()
{
	ajax_reply_start =  "HTTP/1.1 200 OK\r\n"
  "Cache: no-cache\r\n"
  "Content-Type: text/html\r\n";
	json_reply_start =  "HTTP/1.1 200 OK\r\n"
  "Cache: no-cache\r\n"
  "Content-Type: application/x-javascript\r\n";

}
//function to save files
void Executive::savefiles(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	fsniffer2.saveFiles();
	
}

//function to save processes
void Executive::saveprocs(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	prsniffer.saveProcesses();
	
}

//function to save tcp4 ports
void Executive::savet4(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	t4sniffer.savetcp4Ports();	
}
//function to save udp4 ports
void Executive::saveu4(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	u4sniffer.saveudp4Ports();	
}
//function to save tcp6 ports
void Executive::savet6(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	t6sniffer.savetcp6Ports();	
}
//function to save udp6 ports
void Executive::saveu6(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	u6sniffer.saveudp6Ports();	
}
////////////////////////////////////////////////////////////////
///Function to send sniffed file list to the client
void Executive::listReply(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	try{
	int is_jsonp;
	char text[100];
	const char * json;
	std::stringstream ss;
	std::string msg;
	mg_printf(conn, "%s\r\n", json_reply_start);	//prints the json message starting headers
	const char * clength;
	char h1[] = "Content-Length";
	clength = mg_get_header(conn,h1);	//get the length of post data
	int clen = atoi(clength);
	char *pdata = (char *)malloc(clen+clen/8+1);
	int datalen = mg_read(conn,pdata,clen);	//read post data
	pdata[clen] = '\0';
	mg_get_var(pdata, strlen(pdata == NULL ? "" : pdata), "text", text, sizeof(text));
	std::string path(text);
	is_jsonp = handle_jsonp(pdata,conn, request_info);	//find the callback function
	srand((size_t)time(NULL));
	ss<<"[";
	fsniffer2.Clear();
	fsniffer2.sniffFiles(path);
	std::set<std::string> filelist = fsniffer2.getFiles();	//get sniffed files
	for (std::set<std::string>::iterator it=filelist.begin(); it != filelist.end(); it++)
	{
		std::string tempstr = HTMLEncode(*it);	//html encode filepaths
		ss<<"{item: \""<<tempstr<<"\"},";
	}
	ss<<"]";
	msg = ss.str();
	json = msg.c_str();
	mg_printf(conn, "%s", json);	//print json array to the connection

	if (is_jsonp) 	{
		mg_printf(conn, "%s", ")");	//print closing bracket for the function
	}
//	fsniffer2.saveFiles();	//save sniffed files
	}
	catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

////////////////////////////////////////////////////////////////
///Function to send a simple text ajax rely
void Executive::ajaxReply(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	try{
	const char * clength;
	char h1[] = "Content-Length";
	clength = mg_get_header(conn,h1);	//get length of post data
	int clen = atoi(clength);
	char *pdata = (char *)malloc(clen+clen/8+1);
	int datalen = mg_read(conn,pdata,clen);	//read post data
	pdata[clen] = '\0';
	printf("\nUser data: %s",pdata);
	mg_printf(conn, "%s\r\n%s", ajax_reply_start,pdata);
	free(pdata);
	}
	catch(std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
	}
}

////////////////////////////////////////////////////////////////
///Read get message data and find the value for specified key
void Executive::get_qsvar(const struct mg_request_info *request_info,
                      const char *name, char *dst, size_t dst_len) {
  const char *qs = request_info->query_string;
  mg_get_var(qs, strlen(qs == NULL ? "" : qs), name, dst, dst_len);
}

////////////////////////////////////////////////////////////////
///Read post message data and find the value for specified key
void Executive::get_psvar(const char *pdata, const char *name, char *dst, size_t dst_len) 
{
	
	const char *qs = pdata;
	mg_get_var(qs, strlen(qs == NULL ? "" : qs), name, dst, dst_len);
	
}

////////////////////////////////////////////////////////////////
///checks if the post data contains callback information
int Executive::handle_jsonp(char * pdata, struct mg_connection *conn,
                        const struct mg_request_info *request_info) {
  char cb[64];

  get_psvar(pdata, "callback", cb, sizeof(cb));	//get callback function
  if (cb[0] != '\0') {
    mg_printf(conn, "%s(", cb);	//print the callback function start in the reply message
  }
 
  return cb[0] == '\0' ? 0 : 1;
}



////////////////////////////////////////////////////////////////
///Function to send sniffed process list
void Executive::procReply(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	try{
	int is_jsonp;
	
	const char * json;
	std::stringstream ss;
	std::string msg;
	mg_printf(conn, "%s\r\n", json_reply_start);	//prints the json message starting headers
	const char * clength;
	char h1[] = "Content-Length";
	clength = mg_get_header(conn,h1);	//get the length of post data
	int clen = atoi(clength);
	char *pdata = (char *)malloc(clen+clen/8+1);
	int datalen = mg_read(conn,pdata,clen);	//read post data
	pdata[clen] = '\0';
	/*mg_get_var(pdata, strlen(pdata == NULL ? "" : pdata), "text", text, sizeof(text));
	std::string path(text);*/
	is_jsonp = handle_jsonp(pdata,conn, request_info);	//find the callback function
	srand((size_t)time(NULL));
	ss<<"[";
	prsniffer.Clear();
	prsniffer.sniffProcesses();
	std::map<std::string,int> filelist = prsniffer.getProcesses();	//get process list
	for (std::map<std::string,int>::iterator it=filelist.begin(); it != filelist.end(); it++)
	{
		std::string tempstr = HTMLEncode((*it).first);
		ss<<"{item: \""<<tempstr<<" ("<<(*it).second<<")\"},";	//store process name and count
	}
	ss<<"]";
	msg = ss.str();
	json = msg.c_str();
	mg_printf(conn, "%s", json);	//print json array to the connection
	if (is_jsonp) 
	{
		mg_printf(conn, "%s", ")");	//print closing bracket for the function
	}
	//prsniffer.saveProcesses();
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

//function to send sniffed udp4 port list
void Executive::udp4Reply(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	try{
	int is_jsonp;
	const char * json;
	std::stringstream ss;
	std::string msg;
	mg_printf(conn, "%s\r\n", json_reply_start);	//prints the json message starting headers
	const char * clength;
	char h1[] = "Content-Length";
	clength = mg_get_header(conn,h1);	//get the length of post data
	int clen = atoi(clength);
	char *pdata = (char *)malloc(clen+clen/8+1);
	int datalen = mg_read(conn,pdata,clen);	//read post data
	pdata[clen] = '\0';
	/*mg_get_var(pdata, strlen(pdata == NULL ? "" : pdata), "text", text, sizeof(text));
	std::string path(text);*/
	is_jsonp = handle_jsonp(pdata,conn, request_info);	//find the callback function
	srand((size_t)time(NULL));
	ss<<"[";
	u4sniffer.ClearU4();
	u4sniffer.sniffudp4();	//sniff for udp4 ports
	std::set<std::string> u4list = u4sniffer.udp4ports();	//get udp4 port list
	for (std::set<std::string>::iterator it=u4list.begin(); it != u4list.end(); it++)
	{
		std::string tempstr = HTMLEncode(*it);
		ss<<"{item: \""<<tempstr<<"\"},";
	}
	ss<<"]";
	msg = ss.str();
	json = msg.c_str();
	mg_printf(conn, "%s", json);	//print json array to the connection
	if (is_jsonp) 
	{
		mg_printf(conn, "%s", ")");	//print closing bracket for the function
	}
	//u4sniffer.saveudp4Ports();
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

//function to send udp6 port list
void Executive::udp6Reply(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	try{
	int is_jsonp;
	const char * json;
	std::stringstream ss;
	std::string msg;
	mg_printf(conn, "%s\r\n", json_reply_start);	//prints the json message starting headers
	const char * clength;
	char h1[] = "Content-Length";
	clength = mg_get_header(conn,h1);	//get the length of post data
	int clen = atoi(clength);
	char *pdata = (char *)malloc(clen+clen/8+1);
	int datalen = mg_read(conn,pdata,clen);	//read post data
	pdata[clen] = '\0';
	/*mg_get_var(pdata, strlen(pdata == NULL ? "" : pdata), "text", text, sizeof(text));
	std::string path(text);*/
	is_jsonp = handle_jsonp(pdata,conn, request_info);	//find the callback function
	srand((size_t)time(NULL));
	ss<<"[";
	u6sniffer.ClearU6();
	u6sniffer.sniffudp6();
	std::set<std::string> u6list = u6sniffer.udp6ports();
	for (std::set<std::string>::iterator it=u6list.begin(); it != u6list.end(); it++)
	{
		std::string tempstr = HTMLEncode(*it);
		ss<<"{item: \""<<tempstr<<"\"},";
	}
	ss<<"]";
	msg = ss.str();
	json = msg.c_str();
	mg_printf(conn, "%s", json);	//print json array to the connection
	if (is_jsonp) 
	{
		mg_printf(conn, "%s", ")");	//print closing bracket for the function
	}
	//u6sniffer.saveudp6Ports();
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

//function to send tcp6 port list
void Executive::tcp6Reply(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	try{
	int is_jsonp;
	const char * json;
	std::stringstream ss;
	std::string msg;
	mg_printf(conn, "%s\r\n", json_reply_start);	//prints the json message starting headers
	const char * clength;
	char h1[] = "Content-Length";
	clength = mg_get_header(conn,h1);	//get the length of post data
	int clen = atoi(clength);
	char *pdata = (char *)malloc(clen+clen/8+1);
	int datalen = mg_read(conn,pdata,clen);	//read post data
	pdata[clen] = '\0';
	/*mg_get_var(pdata, strlen(pdata == NULL ? "" : pdata), "text", text, sizeof(text));
	std::string path(text);*/
	is_jsonp = handle_jsonp(pdata,conn, request_info);	//find the callback function

	ss<<"[";
	t6sniffer.ClearT6();
	t6sniffer.snifftcp6();
	std::set<std::string> t6list = t6sniffer.tcp6ports();
	for (std::set<std::string>::iterator it=t6list.begin(); it != t6list.end(); it++)
	{
		std::string tempstr = HTMLEncode(*it);
		ss<<"{item: \""<<tempstr<<"\"},";
	}
	ss<<"]";
	msg = ss.str();
	json = msg.c_str();
	mg_printf(conn, "%s", json);	//print json array to the connection
	if (is_jsonp) 
	{
		mg_printf(conn, "%s", ")");	//print closing bracket for the function
	}
	//t6sniffer.savetcp6Ports();
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}

//function to send tcp4 port list
void Executive::tcp4Reply(struct mg_connection *conn, const struct mg_request_info *request_info)
{
	try{
	int is_jsonp;
	const char * json;
	std::stringstream ss;
	std::string msg;
	mg_printf(conn, "%s\r\n", json_reply_start);	//prints the json message starting headers
	const char * clength;
	char h1[] = "Content-Length";
	clength = mg_get_header(conn,h1);	//get the length of post data
	int clen = atoi(clength);
	char *pdata = (char *)malloc(clen+clen/8+1);
	int datalen = mg_read(conn,pdata,clen);	//read post data
	pdata[clen] = '\0';
	/*mg_get_var(pdata, strlen(pdata == NULL ? "" : pdata), "text", text, sizeof(text));
	std::string path(text);*/
	is_jsonp = handle_jsonp(pdata,conn, request_info);	//find the callback function
	ss<<"[";
	t4sniffer.ClearT4();
	t4sniffer.snifftcp4();	//sniff for tcp4 ports
	std::set<std::string> t4list = t4sniffer.tcp4ports();	//get tcp4 port list
	for (std::set<std::string>::iterator it=t4list.begin(); it != t4list.end(); it++)
	{
		std::string tempstr = HTMLEncode(*it);
		ss<<"{item: \""<<tempstr<<"\"},";
	}
	ss<<"]";
	msg = ss.str();
	json = msg.c_str();
	mg_printf(conn, "%s", json);	//print json array to the connection
	if (is_jsonp) 
	{
		mg_printf(conn, "%s", ")");	//print closing bracket for the function
	}
	//t4sniffer.savetcp4Ports();
	}catch(std::exception ex){std::cout << "\n  " << ex.what() << "\n\n";}
}


////////////////////////////////////////////////////////////////////////////////////////////
///Callback function of the server, called whenever there is a new message to the server
void * Executive::callback(enum mg_event event, struct mg_connection *conn, const struct mg_request_info *request_info) 
{
	char temp[] = "yes";
	void *processed = temp;
	Executive ex;
	if (event == MG_NEW_REQUEST) 
	{
		printf("\nUri: %s\n",request_info->uri);
		if(strcmp(request_info->uri,"/ajax/tcp4") == 0)	//checking the URI for tcp4 port sniffing
			ex.tcp4Reply(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/udp4") == 0)	//checking the URI for udp4 port sniffing
			ex.udp4Reply(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/tcp6") == 0)	//checking the URI for tcp6 port sniffing
			ex.tcp6Reply(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/udp6") == 0)	//checking the URI for udp6 port sniffing
			ex.udp6Reply(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/procmsg") == 0)	//checking the URI for process sniffing
			ex.procReply(conn,request_info);	
		else if(strcmp(request_info->uri,"/ajax/filemsg") == 0)	//checking the URI for file sniffing
			ex.listReply(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/savefiles") == 0)	//checking the URI for file sniffing
			ex.savefiles(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/saveprocs") == 0)	//checking the URI for file sniffing
			ex.saveprocs(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/savet4") == 0)	//checking the URI for file sniffing
			ex.savet4(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/saveu4") == 0)	//checking the URI for file sniffing
			ex.saveu4(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/savet6") == 0)	//checking the URI for file sniffing
			ex.savet6(conn,request_info);
		else if(strcmp(request_info->uri,"/ajax/saveu6") == 0)	//checking the URI for file sniffing
			ex.saveu6(conn,request_info);
		else
			processed = NULL;		//return null if not an ajax call, mongoose will return a file instead
	}
	else 
		processed = NULL;
	return processed;
}
////////////////////////////////////////////////////////////////
///Starts server and listens on port 8080
void Executive::startServer()
{
	try{
	struct mg_context *ctx;
	const char *options[] = { "document_root", "html","listening_ports", "8080", NULL};	//providing html as the root folder

	ctx = mg_start(&callback, NULL, options);	//register callback function
	printf("\nServer Started\n");
	getchar();  // Wait until user hits "enter"
	mg_stop(ctx);
	}catch(std::exception ex){std::cout<<ex.what();}
}


///////////////////////////////////////////
////////////TEST STUB /////////////////////
///////////////////////////////////////////
#ifdef TEST_EXECUTIVE
int main(void) {
	Executive server;
	server.startServer();

}
#endif
