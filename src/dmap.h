//
// Created by wsl on 19-4-15.
//

#ifndef SQLDB_DMAP_H
#define SQLDB_DMAP_H

#include "object.h"
#include "dstring.h"
#include <unordered_map>

std::hash<std::string> hasher;

class HashEntry {
public:
    DBString *key = nullptr;
    Object *value = nullptr;

    HashEntry *next = nullptr;

    HashEntry(DBString *key = nullptr, Object *value = nullptr);

    ~HashEntry();

};

class HashTable {
public:
    size_t size;
    size_t used;
    HashEntry **entrys;

    explicit HashTable(size_t s);

    ~HashTable();
};

class DBMap : public Object {
public:

    //决定是否重新哈希
    int rehash = -1;

    HashTable *ht;
    HashTable *ht_temp;

    //构造函数
    explicit DBMap(size_t s = 8);

    ~DBMap() override;

    std::string values() override;

    size_t hashFunc(std::string key);


    void insert(std::string key, Object *value);
    void insert(std::string key, std::string value);
    Object* get(std::string key);
    void del(std::string key);
    void traversal();
    void types(std::string key);
    void keys();
    bool has_key(std::string);
    void rehashCheck();
    void rehashFunction();

};

#include "dmap.cpp"

#endif
