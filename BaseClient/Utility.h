//
//  Utility.h
//  BaseClient
//
//  Created by Qiyu Tan on 3/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BaseClient_Utility_h
#define BaseClient_Utility_h

#define DELETE_S(p)	do{	 \
                            if(p)	delete (p);	\
                            p = NULL;	\
                        }while(0)

#define CHECK_R(x) do{ if(!x) return false; } while(0)

#endif
