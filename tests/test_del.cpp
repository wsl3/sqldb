//
// Created by wsl on 19-4-30.
//
#include <iostream>
#include "../src/dstring.h"
#include"../src/dlist.h"
#include "../src/dmap.h"
using namespace std;

int main() {

    DBMap* p = new DBMap(10);

    DBString* v1 = new DBString("wsl");
    DBMap* v3 = new DBMap();

    p->insert("1", v1);
    p->insert("2", v1);
    p->insert("3", v3);
    p->insert("4", v3);
    p->insert("5", v3);
    p->insert("6", v3);
    p->insert("7", v3);


    p->traversal();
    p->del("6");
    p->traversal();

    return 0;
}
