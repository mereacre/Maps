//
//  unittest.h
//  Maps
//
//  Created by Alexandru Mereacre on 03/02/2015.
//  Copyright (c) 2015 Alexandru. All rights reserved.
//

#ifndef Maps_unittest_h
#define Maps_unittest_h
#include <cassert>
#include "intervalMap.hpp"

void TestInitialInterval()
{
    char initValue = 'A';
    
    interval_map<int, char> map(initValue);
    assert(map[std::numeric_limits<int>::min()]==initValue);
}

void TestAddingOneInterval()
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    int keyBegin = 10, keyEnd = 14;
    char secondValue = 'B';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map[keyBegin]==secondValue);
    assert(map[keyEnd]==initValue);
}

void TestAddingTwoIntervals()
{
    
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    int keyBegin = 10, keyEnd = 14;
    char secondValue = 'B';
    map.assign(keyBegin, keyEnd, secondValue);
    

    // Adding interval [11,13) with 'C'
    keyBegin = 11, keyEnd = 13;
    secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);
    
    IntervalMapTest(map);
    
    assert(map[keyBegin]==secondValue);
    assert(map[keyEnd]==initValue);
}

void RunAllTests()
{
    TestInitialInterval();
    TestAddingOneInterval();
    TestAddingTwoIntervals();
}
#endif
