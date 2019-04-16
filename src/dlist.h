//
// Created by wsl on 19-4-10.
//

#ifndef SQLDB_DLIST_H
#define SQLDB_DLIST_H

#include "object.h"
#include "dstring.h"
#include <string>
#include <iostream>

// 链表中的每一个节点
class ListNode : public DBString {
public:

    ListNode *prev = nullptr;
    ListNode *next = nullptr;

    explicit ListNode(std::string v);

};

// 链表
class DBList : public Object {
public:
    ListNode *head = nullptr;
    ListNode *tail = nullptr;
    unsigned long length = 0; //链表的长度

    DBList();

    ~DBList() override;

    std::string values() override;
    void append(std::string v);

    void appendl(std::string v);

    void pop();

    void lpop();

    void traversal();

    void sort();

    void insert(std::string v, int index);

    void del(int index);
};

//链表节点构造函数
ListNode::ListNode(std::string v) : DBString(v) {

}


//链表构造函数
DBList::DBList() : Object(DBLIST_OBJECT) {
}

//链表析构函数
DBList::~DBList() {
    std::cout<<"delete DBList"<<std::endl;
    while (head != nullptr) {
        auto *p = head;
        head = head->next;
        delete p;
    }

}

std::string DBList::values(){
    return "List Values";
}




//链表添加元素
void DBList::append(std::string v) {
    if (length == 0) {
        head = new ListNode(v);
        tail = head;

    } else {
        auto *p = new ListNode(v);
        p->prev = tail;
        tail->next = p;
        tail = p;
    }
    length += 1;

}

//链表最前侧添加元素
void DBList::appendl(std::string v) {
    if (length == 0) {
        append(v);
        return;
    } else {
        auto *p = new ListNode(v);
        head->prev = p;
        p->next = head;
        head = p;
        length += 1;
        return;
    }

}

//链表pop最后元素
void DBList::pop() {
    if (length == 0) {
        return;
    } else if (length == 1) {
        delete tail;
        tail = nullptr;
        head = nullptr;

    } else {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }
    length -= 1;
}

//链表pop最前面的元素
void DBList::lpop() {
    if (length == 0 || length == 1) {
        pop();
    } else {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }
    length -= 1;
}

void DBList::traversal() {
    int i;
    auto *p = head;
    for (i = 1; p != nullptr; i++, p = p->next) {
        std::cout << i << " : " << p->buff << std::endl;
    }
}

void DBList::sort() {

}

void DBList::insert(std::string v, int index) {

}

void DBList::del(int index) {

}

#endif //SQLDB_DLIST_H
