#include <iostream>
#include "src/dstring.h"
#include"src/dlist.h"
#include "src/dmap.h"

using namespace std;

int main() {
    std::string s = "wsl";
    DBMap m = DBMap(2);
    if(m.ht->entrys[0] == nullptr){
        cout<<"1"<<endl;
    }
    if(m.ht->entrys[1] == nullptr){
        cout<<"2"<<endl;
    }
    cout << endl;
    return 0;
}