//
//  unittest.h
//  Maps
//
//  Created by Alexandru Mereacre on 03/02/2015.
//  Copyright (c) 2015 Alexandru. All rights reserved.
//

#ifndef Maps_unittest_h
#define Maps_unittest_h

#include <time.h>
#include <stdlib.h>
#include <cassert>
#include <array>
#include "intervalMap.hpp"

template<class K, class V>
void TestInitialInterval(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    
    interval_map<int, char> map(initValue);
    assert(map.m_map.find(std::numeric_limits<int>::min())->second==initValue);
}

template<class K, class V>
void TestAddingOneInterval(interval_map<K,V> &mapIn)
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

template<class K, class V>
void TestAddingTwoIntervals(interval_map<K,V> &mapIn)
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

template<class K, class V>
void TestAddingThreeIntervals(interval_map<K,V> &mapIn)
{
    
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    
    // Adding interval [11,13) with 'A'
    //[-infty,A][10,B][11,A]
    int keyBegin = 11, keyEnd = 13;
    char secondValue = 'A';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBeginPrev)->second==secondValuePrev);
    assert(map.m_map.find(keyBegin)->second==initValue);
    assert(map.m_map.size()==3);
}

template<class K, class V>
void TestAddingTwoNegativeIntervals(interval_map<K,V> &mapIn)
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

template<class K, class V>
void TestAddingOverlapingOneInterval(interval_map<K,V> &mapIn)
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

template<class K, class V>
void TestAddingOverlapingSameInterval(interval_map<K,V> &mapIn)
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

template<class K, class V>
void TestAddingOverlapingSameOneInterval(interval_map<K,V> &mapIn)
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

template<class K, class V>
void TestAddingOverlapingSameTwoInterval(interval_map<K,V> &mapIn)
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

template<class K, class V>
void TestAddingOverlapingSameThreeInterval(interval_map<K,V> &mapIn)
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
    int keyBegin = -1, keyEnd = 7;
    char secondValue = 'A';
    map.assign(keyBegin, keyEnd, secondValue);
    
    
    assert(map.m_map.find(keyBegin)==map.m_map.end());
    assert(map.m_map.find(keyEnd)==map.m_map.end());
    assert(map.m_map.find(keyBeginPrev)->second==secondValuePrev);
    assert(map.m_map.find(keyEndPrev)->second==initValue);
}

template<class K, class V>
void TestAddingEndInterval(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);

    // Adding interval [15,20) with 'A'
    //[-infty,A][10,B][14,A]
    int keyBegin = 15, keyEnd = 20;
    char secondValue = 'A';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBegin)==map.m_map.end());
    assert(map.m_map.find(keyEnd)==map.m_map.end());
    assert(map.m_map.find(keyBeginPrev)->second==secondValuePrev);
    assert(map.m_map.find(keyEndPrev)->second==initValue);
}

template<class K, class V>
void TestAddingEndOneInterval(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [9,std::numeric_limits<int>::max()) with 'C'
    //[-infty,A][9,C]
    int keyBegin = 9, keyEnd = std::numeric_limits<int>::max();
    char secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBeginPrev)==map.m_map.end());
    assert(map.m_map.find(keyEndPrev)==map.m_map.end());
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)==map.m_map.end());
}

template<class K, class V>
void TestAddingEndTwoInterval(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [9,std::numeric_limits<int>::max()) with 'C'
    //[-infty,A][9,C]
    int keyBegin = 9, keyEnd = std::numeric_limits<int>::max();
    char secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);

    // Adding interval [12,15) with 'B'
    //[-infty,A][9,C][12,B][15,C]
    keyBeginPrev = 12, keyEndPrev = 15;
    secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)==map.m_map.end());
    assert(map.m_map.find(keyBeginPrev)->second==secondValuePrev);
    assert(map.m_map.find(keyEndPrev)->second==secondValue);
}

template<class K, class V>
void TestAddingBeginningInterval(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [std::numeric_limits<int>::min(),10) with 'C'
    //[-infty,C][10,B][14,A]
    int keyBegin = std::numeric_limits<int>::min(), keyEnd = 10;
    char secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)->second==secondValuePrev);
    assert(map.m_map.find(keyEndPrev)->second==initValue);
    assert(map.m_map.size()==3);
}

template<class K, class V>
void TestAddingWholeInterval(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [std::numeric_limits<int>::min(),std::numeric_limits<int>::max()) with 'C'
    //[-infty,C]
    int keyBegin = std::numeric_limits<int>::min(), keyEnd = std::numeric_limits<int>::max();
    char secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.size()==1);
}

template<class K, class V>
void TestKeysInequality(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [7,3) with 'C'
    //[-infty,A][10,B][14,A]
    int keyBegin = 7, keyEnd = 3;
    char secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBeginPrev)->second==secondValuePrev);
    assert(map.m_map.find(keyEndPrev)->second==initValue);
    assert(map.m_map.size()==3);
}

template<class K, class V>
void TestEqualKeys(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    // Adding interval [10,14) with 'B'
    //[-infty,A][10,B][14,A]
    int keyBeginPrev = 10, keyEndPrev = 14;
    char secondValuePrev = 'B';
    map.assign(keyBeginPrev, keyEndPrev, secondValuePrev);
    
    // Adding interval [10,14) with 'C'
    //[-infty,A][10,C][14,A]
    int keyBegin = 10, keyEnd = 14;
    char secondValue = 'C';
    map.assign(keyBegin, keyEnd, secondValue);
    
    assert(map.m_map.find(keyBegin)->second==secondValue);
    assert(map.m_map.find(keyEnd)->second==initValue);
    assert(map.m_map.size()==3);
}

template<class K, class V>
void TestCanonicityMap(interval_map<K,V> &mapIn)
{
    typename std::map<K,V>::iterator it = mapIn.m_map.begin(), nextit;
    nextit = it; ++nextit;
    
    for(; nextit!=mapIn.m_map.end(); ++nextit,++it)
        assert(nextit->second!=it->second);
}

template<class K, class V>
void TestCanonicity(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);
    
    srand (time(NULL));
    
    int arraySize = 100000;
    
    for (int idx=0; idx<arraySize; idx++) {
        int keyBegin = rand()%arraySize, keyEnd = rand()%arraySize;
        char secondValue = 'A'+rand()%24;
        map.assign(keyBegin, keyEnd, secondValue);
    }
    
    TestCanonicityMap(map);
}

template<class K, class V>
void TestCompareArray(interval_map<K,V> &mapIn)
{
    char initValue = 'A';
    interval_map<int, char> map(initValue);

    const int arraySize = 1000;
    std::array<char, arraySize> arr;
    
    arr.fill(initValue);
    
    for (int idx=0; idx<arraySize; idx++) {
        int keyBegin = rand()%(arraySize-1), keyEnd = rand()%(arraySize-1);
        char secondValue = 'A'+rand()%24;
        
        if(keyBegin>keyEnd) continue;
        
        for(int j=keyBegin; j<keyEnd; j++)
            arr[j] = secondValue;
        
        map.assign(keyBegin, keyEnd, secondValue);
    }
    
    TestCanonicityMap(map);
    
    std::map<int,char>::iterator it = map.m_map.begin(), nextit;
    nextit = it;
    ++it; ++nextit; ++nextit;
    
    for(; nextit!=map.m_map.end(); ++nextit,++it) {
        for( int idx=it->first; idx<nextit->first; idx++) {
            assert(it->second=arr[idx]);
        }
    }
}

template<class K, class V>
void IntervalMapTest(interval_map<K,V> &mapIn)
{
    TestInitialInterval(mapIn);
    TestAddingOneInterval(mapIn);
    TestAddingTwoIntervals(mapIn);
    TestAddingThreeIntervals(mapIn);
    TestAddingTwoNegativeIntervals(mapIn);
    TestAddingOverlapingSameInterval(mapIn);
    TestAddingOverlapingSameOneInterval(mapIn);
    TestAddingOverlapingSameTwoInterval(mapIn);
    TestAddingOverlapingSameThreeInterval(mapIn);
    TestAddingEndInterval(mapIn);
    TestAddingEndOneInterval(mapIn);
    TestAddingEndTwoInterval(mapIn);
    TestAddingBeginningInterval(mapIn);
    TestAddingWholeInterval(mapIn);
    TestAddingOverlapingOneInterval(mapIn);
    TestKeysInequality(mapIn);
    TestEqualKeys(mapIn);
    TestCanonicity(mapIn);
    TestCompareArray(mapIn);
}

#endif
