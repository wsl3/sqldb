//
// Created by wsl on 19-4-15.
//

#ifndef SQLDB_DMAP_H
#define SQLDB_DMAP_H

#include "object.h"
#include "dstring.h"


class HashEntry {
public:
    DBString *key = nullptr;
    Object *value = nullptr;

    HashEntry *next = nullptr;


};

class HashTable {
public:
    int size;
    int used;
    HashEntry **entrys;

    explicit HashTable(int s);
};

class DBMap : public Object {
public:

    HashTable *ht;
    int rehash = -1;
    HashTable *ht_temp;


    explicit DBMap(int s = 8);

//    void insert(DBString key, Object value);
};

#include "dmap.cpp"

#endif
