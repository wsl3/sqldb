#include <iostream>
#include "src/dstring.h"
#include"src/dlist.h"
#include "src/dmap.h"
#include "sqlClick/sqlcli.h"

using namespace std;

int main() {

//    DBMap* p = new DBMap(8);
//
//    DBString* v1 = new DBString("wsl");
//    DBList* v2 = new  DBList();
//    v2->appendl("123");
//
//    DBMap* v3 = new DBMap();
//
//    p->insert("1", v1);
//    p->insert("2", v2);
//    p->insert("3", v3);
//    p->insert("4", v3);
//    p->insert("5", v3);
//    p->insert("6", v3);
//    p->insert("7", v3);
//
//    p->keys();
//    cout<<endl;
//    p->traversal();
//    for(int i=0;i<p->ht->size;i++){
//        if(p->ht->entrys[i] != nullptr){
//            cout<<p->ht->entrys[i]->value->values()<<endl;
//        }
//    }
//
//    DBMap m = *p;
//    for(int i=0;i<m.ht->size;i++){
//        if(m.ht->entrys[i] == nullptr){
//            cout<<i<<"---> NULL"<<endl;
//        }else{
//            cout<<i;
//            auto *p=m.ht->entrys[i];
//            while(p != nullptr){
//                cout<<"---> "<<"( "<<p->key->buff<<", "<<p->value->type<<" )";
//                p = p->next;
//            }
//            cout<<endl;
//        }
//    }

    vector<string> test;
    test = readCommand();


    for(unsigned long i=0;i<test.size();i++){
        cout<<test[i]<<endl;
    }
    return 0;
}