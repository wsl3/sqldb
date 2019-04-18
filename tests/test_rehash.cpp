//
// Created by wsl on 19-4-18.
//

#include <iostream>
#include "../src/dstring.h"
#include"../src/dlist.h"
#include "../src/dmap.h"

using namespace std;

int main() {

    DBMap* p = new DBMap(8);

    DBString* v1 = new DBString("wsl");
    DBList* v2 = new  DBList();
    v2->appendl("123");

    DBMap* v3 = new DBMap();

    p->insert("1", v1);
    p->insert("2", v2);
    p->insert("3", v3);
    p->insert("4", v3);
    p->insert("5", v3);
    p->insert("6", v3);
    cout <<p->ht->used/(p->ht->size*1.0)<<endl;
    p->insert("7", v3);


    p->keys();
    cout<<endl;
    p->traversal();

    cout <<p->ht->used/(p->ht->size*1.0)<<endl;
    return 0;
}