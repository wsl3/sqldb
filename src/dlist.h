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

    void range(int begin, int end);

    void pop();

    void lpop();

    void traversal();

    void sort(bool reverse=false);

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
    std::cout << "delete DBList" << std::endl;
    while (head != nullptr) {
        auto *p = head;
        head = head->next;
        delete p;
    }

}

std::string DBList::values() {
    traversal();
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
    std::cout<<std::endl;
    for (i = 1; p != nullptr; i++, p = p->next) {
        std::cout << i << "): " << p->buff << std::endl;
    }
    std::cout<<std::endl;
}

// to be updated
void DBList::sort(bool reverse) {
    auto *p = head;
    auto *q = tail;
    for(;p!=nullptr;p=p->next){
        for(q=tail;q!=p;q=q->prev){
            // reverse == false --> increment
            if(!reverse && (p->buff > q->buff)){
                std::string temp = p->buff;
                p->buff = q->buff;
                q->buff = temp;
            }else if (reverse && (p->buff < q->buff)){
                std::string temp = p->buff;
                p->buff = q->buff;
                q->buff = temp;
            }
        }
    }
}

// 如果index>length 默认insert到最后
void DBList::insert(std::string v, int index) {
    if (index < 0) {
        std::cout << "Error: index can't < 0!" << std::endl;
        return;
    }
    if(index == 0){
        appendl(v);
        return;
    }
    if(index>=length){
        append(v);
        return;
    }
    auto *p = head;
    int i=0;
    while(i<index){ i++;p=p->next;}
    ListNode* temp = new ListNode(v);
    temp->prev = p->prev;
    temp->next = p;
    p->prev->next = temp;
    p->prev = temp;

}

void DBList::del(int index) {
    if (index < 0 || index >= length) {
        std::cout << "I can't del it!" << std::endl;
        return;
    }
    if (index == 0) {
        lpop();
        return;
    }
    auto *p = head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    p->prev->next = p->next;
    delete p;
    length--;
}

void DBList::range(int begin, int end) {

    if (begin > (length - 1) || end < 0 || begin > end) {
        std::cout << "Error: Index is error!" << std::endl;
        return;
    }
    int i = 0;
    auto *p = this->head;
    while (i != begin) {
        i++;
        p = p->next;
    }
    while (begin <= end && p != nullptr) {
        std::cout << begin << "): " << p->buff << std::endl;
        begin++;
        p = p->next;
    }
}

#endif //SQLDB_DLIST_H
