//
//  EndPoint.cpp
//  BaseClient
//
//  Created by Qiyu Tan on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "EndPoint.h"

namespace BaseClient
{
    
EndPoint::EndPoint(in_addr_t ip, int port)
{
    memset(&_addr, 0, sizeof(_addr));
    _addr.sin_addr.s_addr = ip;
    _addr.sin_port = port;
    _addr.sin_family = AF_INET;
    _addr.sin_len = sizeof(_addr);
    _ip = inet_ntoa(_addr.sin_addr);
}
    
EndPoint::EndPoint(const char *ip, int port)
    :_ip(ip)
{
    memset(&_addr, 0, sizeof(_addr));
    struct in_addr iaddr;
    inet_aton(ip, &iaddr);
    _addr.sin_addr = iaddr; 
    _addr.sin_port = port;
    _addr.sin_family = AF_INET;
    _addr.sin_len = sizeof(_addr);
}
    
const char *EndPoint::ip()
{
    return _ip.c_str();
}
    
int EndPoint::port()
{
    return _addr.sin_port;
}
    
struct sockaddr *EndPoint::addr()
{
    return (struct sockaddr*)(&_addr);
}
    
}
