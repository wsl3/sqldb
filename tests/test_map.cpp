//
// Created by wsl on 19-4-16.
// testing map
//

#include <iostream>
#include "../src/dstring.h"
#include"../src/dlist.h"
#include "../src/dmap.h"

using namespace std;

int main() {
    string s1 = "字符串";
    string s2 = "链表";
    string s3 = "哈希表";

    DBString* v1 = new DBString(s1);
    DBList* v2 = new DBList();
    v2->append(s1);
    v2->appendl(s2);
    DBMap* v3 = new DBMap();
    v3->insert(s1,v1);

    // test map
    DBMap m = DBMap(8);


    m.insert(s1, v1);
    m.insert(s2, v2);
    m.insert(s3, v3);

    //冲突数据
    m.insert("冲突", v1);
    m.insert("冲突", v1);
    m.insert("冲突", v3);

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