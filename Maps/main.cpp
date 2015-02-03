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

#define N_DATA 10

class KeyInt {
public:
    KeyInt(){ key = -1; }
    KeyInt(int keyIn):key(keyIn){}
    
    int GetKey() const { return key; }
    void SetKey(int keyIn) { key = keyIn; }
    
    
    int GetMin() const { return -1; }
    
private:
    int key;

};

bool operator < (const KeyInt& valone, const KeyInt& valtwo) {
    return valone.GetKey()<valtwo.GetKey();
}

class ValueChar {
public:
    ValueChar() { value = -1;}
    ValueChar(char val):value(val){}
    
    void SetValue(char valueIn) { value = valueIn; }
    
    int GetValue() { return value; }
    
    bool operator == (const ValueChar& valtwo) { return this->value==valtwo.value; }

private:
    char value;
    
};

template<class K, class V>
typedef struct Element {
    K key;
    V value;
};

bool InsertInArray(std::vector<Element<KeyInt,ValueChar>> &arrIn, Element<KeyInt,ValueChar> element)
{
    std::vector<Element<KeyInt,ValueChar>>::iterator it = arrIn.begin(), previt = arrIn.begin();
    
    if(!arrIn.size()) {
        arrIn.push_back(element);
        return 1;
    }
    
    for (;it != arrIn.end(); ++it) {
        if(element.key<(*it).key && !((*it).value==element.value)) {
            if(!((*previt).value==element.value))
                arrIn.insert(it, element);
            return 1;
        }
        else if(!(element.key<(*it).key) && !((*it).value==element.value)) {
            previt = it;
            continue;
        }
        else if(element.key<(*it).key && (*it).value==element.value) {
            arrIn.insert(arrIn.erase(it), element);
            
            if(!((*previt).key<element.key))
                arrIn.erase(previt);
            return 1;
        }
        previt = it;
    }
    
    if(!(element.key<(*previt).key) && !((*previt).value==element.value))
        arrIn.insert(it, element);
    
    return 1;
}

void ShowArray(std::vector<Element<KeyInt, ValueChar>> arrIn)
{
    for (int idx = 0; idx<arrIn.size(); idx++) {
        std::cout << arrIn[idx].key.GetKey()<<"->"<<arrIn[idx].value.GetValue()<<"\n";
    }
}

std::vector<Element<KeyInt, ValueChar>> GenLongArr(std::vector<Element<KeyInt, ValueChar>> &arrIn)
{
    
    std::vector<Element<KeyInt,ValueChar>> arr;
    
    for (int idx = 0; idx<arrIn.size()-1; idx++) {
        int firstIdx = (arrIn[idx].key.GetKey()==arrIn[idx].key.GetMin()) ? 0 : arrIn[idx].key.GetKey();
        for (int j = firstIdx; j<arrIn[idx+1].key.GetKey(); j++)
            arr.push_back(arrIn[idx]);
    }
    
    arr.push_back(arrIn[arrIn.size()-1]);
    
    return arr;
}

std::vector<Element<KeyInt, ValueChar>> GenLongMap(std::multimap<KeyInt,ValueChar> &mmap)
{
    Element<KeyInt,ValueChar> elem;
    
    std::vector<Element<KeyInt,ValueChar>> arr;
    std::multimap<KeyInt,ValueChar>::iterator it = mmap.begin(), nextit = mmap.begin();
    ++nextit;
    while(nextit!=mmap.end()) {
        int firstIdx = ((*it).first.GetKey()==(*it).first.GetMin()) ? 0 : (*it).first.GetKey();
        
        elem.key = (*it).first;
        elem.value = (*it).second;
        
        for (int j = firstIdx; j<(*nextit).first.GetKey(); j++)
            arr.push_back(elem);
        
        it = nextit;
        ++nextit;
    }
    
    elem.key = (*it).first;
    elem.value = (*it).second;
    arr.push_back(elem);
    
    return arr;
}

void ProcessMultiMap(std::multimap<KeyInt,ValueChar> &mmap)
{
    std::multimap<KeyInt,ValueChar>::iterator it = mmap.begin(), nextit = mmap.begin();
    ++nextit;
    
    while(nextit!=mmap.end()) {
        if((*nextit).second.GetValue()==(*it).second.GetValue())
            nextit = mmap.erase(nextit);
        else {
            it = nextit;
            ++nextit;
        }
    }
}

bool CompareArrMap(std::vector<Element<KeyInt, ValueChar>> &arrIn, std::multimap<KeyInt,ValueChar> &mmap)
{
    std::vector<Element<KeyInt,ValueChar>>::iterator itArr = arrIn.begin();
    std::multimap<KeyInt,ValueChar>::iterator itMap = mmap.begin();
    if(arrIn.size()!=mmap.size()) {
        std::cout<<"Diffent sizes: "<<arrIn.size()<<" "<<mmap.size()<<"\n";
        return 0;
    }
    for(;itArr!=arrIn.end();++itArr,++itMap) {
        if((*itArr).key.GetKey()!=(*itMap).first.GetKey() || (*itArr).value.GetValue()!=(*itMap).second.GetValue()) {
            std::cout<<"Different keys or values "<<(*itArr).key.GetKey()<<":"<<(*itMap).first.GetKey()<<"|"<<(*itArr).value.GetValue()<<":"<<(*itMap).second.GetValue()<<"\n";
            return 0;
        }
    }
    return 1;
}

void InsertIntoMap(std::multimap<KeyInt,ValueChar> &mmap, KeyInt keyBegin, KeyInt keyEnd, ValueChar val)
{
    std::multimap<KeyInt,ValueChar>::iterator itKeyEnd = mmap.upper_bound(keyEnd);
    std::multimap<KeyInt,ValueChar>::iterator itKeyBegin = mmap.lower_bound(keyBegin);
    std::multimap<KeyInt,ValueChar>::iterator nextit = mmap.erase(itKeyBegin, itKeyEnd);
    
    mmap.insert(nextit, std::make_pair(keyBegin, val));
    ProcessMultiMap(mmap);
}

int main(int argc, const char * argv[]) {
    std::vector<Element<KeyInt,ValueChar>> arr;
    std::multimap<KeyInt,ValueChar> multiMap;
    
    srand (time(NULL));
    
    Element<KeyInt,ValueChar> elem;
    
    KeyInt key = elem.key;
    ValueChar value = elem.value;
    
    InsertInArray( arr, elem);
    multiMap.insert(std::make_pair(key, value));
    

    for (int idx = 0; idx<N_DATA; idx++) {
        Element<KeyInt,ValueChar> elem;
        
        elem.key.SetKey(rand()%5);
        elem.value.SetValue(65+rand()%5);
        
        key = elem.key;
        value = elem.value;
        
        multiMap.insert(std::make_pair(key, value));
        //ProcessMultiMap(multiMap);
        
        std::cout <<">"<< elem.key.GetKey()<<"->"<<elem.value.GetValue()<<"\n";
        InsertInArray( arr, elem);
        ShowArray(arr);
        std::cout<<"\n";
    }
    
    std::multimap<KeyInt,ValueChar>::iterator it = multiMap.begin();
    ProcessMultiMap(multiMap);
    
    
    std::cout<<"\n";
    it = multiMap.begin();
    for(;it!=multiMap.end(); ++it) {
        std::cout << (*it).first.GetKey()<<"->"<<(*it).second.GetValue()<<"\n";
    }

    std::cout<<"::\n";
    ShowArray(GenLongMap(multiMap));
    std::cout<<"[]\n";
    ShowArray(GenLongArr(arr));
    
    //if(!CompareArrMap(arr, multiMap))
    //    return 1;
    return 0;
}
