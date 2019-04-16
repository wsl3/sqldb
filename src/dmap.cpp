//
// Created by wsl on 19-4-15.
//
#include "dmap.h"

//构造函数
DBMap::DBMap(size_t s) : Object(DBMAP_OBJECT) {
    rehash = -1;
    ht_temp = nullptr;
    ht = new HashTable(s);
}

HashEntry::HashEntry(DBString *key, Object *value) {
    this->key = key;
    this->value = value;
}

HashTable::HashTable(size_t s) {
    used = 0;
    size = s;
    entrys = new HashEntry *[size];
    for (int i = 0; i < size; i++) {
        entrys[i] = nullptr;
    }
}

//成员函数
size_t DBMap::hashFunc(std::string key) {
    return hasher(key) & (ht->size - 1);
}

void DBMap::insert(std::string key, Object *value) {
    size_t index = hashFunc(key);
    DBString *key_p = new DBString(key);
    if (ht->entrys[index] == nullptr) {
        ht->entrys[index] = new HashEntry(key_p, value);
    } else {
        HashEntry *p = ht->entrys[index];
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = new HashEntry(key_p, value);
    }
    ht->used += 1;
}