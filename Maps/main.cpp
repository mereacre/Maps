//
//  main.cpp
//  Maps
//
//  Created by Alexandru on 01/02/2015.
//  Copyright (c) 2015 Alexandru. All rights reserved.
//

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <map>
#include "unittest.h"

# ifdef _NDEBUG
# undef _STLP_DEBUG
# else
# define _STLP_DEBUG 1
# endif

int main(int argc, const char * argv[]) {
    
    interval_map<int,char> test(0);
    IntervalMapTest(test);
    
    return 0;
}
