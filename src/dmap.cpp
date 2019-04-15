//
// Created by wsl on 19-4-15.
//
#include "dmap.h"

DBMap::DBMap(int s) : Object(DBMAP_OBJECT) {


    rehash = -1;
    ht_temp = nullptr;
    ht = new HashTable(s);
}

HashTable::HashTable(int s) {
    int size = s;
    int used = 0;

    //entrys指向指针数组
    entrys = new HashEntry *[size];
    for (int i = 0; i < size; i++) {
        entrys[i] = nullptr;
    }
}