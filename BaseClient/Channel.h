//
//  Channel.h
//  BaseClient
//
//  Created by Qiyu Tan on 4/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BaseClient_Channel_h
#define BaseClient_Channel_h

namespace BaseClient {
    
typedef enum
{
    kChannelTypeTcp,
    kChannelTypeUdp
}ChannelType;
    
    
#ifdef _POSIX_
    typedef int socket_t;
#else
    typedef SOCKET socket_t;
#endif

class Channel
{
public:
    static Channel *create(ChannelType type);
    static void destroy(Channel *c);
    
};
    
}

#endif
