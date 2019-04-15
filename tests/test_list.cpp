//
// Created by wsl on 19-4-15.
//
#include "../src/dlist.h"
#include <iostream>
using namespace std;
int main()
{
    DBList p = DBList();
    p.append("wsl");
    p.appendl("wjl");
    p.appendl("徐jj");
    p.traversal();

    cout<<endl;

    p.pop();
    p.lpop();
    p.traversal();
    return 0;
}