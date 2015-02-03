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
//#include "intervalMap.hpp"
#include "unittest.h"

template<class K, class V>
void IntervalMapTest(interval_map<K,V>& inMap)
{
    /*typename std::map<K,V>::const_iterator it = inMap.m_map.begin();
     for(;it!=inMap.m_map.end(); ++it)
     std::cout<<it->first<<" -> "<<it->second<<"\n";
     */
}

int main(int argc, const char * argv[]) {
    
    RunAllTests();
    return 0;
}
