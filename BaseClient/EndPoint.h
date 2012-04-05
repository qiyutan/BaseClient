//
//  EndPoint.h
//  BaseClient
//
//  Created by Qiyu Tan on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BaseClient_EndPoint_h
#define BaseClient_EndPoint_h

#ifdef _POSIX_
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include <string>

namespace BaseClient {
    
    
class EndPoint
{
public:
    EndPoint(in_addr_t ip, int port);
    EndPoint(const char *name, int port);
    
    const char *ip();
    int port();
    
    struct sockaddr *addr();
    
private:
    struct sockaddr_in _addr;
    std::string _ip;
};
    
}


#endif
