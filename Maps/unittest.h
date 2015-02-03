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
    assert(map.m_map.find(std::numeric_limits<int>::min())->second==initValue);
}

void TestAddingOneInterval()
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBegin = 10, keyEnd = 14;
    char secondValue = 'B';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)->second==initValue);
}

void TestAddingTwoIntervals()
{
    
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    int keyBegin = 10, keyEnd = 14;
    char secondValuePrev = 'B';
    map.assign(keyBegin, keyEnd, secondValuePrev);
    

    // Adding interval [11,13) with 'C'
    //[-infty,A][10,B][11,C][13,B][14,A]
    keyBegin = 11, keyEnd = 13;
    char secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)->second==secondValuePrev);
}

void TestAddingTwoNegativeIntervals()
{
    
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    int keyBegin = 10, keyEnd = 14;
    char secondValuePrev = 'B';
    map.assign(keyBegin, keyEnd, secondValuePrev);
    
    
    // Adding interval [-5,7) with 'C'
    //[-infty,A][-5,C][7,A][10,B][14,A]
    keyBegin = -5, keyEnd = 7;
    char secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)->second==initValue);
}

void TestAddingOverlapingOneInterval()
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [5,12) with 'C'
    //[-infty,A][5,C][12,B][14,A]
    int keyBegin = 5, keyEnd = 12;
    char secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);
    
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)->second==secondValuePrev);
    assert(map.m_map.find(keyBeginPrev)==map.m_map.end());
}

void TestAddingOverlapingSameInterval()
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [5,12) with 'B'
    //[-infty,A][5,B][14,A]
    int keyBegin = 5, keyEnd = 12;
    char secondValue = 'B';
    map.assign(keyBegin, keyEnd, secondValue);
    
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)==map.m_map.end());
    assert(map.m_map.find(keyEndPrev)->second==initValue);
}

void TestAddingOverlapingSameOneInterval()
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [5,15) with 'B'
    //[-infty,A][5,B][15,A]
    int keyBegin = 5, keyEnd = 15;
    char secondValue = 'B';
    map.assign(keyBegin, keyEnd, secondValue);
    
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)->second==initValue);
    assert(map.m_map.find(keyBeginPrev)==map.m_map.end());
    assert(map.m_map.find(keyEndPrev)==map.m_map.end());
}

void TestAddingOverlapingSameTwoInterval()
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [12,13) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBegin = 12, keyEnd = 13;
    char secondValue = 'B';
    map.assign(keyBegin, keyEnd, secondValue);
    
    
    assert(map.m_map.find(keyBegin)==map.m_map.end());
    assert(map.m_map.find(keyEnd)==map.m_map.end());
    assert(map.m_map.find(keyBeginPrev)->second==secondValuePrev);
    assert(map.m_map.find(keyEndPrev)->second==initValue);
}

void TestAddingOverlapingSameThreeInterval()
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [-1,7) with 'A'
    //[-infty,A][10,B][14,A]
    int keyBegin = -1, keyEnd = 13;
    char secondValue = 'B';
    map.assign(keyBegin, keyEnd, secondValue);
    
    
    assert(map.m_map.find(keyBegin)==map.m_map.end());
    assert(map.m_map.find(keyEnd)==map.m_map.end());
    assert(map.m_map.find(keyBeginPrev)->second==secondValuePrev);
    assert(map.m_map.find(keyEndPrev)->second==initValue);
}

void RunAllTests()
{
    TestInitialInterval();
    TestAddingOneInterval();
    TestAddingTwoIntervals();
    TestAddingTwoNegativeIntervals();
    TestAddingOverlapingSameInterval();
    TestAddingOverlapingSameOneInterval();
    TestAddingOverlapingSameTwoInterval();
    TestAddingOverlapingSameThreeInterval();
}

#endif
