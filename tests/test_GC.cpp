//
// Created by wsl on 19-4-16.
//

#include <iostream>
#include "../src/dstring.h"
#include"../src/dlist.h"
#include "../src/dmap.h"
using namespace std;

int main() {

    DBMap* p = new DBMap(10);

    DBString* v1 = new DBString("wsl");
    DBList* v2 = new  DBList();
    v2->appendl("123");

    DBMap* v3 = new DBMap();

    p->insert("1", v1);
    p->insert("2", v2);
    p->insert("3", v3);

    for(int i=0;i<p->ht->size;i++){
        if(p->ht->entrys[i] != nullptr){
            cout<<p->ht->entrys[i]->value->values()<<endl;
        }
    }

    DBMap m = *p;
    for(int i=0;i<m.ht->size;i++){
        if(m.ht->entrys[i] == nullptr){
            cout<<i<<"---> NULL"<<endl;
        }else{
            cout<<i;
            auto *p=m.ht->entrys[i];
            while(p != nullptr){
                cout<<"---> "<<"( "<<p->key->buff<<", "<<p->value->type<<" )";
                p = p->next;
            }
            cout<<endl;
        }
    }

    cout << endl;
    return 0;
}