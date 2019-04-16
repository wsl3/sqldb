#include <iostream>
#include "src/dstring.h"
#include"src/dlist.h"
#include "src/dmap.h"

using namespace std;

int main() {
    string s = "wsl";
    string s1 = "wjl";


    DBMap m = DBMap(8);

    DBString* v1 = new DBString(s);
    DBList* v2 = new DBList();

    v2->append(s);
    v2->appendl(s1);

    m.insert(s, v1);
    m.insert(s1, v2);
    m.insert("1", v1);
    m.insert("2", v1);
    m.insert("2", v1);
    m.insert("2", v1);
    m.insert("3", v1);

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