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

//    m.insert(s, v1);
//    m.insert(s1, v2);


    m.insert("2", v1);
    m.insert("2", v2);
//    m.insert("3", v1);

    m.traversal();

    cout << endl;
    return 0;
}