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

#define N_DATA 10

class KeyInt {
public:
    KeyInt(){ key = 0; }
    KeyInt(int keyIn):key(keyIn){}
    
    int GetKey() { return key; }
    void SetKey(int keyIn) { key = keyIn; }
    
    bool operator < (const KeyInt& valtwo) { return this->key<valtwo.key; }
    
private:
    int key;

};

class ValueChar {
public:
    ValueChar() { value = 0;}
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
            arrIn.insert(it, element);
            arrIn.erase(it+1);
            
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

void ShowArray(std::vector<Element<KeyInt, ValueChar>> &arrIn)
{
    for (int idx = 0; idx<arrIn.size(); idx++) {
        std::cout << arrIn[idx].key.GetKey()<<"->"<<arrIn[idx].value.GetValue()<<"\n";
    }
}

int main(int argc, const char * argv[]) {
    std::vector<Element<KeyInt,ValueChar>> arr;
    
    srand (time(NULL));
    
    Element<KeyInt,ValueChar> elemone;
    elemone.key.SetKey(3);
    elemone.value.SetValue('B');
    
    InsertInArray(arr, elemone);

    Element<KeyInt,ValueChar> elemtwo;
    elemtwo.key.SetKey(0);
    elemtwo.value.SetValue('A');
    
    InsertInArray(arr, elemtwo);

    Element<KeyInt,ValueChar> elemthree;
    elemthree.key.SetKey(5);
    elemthree.value.SetValue('A');
    
    InsertInArray(arr, elemthree);

    /*
    for (int idx = 0; idx<N_DATA; idx++) {
        Element<KeyInt,ValueChar> elem;
        
        elem.key.SetKey(rand()%1000);
        elem.value.SetValue(65+rand()%25);
        std::cout << elem.key.GetKey()<<"->"<<elem.value.GetValue()<<"\n";
        InsertInArray(arr, elem);
    }
    */
    
    
    Element<KeyInt,ValueChar> elemfour;
    elemfour.key.SetKey(2);
    elemfour.value.SetValue('B');
    
    InsertInArray(arr, elemfour);
    

    Element<KeyInt,ValueChar> elemfive;
    elemfive.key.SetKey(6);
    elemfive.value.SetValue('A');
    
    InsertInArray(arr, elemfive);

    Element<KeyInt,ValueChar> elemsix;
    elemsix.key.SetKey(1);
    elemsix.value.SetValue('A');
    
    InsertInArray(arr, elemsix);
    
    Element<KeyInt,ValueChar> elemseven;
    elemseven.key.SetKey(0);
    elemseven.value.SetValue('B');
    
    InsertInArray(arr, elemseven);

    Element<KeyInt,ValueChar> elemeight;
    elemeight.key.SetKey(5);
    elemeight.value.SetValue('B');
    
    InsertInArray(arr, elemeight);

    std::cout<<"\n";
    
    ShowArray(arr);
    return 0;
}
