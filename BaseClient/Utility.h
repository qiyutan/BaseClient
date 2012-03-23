//
//  Utility.h
//  BaseClient
//
//  Created by Qiyu Tan on 3/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BaseClient_Utility_h
#define BaseClient_Utility_h

#define C_DELETE(p)	do{	 \
                            if(p)	delete (p);	\
                            p = NULL;	\
                        }while(0)


#endif
