//
// Created by wsl on 19-4-20.
//

#ifndef SQLDB_VM_H
#define SQLDB_VM_H

#include <vector>
#include "compile.h"
#include "cmdobjects.h"
#include "../src/dmap.h"

using namespace std;

class VirtualMachine {
private:
    map<string, int> dict;
    DBMap *mp;

    void init();

    void getFunc(vector<string> tokens);

    void existFunc(vector<string> tokens);

    void setFunc(vector<string> tokens);

public:
    VirtualMachine();

    ~VirtualMachine();

    void run();

};


void VirtualMachine::run() {
    init();
    while (true) {
        // 读取输入命令
        vector<string> tokens = readCommand();
        if (tokens.empty()) {
            continue;
        }

        switch (dict[tokens[0]]) {
            case GET:
                getFunc(tokens);
                break;
            case SET:
                setFunc(tokens);
                break;
            case EXIST:
                existFunc(tokens);
                break;

            case EXIT:
                exit(1);

        }

    }
}

VirtualMachine::VirtualMachine() {
    //cmd 初始化
    init();
    //数据库底层 哈系表初始化
    mp = new DBMap(1000);
}

VirtualMachine::~VirtualMachine() {
    delete mp;
}

void VirtualMachine::init() {
    _init(dict);
}

void VirtualMachine::getFunc(vector<string> tokens) {
    cout << "get 操作\n";
    string value = mp->get(tokens[1]);
    cout << value;
}

void VirtualMachine::setFunc(vector<string> tokens) {
    cout << "set 操作\n";
    string key = tokens[1];
    DBString *value = new DBString(tokens[2]);
    mp->insert(key, value);

}

void VirtualMachine::existFunc(vector<string> tokens) {
    if (mp->has_key(tokens[1])) {
        cout << "有的有的\n";
    } else {
        cout << "没有\n";
    }
}

#endif //SQLDB_VM_H
