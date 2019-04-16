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

DBMap::~DBMap() {
    std::cout<<"delete DBMap"<<"\n";
    delete ht;
}

HashEntry::HashEntry(DBString *key, Object *value) {
    this->key = key;
    this->value = value;
}

HashEntry::~HashEntry() {
    std::cout<<"delete HashEntry"<<std::endl;
    delete key;
    delete value;
}

HashTable::HashTable(size_t s) {
    used = 0;
    size = s;
    entrys = new HashEntry *[size];
    for (int i = 0; i < size; i++) {
        entrys[i] = nullptr;
    }
}

HashTable::~HashTable() {
    std::cout<<"delete ht"<<std::endl;
    for (int i = 0; (i < size) && (used > 0); i++) {
        if (entrys[i] != nullptr) {
            delete entrys[i];
            used -= 1;
        }
    }
}

//成员函数
size_t DBMap::hashFunc(std::string key) {
    return hasher(key) & (ht->size - 1);
}


// 向哈希表中添加数据的时候, 如果有Key则只改变对应的value
void DBMap::insert(std::string key, Object *value) {
    size_t index = hashFunc(key);
    DBString *key_p = new DBString(key);
    if (ht->entrys[index] == nullptr) {
        ht->entrys[index] = new HashEntry(key_p, value);
    } else {
        HashEntry *p = ht->entrys[index];
        HashEntry *prev = p;
        while (p != nullptr) {
            // check key
            if (p->key->buff == key) {
                delete p->value;
                p->value = value;
                return;
            }
            prev = p;
            p = p->next;
        }
        prev->next = new HashEntry(key_p, value);
    }
    // used+1
    ht->used += 1;
}

void DBMap::traversal() {
    std::cout << "size: " << ht->size << " used: " << ht->used << std::endl;
    for (int i = 0; i < ht->size; i++) {
        if (ht->entrys[i] == nullptr) {
            std::cout << i << "---> NULL" << std::endl;
        } else {
            std::cout << i;
            auto *p = ht->entrys[i];
            while (p != nullptr) {
                std::cout << "---> " << "( " << p->key->buff << ", " << p->value->type << " )";
                p = p->next;
            }
            std::cout << std::endl;
        }
    }
}

Object *DBMap::get(std::string key) {
    size_t index = hashFunc(key);
    if (ht->entrys[index] == nullptr) {
        return nullptr;
    } else {
        auto *p = ht->entrys[index];
        while (p != nullptr) {
            if (p->key->buff == key) {
                return p->value;
            } else {
                p = p->next;
            }
        }
        return nullptr;
    }
}

std::string DBMap::values(){
    return "Map values";
}